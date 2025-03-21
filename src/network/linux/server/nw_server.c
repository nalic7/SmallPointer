static int
	server_socket,
	client_socket,
	epoll;

static uint16_t m_max_epoll_event = 2;

static struct epoll_event stack_epoll_event;
static struct epoll_event *epoll_event_p;

void nws_init()
{
	epoll_event_p = malloc(sizeof(struct epoll_event) * m_max_epoll_event);

	struct sockaddr_in server_sockaddr_in, client_sockaddr_in;
	socklen_t addrlen = sizeof(server_sockaddr_in);

	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		error("socket")
	}

	// bzero((char *)sockaddr_in_p, sizeof(struct sockaddr_in));
	server_sockaddr_in.sin_family = AF_INET;
	server_sockaddr_in.sin_addr.s_addr = INADDR_ANY;
	server_sockaddr_in.sin_port = htons(NALI_SC_PORT);
	if (bind(server_socket, (struct sockaddr*)&server_sockaddr_in, sizeof(server_sockaddr_in)) < 0)
	{
		error("bind")
	}

	if (listen(server_socket, 3) < 0)
	{
		error("listen")
	}
	info("PORT %d", NALI_SC_PORT)

	epoll = epoll_create1(0);
	if (epoll == -1)
	{
		error("epoll_create1")
	}

	stack_epoll_event.events = EPOLLIN;
	stack_epoll_event.data.fd = server_socket;
	if (epoll_ctl(epoll, EPOLL_CTL_ADD, server_socket, &stack_epoll_event) == -1)
	{
		error("epoll_ctl")
	}

	while (1)
	{
		int event_count = epoll_wait(epoll, epoll_event_p, m_max_epoll_event, -1);

		for (int i = 0; i < event_count; i++)
		{
			int fd = epoll_event_p[i].data.fd;

			if (fd == server_socket)
			{
				if ((client_socket = accept(server_socket, (struct sockaddr*)&client_sockaddr_in, &addrlen)) < 0)
				{
					error("accept")
				}

				stack_epoll_event.events = EPOLLIN;
				stack_epoll_event.data.fd = client_socket;
				epoll_ctl(epoll, EPOLL_CTL_ADD, client_socket, &stack_epoll_event);
			}
			else
			{
				char buffer[1024];
				int bytes_read = recv(fd, buffer, sizeof(buffer), 0);
				if (bytes_read <= 0)
				{
					close(fd);
				}
				else
				{
					send(fd, buffer, bytes_read, 0);
				}
			}
		}
	}
}

void nws_key(char *char_p)
{
	if (strcmp(char_p, "s") == 0)
	{
		uint8_t size = sizeof(uint16_t) + 1;
		char *message = malloc(size);
		((uint16_t*)message)[0] = 1;
		message[sizeof(uint16_t)] = 'c';
		if (send(client_socket, message, size, 0) <= 0)
		{
			error("send")
		}
	}
}

void nws_clean()
{
	close(server_socket);
	close(client_socket);
}