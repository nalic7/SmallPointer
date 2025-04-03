uint8_t m_net_client_state = 0;

int m_client_socket;
static struct sockaddr_in sockaddr_in;

static void clean()
{
	close(m_client_socket);
}

static uint8_t length;
static void get()
{
	// info("recv %ld", recv(m_client_socket, &length, sizeof(uint8_t), MSG_DONTWAIT))
	// info("%s", strerror(errno))
	// info("length %d", length)
	recv(m_client_socket, &length, sizeof(uint8_t), MSG_DONTWAIT);

	if (length > 0)
	{
		char *char_p = (char*)malloc(length);

		info("recv %ld", recv(m_client_socket, char_p, length, 0))
		info("%s", strerror(errno))

		char_p = (char*)realloc(char_p, length + 1);
		info("char_p %s", char_p)

		free(char_p);
	}
}

static int errno_temp = 0;
static void out()
{
	if (errno != errno_temp)
	{
		info("c %d %s", errno, strerror(errno))
		// m_net_client_state |= NALI_NET_CLIENT_FAIL;
	}
	else
	{
		// m_net_client_state &= 255 - NALI_NET_CLIENT_INIT;
	}
	m_net_client_state &= 255 - NALI_NET_CLIENT_INIT;
	errno_temp = errno;
}

static int r;
static int init(void *arg)
{
	info("sinit")
	m_net_client_state &= 255 - NALI_NET_CLIENT_FAIL;

	info("socket %d", r = m_client_socket = socket(AF_INET, SOCK_STREAM, 0))
	//errno.h ECONNREFUSED ETIMEDOUT
	info("%s", strerror(errno))

	if (r < 0)
	{
		m_net_client_state |= NALI_NET_CLIENT_FAIL;
	}

	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(NALI_SC_PORT);

	info("inet_pton %d", r = inet_pton(AF_INET, NALI_IP, &sockaddr_in.sin_addr))
	info("%s", strerror(errno))

	if (r < 0)
	{
		m_net_client_state |= NALI_NET_CLIENT_FAIL;
	}

	info("connect %d", r = connect(m_client_socket, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)))
	info("%s", strerror(errno))

	if (r < 0)
	{
		m_net_client_state |= NALI_NET_CLIENT_FAIL;
	}

	info("setsockopt %d", r = setsockopt(m_client_socket, SOL_SOCKET, SO_RCVTIMEO, &(struct timeval){.tv_sec = 5, .tv_usec = 0}, sizeof(struct timeval)))
	info("%s", strerror(errno))

	if (r < 0)
	{
		m_net_client_state |= NALI_NET_CLIENT_FAIL;
	}

	while (!(m_net_client_state & NALI_NET_CLIENT_FAIL))
	{
		get();
		out();
	}

	clean();
	m_net_client_state &= 255 - NALI_NET_CLIENT_INIT;
	info("einit")
	return 0;
}

void nwc_init()
{
	m_net_client_state |= NALI_NET_CLIENT_FAIL;
	while (m_net_client_state & NALI_NET_CLIENT_FAIL)
	{
		m_net_client_state |= NALI_NET_CLIENT_INIT;
		if (thrd_create(&(thrd_t){}, init, NULL) != thrd_success)
		{
			error("thrd_create")
		}

		while (m_net_client_state & NALI_NET_CLIENT_INIT)
		{
			thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
		}
	}
}