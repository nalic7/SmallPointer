int main()
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	char buffer[BUFFER_SIZE] = {0};

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		error("socket")
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
	{
		error("inet_pton")
	}

	if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
	{
		error("connect")
	}

	char *message = "Client";
	send(sock, message, strlen(message), 0);

	int bytes_read = read(sock, buffer, BUFFER_SIZE);
	info("read %s", buffer)

	close(sock);
	return 0;
}