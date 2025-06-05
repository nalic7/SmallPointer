float ls_p_rt_p[NALI_NLS_MAX_CLIENT][3+3];
NALI_LB_CT ls_p_c_p[NALI_NLS_MAX_CLIENT][3];

NALI_LB_MT ls_m_bl_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX] = {0};
NALI_LB_MT ls_m_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX][NALI_LB_M8BL];
float *ls_m_rt_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX];

NALI_LB_MT ls_re_m_bl_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX] = {0};
NALI_LB_MT *ls_re_m_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX];

#define NALI_LS_STATE_ON 1
static uint8_t ls_state;
void ls_set()
{
	srand(time(NULL));

	ls_state = NALI_LS_STATE_ON;

	for (NALI_LB_CT l_0 = 0; l_0 < NALI_LB_CIBL; ++l_0)
		for (NALI_LB_CT l_1 = 0; l_1 < NALI_LB_CIBL; ++l_1)
			for (NALI_LB_CT l_2 = 0; l_2 < NALI_LB_CIBL; ++l_2)
				for (NALI_LB_MT l_3 = 0; l_3 < NALI_VD_M_MAX; ++l_3)
					ls_m_rt_p[l_0][l_1][l_2][l_3] = malloc(0);
}

static NALI_LB_CT ls_load_bl = 0;
static NALI_LB_CT *ls_load_p;
void ls_loop()
{
	while (ls_state & NALI_LS_STATE_ON)
	{
		//read file
		//map
		//e
		//send
		//check time 20/sec

		for (NALI_LB_CT l_0 = 0; l_0 < ls_load_bl; ++l_0)
		{
			ls_load_p[l_0 * sizeof(NALI_LB_CT) * 3];
		}
	}

	for (NALI_LB_CT l_0 = 0; l_0 < NALI_LB_CIBL; ++l_0)
		for (NALI_LB_CT l_1 = 0; l_1 < NALI_LB_CIBL; ++l_1)
			for (NALI_LB_CT l_2 = 0; l_2 < NALI_LB_CIBL; ++l_2)
				for (NALI_LB_MT l_3 = 0; l_3 < NALI_VD_M_MAX; ++l_3)
					free(ls_m_rt_p[l_0][l_1][l_2][l_3]);
}

void ls_free()
{
	ls_state &= 0xFFu - NALI_LS_STATE_ON;
}