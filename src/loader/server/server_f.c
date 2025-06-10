void (*nlsf_data_fp[NALI_LSF_DATA_FP_SIZE])(NALI_LB_UT ui, uint8_t *) = {lsf_key_user};

//package won't pack
// void nlsf_read_data(uint8_t *data_p)
// {
// 	if (*data_p != 255)
// 	{
// 		nlsf_data_fp[*data_p](data_p + 1);
// 	}
// }

void lsf_new_user(NALI_LB_UT ui)
{
	uint8_t n_bl = MATH_LENGTH(nls_u_p[ui]);
	// char *c_p = malloc(sizeof(NALI_F_SAVE_USER) - 1 + n + 1);
	char *c_p = malloc(sizeof(NALI_F_SAVE_USER) + n_bl);
	c_p[sizeof(NALI_F_SAVE_USER) - 1 + n_bl] = 0;

	memcpy(c_p, NALI_F_SAVE_USER, sizeof(NALI_F_SAVE_USER) - 1);
	sprintf(c_p + sizeof(NALI_F_SAVE_USER) - 1, "%d", nls_u_p[ui]);

	FILE *file_p = fopen(c_p, "r");

	if (file_p)
	{
		uint32_t file_bl;
		void* data_p = f_read1(file_p, &file_bl);

		memcpy(nls_u_rt_p + ui * (3 + 3), data_p, sizeof(float) * (3 + 3));
		memcpy(nls_u_c_p + ui * 3, data_p + sizeof(float) * (3 + 3), sizeof(NALI_LB_CT) * 3);

		free(data_p);
	}
	else
	{
		//random spawn
		nls_u_c_p[ui * 3] = rand() % NALI_LB_CIBL;
		nls_u_c_p[ui * 3 + 1] = rand() % NALI_LB_CIBL;
		nls_u_c_p[ui * 3 + 2] = rand() % NALI_LB_CIBL;

		//world / space
		//-NALI_LB_CFBL 0 NALI_LB_CFBL
		memset(nls_u_rt_p + ui * (3 + 3), 0, sizeof(float) * (3 + 3));
	}
	free(c_p);
}

//need in thread

void lsf_key_user(NALI_LB_UT ui, uint8_t *data_p)
{
	NALI_LB_UT u = nls_u_p[ui];

	uint16_t key = *(uint16_t *)data_p;
	data_p += sizeof(uint16_t);

	if (key & NALI_LB_S_KEY_W)
	{

	}
	// nlsf_read_data(data_p);
}

//sync entity / map

static void lsf_new_model(NALI_LB_MT m, NALI_LB_CT c_p[3], float rt_p[3 + 3])
{
	ls_m_p = realloc(ls_m_p, sizeof(NALI_LB_MT) * (ls_m_bl + 1));
	// ls_m_i_p = realloc(ls_m_i_p, sizeof(NALI_LB_MIT) * (ls_m_bl + 1));
	ls_m_c_p = realloc(ls_m_c_p, sizeof(NALI_LB_CT) * 3 * (ls_m_bl + 1));
	ls_m_rt_p = realloc(ls_m_rt_p, sizeof(float) * (3 + 3) * (ls_m_bl + 1));

	ls_m_p[ls_m_bl] = m;
	// ls_m_i_p[ls_m_bl] = ls_m_bl;
	memcpy(ls_m_c_p + ls_m_bl * sizeof(NALI_LB_CT) * 3, c_p, sizeof(NALI_LB_CT) * 3);
	memcpy(ls_m_rt_p + ls_m_bl * sizeof(NALI_LB_CT) * (3 + 3), rt_p, sizeof(NALI_LB_CT) * (3 + 3));
	++ls_m_bl;
}
static void lsf_rm_model(NALI_LB_MIT mi)
{
	ls_m_p[mi] = ls_m_p[--ls_m_bl];
	// ls_m_i_p[mi] = ls_m_i_p[ls_m_bl];
	memcpy(ls_m_c_p + mi * sizeof(NALI_LB_CT) * 3, ls_m_c_p + ls_m_bl * sizeof(NALI_LB_CT) * 3, sizeof(NALI_LB_CT) * 3);
	memcpy(ls_m_rt_p + mi * sizeof(float) * (3 + 3), ls_m_rt_p + ls_m_bl * sizeof(float) * (3 + 3), sizeof(float) * (3 + 3));
	ls_m_p = realloc(ls_m_p, sizeof(NALI_LB_MT) * ls_m_bl);
	// ls_m_i_p = realloc(ls_m_i_p, sizeof(NALI_LB_MIT) * ls_m_bl);
	ls_m_c_p = realloc(ls_m_c_p, sizeof(NALI_LB_CT) * 3 * ls_m_bl);
	ls_m_rt_p = realloc(ls_m_rt_p, sizeof(float) * (3 + 3) * ls_m_bl);

	//update ls_m_bl to mi

	// ls_r_m_i_p = realloc(ls_r_m_i_p, sizeof(NALI_LB_MIT) * (ls_r_m_bl + 1));
	// ls_r_m_i_p[ls_r_m_bl] = mi;
	// ++ls_r_m_bl;
}