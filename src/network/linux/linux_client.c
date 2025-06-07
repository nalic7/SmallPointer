uint8_t nlc_state = 0;

static int init(void *p)
{
	int l_r;
	int m_client_socket;
	struct sockaddr_in sockaddr_in;

	NALI_D_LOG("sinit")
	nlc_state &= 0xFFu - NALI_NLC_FAIL;

	NALI_D_INFO("socket %d", l_r = m_client_socket = socket(AF_INET, SOCK_STREAM, 0))
	//errno.h ECONNREFUSED ETIMEDOUT
	NALI_D_LOG("%s", strerror(errno))

	if (l_r < 0)
	{
		nlc_state |= NALI_NLC_FAIL;
	}

	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(NALI_SC_PORT);

	NALI_D_INFO("inet_pton %d", l_r = inet_pton(AF_INET, NALI_NLC_IP, &sockaddr_in.sin_addr))
	NALI_D_LOG("%s", strerror(errno))

	if (l_r < 0)
	{
		nlc_state |= NALI_NLC_FAIL;
	}

	NALI_D_INFO("connect %d", l_r = connect(m_client_socket, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)))
	NALI_D_LOG("%s", strerror(errno))

	if (l_r < 0)
	{
		nlc_state |= NALI_NLC_FAIL;
	}

	NALI_D_INFO("setsockopt %d", l_r = setsockopt(m_client_socket, SOL_SOCKET, SO_RCVTIMEO, NALI_NLC_TIMEOUT, sizeof(struct timeval)))
	NALI_D_LOG("%s", strerror(errno))

	if (l_r < 0)
	{
		nlc_state |= NALI_NLC_FAIL;
	}

	int errno_temp = 0;
	uint16_t data_bl;
	uint8_t *data_p;
	ssize_t r;
	while (!(nlc_state & NALI_NLC_FAIL))
	{
		//s0-get
		// info("recv %ld", recv(m_client_socket, &length, sizeof(uint8_t), MSG_DONTWAIT))
		// info("%s", strerror(errno))
		// info("length %d", length)

		//p[length data...]
		r = recv(m_client_socket, &data_bl, sizeof(uint16_t), MSG_DONTWAIT);

		if (r > 0)
		{
			data_p = malloc(data_bl + 1);
			r = recv(m_client_socket, data_p, data_bl, 0);

			if (r > 0)
			{
				data_p[data_bl] = 255;
				nlcf_data_fp[*data_p](data_p);
			}

			free(data_p);
		}
		//e0-get

		//s0-out
		if (errno != errno_temp)
		{
			NALI_D_LOG("c %d %s", errno, strerror(errno))
			if (errno == ETIMEDOUT || errno == ECONNRESET || errno == ENETRESET || errno == ECONNABORTED)
			{
				nlc_state |= NALI_NLC_FAIL;
			}
		}
		else
		{
			nlc_state &= 0xFFu - NALI_NLC_INIT;
		}
		errno_temp = errno;
		//e0-out
	}

	close(m_client_socket);
	nlc_state &= 0xFFu - NALI_NLC_INIT;
	NALI_D_LOG("einit")
	return 0;
}

void nlc_set()
{
	nlc_state |= NALI_NLC_FAIL;
	while (nlc_state & NALI_NLC_FAIL)
	{
		nlc_state |= NALI_NLC_INIT;
		NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, init, NULL))

		while (nlc_state & NALI_NLC_INIT)
		{
			thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
		}
	}
}