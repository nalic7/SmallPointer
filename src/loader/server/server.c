float ls_u_rt_p[NALI_LB_MAX_CLIENT][3+3];
NALI_LB_CT ls_u_c_p[NALI_LB_MAX_CLIENT][3];

NALI_LB_MT ls_m_bl_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX] = {0};
NALI_LB_MT ls_m_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX][NALI_LB_M8BL];
float *ls_m_rt_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX];

NALI_LB_MT ls_re_m_bl_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX] = {0};
NALI_LB_MT *ls_re_m_p[NALI_LB_CIBL][NALI_LB_CIBL][NALI_LB_CIBL][NALI_VD_M_MAX];

//sync c0 c1 ...
uint16_t ls_net_bl_p[NALI_LB_MAX_CLIENT] = {0};
uint8_t ls_net_p[NALI_LB_MAX_CLIENT][sizeof(uint16_t) + sizeof(float) * (3 + 3) + sizeof(NALI_LB_CT) * 3 + NALI_LS_NET_BL];

#define NALI_LS_STATE_ON 1
static uint8_t ls_state;
void ls_set()
{
	ls_state = NALI_LS_STATE_ON;

	for (NALI_LB_CT l_0 = 0; l_0 < NALI_LB_CIBL; ++l_0)
		for (NALI_LB_CT l_1 = 0; l_1 < NALI_LB_CIBL; ++l_1)
			for (NALI_LB_CT l_2 = 0; l_2 < NALI_LB_CIBL; ++l_2)
				for (NALI_LB_MT l_3 = 0; l_3 < NALI_VD_M_MAX; ++l_3)
					ls_m_rt_p[l_0][l_1][l_2][l_3] = malloc(0);

	NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_USER, S_IRUSR | S_IWUSR | S_IXUSR))
	for (NALI_LB_UT l_0 = 0; l_0 < NALI_LB_MAX_CLIENT; ++l_0)
	{
		uint8_t n_bl = MATH_LENGTH(l_0);
		// char *c_p = malloc(sizeof(NALI_F_SAVE_USER) - 1 + n + 1);
		char *c_p = malloc(sizeof(NALI_F_SAVE_USER) + n_bl);
		c_p[sizeof(NALI_F_SAVE_USER) - 1 + n_bl] = 0;

		memcpy(c_p, NALI_F_SAVE_USER, sizeof(NALI_F_SAVE_USER) - 1);
		sprintf(c_p + sizeof(NALI_F_SAVE_USER) - 1, "%d", l_0);

		FILE *file_p = fopen(c_p, "r");

		if (file_p)
		{
			uint32_t file_bl;
			void* data_p = f_read1(file_p, &file_bl);

			memcpy(ls_u_rt_p[l_0], data_p, sizeof(float) * (3 + 3));
			memcpy(ls_u_c_p[l_0], data_p + sizeof(float) * (3 + 3), sizeof(NALI_LB_CT) * 3);

			free(data_p);
		}
		else
		{
			//random spawn
			ls_u_c_p[l_0][0] = rand() % NALI_LB_CIBL;
			ls_u_c_p[l_0][1] = rand() % NALI_LB_CIBL;
			ls_u_c_p[l_0][2] = rand() % NALI_LB_CIBL;

			//world / space
			//-NALI_LB_CFBL 0 NALI_LB_CFBL
			memset(ls_u_rt_p[l_0], 0, sizeof(float) * (3 + 3));
		}
		free(c_p);
	}

	NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_USER_ITEM, S_IRUSR | S_IWUSR | S_IXUSR))
	NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_USER_TEAM, S_IRUSR | S_IWUSR | S_IXUSR))

	NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_MAP, S_IRUSR | S_IWUSR | S_IXUSR))

	NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, ls_loop, NULL))
}

static NALI_LB_CT ls_load_bl = 0;
static NALI_LB_CT *ls_load_p;
int ls_loop(void *p)
{
	//rand_r
	//use in thread only
	srand(time(NULL));

	uint8_t tick = 0;
	struct timespec tick_start, tick_end, tick_sleep = {0};
	double sleep;
	clock_gettime(CLOCK_MONOTONIC, &tick_start);
	while (ls_state & NALI_LS_STATE_ON)
	{
		//read file
		//map
		//e

		for (NALI_LB_CT l_0 = 0; l_0 < ls_load_bl; ++l_0)
		{
			ls_load_p[l_0 * sizeof(NALI_LB_CT) * 3];
		}

		//send
		for (NALI_LB_UT l_0 = 0; l_0 < NALI_LB_MAX_CLIENT; ++l_0)
		{
			nls_send(l_0, ls_net_p[l_0], ls_net_bl_p[l_0]);
		}

		if (++tick == NALI_LS_MAX_TICK)
		{
			clock_gettime(CLOCK_MONOTONIC, &tick_end);
			sleep = tick_end.tv_sec + (double)tick_end.tv_nsec / 1e9 - tick_start.tv_sec - (double)tick_start.tv_nsec / 1e9;
			if (sleep < 1.0)
			{
				tick_sleep.tv_nsec = (1.0 - sleep) * 1e9;
				thrd_sleep(&tick_sleep, NULL);
			}
			tick = 0;
		}
	}

	for (NALI_LB_CT l_0 = 0; l_0 < NALI_LB_CIBL; ++l_0)
		for (NALI_LB_CT l_1 = 0; l_1 < NALI_LB_CIBL; ++l_1)
			for (NALI_LB_CT l_2 = 0; l_2 < NALI_LB_CIBL; ++l_2)
				for (NALI_LB_MT l_3 = 0; l_3 < NALI_VD_M_MAX; ++l_3)
					free(ls_m_rt_p[l_0][l_1][l_2][l_3]);

	return 0;
}

void ls_free()
{
	ls_state &= 0xFFu - NALI_LS_STATE_ON;
}