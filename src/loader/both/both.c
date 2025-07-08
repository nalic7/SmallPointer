mtx_t *lb_mtx_t_p = &(mtx_t){};

// NALI_LB_MT lb_ms_p[NALI_LB_N_MAX] =
// {
// 	NALI_EBPOMI0_M
// };

// uint8_t lb_ms_a_p[NALI_LB_N_MAX] =
// {
// 	NALI_EBPOMI0_A
// };

// uint8_t *lb_ms_ap_p[NALI_LB_N_MAX] =
// {
// 	ebpomi0_ms_ap_p
// };

// uint8_t lb_ms_abl_p[NALI_LB_N_MAX] =
// {
// 	NALI_EBPOMI0_MS_AP_BL
// };

// VkDeviceSize lb_ms_vkdevicesize_p[NALI_LB_N_MAX] =
// {
// 	NALI_EBPOMI0_MS_VKDEVICESIZE
// };

void *lb_cache_p;

void lb_set()
{
	NALI_D_INFO("mtx_init %d", mtx_init(lb_mtx_t_p, mtx_plain))

	lb_cache_p = malloc(NALI_LB_CACHE_P_BL);
	NALI_LB_CACHE_P_D_BL_P = malloc(sizeof(uint32_t) * 2);
	NALI_LB_CACHE_P_D_BL_P[1] = 0;
	NALI_LB_CACHE_P_D_P = f_read(NALI_F_HOME_ASSET, NALI_LB_CACHE_P_D_BL_P);
}

#define NALI_LB_RZ NALI_M_D2R(180.0F)
//t_p lt_v4_array
void lb_u_update(float w_p[16], float ry, float q_v4_array[4], float q0_m4x4_array[16], float q1_m4x4_array[16])
{
	memcpy(w_p, mm4x4_array, sizeof(mm4x4_array));

	mv4_q(0, 0, NALI_LB_RZ, q_v4_array);
	mv4_q2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, w_p, sizeof(float) * 16);
	mm4x4_m(q1_m4x4_array, q0_m4x4_array, w_p);

	mv4_q(0, ry, 0, q_v4_array);
	mv4_q2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, w_p, sizeof(float) * 16);
	mm4x4_m(q1_m4x4_array, q0_m4x4_array, w_p);
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
				lc_free();
			}
			else if (!strcmp(char_p, "rc\n"))
			{
			}
		#endif

		#if C_NALI_SERVER
			if (!strcmp(char_p, "qs\n"))
			{
				ls_free();
			}
			else if (!strcmp(char_p, "rs\n"))
			{
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
	if (s_state & NALI_S_S_EXIT)
	{
		return;
	}
	s_state |= NALI_S_S_EXIT;

	ls_free();
	mtx_lock(lb_mtx_t_p);
	mtx_unlock(lb_mtx_t_p);
	lc_free();
	mtx_lock(lb_mtx_t_p);
	mtx_unlock(lb_mtx_t_p);

	al_clean();

	#ifndef C_NALI_S_ANDROID
		swlc_clean();
	#endif

	mtx_destroy(lb_mtx_t_p);

	d_free();

	exit(EXIT_SUCCESS);
}