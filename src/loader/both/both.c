// mtx_t *lb_mtx_t_p = &(mtx_t){};
uint8_t lb_ms_p[NALI_LB_N_MAX] =
{
	NALI_EPOMI0_M
};

uint8_t lb_ms_a_p[NALI_LB_N_MAX] =
{
	NALI_EPOMI0_A
};

uint8_t *lb_ms_ap_p[NALI_LB_N_MAX] =
{
	e_pomi0_ms_ap_p
};

uint8_t lb_ms_abl_p[NALI_LB_N_MAX] =
{
	NALI_EPOMI0_MS_AP_BL
};

void *lb_cache_p;

void lb_set()
{
	// NALI_D_INFO("mtx_init %d", mtx_init(lb_mtx_t_p, mtx_plain))

	lb_cache_p = malloc(NALI_LB_CACHE_P_BL);
	NALI_LB_CACHE_P_D_BL_P = malloc(sizeof(uint32_t) * 2);
	NALI_LB_CACHE_P_D_BL_P[1] = 0;
	NALI_LB_CACHE_P_D_P = f_read(NALI_F_HOME_ASSET, NALI_LB_CACHE_P_D_BL_P);
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

		#ifdef C_NALI_CLIENT
			if (!strcmp(char_p, "qc\n"))
			{
				nlc_state |= NALI_NLC_FAIL;
			}
		#endif

		#if C_NALI_SERVER
			if (!strcmp(char_p, "qs\n"))
			{
				// ls_state ^= NALI_LS_STATE_ON;
				nls_state |= NALI_NLS_FAIL;
			}
		#endif

		#if C_NALI_SERVER || C_NALI_CLIENT
			if (!strcmp(char_p, "q\n"))
			{
				lb_free1();
			}

			free(char_p);
			char_p = NULL;
			size = 0;
		#endif
	}
}

void lb_free0()
{
	free(NALI_LB_CACHE_P_D_BL_P);
	free(NALI_LB_CACHE_P_D_P);
	free(lb_cache_p);
}

void lb_free1()
{
	if (!(s_surface_state & NALI_SURFACE_C_S_EXIT))
	{
		s_surface_state |= NALI_SURFACE_C_S_EXIT | NALI_SURFACE_C_S_CLEAN;
		al_clean();
		// while (vkqdpdi_vkinstance != VK_NULL_HANDLE || m_client_socket != -1)
		while (vkqdpdi_vkinstance != VK_NULL_HANDLE)
		{
			thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
		}
		wlc_clean();

		// mtx_destroy(lb_mtx_t_p);

		d_free();

		exit(EXIT_SUCCESS);
	}
}