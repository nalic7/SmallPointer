NALI_LB_UT lsc_uhi_bl = 0;
NALI_LSC_CHT *lsc_uhi_p;

NALI_LB_UT *lsc_uhbl_p;
NALI_LB_UT **lsc_uh_p;

NALI_LB_MIT lsc_mihi_bl = 0;
NALI_LSC_CHT *lsc_mihi_p;

NALI_LB_MIT *lsc_mihbl_p;
NALI_LB_MIT **lsc_mih_p;

NALI_LSC_CHT lsc_new_c_h(NALI_LB_CT x, NALI_LB_CT y, NALI_LB_CT z)
{
	#define r NALI_LB_CIBL * NALI_LB_CIBL;
	return x * r + y * NALI_LB_CIBL + z;
}
// static void get_c_hash(NALI_LSC_CHT hi)
// {
// 	NALI_LB_CT z = hi % NALI_LB_CIBL;
// 	NALI_LB_CT y = (hi / NALI_LB_CIBL) % NALI_LB_CIBL;
// 	NALI_LB_CT x = hi / (NALI_LB_CIBL * NALI_LB_CIBL);
// }

void lsc_set()
{
	lsc_uhi_p = malloc(0);

	lsc_uh_p = malloc(0);
	lsc_uhbl_p = malloc(0);

	lsc_mihi_p = malloc(0);

	lsc_mih_p = malloc(0);
	lsc_mihbl_p = malloc(0);
}

void lsc_sync_all_m2new_u(NALI_LB_UT ui)
{
	NALI_LB_UT u = ls_u_p[ui];
	NALI_LB_CT x = ls_uc_p[ui * 3];
	NALI_LB_CT y = ls_uc_p[ui * 3 + 1];
	NALI_LB_CT z = ls_uc_p[ui * 3 + 2];
	NALI_LB_MIT *mi_p = lsc_mih_p[lsc_new_c_h(x, y, z)];
	// NALI_LB_MT m = ls_m_p[mi];

	*(NALI_LB_C_DATA_FP_T *)ls_net_p = NALI_LB_C_SYNC_ALL_M_C;
	ls_net_bl = sizeof(NALI_LB_C_DATA_FP_T);
	// *(NALI_LB_UT *)ls_net_p = ls_u_bl;
	// ls_net_bl += sizeof(NALI_LB_UT);
	// memcpy(ls_net_p + ls_net_bl, ls_u_p, ls_u_bl * sizeof(NALI_LB_UT));
	// ls_net_bl += ls_u_bl * sizeof(NALI_LB_UT);
	// memcpy(ls_net_p + ls_net_bl, ls_urt_p, ls_u_bl * sizeof(float) * (3 + 3));
	// ls_net_bl += ls_u_bl * sizeof(float) * (3 + 3);
	// memcpy(ls_net_p + ls_net_bl, ls_uc_p, ls_u_bl * sizeof(NALI_LB_CT) * 3);
	// ls_net_bl += ls_u_bl * sizeof(NALI_LB_CT) * 3;

	nls_send(ui);
}

//m add send to only c u
void lsc_add_m2u(NALI_LSC_CHT mih)
{
	for (NALI_LB_UT l_0 = 0; l_0 < ls_u_bl; ++l_0)
	{
		NALI_LB_UT u = ls_u_p[l_0];
		NALI_LB_CT x = ls_uc_p[l_0 * 3];
		NALI_LB_CT y = ls_uc_p[l_0 * 3 + 1];
		NALI_LB_CT z = ls_uc_p[l_0 * 3 + 2];

		if (mih == lsc_new_c_h(x, y, z))
		{
			*(NALI_LB_C_DATA_FP_T *)ls_net_p = NALI_LB_C_ADD_M;
			ls_net_bl = sizeof(NALI_LB_C_DATA_FP_T);
			nls_send(l_0);
		}
	}
}

void lsc_free()
{
	lsc_uhi_bl = 0;
	free(lsc_uhi_p);

	free(lsc_uh_p);
	free(lsc_uhbl_p);

	lsc_mihi_bl = 0;
	free(lsc_mihi_p);

	free(lsc_mih_p);
	free(lsc_mihbl_p);
}