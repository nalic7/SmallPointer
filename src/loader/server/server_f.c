void (*nlsf_data_fp[NALI_NLS_DATA_FP_SIZE])(uint8_t *) = {nlsf_key_player};

//package won't pack
// void nlsf_read_data(uint8_t *data_p)
// {
// 	if (*data_p != 255)
// 	{
// 		nlsf_data_fp[*data_p](data_p + 1);
// 	}
// }

void nlsf_key_player(uint8_t *data_p)
{
	NALI_LB_UT u = *(NALI_LB_UT *)data_p;
	data_p += sizeof(NALI_LB_UT);

	uint16_t key = *(uint16_t *)data_p;
	data_p += sizeof(uint16_t);

	if (key & NALI_NLB_S_KEY_W)
	{

	}
	// nlsf_read_data(data_p);
}

//sync entity / map

static void nlsf_add_model(NALI_LB_CT x, NALI_LB_CT y, NALI_LB_CT z, NALI_LB_MT m0, float rt_p[3 + 3])
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
static void nlsf_rm_model(NALI_LB_CT x, NALI_LB_CT y, NALI_LB_CT z, NALI_LB_MT m0, NALI_LB_MT m1)
{
	ls_m_p[x][y][z][m0][m1 / 8] ^= 1 << m1 % 8;

	ls_re_m_p[x][y][z][m0][ls_re_m_bl_p[x][y][z][m0]] = m1;
	ls_re_m_p[x][y][z][m0] = realloc(ls_re_m_p[x][y][z][m0], sizeof(NALI_LB_MT) * (ls_re_m_bl_p[x][y][z][m0] + 1));
	++ls_re_m_bl_p[x][y][z][m0];

	--ls_m_bl_p[x][y][z][m0];
	ls_m_rt_p[x][y][z][m0] = realloc(ls_m_rt_p[x][y][z][m0], sizeof(float) * (3 + 3) * ls_m_bl_p[x][y][z][m0]);
}