// mtx_t *ls_mtx_t_p = &(mtx_t){};

NALI_LB_MIT ls_m_bl = 0;
NALI_LB_MT *ls_m_p;
// NALI_LB_MIT *ls_m_i_p;
NALI_LB_CT *ls_m_c_p;
float *ls_m_rt_p;

// NALI_LB_MIT ls_r_m_bl = 0;
// NALI_LB_MIT *ls_r_m_i_p;

//sync c0 c1 ...
NALI_LB_PT *ls_net_bl_p;
uint8_t *ls_net_p;

#define NALI_LS_STATE_ON 1
static uint8_t ls_state;
void ls_set()
{
	// NALI_D_INFO("mtx_init %d", mtx_init(ls_mtx_t_p, mtx_plain))

	ls_state = NALI_LS_STATE_ON;

	ls_m_p = malloc(0);
	// ls_m_i_p = malloc(0);
	ls_m_c_p = malloc(0);
	ls_m_rt_p = malloc(0);

	ls_net_bl_p = malloc(0);
	ls_net_p = malloc(0);

	// ls_r_m_i_p = malloc(0);

	NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_USER, S_IRUSR | S_IWUSR | S_IXUSR))
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
			nls_send(l_0, ls_net_p + l_0 * NALI_LB_NET_BL, ls_net_bl_p[l_0]);
		}

		if (++tick == NALI_LB_MAX_TICK)
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

	// free(ls_r_m_i_p);

	free(ls_net_p);
	free(ls_net_bl_p);

	free(ls_m_rt_p);
	free(ls_m_c_p);
	// free(ls_m_i_p);
	free(ls_m_p);
	ls_m_bl = 0;

	// mtx_destroy(ls_mtx_t_p);

	return 0;
}

void ls_free()
{
	ls_state &= 0xFFu - NALI_LS_STATE_ON;
}