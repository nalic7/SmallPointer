uint8_t m_net_server_state = 0;

static int
	server_fd,
	epfd;

static struct epoll_event *epoll_event_p;

// static void key(char *char_p)
// {
// 	if (!strcmp(char_p, "s"))
// 	{
// 		uint8_t size = sizeof(uint16_t) + 1;
// 		char *message = malloc(size);
// 		((uint16_t*)message)[0] = 1;
// 		message[sizeof(uint16_t)] = 'c';
// 		info("send %ld", send(client_socket, message, size, 0))
// 		info("%s", strerror(errno))
// 	}
// }

static uint8_t client_fd_select = 0;
static int *client_fd_p;

static void clean()
{
	for (uint8_t u = 0; u < NALI_MAX_CLIENT; u++)
	{
		if (client_fd_p[u] != -1)
		{
			close(client_fd_p[u]);
			client_fd_p[u] = -1;
		}
	}

	close(epfd);
	close(server_fd);
	free(epoll_event_p);
	nali_log("clean_nw_server")
}

#ifdef NALI_DEBUG
static int errno_temp = 0;
static void out()
{
	if (errno != errno_temp)
	{
		nali_log("s %d %s", errno, strerror(errno))
	}
	else
	{
		m_net_server_state &= 0xFFu - NALI_NET_SERVER_INIT;
	}
	errno_temp = errno;
}
#endif

static int r;
static int init(void *arg)
{
	m_net_server_state &= 0xFFu - NALI_NET_SERVER_FAIL;

	epoll_event_p = malloc(sizeof(struct epoll_event) * NALI_MAX_EPOLL_EVENT);
	client_fd_p = malloc(sizeof(int) * NALI_MAX_CLIENT);
	memset(client_fd_p, -1, sizeof(int) * NALI_MAX_CLIENT);

	struct sockaddr_in server_sockaddr_in, client_sockaddr_in;
	socklen_t addrlen = sizeof(server_sockaddr_in);

	nali_info("socket %d", r = server_fd = socket(AF_INET, SOCK_STREAM, 0))
	nali_log("%s", strerror(errno))
	if (r < 0)
	{
		m_net_server_state |= NALI_NET_SERVER_FAIL;
	}

	nali_info("setsockopt %d", r = setsockopt(server_fd, SOL_SOCKET, SO_RCVTIMEO, &(struct timeval){.tv_sec = 5, .tv_usec = 0}, sizeof(struct timeval)))
	nali_log("%s", strerror(errno))
	if (r < 0)
	{
		m_net_server_state |= NALI_NET_SERVER_FAIL;
	}

	memset(&server_sockaddr_in, 0, sizeof(struct sockaddr_in));
	server_sockaddr_in.sin_family = AF_INET;
	server_sockaddr_in.sin_addr.s_addr = INADDR_ANY;
	server_sockaddr_in.sin_port = htons(NALI_SC_PORT);

	nali_info("bind %d", r = bind(server_fd, (struct sockaddr*)&server_sockaddr_in, sizeof(server_sockaddr_in)))
	nali_log("%s", strerror(errno))
	if (r < 0)
	{
		m_net_server_state |= NALI_NET_SERVER_FAIL;
	}

	nali_info("listen %d", r = listen(server_fd, 3))
	nali_log("%s", strerror(errno))
	if (r < 0)
	{
		m_net_server_state |= NALI_NET_SERVER_FAIL;
	}

	nali_info("epoll_create1 %d", r = epfd = epoll_create1(0))
	nali_log("%s", strerror(errno))
	if (r < 0)
	{
		m_net_server_state |= NALI_NET_SERVER_FAIL;
	}

	nali_info("epoll_ctl %d", r = epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &(struct epoll_event){.events = EPOLLIN, .data.fd = server_fd}))
	nali_log("%s", strerror(errno))
	if (r < 0)
	{
		m_net_server_state |= NALI_NET_SERVER_FAIL;
	}

	uint8_t size;
	uint8_t *uint8_t_p;
	ssize_t r;
	while (!(m_net_server_state & NALI_NET_SERVER_FAIL))
	{
		int event_count = epoll_wait(epfd, epoll_event_p, NALI_MAX_EPOLL_EVENT, 1000);

		for (int i = 0; i < event_count; i++)
		{
			int fd = epoll_event_p[i].data.fd;

			if (fd == server_fd)
			{
				nali_info("accept %d", client_fd_p[client_fd_select] = accept(server_fd, (struct sockaddr*)&client_sockaddr_in, &addrlen))
				nali_log("%s", strerror(errno))

				nali_info("epoll_ctl %d", epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd_p[client_fd_select], &(struct epoll_event){.events = EPOLLIN, .data.fd = client_fd_p[client_fd_select]}))

				++client_fd_select;
			}
			else
			{
				// ssize_t r = recv(fd, &size, sizeof(uint8_t), MSG_DONTWAIT);
				r = recv(fd, &size, sizeof(uint8_t), 0);
				nali_log("recv %ld", r)
				if (r == 0)
				{
					nali_info("epoll_ctl %d", epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL))
					close(fd);

					client_fd_p[--client_fd_select] = -1;
				}
				else
				{
					uint8_t_p = malloc(size);
					r = recv(fd, &uint8_t_p, size, 0);

					free(uint8_t_p);
				}
			}
		}

		#ifdef NALI_DEBUG
			out();
		#else
			m_net_server_state &= 0xFFu - NALI_NET_SERVER_INIT;
		#endif
	}

	clean();
	m_net_server_state &= 0xFFu - NALI_NET_SERVER_INIT;
	return 0;
}
void nws_init()
{
	m_net_server_state |= NALI_NET_SERVER_FAIL;
	while (m_net_server_state & NALI_NET_SERVER_FAIL)
	{
		m_net_server_state |= NALI_NET_SERVER_INIT;
		nali_info("thrd_create %d", thrd_create(&(thrd_t){}, init, NULL))

		while (m_net_server_state & NALI_NET_SERVER_INIT)
		{
			thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
		}
	}
}