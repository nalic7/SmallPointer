static int client_socket;

static int loopKey(void *arg)
{
	char *char_p;
	size_t size;
	while ((m_surface_state & NALI_SURFACE_C_S_CLEAN) == 0)
	{
		getline(&char_p, &size, stdin);



		free(char_p);
	}

	return 0;
}

static int loopRecv(void *arg)
{
	while ((m_surface_state & NALI_SURFACE_C_S_CLEAN) == 0)
	{
		uint16_t length;
		if (recv(client_socket, &length, sizeof(uint16_t), 0) <= 0)
		{
			error("recv")
		}
	
		char *char_p = (char*)malloc(length);
		if (!char_p)
		{
			error("malloc")
		}
	
		if (recv(client_socket, char_p, length, 0) <= 0)
		{
			error("recv")
		}
	
		if (1)
		{
			char_p = (char*)realloc(char_p, length + 1);
			info("char_p %s", char_p)
		}
		free(char_p);
	}

	nwc_clean();
	return 0;
}

void nwb_init()
{
	thrd_t
	key_thrd_t,
	recv_thrd_t;
	if (thrd_create(&key_thrd_t, loopKey, NULL) != thrd_success)
	{
		error("thrd_create")
	}
	if (thrd_create(&recv_thrd_t, loopRecv, NULL) != thrd_success)
	{
		error("thrd_create")
	}
}

void nwc_init(const char* ip)
{
	struct sockaddr_in sockaddr_in;

	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		error("socket")
	}

	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(NALI_SC_PORT);
	if (inet_pton(AF_INET, ip, &sockaddr_in.sin_addr) <= 0)
	{
		error("inet_pton")
	}

	if (connect(client_socket, (struct sockaddr*)&sockaddr_in, sizeof(sockaddr_in)) < 0)
	{
		error("connect")
	}

	nwb_init();
}

void nwc_key(char *char_p)
{
	if (strcmp(char_p, "c") == 0)
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

void nwc_clean()
{
	close(client_socket);
	client_socket = -1;
}