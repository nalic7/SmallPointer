void lsc_sync_all_m_c2new_u(NALI_LB_UT ui)
{
	NALI_LB_UT u = lsu_p[ui];
	NALI_LB_CT x = lsu_c_p[ui * 3];
	NALI_LB_CT y = lsu_c_p[ui * 3 + 1];
	NALI_LB_CT z = lsu_c_p[ui * 3 + 2];
	NALI_LB_MIT *mi_p = lsm_i_h_p[M_H3(x, y, z, NALI_LB_CIBL)];
	// NALI_LB_MT m = ls_m_p[mi];

	*(NALI_LB_C_DATA_FP_T *)ls_net_p = NALI_LB_C_SYNC_ALL_M_C2NEW_U;
	ls_net_bl = sizeof(NALI_LB_C_DATA_FP_T);

	memcpy(ls_net_p + ls_net_bl, lsu_c_p + ui * 3, sizeof(NALI_LB_CT) * 3);
	ls_net_bl += sizeof(NALI_LB_CT) * 3;

	// lsm_i_hbl_p[];
	// lsm_i_h_p[];

	*(NALI_LB_MIT *)ls_net_p = lsm_bl;
	ls_net_bl += sizeof(NALI_LB_MIT);
	memcpy(ls_net_p + ls_net_bl, lsm_p, lsm_bl * sizeof(NALI_LB_MT));
	ls_net_bl += lsm_bl * sizeof(NALI_LB_MT);
	memcpy(ls_net_p + ls_net_bl, lsm_rt_p, lsm_bl * sizeof(float) * (3 + 3));
	ls_net_bl += lsm_bl * sizeof(float) * (3 + 3);

	nls_send(ui);
}

//m add send to only c u
void lsc_add_m_c2u(NALI_LB_CHT mih)
{
	for (NALI_LB_UT l_0 = 0; l_0 < lsu_bl; ++l_0)
	{
		NALI_LB_UT u = lsu_p[l_0];
		NALI_LB_CT x = lsu_c_p[l_0 * 3];
		NALI_LB_CT y = lsu_c_p[l_0 * 3 + 1];
		NALI_LB_CT z = lsu_c_p[l_0 * 3 + 2];

		if (mih == M_H3(x, y, z, NALI_LB_CIBL))
		{
			*(NALI_LB_C_DATA_FP_T *)ls_net_p = NALI_LB_C_ADD_M_C;
			ls_net_bl = sizeof(NALI_LB_C_DATA_FP_T);
			nls_send(l_0);
		}
	}
}