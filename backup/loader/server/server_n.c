void (*nlsf_data_fp[NALI_LSF_DATA_FP_BL])(NALI_LB_UT ui, uint8_t *) = {lsf_key_u};

// void nlsf_read_data(uint8_t *data_p)
// {
// 	if (*data_p != 255)
// 	{
// 		nlsf_data_fp[*data_p](data_p + 1);
// 	}
// }

// static void sync_all_u_c2new_u()
// {
// 	// if (lsu_bl > 0)
// 	// {
// 	// 	*(NALI_LB_C_DATA_FP_T *)ls_net_p = NALI_LB_C_SYNC_ALL_U_C2NEW_U;
// 	// 	ls_net_bl = sizeof(NALI_LB_C_DATA_FP_T);
// 	// 	*(NALI_LB_UT *)ls_net_p = lsu_bl;
// 	// 	ls_net_bl += sizeof(NALI_LB_UT);
// 	// 	memcpy(ls_net_p + ls_net_bl, lsu_p, lsu_bl * sizeof(NALI_LB_UT));
// 	// 	ls_net_bl += lsu_bl * sizeof(NALI_LB_UT);
// 	// 	memcpy(ls_net_p + ls_net_bl, lsu_rt_p, lsu_bl * sizeof(float) * (3 + 3));
// 	// 	ls_net_bl += lsu_bl * sizeof(float) * (3 + 3);
// 	// 	memcpy(ls_net_p + ls_net_bl, lsu_c_p, lsu_bl * sizeof(NALI_LB_CT) * 3);
// 	// 	ls_net_bl += lsu_bl * sizeof(NALI_LB_CT) * 3;

// 	// 	nls_send(lsu_bl);
// 	// }
// }
void lsf_add_u(NALI_LB_UT u)
{
	mtx_lock(ls_mtx_t_p);

	lsu_h1_p = realloc(lsu_h1_p, sizeof(NALI_LB_UT) * (lsu_h1_bl + 1));
	lsu_h1_p[lsu_h1_bl] = u;

	//s0-new_u
	fseek(ls_file_p, u * sizeof(uintptr_t), SEEK_SET);
	
	uintptr_t u_up;
	fread(&u_up, sizeof(uintptr_t), 1, ls_file_p);

	if (u_up)
	{
		(lsu_p + lsu_h1_bl)->s |= NALI_LSU_S_CONNECT;
	}
	else
	{
		lsu_p = realloc(lsu_p, sizeof(LSU) * (lsu_h1_bl + 1));
		u_up = (uintptr_t)(lsu_p + lsu_h1_bl);

		//random spawn
		(lsu_p + lsu_h1_bl)->s = NALI_LSU_S_CONNECT;
		(lsu_p + lsu_h1_bl)->c = M_H3(rand() % NALI_LB_CIBL, rand() % NALI_LB_CIBL, rand() % NALI_LB_CIBL, NALI_LB_CIBL);

		//world / space
		//-NALI_LB_CFBL 0 NALI_LB_CFBL
		memset((lsu_p + lsu_h1_bl)->rt, 0, sizeof(float) * (3 + 3));

		fseek(ls_file_p, -sizeof(uintptr_t), SEEK_CUR);
		fwrite(&u_up, sizeof(uintptr_t), 1, ls_file_p);
	}
	//e0-new_u

	//h
	//void *c_h3[f] -> *c_h3
	//f
	//void * max c

	//new u
	//1 u[rt c] in c
	//2 check all u -> 2 sync all u/m for new u im c
	//2.5 check same value
	//3 send

	//u
	//1 new u[rt c] in c
	//2 check all u -> 2 sync all u/m for u in c
	//2.5 check same value
	//3 send

	sync_all_u_c2new_u();
	// *(NALI_LB_C_DATA_FP_T *)ls_net_p = NALI_LB_C_ADD_U_C;
	// ls_net_bl = sizeof(NALI_LB_C_DATA_FP_T);
	// *(NALI_LB_UT *)ls_net_p = u;
	// ls_net_bl += sizeof(NALI_LB_UT);
	// memcpy(ls_net_p + ls_net_bl, lsu_rt_p + lsu_bl * (3 + 3), sizeof(float) * (3 + 3));
	// ls_net_bl += sizeof(float) * (3 + 3);
	// memcpy(ls_net_p + ls_net_bl, lsu_c_p + lsu_bl * 3, sizeof(NALI_LB_CT) * 3);
	// ls_net_bl += sizeof(NALI_LB_CT) * 3;
	// for (NALI_LB_UT l_0 = 0; l_0 < (lsu_bl + 1); ++l_0)
	// {
	// 	nls_send(l_0);
	// }
	// lsc_sync_all_m_c2new_u(lsu_bl);

	//add to h

	++lsu_h1_bl;

	mtx_unlock(ls_mtx_t_p);
}

void lsf_rm_u(NALI_LB_UT ui)
{
	mtx_lock(ls_mtx_t_p);

	(lsu_p + ui)->s ^= NALI_LSU_S_CONNECT;

	// lsu_p[ui] = lsu_p[--lsu_h1_bl];
	// memcpy(lsu_p + ui * sizeof(LSU), lsu_p + lsu_h1_bl * sizeof(LSU), sizeof(LSU));

	// lsu_p = realloc(lsu_p, sizeof(lsu_p) * lsu_h1_bl);
	// lsu_h1_p = realloc(lsu_h1_p, sizeof(NALI_LB_UT) * lsu_h1_bl);

	mtx_unlock(ls_mtx_t_p);
}

void lsf_key_u(NALI_LB_UT ui, uint8_t *data_p)
{
	NALI_LB_UT u = lsu_p[ui];

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

	lsm_p = realloc(lsm_p, sizeof(NALI_LB_MT) * (lsm_bl + 1));
	lsm_c_p = realloc(lsm_c_p, sizeof(NALI_LB_CT) * 3 * (lsm_bl + 1));
	lsm_rt_p = realloc(lsm_rt_p, sizeof(float) * (3 + 3) * (lsm_bl + 1));

	lsm_p[lsm_bl] = m;
	memcpy(lsm_c_p + lsm_bl * 3, c_p, sizeof(NALI_LB_CT) * 3);
	memcpy(lsm_rt_p + lsm_bl * (3 + 3), rt_p, sizeof(float) * (3 + 3));

	NALI_LB_CHT c_h = M_H3(lsm_c_p[lsm_bl * 3], lsm_c_p[lsm_bl * 3 + 1], lsm_c_p[lsm_bl * 3 + 2], NALI_LB_CIBL);
	lsm_i_hi_p = realloc(lsm_i_hi_p, sizeof(NALI_LB_CHT) * (lsm_i_hi_bl + 1));
	if (lsm_i_hi_bl > 0)
	{
		if (lsm_i_hi_p[lsm_i_hi_bl - 1] > c_h)
		{
			lsm_i_hi_p[lsm_i_hi_bl] = lsm_i_hi_p[lsm_i_hi_bl - 1];
		}
		else
		{
			lsm_i_hi_p[lsm_i_hi_bl] = c_h;

			if (lsm_i_hi_p[lsm_i_hi_bl - 1] < c_h)
			{
				lsm_i_hbl_p = realloc(lsm_i_hbl_p, sizeof(NALI_LB_MIT) * (c_h + 1));
				lsm_i_h_p = realloc(lsm_i_h_p, sizeof(NALI_LB_MIT *) * (c_h + 1));
				lsm_i_hbl_p[c_h] = 0;
				lsm_i_h_p[c_h] = malloc(0);
			}
		}
	}
	++lsm_i_hi_bl;

	lsm_i_h_p[c_h] = realloc(lsm_i_h_p[c_h], sizeof(NALI_LB_MIT) * (lsm_i_hbl_p[c_h] + 1));
	lsm_i_h_p[c_h][lsm_i_hbl_p[c_h]] = lsm_bl;

	++lsm_i_hbl_p[c_h];

	++lsm_bl;

	//send in c u
	lsc_add_m_c2u(c_h);

	mtx_unlock(ls_mtx_t_p);
}
static void lsf_rm_m(NALI_LB_MIT mi)
{
	mtx_lock(ls_mtx_t_p);

	NALI_LB_CHT c_h = M_H3(lsm_c_p[mi * 3], lsm_c_p[mi * 3 + 1], lsm_c_p[mi * 3 + 2], NALI_LB_CIBL);
	--lsm_i_hi_bl;
	if (lsm_i_hi_p[lsm_i_hi_bl] > c_h)
	{
		for (NALI_LB_MIT l_0 = 0; l_0 < lsm_i_hi_bl; ++l_0)
		{
			lsm_i_hi_p[c_h] = lsm_i_hi_p[lsm_i_hi_bl];
		}
	}
	lsm_i_hi_p = realloc(lsm_i_hi_p, sizeof(NALI_LB_CHT) * lsm_i_hi_bl);

	if (--lsm_i_hbl_p[c_h] == 0)
	{
		lsm_i_hbl_p[c_h] = lsm_i_hbl_p[lsm_i_hi_bl];
		free(lsm_i_h_p[c_h]);
		lsm_i_h_p[c_h] = lsm_i_h_p[lsm_i_hi_bl];

		lsm_i_hbl_p = realloc(lsm_i_hbl_p, sizeof(NALI_LB_MIT) * lsm_i_hi_bl);
		lsm_i_h_p = realloc(lsm_i_h_p, sizeof(NALI_LB_MT) * lsm_i_hi_bl);
	}
	else
	{
		lsm_i_h_p[c_h] = realloc(lsm_i_h_p[c_h], sizeof(NALI_LB_MIT) * lsm_i_hbl_p[c_h]);
	}

	lsm_p[mi] = lsm_p[--lsm_bl];
	// ls_m_i_p[mi] = ls_m_i_p[ls_m_bl];
	memcpy(lsm_c_p + mi * 3, lsm_c_p + lsm_bl * 3, sizeof(NALI_LB_CT) * 3);
	memcpy(lsm_rt_p + mi * (3 + 3), lsm_rt_p + lsm_bl * (3 + 3), sizeof(float) * (3 + 3));
	lsm_p = realloc(lsm_p, sizeof(NALI_LB_MT) * lsm_bl);
	// ls_m_i_p = realloc(ls_m_i_p, sizeof(NALI_LB_MIT) * ls_m_bl);
	lsm_c_p = realloc(lsm_c_p, sizeof(NALI_LB_CT) * 3 * lsm_bl);
	lsm_rt_p = realloc(lsm_rt_p, sizeof(float) * (3 + 3) * lsm_bl);

	//update ls_m_bl to mi

	// ls_r_m_i_p = realloc(ls_r_m_i_p, sizeof(NALI_LB_MIT) * (ls_r_m_bl + 1));
	// ls_r_m_i_p[ls_r_m_bl] = mi;
	// ++ls_r_m_bl;

	mtx_unlock(ls_mtx_t_p);
}