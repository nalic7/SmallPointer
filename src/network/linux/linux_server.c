uint8_t nls_state = 0;

static int client_fd_p[sizeof(int) * NALI_LB_MAX_CLIENT] = {-1};
static int init(void *p)
{
	//s0-l
	int
		server_fd,
		epfd,

		l_r;

	struct epoll_event epoll_event_p[NALI_NLS_MAX_EPOLL_EVENT];

	uint8_t client_fd_select = 0;
	//e0-l

	nls_state &= 0xFFu - NALI_NLS_FAIL;

	struct sockaddr_in server_sockaddr_in, client_sockaddr_in;
	socklen_t addrlen = sizeof(server_sockaddr_in);

	NALI_D_INFO("socket %d", l_r = server_fd = socket(AF_INET, SOCK_STREAM, 0))
	NALI_D_LOG("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NLS_FAIL;
	}

	//SO_RCVTIMEO
	NALI_D_INFO("setsockopt %d", l_r = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, NALI_NLS_TIMEOUT, sizeof(struct timeval)))
	NALI_D_LOG("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NLS_FAIL;
	}

	memset(&server_sockaddr_in, 0, sizeof(struct sockaddr_in));
	server_sockaddr_in.sin_family = AF_INET;
	server_sockaddr_in.sin_addr.s_addr = INADDR_ANY;
	server_sockaddr_in.sin_port = htons(NALI_SC_PORT);

	NALI_D_INFO("bind %d", l_r = bind(server_fd, (struct sockaddr*)&server_sockaddr_in, sizeof(server_sockaddr_in)))
	NALI_D_LOG("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NLS_FAIL;
	}

	NALI_D_INFO("listen %d", l_r = listen(server_fd, 3))
	NALI_D_LOG("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NLS_FAIL;
	}

	NALI_D_INFO("epoll_create1 %d", l_r = epfd = epoll_create1(0))
	NALI_D_LOG("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NLS_FAIL;
	}

	NALI_D_INFO("epoll_ctl %d", l_r = epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &(struct epoll_event){.events = EPOLLIN, .data.fd = server_fd}))
	NALI_D_LOG("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NLS_FAIL;
	}

	uint16_t data_bl;
	uint8_t *data_p;
	ssize_t r;

	int errno_temp = 0;
	while (!(nls_state & NALI_NLS_FAIL))
	{
		int event_count = epoll_wait(epfd, epoll_event_p, NALI_NLS_MAX_EPOLL_EVENT, 1000);

		for (int i = 0; i < event_count; i++)
		{
			int fd = epoll_event_p[i].data.fd;

			if (fd == server_fd)
			{
				int new_fd;
				NALI_D_INFO("accept %d", new_fd = accept(server_fd, (struct sockaddr*)&client_sockaddr_in, &addrlen))
				NALI_D_LOG("%s", strerror(errno))

				if (client_fd_select == NALI_LB_MAX_CLIENT)
				{
					close(new_fd);
				}
				else
				{
					client_fd_p[client_fd_select] = new_fd;
					NALI_D_INFO("epoll_ctl %d", epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd_p[client_fd_select], &(struct epoll_event){.events = EPOLLIN, .data.fd = client_fd_p[client_fd_select]}))

					++client_fd_select;
				}
			}
			else
			{
				// ssize_t r = recv(fd, &size, sizeof(uint8_t), MSG_DONTWAIT);
				r = recv(fd, &data_bl, sizeof(uint16_t), 0);
				NALI_D_LOG("recv %ld", r)
				if (r == 0)
				{
					NALI_D_INFO("epoll_ctl %d", epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL))
					close(fd);

					client_fd_p[--client_fd_select] = -1;
				}
				else
				{
					data_p = malloc(data_bl + 1);
					r = recv(fd, &data_p, data_bl, 0);

					if (r > 0)
					{
						data_p[data_bl] = 255;
						nlsf_data_fp[*data_p](data_p);
					}

					free(data_p);
				}
			}
		}

		if (errno != errno_temp)
		{
			NALI_D_INFO_A("s %d %s", errno, strerror(errno))
		}
		else
		{
			nls_state &= 0xFFu - NALI_NLS_INIT;
		}
		errno_temp = errno;
	}

	//s0-clean
	for (uint8_t u = 0; u < NALI_LB_MAX_CLIENT; u++)
	{
		if (client_fd_p[u] != -1)
		{
			close(client_fd_p[u]);
			client_fd_p[u] = -1;
		}
	}

	close(epfd);
	close(server_fd);
	NALI_D_LOG("clean_nw_server")
	//e0-clean

	nls_state &= 0xFFu - NALI_NLS_INIT;
	return 0;
}

void nls_set()
{
	nls_state |= NALI_NLS_FAIL;
	while (nls_state & NALI_NLS_FAIL)
	{
		nls_state |= NALI_NLS_INIT;
		NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, init, NULL))

		while (nls_state & NALI_NLS_INIT)
		{
			thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
		}
	}
}

void nls_send(NALI_LB_UT u, uint8_t *data_p, uint16_t data_bl)
{
	send(client_fd_p[u], data_p, data_bl, 0);
}