void *lb_cache_p;

void lb_set()
{
	lb_cache_p = malloc(NALI_CACHE_P_BL);
	NALI_CACHE_P_D_BL_P = malloc(sizeof(uint32_t) * 2);
	NALI_CACHE_P_D_BL_P[1] = 0;
	NALI_CACHE_P_D_P = f_read(NALI_F_HOME_ASSET, NALI_CACHE_P_D_BL_P);
}

void lb_loop()
{
	#if C_NALI_SERVER || C_NALI_CLIENT
		char *char_p = NULL;
		size_t size = 0;
	#endif
	while (1)
	{
		#if C_NALI_SERVER || C_NALI_CLIENT
			NALI_D_INFO_A("getline %ld", getline(&char_p, &size, stdin))
		#endif

		// #ifdef C_NALI_CLIENT
		// 	if (!strcmp(char_p, "cq\n"))
		// 	{
		// 		nlc_state |= NALI_NLC_FAIL;
		// 	}
		// #endif

		// #if C_NALI_SERVER
		// 	if (!strcmp(char_p, "sq\n"))
		// 	{
		// 		// ls_state ^= NALI_LS_STATE_ON;
		// 		nls_state |= NALI_NLS_FAIL;
		// 	}
		// #endif

		#if C_NALI_SERVER || C_NALI_CLIENT
			// if (!strcmp(char_p, "q\n"))
			// {
			// 	//exit / free all
			// 	d_free();
			// }

			free(char_p);
			char_p = NULL;
			size = 0;
		#endif
	}
}

void lb_free()
{
	free(NALI_CACHE_P_D_BL_P);
	free(NALI_CACHE_P_D_P);
	free(lb_cache_p);
}