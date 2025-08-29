lcs__ lcs___p[NALI_LB_MIM];

uint32_t lcs_s_bl;
lcs_s *lcs_s_p;

void lcs_set()
{
	lcs_s_p = malloc(0);
	// lcs_vkmappedmemoryrange_p = malloc(0);

	// for (uint8_t l_0 = 0; l_0 < NALI_LCS_A_BL; ++l_0)
	// {
	// 	lcs_b_vkdevicesize_p[l_0] = malloc(0);
	// }

	//init unused value
	for (NALI_LB_MIT l_0 = 0; l_0 < NALI_LB_MIM; ++l_0)
	{
		//ch can pass with _update
		lcs___p[l_0].m.mi = NALI_LB_MIN;
		lcs___p[l_0].m.state = 0;
		// lsm__update_p[l_0].ms = NALI_LB_MSM;
		lcs___p[l_0].m.m = NALI_LB_MN;
		lcs___p[l_0].m.aki = NALI_LB_AKIN;
	}
}

void lcs_free()
{
	free(lcs_s_p);
}
