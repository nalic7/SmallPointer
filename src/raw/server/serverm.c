// void (*lsm_fp[_RB_FP_BL])(_RB_MIT mi) =
// {
// 	espomi0_set
// };

//mi in ch
_RB_MIT *lsm_c_mi_p[_RB_CIBL * _RB_CIBL * _RB_CIBL];
//m data in ch
LB_M *lsm_c_lb_m_p[_RB_CIBL * _RB_CIBL * _RB_CIBL];
_RB_MIT lsm_c_bl_p[_RB_CIBL * _RB_CIBL * _RB_CIBL] = {0};

//ch in m data for server only
_RB_CHT *lsm_m_ch_p;
//i to ch
_RB_MIT *lsm_m_i_p;
_RB_MIT lsm_m_bl = 0;

//free mi
_RB_MIT *lsm_f_mi_p;
_RB_MIT lsm_f_mi_bl = 0;

void lsm_ad_m(_RB_CHT ch)
{
	if (lsm_m_bl == _RB_MIM)
		return;

	_RB_MIT mi = lsm_m_bl++;
	lsm_m_ch_p = realloc(lsm_m_ch_p, sizeof(_RB_CHT) * lsm_m_bl);
	lsm_m_ch_p[mi] = ch;
	lsm_m_i_p = realloc(lsm_m_i_p, sizeof(_RB_MIT) * lsm_m_bl);
	lsm_m_i_p[mi] = lsm_c_bl_p[ch];

	if (++lsm_c_bl_p[ch] == 1)
	{
		lsm_c_mi_p[ch] = malloc(sizeof(_RB_MIT));
		lsm_c_lb_m_p[ch] = malloc(sizeof(LB_M));
	}
	else
	{
		lsm_c_mi_p[ch] = realloc(lsm_c_mi_p[ch], sizeof(_RB_MIT) * lsm_c_bl_p[ch]);
		lsm_c_lb_m_p[ch] = realloc(lsm_c_lb_m_p[ch], sizeof(LB_M) * lsm_c_bl_p[ch]);
	}

	lsm_c_mi_p[ch][lsm_m_i_p[mi]] = mi;

	if (lsm_f_mi_bl)
		lsm_c_lb_m_p[ch][lsm_m_i_p[mi]].mi = lsm_f_mi_p[--lsm_f_mi_bl];
	else
		lsm_c_lb_m_p[ch][lsm_m_i_p[mi]].mi = mi;
}

void lsm_rm_m(_RB_MIT mi)
{
	_RB_CHT c_ch = lsm_m_ch_p[mi];
	_RB_MIT c_i = lsm_m_i_p[mi];

	lsm_f_mi_p = realloc(lsm_f_mi_p, sizeof(_RB_MIT) * ++lsm_f_mi_bl);
	lsm_f_mi_p[lsm_f_mi_bl - 1] = mi;

	--lsm_m_bl;
	lsm_m_ch_p[mi] = lsm_m_ch_p[lsm_m_bl];
	lsm_m_ch_p = realloc(lsm_m_ch_p, sizeof(_RB_CHT) * lsm_m_bl);
	lsm_m_i_p[mi] = lsm_m_i_p[lsm_m_bl];
	lsm_m_i_p = realloc(lsm_m_i_p, sizeof(_RB_MIT) * lsm_m_bl);

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

void lsm_send(_RB_UT u)
{
	//should check in view before send?
	NS ns = ns_p[u];
	for (_RB_UT l_0 = 0; l_0 < ns.ch_bl; ++l_0)
	{
		_RB_CHT ch = ns.ch_p[l_0];
		*(_RB_MIT *)(ls_net_p + ls_net_bl) = lsm_c_bl_p[ch];
		ls_net_bl += sizeof(_RB_MIT);

		memcpy(ls_net_p + ls_net_bl, lsm_c_lb_m_p[ch], sizeof(LB_M) * lsm_c_bl_p[ch]);
		ls_net_bl += sizeof(LB_M) * lsm_c_bl_p[ch];
	}
}

void lsm_open()
{
	if (ls_file_p)
	{
		fread(lsm_c_bl_p, sizeof(_RB_MIT), _RB_CIBL * _RB_CIBL * _RB_CIBL, ls_file_p);

		for (_RB_MIT l_0 = 0; l_0 < _RB_CIBL * _RB_CIBL * _RB_CIBL; ++l_0)
			if (lsm_c_bl_p[l_0])
			{
				fread(lsm_c_mi_p[l_0], sizeof(_RB_MIT), lsm_c_bl_p[l_0], ls_file_p);
				fread(lsm_c_lb_m_p[l_0], sizeof(LB_M), lsm_c_bl_p[l_0], ls_file_p);
			}

		fread(&lsm_m_bl, sizeof(_RB_MIT), 1, ls_file_p);
		lsm_m_ch_p = malloc(sizeof(_RB_CHT) * lsm_m_bl);
		lsm_m_i_p = malloc(sizeof(_RB_MIT) * lsm_m_bl);
		fread(lsm_m_ch_p, sizeof(_RB_CHT), lsm_m_bl, ls_file_p);
		fread(lsm_m_i_p, sizeof(_RB_MIT), lsm_m_bl, ls_file_p);

		fread(&lsm_f_mi_bl, sizeof(_RB_MIT), 1, ls_file_p);
		lsm_f_mi_p = malloc(sizeof(_RB_MIT) * lsm_f_mi_bl);
		fread(lsm_f_mi_p, sizeof(_RB_MIT), lsm_f_mi_bl, ls_file_p);
	}
	else
	{
		lsm_m_ch_p = malloc(0);
		lsm_m_i_p = malloc(0);
		lsm_f_mi_p = malloc(0);

		//! test s
		//s0-test world init
		_RB_CHT ch = 0;
		_RB_MIT mi = lsm_m_bl;
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
	fwrite(lsm_c_bl_p, sizeof(_RB_MIT), _RB_CIBL * _RB_CIBL * _RB_CIBL, ls_file_p);
	for (_RB_MIT l_0 = 0; l_0 < _RB_CIBL * _RB_CIBL * _RB_CIBL; ++l_0)
		if (lsm_c_bl_p[l_0])
		{
			fwrite(lsm_c_mi_p[l_0], sizeof(_RB_MIT), lsm_c_bl_p[l_0], ls_file_p);
			fwrite(lsm_c_lb_m_p[l_0], sizeof(LB_M), lsm_c_bl_p[l_0], ls_file_p);
		}

	fwrite(&lsm_m_bl, sizeof(_RB_MIT), 1, ls_file_p);
	fwrite(lsm_m_ch_p, sizeof(_RB_CHT), lsm_m_bl, ls_file_p);
	fwrite(lsm_m_i_p, sizeof(_RB_MIT), lsm_m_bl, ls_file_p);

	fwrite(&lsm_f_mi_bl, sizeof(_RB_MIT), 1, ls_file_p);
	fwrite(lsm_f_mi_p, sizeof(_RB_MIT), lsm_f_mi_bl, ls_file_p);
}

void lsm_free()
{
	for (_RB_CHT l_0 = 0; l_0 < _RB_CIBL * _RB_CIBL * _RB_CIBL; ++l_0)
		if (lsm_c_bl_p[l_0])
		{
			free(lsm_c_mi_p[l_0]);
			free(lsm_c_lb_m_p[l_0]);
		}

	free(lsm_m_ch_p);
	free(lsm_m_i_p);
	free(lsm_f_mi_p);
}
