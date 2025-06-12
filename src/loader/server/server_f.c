void (*nlsf_data_fp[NALI_LSF_DATA_FP_BL])(NALI_LB_UT ui, uint8_t *) = {lsf_key_user};

// void nlsf_read_data(uint8_t *data_p)
// {
// 	if (*data_p != 255)
// 	{
// 		nlsf_data_fp[*data_p](data_p + 1);
// 	}
// }

//when get u need mtx only in ls

//every u will select their c
// static void sync_all_m2new_u()
// {

// }
static void sync_all_u2new_u()
{
	if (ls_u_bl > 0)
	{
		*(NALI_LB_C_DATA_FP_T *)ls_net_p = NALI_LB_C_SYNC_ALL_U2NEW_U;
		ls_net_bl = sizeof(NALI_LB_C_DATA_FP_T);
		*(NALI_LB_UT *)ls_net_p = ls_u_bl;
		ls_net_bl += sizeof(NALI_LB_UT);
		memcpy(ls_net_p + ls_net_bl, ls_u_p, ls_u_bl * sizeof(NALI_LB_UT));
		ls_net_bl += ls_u_bl * sizeof(NALI_LB_UT);
		memcpy(ls_net_p + ls_net_bl, ls_urt_p, ls_u_bl * sizeof(float) * (3 + 3));
		ls_net_bl += ls_u_bl * sizeof(float) * (3 + 3);
		memcpy(ls_net_p + ls_net_bl, ls_uc_p, ls_u_bl * sizeof(NALI_LB_CT) * 3);
		ls_net_bl += ls_u_bl * sizeof(NALI_LB_CT) * 3;

		nls_send(ls_u_bl);
	}
}
static void new_u()
{
	uint8_t n_bl = MATH_LENGTH(ls_u_p[ls_u_bl]);
	char *c_p = malloc(sizeof(NALI_F_SAVE_USER) + n_bl);
	c_p[sizeof(NALI_F_SAVE_USER) - 1 + n_bl] = 0;

	memcpy(c_p, NALI_F_SAVE_USER, sizeof(NALI_F_SAVE_USER) - 1);
	sprintf(c_p + sizeof(NALI_F_SAVE_USER) - 1, "%d", ls_u_p[ls_u_bl]);

	FILE *file_p = fopen(c_p, "rb");

	if (file_p)
	{
		uint32_t file_bl;
		void* data_p = f_read1(file_p, &file_bl);

		memcpy(ls_urt_p + ls_u_bl * (3 + 3), data_p, sizeof(float) * (3 + 3));
		memcpy(ls_uc_p + ls_u_bl * 3, data_p + sizeof(float) * (3 + 3), sizeof(NALI_LB_CT) * 3);

		free(data_p);
	}
	else
	{
		//random spawn
		ls_uc_p[ls_u_bl * 3] = rand() % NALI_LB_CIBL;
		ls_uc_p[ls_u_bl * 3 + 1] = rand() % NALI_LB_CIBL;
		ls_uc_p[ls_u_bl * 3 + 2] = rand() % NALI_LB_CIBL;

		//world / space
		//-NALI_LB_CFBL 0 NALI_LB_CFBL
		memset(ls_urt_p + ls_u_bl * (3 + 3), 0, sizeof(float) * (3 + 3));
	}

	free(c_p);
}
void lsf_add_u(NALI_LB_UT u)
{
	mtx_lock(ls_mtx_t_p);

	ls_u_p = realloc(ls_u_p, sizeof(NALI_LB_UT) * (ls_u_bl + 1));

	ls_u_p[ls_u_bl] = u;

	ls_urt_p = realloc(ls_urt_p, sizeof(float) * (3 + 3) * (ls_u_bl + 1));
	ls_uc_p = realloc(ls_uc_p, sizeof(NALI_LB_CT) * 3 * (ls_u_bl + 1));
	new_u();

	sync_all_u2new_u();
	// sync_all_m2new_u();
	*(NALI_LB_C_DATA_FP_T *)ls_net_p = NALI_LB_C_ADD_U;
	ls_net_bl = sizeof(NALI_LB_C_DATA_FP_T);
	*(NALI_LB_UT *)ls_net_p = u;
	ls_net_bl += sizeof(NALI_LB_UT);
	memcpy(ls_net_p + ls_net_bl, ls_urt_p + ls_u_bl * (3 + 3), sizeof(float) * (3 + 3));
	ls_net_bl += sizeof(float) * (3 + 3);
	memcpy(ls_net_p + ls_net_bl, ls_uc_p + ls_u_bl * 3, sizeof(NALI_LB_CT) * 3);
	ls_net_bl += sizeof(NALI_LB_CT) * 3;
	for (NALI_LB_UT l_0 = 0; l_0 < (ls_u_bl + 1); ++l_0)
	{
		nls_send(l_0);
	}
	lsc_sync_all_m2new_u(ls_u_bl);

	//add to h

	++ls_u_bl;

	mtx_unlock(ls_mtx_t_p);
}

void lsf_rm_u(NALI_LB_UT ui)
{
	mtx_lock(ls_mtx_t_p);

	ls_u_p[ui] = ls_u_p[--ls_u_bl];
	memcpy(ls_urt_p + ui * (3 + 3), ls_urt_p + ls_u_bl * (3 + 3), sizeof(float) * (3 + 3));
	memcpy(ls_uc_p + ui * 3, ls_uc_p + ls_u_bl * 3, sizeof(NALI_LB_CT) * 3);

	ls_u_p = realloc(ls_u_p, sizeof(NALI_LB_UT) * ls_u_bl);
	ls_urt_p = realloc(ls_urt_p, ls_u_bl * sizeof(float) * (3 + 3));
	ls_uc_p = realloc(ls_uc_p, ls_u_bl * sizeof(NALI_LB_CT) * 3);

	mtx_unlock(ls_mtx_t_p);
}

//need in thread

void lsf_key_user(NALI_LB_UT ui, uint8_t *data_p)
{
	NALI_LB_UT u = ls_u_p[ui];

	uint16_t key = *(uint16_t *)data_p;
	data_p += sizeof(uint16_t);

	if (key & NALI_LB_S_KEY_W)
	{
		mtx_lock(ls_mtx_t_p);

		mtx_unlock(ls_mtx_t_p);
	}
	// nlsf_read_data(data_p);
}

//sync entity / map
static void lsf_add_m(NALI_LB_MT m, NALI_LB_CT c_p[3], float rt_p[3 + 3])
{
	mtx_lock(ls_mtx_t_p);

	ls_m_p = realloc(ls_m_p, sizeof(NALI_LB_MT) * (ls_m_bl + 1));
	// ls_m_i_p = realloc(ls_m_i_p, sizeof(NALI_LB_MIT) * (ls_m_bl + 1));
	ls_mc_p = realloc(ls_mc_p, sizeof(NALI_LB_CT) * 3 * (ls_m_bl + 1));
	ls_mrt_p = realloc(ls_mrt_p, sizeof(float) * (3 + 3) * (ls_m_bl + 1));

	ls_m_p[ls_m_bl] = m;
	// ls_m_i_p[ls_m_bl] = ls_m_bl;
	memcpy(ls_mc_p + ls_m_bl * 3, c_p, sizeof(NALI_LB_CT) * 3);
	memcpy(ls_mrt_p + ls_m_bl * (3 + 3), rt_p, sizeof(float) * (3 + 3));

	NALI_LSC_CHT c_h = lsc_new_c_h(ls_mc_p[ls_m_bl * 3], ls_mc_p[ls_m_bl * 3 + 1], ls_mc_p[ls_m_bl * 3 + 2]);
	lsc_mihi_p = realloc(lsc_mihi_p, sizeof(NALI_LSC_CHT) * (lsc_mihi_bl + 1));
	if (lsc_mihi_bl > 0)
	{
		if (lsc_mihi_p[lsc_mihi_bl - 1] > c_h)
		{
			lsc_mihi_p[lsc_mihi_bl] = lsc_mihi_p[lsc_mihi_bl - 1];
		}
		else
		{
			lsc_mihi_p[lsc_mihi_bl] = c_h;

			if (lsc_mihi_p[lsc_mihi_bl - 1] < c_h)
			{
				lsc_mihbl_p = realloc(lsc_mihbl_p, sizeof(NALI_LB_MIT) * (c_h + 1));
				lsc_mih_p = realloc(lsc_mih_p, sizeof(NALI_LB_MIT *) * (c_h + 1));
				lsc_mihbl_p[c_h] = 0;
				lsc_mih_p[c_h] = malloc(0);
			}
		}
	}
	++lsc_mihi_bl;

	lsc_mih_p[c_h] = realloc(lsc_mih_p[c_h], sizeof(NALI_LB_MIT) * (lsc_mihbl_p[c_h] + 1));
	lsc_mih_p[c_h][lsc_mihbl_p[c_h]] = ls_m_bl;

	++lsc_mihbl_p[c_h];

	++ls_m_bl;

	//send in c u
	lsc_add_m2u(c_h);

	mtx_unlock(ls_mtx_t_p);
}
static void lsf_rm_m(NALI_LB_MIT mi)
{
	mtx_lock(ls_mtx_t_p);

	NALI_LSC_CHT c_h = lsc_new_c_h(ls_mc_p[mi * 3], ls_mc_p[mi * 3 + 1], ls_mc_p[mi * 3 + 2]);
	--lsc_mihi_bl;
	if (lsc_mihi_p[lsc_mihi_bl] > c_h)
	{
		for (NALI_LB_MIT l_0 = 0; l_0 < lsc_mihi_bl; ++l_0)
		{
			lsc_mihi_p[c_h] = lsc_mihi_p[lsc_mihi_bl];
		}
	}
	lsc_mihi_p = realloc(lsc_mihi_p, sizeof(NALI_LSC_CHT) * lsc_mihi_bl);

	if (--lsc_mihbl_p[c_h] == 0)
	{
		lsc_mihbl_p[c_h] = lsc_mihbl_p[lsc_mihi_bl];
		free(lsc_mih_p[c_h]);
		lsc_mih_p[c_h] = lsc_mih_p[lsc_mihi_bl];

		lsc_mihbl_p = realloc(lsc_mihbl_p, sizeof(NALI_LB_MIT) * lsc_mihi_bl);
		lsc_mih_p = realloc(lsc_mih_p, sizeof(NALI_LB_MT) * lsc_mihi_bl);
	}
	else
	{
		lsc_mih_p[c_h] = realloc(lsc_mih_p[c_h], sizeof(NALI_LB_MIT) * lsc_mihbl_p[c_h]);
	}

	ls_m_p[mi] = ls_m_p[--ls_m_bl];
	// ls_m_i_p[mi] = ls_m_i_p[ls_m_bl];
	memcpy(ls_mc_p + mi * 3, ls_mc_p + ls_m_bl * 3, sizeof(NALI_LB_CT) * 3);
	memcpy(ls_mrt_p + mi * (3 + 3), ls_mrt_p + ls_m_bl * (3 + 3), sizeof(float) * (3 + 3));
	ls_m_p = realloc(ls_m_p, sizeof(NALI_LB_MT) * ls_m_bl);
	// ls_m_i_p = realloc(ls_m_i_p, sizeof(NALI_LB_MIT) * ls_m_bl);
	ls_mc_p = realloc(ls_mc_p, sizeof(NALI_LB_CT) * 3 * ls_m_bl);
	ls_mrt_p = realloc(ls_mrt_p, sizeof(float) * (3 + 3) * ls_m_bl);

	//update ls_m_bl to mi

	// ls_r_m_i_p = realloc(ls_r_m_i_p, sizeof(NALI_LB_MIT) * (ls_r_m_bl + 1));
	// ls_r_m_i_p[ls_r_m_bl] = mi;
	// ++ls_r_m_bl;

	mtx_unlock(ls_mtx_t_p);
}