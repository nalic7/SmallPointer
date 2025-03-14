int main()
{
	int server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	char buffer[BUFFER_SIZE] = {0};

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		error("socket")
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
	{
		error("bind")
	}

	if (listen(server_fd, 3) < 0)
	{
		error("listen")
	}
	info("PORT %d", PORT)

	if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
	{
		error("accept")
	}

	int bytes_read = read(new_socket, buffer, BUFFER_SIZE);
	info("read %s", buffer);

	send(new_socket, buffer, bytes_read, 0);

	close(new_socket);
	close(server_fd);
	return 0;
}