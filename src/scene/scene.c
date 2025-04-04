int main()
{
	// #ifdef NALI_DEBUG
	// 	debug_init();
	// #endif

	#if NALI_SERVER
		nws_init();
	#endif
	#ifdef NALI_CLIENT
		lc_init();
		wlc_init();
		vk_init();
		al_init();
		lc_initVK();
		nwc_init();
		m_pointer_id = 0;
	#endif

	char *char_p = NULL;
	size_t size = 0;
	while (1)
	{
		getline(&char_p, &size, stdin);
		nali_info_t("getline %ld", getline(&char_p, &size, stdin))

		#ifdef NALI_CLIENT
		if (!strcmp(char_p, "c\n"))
		{
			uint8_t size = sizeof(uint16_t) + 1;
			char *message = malloc(size);
			((uint16_t*)message)[0] = 1;
			message[sizeof(uint16_t)] = 'c';
			nali_info("send %ld", send(m_client_socket, message, size, 0))
			nali_log("%s", strerror(errno))
		}
		else if (!strcmp(char_p, "cq\n"))
		{
			m_net_client_state |= NALI_NET_CLIENT_FAIL;
		}
		#endif
		#if NALI_SERVER

			#ifdef NALI_CLIENT
		else if
			#else
		if
			#endif
		(!strcmp(char_p, "sq\n"))
		{
			m_net_server_state |= NALI_NET_SERVER_FAIL;
		}
		// #ifdef NALI_DEBUG
		// if (!strcmp(char_p, "dq\n"))
		// {
		// 	debug_free();
		// }
		// #endif

		// 	exit(EXIT_SUCCESS);

		#endif

		free(char_p);
		char_p = NULL;
		size = 0;
	}
}