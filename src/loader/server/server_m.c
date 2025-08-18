// void (*lsm_fp[NALI_LB_FP_BL])(NALI_LB_MIT mi) =
// {
// 	espomi0_set
// };

//mi in ch
NALI_LB_MIT *lsm_c_mi_p[NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL];
//m data in ch
LB_M *lsm_c_lb_m_p[NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL];
NALI_LB_MIT lsm_c_bl_p[NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL] = {0};

//ch in m data for server only
NALI_LB_CHT *lsm_m_ch_p;
//i to ch
NALI_LB_MIT *lsm_m_i_p;
NALI_LB_MIT lsm_m_bl = 0;

//free mi
NALI_LB_MIT *lsm_f_mi_p;
NALI_LB_MIT lsm_f_mi_bl = 0;

void lsm_ad_m(NALI_LB_CHT ch)
{
	if (lsm_m_bl == NALI_LB_MIM)
		return;

	NALI_LB_MIT mi = lsm_m_bl++;
	lsm_m_ch_p = realloc(lsm_m_ch_p, sizeof(NALI_LB_CHT) * lsm_m_bl);
	lsm_m_ch_p[mi] = ch;
	lsm_m_i_p = realloc(lsm_m_i_p, sizeof(NALI_LB_MIT) * lsm_m_bl);
	lsm_m_i_p[mi] = lsm_c_bl_p[ch];

	if (++lsm_c_bl_p[ch] == 1)
	{
		lsm_c_mi_p[ch] = malloc(sizeof(NALI_LB_MIT));
		lsm_c_lb_m_p[ch] = malloc(sizeof(LB_M));
	}
	else
	{
		lsm_c_mi_p[ch] = realloc(lsm_c_mi_p[ch], sizeof(NALI_LB_MIT) * lsm_c_bl_p[ch]);
		lsm_c_lb_m_p[ch] = realloc(lsm_c_lb_m_p[ch], sizeof(LB_M) * lsm_c_bl_p[ch]);
	}

	lsm_c_mi_p[ch][lsm_m_i_p[mi]] = mi;

	if (lsm_f_mi_bl)
		lsm_c_lb_m_p[ch][lsm_m_i_p[mi]].mi = lsm_f_mi_p[--lsm_f_mi_bl];
	else
		lsm_c_lb_m_p[ch][lsm_m_i_p[mi]].mi = mi;
}

void lsm_rm_m(NALI_LB_MIT mi)
{
	NALI_LB_CHT c_ch = lsm_m_ch_p[mi];
	NALI_LB_MIT c_i = lsm_m_i_p[mi];

	lsm_f_mi_p = realloc(lsm_f_mi_p, sizeof(NALI_LB_MIT) * ++lsm_f_mi_bl);
	lsm_f_mi_p[lsm_f_mi_bl - 1] = mi;

	--lsm_m_bl;
	lsm_m_ch_p[mi] = lsm_m_ch_p[lsm_m_bl];
	lsm_m_ch_p = realloc(lsm_m_ch_p, sizeof(NALI_LB_CHT) * lsm_m_bl);
	lsm_m_i_p[mi] = lsm_m_i_p[lsm_m_bl];
	lsm_m_i_p = realloc(lsm_m_i_p, sizeof(NALI_LB_MIT) * lsm_m_bl);

	if (--lsm_c_bl_p[c_ch])
	{
		lsm_c_mi_p[c_ch][c_i] = lsm_c_mi_p[c_ch][lsm_c_bl_p[c_ch]];
		lsm_c_lb_m_p[c_ch][c_i] = lsm_c_lb_m_p[c_ch][lsm_c_bl_p[c_ch]];
		lsm_c_lb_m_p[c_ch][c_i].mi = lsm_c_mi_p[c_ch][c_i];
	}
	else
	{
		free(lsm_c_mi_p[c_ch]);
		free(lsm_c_lb_m_p[c_ch]);
	}
}

void lsm_update()
{
	//! ai & path
}

void lsm_send(NALI_LB_UT u)
{
	//should check in view before send?
	NS ns = ns_p[u];
	for (NALI_LB_UT l_0 = 0; l_0 < ns.ch_bl; ++l_0)
	{
		NALI_LB_CHT ch = ns.ch_p[l_0];
		*(NALI_LB_MIT *)(ls_net_p + ls_net_bl) = lsm_c_bl_p[ch];
		ls_net_bl += sizeof(NALI_LB_MIT);

		memcpy(ls_net_p + ls_net_bl, lsm_c_lb_m_p[ch], sizeof(LB_M) * lsm_c_bl_p[ch]);
		ls_net_bl += sizeof(LB_M) * lsm_c_bl_p[ch];
	}
}

void lsm_open()
{
	if (ls_file_p)
	{
		fread(lsm_c_bl_p, sizeof(NALI_LB_MIT), NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL, ls_file_p);

		for (NALI_LB_MIT l_0 = 0; l_0 < NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL; ++l_0)
			if (lsm_c_bl_p[l_0])
			{
				fread(lsm_c_mi_p[l_0], sizeof(NALI_LB_MIT), lsm_c_bl_p[l_0], ls_file_p);
				fread(lsm_c_lb_m_p[l_0], sizeof(LB_M), lsm_c_bl_p[l_0], ls_file_p);
			}

		fread(&lsm_m_bl, sizeof(NALI_LB_MIT), 1, ls_file_p);
		lsm_m_ch_p = malloc(sizeof(NALI_LB_CHT) * lsm_m_bl);
		lsm_m_i_p = malloc(sizeof(NALI_LB_MIT) * lsm_m_bl);
		fread(lsm_m_ch_p, sizeof(NALI_LB_CHT), lsm_m_bl, ls_file_p);
		fread(lsm_m_i_p, sizeof(NALI_LB_MIT), lsm_m_bl, ls_file_p);

		fread(&lsm_f_mi_bl, sizeof(NALI_LB_MIT), 1, ls_file_p);
		lsm_f_mi_p = malloc(sizeof(NALI_LB_MIT) * lsm_f_mi_bl);
		fread(lsm_f_mi_p, sizeof(NALI_LB_MIT), lsm_f_mi_bl, ls_file_p);
	}
	else
	{
		lsm_m_ch_p = malloc(0);
		lsm_m_i_p = malloc(0);
		lsm_f_mi_p = malloc(0);

		//! test s
		//s0-test world init
		NALI_LB_CHT ch = 0;
		NALI_LB_MIT mi = lsm_m_bl;
		lsm_ad_m(ch);
		LB_M lb_m = lsm_c_lb_m_p[ch][lsm_m_i_p[mi]];
		memset(lb_m.rt_p, 0, sizeof(float) * (3 + 2));
		//set model attribute
		lb_m.m = NALI_EBPOMI2_M;
		lb_m.ma = NALI_EBPOMI2_MA;
		//set animate
		lb_m.aki = NALI_EBPOMI2_AKI;
		lb_m.af = 0;
		//ai / math can call in
		//e0-test world init

		//s0-test rm
		// lsm_rm_m(mi);
		//e0-test rm
	}
}

void lsm_save()
{
	fwrite(lsm_c_bl_p, sizeof(NALI_LB_MIT), NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL, ls_file_p);
	for (NALI_LB_MIT l_0 = 0; l_0 < NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL; ++l_0)
		if (lsm_c_bl_p[l_0])
		{
			fwrite(lsm_c_mi_p[l_0], sizeof(NALI_LB_MIT), lsm_c_bl_p[l_0], ls_file_p);
			fwrite(lsm_c_lb_m_p[l_0], sizeof(LB_M), lsm_c_bl_p[l_0], ls_file_p);
		}

	fwrite(&lsm_m_bl, sizeof(NALI_LB_MIT), 1, ls_file_p);
	fwrite(lsm_m_ch_p, sizeof(NALI_LB_CHT), lsm_m_bl, ls_file_p);
	fwrite(lsm_m_i_p, sizeof(NALI_LB_MIT), lsm_m_bl, ls_file_p);

	fwrite(&lsm_f_mi_bl, sizeof(NALI_LB_MIT), 1, ls_file_p);
	fwrite(lsm_f_mi_p, sizeof(NALI_LB_MIT), lsm_f_mi_bl, ls_file_p);
}

void lsm_free()
{
	for (NALI_LB_CHT l_0 = 0; l_0 < NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL; ++l_0)
		if (lsm_c_bl_p[l_0])
		{
			free(lsm_c_mi_p[l_0]);
			free(lsm_c_lb_m_p[l_0]);
		}

	free(lsm_m_ch_p);
	free(lsm_m_i_p);
	free(lsm_f_mi_p);
}
