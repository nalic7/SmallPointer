uint8_t nlc_state = 0;

static void get()
{
	uint8_t length;
	// info("recv %ld", recv(m_client_socket, &length, sizeof(uint8_t), MSG_DONTWAIT))
	// info("%s", strerror(errno))
	// info("length %d", length)

	//p[length data...]
	recv(m_client_socket, &length, sizeof(uint8_t), MSG_DONTWAIT);

	if (length > 0)
	{
		char *char_p = (char*)malloc(length);

		nali_info("recv %ld", recv(m_client_socket, char_p, length, 0))

		char_p = (char*)realloc(char_p, length + 1);
		nali_log("char_p %s", char_p)

		free(char_p);
	}
}

#ifdef NALI_DEBUG
static int errno_temp = 0;
static void out()
{
	if (errno != errno_temp)
	{
		nali_log("c %d %s", errno, strerror(errno))
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
}
#endif

static int r;
static int init(void *arg)
{
	int m_client_socket;
	struct sockaddr_in sockaddr_in;

	nali_log("sinit")
	nlc_state &= 0xFFu - NALI_NLC_FAIL;

	nali_info("socket %d", r = m_client_socket = socket(AF_INET, SOCK_STREAM, 0))
	//errno.h ECONNREFUSED ETIMEDOUT
	nali_log("%s", strerror(errno))

	if (r < 0)
	{
		nlc_state |= NALI_NLC_FAIL;
	}

	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(NALI_SC_PORT);

	nali_info("inet_pton %d", r = inet_pton(AF_INET, NALI_NLC_IP, &sockaddr_in.sin_addr))
	nali_log("%s", strerror(errno))

	if (r < 0)
	{
		nlc_state |= NALI_NLC_FAIL;
	}

	nali_info("connect %d", r = connect(m_client_socket, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)))
	nali_log("%s", strerror(errno))

	if (r < 0)
	{
		nlc_state |= NALI_NLC_FAIL;
	}

	nali_info("setsockopt %d", r = setsockopt(m_client_socket, SOL_SOCKET, SO_RCVTIMEO, NALI_NLC_TIMEOUT, sizeof(struct timeval)))
	nali_log("%s", strerror(errno))

	if (r < 0)
	{
		nlc_state |= NALI_NLC_FAIL;
	}

	while (!(nlc_state & NALI_NLC_FAIL))
	{
		get();
		#ifdef NALI_DEBUG
			out();
		#else
			m_net_client_state &= 0xFFu - NALI_NLC_INIT;
		#endif
	}

	close(m_client_socket);
	nlc_state &= 0xFFu - NALI_NLC_INIT;
	nali_log("einit")
	return 0;
}

void nlc_set()
{
	nlc_state |= NALI_NLC_FAIL;
	while (nlc_state & NALI_NLC_FAIL)
	{
		nlc_state |= NALI_NLC_INIT;
		nali_info("thrd_create %d", thrd_create(&(thrd_t){}, init, NULL))

		while (nlc_state & NALI_NLC_INIT)
		{
			thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
		}
	}
}