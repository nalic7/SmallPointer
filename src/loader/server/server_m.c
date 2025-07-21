// void (*lsm_fp[NALI_LB_FP_BL])(NALI_LB_MIT mi) =
// {
// 	espomi0_set
// };

NALI_LB_MIT lsm_i_p[NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL];
LB_M **lsm_lb_m_p;
NALI_LB_MIT *lsm_bl_p;
NALI_LB_MIT lsm_bl = 0;

static NALI_LB_MIT _update = 0;
static NALI_LB_MIT *_re_update_p;
static NALI_LB_MIT _re_update_bl = 0;

void lsm_ad_m(NALI_LB_CHT ch/* , NALI_LB_MST ms */)
{
	NALI_LB_MIT mi = lsm_i_p[ch];
	if (mi != NALI_LB_MIN)
	{
		if (lsm_bl == NALI_LB_MIM)
		{
			return;
		}

		mi = lsm_bl;
		lsm_lb_m_p = realloc(lsm_lb_m_p, sizeof(LB_M *) * ++lsm_bl);
		lsm_bl_p = realloc(lsm_bl_p, sizeof(NALI_LB_MIT) * lsm_bl);
		lsm_bl_p[mi] = 0;
		lsm_lb_m_p[mi] = malloc(0);
		lsm_i_p[ch] = mi;
	}
	else if (mi == NALI_LB_MIM)
	{
		return;
	}
	lsm_lb_m_p[mi] = realloc(lsm_lb_m_p[mi], sizeof(LB_M) * (lsm_bl_p[mi] + 1));
	// lsm_lb_m_p[mi][lsm_bl_p[mi]].m = lb_ms_p[ms];
	// lsm_fp[ms](mi);

	if (_re_update_bl)
		lsm_lb_m_p[mi][lsm_bl_p[mi]].update = _re_update_p[--_re_update_bl];
	else
		lsm_lb_m_p[mi][lsm_bl_p[mi]].update = _update;
	++_update;

	++lsm_bl_p[mi];
}

// void lsm_mv_m(NALI_LB_CHT ch, NALI_LB_MIT a_mi, NALI_LB_MIT b_mi)
// {
// 	lsm_p[ch][a_mi] = lsm_p[ch][lsm_bl_p[b_mi]];
// }

// void lsm_mv1_m(NALI_LB_CHT a_ch, NALI_LB_CHT b_ch, NALI_LB_MIT a_mi, NALI_LB_MIT b_mi)
// {
// 	lsm_p[a_ch][a_mi] = lsm_p[b_ch][lsm_bl_p[b_mi]];
// }

void lsm_rm_m(NALI_LB_CHT ch, NALI_LB_MIT mii)
{
	NALI_LB_MIT mi = lsm_i_p[ch];

	_re_update_p[_re_update_bl] = lsm_lb_m_p[mi][mii].update;
	++_re_update_bl;

	if (--lsm_bl_p[mi])
	{
		lsm_lb_m_p[mi][mii] = lsm_lb_m_p[lsm_bl_p[mi]][mii];
		lsm_lb_m_p[mi] = realloc(lsm_lb_m_p[mi], sizeof(LB_M) * lsm_bl_p[mi]);
	}
	else
	{
		free(lsm_lb_m_p[mi]);
		lsm_lb_m_p[mi] = lsm_lb_m_p[--lsm_bl];
		lsm_lb_m_p = realloc(lsm_lb_m_p, sizeof(LB_M *) * lsm_bl);

		lsm_bl_p[mi] = lsm_bl_p[lsm_bl];
		lsm_bl_p = realloc(lsm_bl_p, sizeof(NALI_LB_MIT) * lsm_bl);

		lsm_i_p[ch] = NALI_LB_MIN;
	}

	--_update;
}

void lsm_update()
{
	//ai & path
	//select which m should update in / off
	// for (NALI_LB_MIT l_0 = 0; l_0 < lsm_bl; ++l_0)
	// {
	// 	for (NALI_LB_MIT l_1 = 0; l_1 < lsm_bl_p[l_0]; ++l_1)
	// 	{
	// 		// lsm_lb_m_p[l_0][l_1];
	// 	}
	// }
}

void lsm_send(NALI_LB_UT u)
{
	//should check in view before send?
	for (NALI_LB_UT l_0 = 0; l_0 < ns_p[u].ch_bl; ++l_0)
	{
		NALI_LB_MIT mi = lsm_i_p[ns_p[u].ch_p[l_0]];

		*(NALI_LB_MIT *)(ls_net_p + ls_net_bl) = lsm_bl_p[mi];
		ls_net_bl += sizeof(NALI_LB_MIT);

		memcpy(ls_net_p + ls_net_bl, lsm_lb_m_p[mi], sizeof(LB_M) * lsm_bl_p[mi]);
		ls_net_bl += sizeof(LB_M) * lsm_bl_p[mi];
	}
}

void lsm_open()
{
	for (NALI_LB_CHT l_0 = 0; l_0 < NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL; ++l_0)
	{
		lsm_i_p[l_0] = NALI_LB_MIN;
	}

	lsm_lb_m_p = malloc(0);

	if (ls_file_p)
	{
		fread(lsm_i_p, sizeof(NALI_LB_MIT), NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL, ls_file_p);
		fread(&lsm_bl, sizeof(NALI_LB_MIT), 1, ls_file_p);

		lsm_bl_p = malloc(sizeof(NALI_LB_MIT) * lsm_bl);
		uint32_t l0 = 0;
		for (NALI_LB_MIT l_0 = 0; l_0 < lsm_bl; ++l_0)
		{
			fread(lsm_bl_p + l_0, sizeof(NALI_LB_MIT), 1, ls_file_p);

			l0 += sizeof(LB_M) * lsm_bl_p[l_0];
			lsm_lb_m_p = realloc(lsm_lb_m_p, l0);
			fread(lsm_lb_m_p[l_0], sizeof(LB_M), lsm_bl_p[l_0], ls_file_p);
		}

		fread(&_re_update_bl, sizeof(NALI_LB_MIT), 1, ls_file_p);
		_re_update_p = malloc(_re_update_bl);
		fread(_re_update_p, sizeof(NALI_LB_MIT), _re_update_bl, ls_file_p);
	}
	else
	{
		//s0-test world init
		NALI_LB_CHT ch = 0;
		NALI_LB_MIT mi = lsm_i_p[ch];
		lsm_ad_m(ch/* , NALI_EBPOMI0_MS */);
		memset(lsm_lb_m_p[mi][lsm_bl_p[mi] - 1].rt_p, 0, sizeof(float) * (3 + 2));
		//set model attribute
		lsm_lb_m_p[mi][lsm_bl_p[mi] - 1].m = NALI_EBPOMI0_M;
		lsm_lb_m_p[mi][lsm_bl_p[mi] - 1].ma = NALI_EBPOMI0_MA;
		//set animate
		lsm_lb_m_p[mi][lsm_bl_p[mi] - 1].a = NALI_EBPOMI0_A;
		lsm_lb_m_p[mi][lsm_bl_p[mi] - 1].af = 0;
		//ai / math can call in
		//e0-test world init

		//s0-test rm
		// lsm_rm_m(ch, 0);
		//e0-test rm

		lsm_bl_p = malloc(0);
		_re_update_p = malloc(0);
	}
}

void lsm_save()
{
	fwrite(lsm_i_p, sizeof(NALI_LB_MIT), NALI_LB_CIBL * NALI_LB_CIBL * NALI_LB_CIBL, ls_file_p);
	fwrite(&lsm_bl, sizeof(NALI_LB_MIT), 1, ls_file_p);

	for (NALI_LB_MIT l_0 = 0; l_0 < lsm_bl; ++l_0)
	{
		fwrite(lsm_bl_p + l_0, sizeof(NALI_LB_MIT), 1, ls_file_p);
		fwrite(lsm_lb_m_p[l_0], sizeof(LB_M), lsm_bl_p[l_0], ls_file_p);
	}

	fwrite(&_re_update_bl, sizeof(NALI_LB_MIT), 1, ls_file_p);
	fwrite(_re_update_p, sizeof(NALI_LB_MIT), _re_update_bl, ls_file_p);
}

void lsm_free()
{
	for (NALI_LB_MIT l_0 = 0; l_0 < lsm_bl; ++l_0)
	{
		free(lsm_lb_m_p[l_0]);
	}

	free(lsm_lb_m_p);
	free(lsm_bl_p);
}