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
	info("clean_nw_server")
}

static int errno_temp = 0;
static void out()
{
	if (errno != errno_temp)
	{
		info("s %d %s", errno, strerror(errno))
	}
	errno_temp = errno;
}

static int init(void *arg)
{
	epoll_event_p = malloc(sizeof(struct epoll_event) * NALI_MAX_EPOLL_EVENT);
	client_fd_p = malloc(sizeof(int) * NALI_MAX_CLIENT);
	memset(client_fd_p, -1, sizeof(int) * NALI_MAX_CLIENT);

	struct sockaddr_in server_sockaddr_in, client_sockaddr_in;
	socklen_t addrlen = sizeof(server_sockaddr_in);

	info("socket %d", server_fd = socket(AF_INET, SOCK_STREAM, 0))
	info("%s", strerror(errno))

	info("setsockopt %d", setsockopt(server_fd, SOL_SOCKET, SO_RCVTIMEO, &(struct timeval){.tv_sec = 5, .tv_usec = 0}, sizeof(struct timeval)))
	info("%s", strerror(errno))

	memset(&server_sockaddr_in, 0, sizeof(struct sockaddr_in));
	server_sockaddr_in.sin_family = AF_INET;
	server_sockaddr_in.sin_addr.s_addr = INADDR_ANY;
	server_sockaddr_in.sin_port = htons(NALI_SC_PORT);

	info("bind %d", bind(server_fd, (struct sockaddr*)&server_sockaddr_in, sizeof(server_sockaddr_in)))
	info("%s", strerror(errno))

	info("listen %d", listen(server_fd, 3))
	info("%s", strerror(errno))

	info("epoll_create1 %d", epfd = epoll_create1(0))
	info("%s", strerror(errno))

	info("epoll_ctl %d", epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &(struct epoll_event){.events = EPOLLIN, .data.fd = server_fd}))
	info("%s", strerror(errno))

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
				info("accept %d", client_fd_p[client_fd_select] = accept(server_fd, (struct sockaddr*)&client_sockaddr_in, &addrlen))
				info("%s", strerror(errno))

				epoll_ctl(epfd, EPOLL_CTL_ADD, client_fd_p[client_fd_select], &(struct epoll_event){.events = EPOLLIN, .data.fd = client_fd_p[client_fd_select]});

				++client_fd_select;
			}
			else
			{
				// ssize_t r = recv(fd, &size, sizeof(uint8_t), MSG_DONTWAIT);
				r = recv(fd, &size, sizeof(uint8_t), 0);
				info("recv %ld", r)
				if (r == 0)
				{
					epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
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

		out();
	}

	clean();
	return 0;
}
void nws_init()
{
	if (thrd_create(&(thrd_t){}, init, NULL) != thrd_success)
	{
		error("thrd_create")
	}
}