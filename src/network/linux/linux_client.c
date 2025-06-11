uint8_t nlc_state = 0;

static int server_socket;
static int init(void *p)
{
	int l_r;
	struct sockaddr_in sockaddr_in;

	NALI_D_LOG("sinit")
	nlc_state &= 0xFFu - NALI_NLC_FAIL;

	NALI_D_INFO("socket %d", l_r = server_socket = socket(AF_INET, SOCK_STREAM, 0))
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

	NALI_D_INFO("connect %d", l_r = connect(server_socket, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)))
	NALI_D_LOG("%s", strerror(errno))

	if (l_r < 0)
	{
		nlc_state |= NALI_NLC_FAIL;
	}

	NALI_D_INFO("setsockopt %d", l_r = setsockopt(server_socket, SOL_SOCKET, SO_RCVTIMEO, NALI_NLC_TIMEOUT, sizeof(struct timeval)))
	NALI_D_LOG("%s", strerror(errno))

	if (l_r < 0)
	{
		nlc_state |= NALI_NLC_FAIL;
	}

	//send new user
	nlc_send((NALI_LB_UT *){NALI_NLC_ID}, sizeof(NALI_LB_UT));

	int errno_temp = 0;
	NALI_LB_PT data_bl;
	uint8_t *data_p;
	ssize_t r;
	while (!(nlc_state & NALI_NLC_FAIL))
	{
		//s0-get
		r = recv(server_socket, &data_bl, sizeof(NALI_LB_PT), MSG_DONTWAIT);

		if (r > 0)
		{
			data_p = malloc(data_bl);
			r = recv(server_socket, data_p, data_bl, MSG_DONTWAIT);

			if (r > 0)
			{
				nlcf_data_fp[*data_p](data_p);
			}

			free(data_p);
		}
		//e0-get

		//s0-out
		if (errno != errno_temp)
		{
			NALI_D_INFO_A("c %d %s", errno, strerror(errno))
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

	close(server_socket);
	NALI_D_LOG("einit")
	nlc_state &= 0xFFu - NALI_NLC_INIT;

	if (s_surface_state & NALI_S_S_EXIT_C)
	{
		mtx_unlock(lc_mtx_t_p);
	}
	else
	{
		lc_re();
		nlc_set();
	}

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

void nlc_send()
{
	send(server_socket, lc_net_p, lc_net_bl, MSG_DONTWAIT);
}