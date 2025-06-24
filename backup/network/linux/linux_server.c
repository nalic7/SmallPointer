uint8_t nls_state = 0;

typedef struct
{
	int fd;
	NALI_LB_UT ui;
} c_fd;
static c_fd *c_fd_p;

static void close_i(int epfd, int fd)
{
	NALI_D_INFO("epoll_ctl %d", epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL))
	close(fd);

	c_fd_p = realloc(c_fd_p, sizeof(c_fd) * --lsu_h1_bl);
}

static int init(void *p)
{
	c_fd_p = malloc(0);

	//s0-l
	int
		server_fd,
		epfd,

		l_r;

	struct epoll_event epoll_event_p[NALI_NLS_MAX_EPOLL_EVENT];
	//e0-l

	nls_state &= 0xFFu - NALI_NS_FAIL;

	struct sockaddr_in server_sockaddr_in, client_sockaddr_in;
	socklen_t addrlen = sizeof(server_sockaddr_in);

	NALI_D_INFO("socket %d", l_r = server_fd = socket(AF_INET, SOCK_STREAM, 0))
	NALI_D_LOG("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NS_FAIL;
	}

	//SO_RCVTIMEO
	NALI_D_INFO("setsockopt %d", l_r = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, NALI_NLS_TIMEOUT, sizeof(struct timeval)))
	NALI_D_LOG("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NS_FAIL;
	}

	memset(&server_sockaddr_in, 0, sizeof(struct sockaddr_in));
	server_sockaddr_in.sin_family = AF_INET;
	server_sockaddr_in.sin_addr.s_addr = INADDR_ANY;
	server_sockaddr_in.sin_port = htons(NALI_SC_PORT);

	NALI_D_INFO("bind %d", l_r = bind(server_fd, (struct sockaddr*)&server_sockaddr_in, sizeof(server_sockaddr_in)))
	NALI_D_LOG("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NS_FAIL;
	}

	NALI_D_INFO("listen %d", l_r = listen(server_fd, 3))
	NALI_D_LOG("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NS_FAIL;
	}

	NALI_D_INFO("epoll_create1 %d", l_r = epfd = epoll_create1(0))
	NALI_D_LOG("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NS_FAIL;
	}

	NALI_D_INFO("epoll_ctl %d", l_r = epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &(struct epoll_event){.events = EPOLLIN, .data.ptr = &server_fd}))
	NALI_D_LOG("%s", strerror(errno))
	if (l_r < 0)
	{
		nls_state |= NALI_NS_FAIL;
	}

	NALI_LB_PT data_bl;
	uint8_t *data_p;
	ssize_t r;

	int errno_temp = 0;
	while (!(nls_state & NALI_NS_FAIL))
	{
		int event_count = epoll_wait(epfd, epoll_event_p, NALI_NLS_MAX_EPOLL_EVENT, 1000);

		for (int i = 0; i < event_count; i++)
		{
			if (epoll_event_p[i].data.ptr == &server_fd)
			{
				int new_fd;
				NALI_D_INFO("accept %d", new_fd = accept(server_fd, (struct sockaddr*)&client_sockaddr_in, &addrlen))
				NALI_D_LOG("%s", strerror(errno))

				if (lsu_h1_bl == NALI_LB_UM)
				{
					close(new_fd);
				}
				else
				{
					c_fd_p = realloc(c_fd_p, sizeof(c_fd) * (lsu_h1_bl + 1));
					c_fd_p[lsu_h1_bl].fd = new_fd;
					c_fd_p[lsu_h1_bl].ui = NALI_LB_UN;
					NALI_D_INFO("epoll_ctl %d", epoll_ctl(epfd, EPOLL_CTL_ADD, new_fd, &(struct epoll_event){.events = EPOLLIN, .data.ptr = c_fd_p}))
				}
			}
			else
			{
				c_fd l_c_fd_p = *(c_fd *)epoll_event_p[i].data.ptr;
				int fd = l_c_fd_p.fd;
				NALI_LB_UT ui = l_c_fd_p.ui;

				r = recv(fd, &data_bl, sizeof(NALI_LB_PT), MSG_DONTWAIT);

				if (r == 0)
				{
					close_i(epfd, fd);

					if (ui != NALI_LB_UN)
					{
						lsf_rm_u(ui);
					}
				}
				else
				{
					if (lsu_h1_p[ui] == NALI_LB_UN)
					{
						if (r == sizeof(NALI_LB_UT))
						{
							data_p = malloc(data_bl);
							r = recv(fd, &data_p, data_bl, MSG_DONTWAIT);

							if (r > 0 && *data_p < NALI_LB_UM)
							{
								uint8_t l0 = 0;
								for (NALI_LB_UT l_0 = 0; l_0 < lsu_h1_bl; ++l_0)
								{
									// fseek(ls_file_p, lsu_h1_p[lsu_h_ul] * (sizeof(uint8_t) + sizeof(NALI_LB_CT) * 3 + sizeof(float) * (3 + 3)), SEEK_SET);

									if (lsu_h1_p[ui] == *data_p)
									{
										l0 |= 1;
										break;
									}
								}

								if (l0)
								{
									close_i(epfd, fd);
								}
								else
								{
									lsu_h1_p[ui] = *data_p;
									lsf_add_u(ui);
								}
							}
							else
							{
								close_i(epfd, fd);
							}

							free(data_p);
						}
						else
						{
							close_i(epfd, fd);
						}
					}
					else
					{
						data_p = malloc(data_bl);
						r = recv(fd, &data_p, data_bl, MSG_DONTWAIT);

						if (r > 0)
						{
							nlsf_data_fp[*data_p](ui, data_p);
						}

						free(data_p);
					}
				}
			}
		}

		if (errno != errno_temp)
		{
			NALI_D_INFO_A("s %d %s", errno, strerror(errno))
		}
		else
		{
			nls_state &= 0xFFu - NALI_NS_INIT;
		}
		errno_temp = errno;
	}

	//s0-clean
	for (uint8_t u = 0; u < lsu_h1_bl; u++)
	{
		close_i(epfd, c_fd_p[u].fd);
	}

	close(epfd);
	close(server_fd);
	NALI_D_LOG("clean_nw_server")
	//e0-clean

	free(c_fd_p);

	nls_state &= 0xFFu - NALI_NS_INIT;

	if (s_surface_state & NALI_S_S_EXIT_S)
	{
		mtx_unlock(ls_mtx_t_p);
	}
	else
	{
		ls_re();
		nls_set();
	}

	return 0;
}

void nls_set()
{
	nls_state |= NALI_NS_FAIL;
	while (nls_state & NALI_NS_FAIL)
	{
		nls_state |= NALI_NS_INIT;
		NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, init, NULL))

		while (nls_state & NALI_NS_INIT)
		{
			thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
		}
	}
}

void nls_send(NALI_LB_UT ui)
{
	send(c_fd_p[ui].fd, ls_net_p, ls_net_bl, MSG_DONTWAIT);
}