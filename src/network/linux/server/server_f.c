void (*nlsf_data_fp[NALI_NLS_DATA_FP_SIZE])(uint8_t *) = {nlsf_key_player, 0, 0};

void nlsf_read_data(uint8_t *data_p)
{
	if (*data_p != 255)
	{
		nlsf_data_fp[*data_p](data_p + 1);
	}
}

//new sync start loop after connect
void nlsf_new_player(uint8_t *data_p)
{
	NALI_LB_PT u = *(NALI_LB_PT *)data_p;

	//random spawn
	ls_p_c_p[u][0] = rand() % NALI_LB_CIBL;
	ls_p_c_p[u][1] = rand() % NALI_LB_CIBL;
	ls_p_c_p[u][2] = rand() % NALI_LB_CIBL;

	//world / space
	//-NALI_LB_CFBL 0 NALI_LB_CFBL
	memset(ls_p_rt_p[u], 0, sizeof(float) * (3 + 3));
}

void nlsf_sync_player(NALI_LB_PT u)
{
	//client need
	//send
	ls_p_c_p[u];
	ls_p_rt_p[u];
}

void nlsf_key_player(NALI_LB_PT u, uint16_t key)
{
	if (key & NALI_NLB_S_KEY_W)
	{

	}
}

void nlsf_add_model(NALI_LB_CT x, NALI_LB_CT y, NALI_LB_CT z, NALI_LB_MT m0, float rt_p[3 + 3])
{
	NALI_LB_MT m1;
	if (ls_re_m_bl_p[x][y][z][m0])
	{
		m1 = ls_re_m_p[x][y][z][m0][--ls_re_m_bl_p[x][y][z][m0]];
		ls_re_m_p[x][y][z][m0] = realloc(ls_re_m_p[x][y][z][m0], sizeof(NALI_LB_MT) * (ls_re_m_bl_p[x][y][z][m0]));
	}
	else
	{
		m1 = ls_m_bl_p[x][y][z][m0];
	}
	++ls_m_bl_p[x][y][z][m0];
	ls_m_p[x][y][z][m0][m1 / 8] ^= 1 << m1 % 8;

	ls_m_rt_p[x][y][z][m0] = realloc(ls_m_rt_p[x][y][z][m0], sizeof(float) * (3 + 3) * ls_m_bl_p[x][y][z][m0]);
	memcpy(ls_m_rt_p[x][y][z][m0] + m1 * (3 + 3), rt_p, sizeof(float) * (3 + 3));
}

//C[X|Y|Z] M[0|1] *

//0 1 2 -> 3
//R/C 1 2 -> 2
//0 1 2 -> 3
void nlsf_rm_model(NALI_LB_CT x, NALI_LB_CT y, NALI_LB_CT z, NALI_LB_MT m0, NALI_LB_MT m1)
{
	ls_m_p[x][y][z][m0][m1 / 8] ^= 1 << m1 % 8;

	ls_re_m_p[x][y][z][m0][ls_re_m_bl_p[x][y][z][m0]] = m1;
	ls_re_m_p[x][y][z][m0] = realloc(ls_re_m_p[x][y][z][m0], sizeof(NALI_LB_MT) * (ls_re_m_bl_p[x][y][z][m0] + 1));
	++ls_re_m_bl_p[x][y][z][m0];

	--ls_m_bl_p[x][y][z][m0];
	ls_m_rt_p[x][y][z][m0] = realloc(ls_m_rt_p[x][y][z][m0], sizeof(float) * (3 + 3) * ls_m_bl_p[x][y][z][m0]);
}