uint8_t nls_state = 0;

static int init(void *arg)
{
	//s0-l
	int
		server_fd,
		epfd,

		l_r;

	struct epoll_event epoll_event_p[NALI_NLS_MAX_EPOLL_EVENT];

	uint8_t client_fd_select = 0;
	int *client_fd_p;
	//e0-l

	nls_state &= 0xFFu - NALI_NLS_FAIL;

	client_fd_p = malloc(sizeof(int) * NALI_NLS_MAX_CLIENT);
	memset(client_fd_p, -1, sizeof(int) * NALI_NLS_MAX_CLIENT);

	struct sockaddr_in server_sockaddr_in, client_sockaddr_in;
	socklen_t addrlen = sizeof(server_sockaddr_in);

	nali_info("socket %d", l_r = server_fd = socket(AF_INET, SOCK_STREAM, 0))
	nali_log("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NLS_FAIL;
	}

	//SO_RCVTIMEO
	nali_info("setsockopt %d", l_r = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, NALI_NLS_TIMEOUT, sizeof(struct timeval)))
	nali_log("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NLS_FAIL;
	}

	memset(&server_sockaddr_in, 0, sizeof(struct sockaddr_in));
	server_sockaddr_in.sin_family = AF_INET;
	server_sockaddr_in.sin_addr.s_addr = INADDR_ANY;
	server_sockaddr_in.sin_port = htons(NALI_SC_PORT);

	nali_info("bind %d", l_r = bind(server_fd, (struct sockaddr*)&server_sockaddr_in, sizeof(server_sockaddr_in)))
	nali_log("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NLS_FAIL;
	}

	nali_info("listen %d", l_r = listen(server_fd, 3))
	nali_log("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NLS_FAIL;
	}

	nali_info("epoll_create1 %d", l_r = epfd = epoll_create1(0))
	nali_log("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NLS_FAIL;
	}

	nali_info("epoll_ctl %d", l_r = epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &(struct epoll_event){.events = EPOLLIN, .data.fd = server_fd}))
	nali_log("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NLS_FAIL;
	}

	uint8_t size;
	uint8_t *uint8_t_p;
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
				nali_info("accept %d", new_fd = accept(server_fd, (struct sockaddr*)&client_sockaddr_in, &addrlen))
				nali_log("%s", strerror(errno))

				if (client_fd_select == NALI_NLS_MAX_CLIENT)
				{
					close(new_fd);
				}
				else
				{
					client_fd_p[client_fd_select] = new_fd;
					nali_info("epoll_ctl %d", epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd_p[client_fd_select], &(struct epoll_event){.events = EPOLLIN, .data.fd = client_fd_p[client_fd_select]}))

					++client_fd_select;
				}
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
					uint8_t_p = malloc(size + 1);
					r = recv(fd, &uint8_t_p, size, 0);

					if (r > 0)
					{
						uint8_t_p[size] = 0;
						nlcf_data_fp[*uint8_t_p](uint8_t_p);
					}

					free(uint8_t_p);
				}
			}
		}

		if (errno != errno_temp)
		{
			nali_info_t("s %d %s", errno, strerror(errno))
		}
		else
		{
			nls_state &= 0xFFu - NALI_NLS_INIT;
		}
		errno_temp = errno;
	}

	//s0-clean
	for (uint8_t u = 0; u < NALI_NLS_MAX_CLIENT; u++)
	{
		if (client_fd_p[u] != -1)
		{
			close(client_fd_p[u]);
			client_fd_p[u] = -1;
		}
	}

	close(epfd);
	close(server_fd);
	nali_log("clean_nw_server")
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
		nali_info("thrd_create %d", thrd_create(&(thrd_t){}, init, NULL))

		while (nls_state & NALI_NLS_INIT)
		{
			thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
		}
	}
}