// static int
// 	client_socket,
// 	epoll;

// uint16_t m_max_epoll_event = 2;

// static struct epoll_event ev;
// static struct epoll_event* epoll_event_p;

// void nws_init()
// {
// 	struct sockaddr_in sockaddr_in;
// 	int addrlen = sizeof(sockaddr_in);

// 	if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
// 	{
// 		error("socket")
// 	}

// 	sockaddr_in.sin_family = AF_INET;
// 	sockaddr_in.sin_addr.s_addr = INADDR_ANY;
// 	sockaddr_in.sin_port = htons(NALI_SC_PORT);
// 	if (bind(m_socket, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)) < 0)
// 	{
// 		error("bind")
// 	}

// 	if (listen(m_socket, 3) < 0)
// 	{
// 		error("listen")
// 	}
// 	info("PORT %d", NALI_SC_PORT)

// 	epoll = epoll_create1(0);
// 	if (epoll == -1)
// 	{
// 		error("epoll_create1")
// 	}

// 	ev.events = EPOLLIN;
//     ev.data.fd = m_socket;
//     if (epoll_ctl(epoll, EPOLL_CTL_ADD, m_socket, &ev) == -1)
// 	{
// 		error("epoll_ctl")
//     }

// 	if ((client_socket = accept(m_socket, (struct sockaddr*)&sockaddr_in, (socklen_t*)&addrlen)) < 0)
// 	{
// 		error("accept")
// 	}

// 	nwb_init();
// }

// void nws_key(char* char_p)
// {
// 	if (strcmp(char_p, "s") == 0)
// 	{
// 		uint8_t size = sizeof(uint16_t) + 1;
// 		char* message = malloc(size);
// 		((uint16_t*)message)[0] = 1;
// 		message[sizeof(uint16_t)] = 'c';
// 		if (send(client_socket, message, size, 0) <= 0)
// 		{
// 			error("send")
// 		}
// 	}
// }

// void nws_clean()
// {
// 	close(m_socket);
// 	close(client_socket);
// }

// int main() {
// 	while (1) {
// 		FD_ZERO(&read_fds);
// 		FD_SET(server_socket, &read_fds);
// 		max_sd = server_socket;

// 		// Add client sockets to set
// 		for (i = 0; i < MAX_CLIENTS; i++) {
// 			if (client_sockets[i] > 0)
// 				FD_SET(client_sockets[i], &read_fds);
// 			if (client_sockets[i] > max_sd)
// 				max_sd = client_sockets[i];
// 		}

// 		// Wait for activity
// 		activity = select(0, &read_fds, NULL, NULL, NULL);

// 		// New connection
// 		if (FD_ISSET(server_socket, &read_fds)) {
// 			client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
// 			printf("New client connected\n");

// 			// Store client socket
// 			for (i = 0; i < MAX_CLIENTS; i++) {
// 				if (client_sockets[i] == 0) {
// 					client_sockets[i] = client_socket;
// 					break;
// 				}
// 			}
// 		}

// 		// Check each client for incoming messages
// 		for (i = 0; i < MAX_CLIENTS; i++) {
// 			if (client_sockets[i] > 0 && FD_ISSET(client_sockets[i], &read_fds)) {
// 				char buffer[1024];
// 				int bytes_read = read(client_sockets[i], buffer, sizeof(buffer));
// 				if (bytes_read <= 0) {
// 					// Client disconnected
// 					close(client_sockets[i]);
// 					client_sockets[i] = 0;
// 					printf("Client disconnected\n");
// 				} else {
// 					buffer[bytes_read] = '\0';
// 					printf("Received: %s\n", buffer);
// 				}
// 			}
// 		}
// 	}

// 	return 0;
// }