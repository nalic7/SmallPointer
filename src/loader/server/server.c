mtx_t *ls_mtx_t_p = &(mtx_t){};

NALI_LB_UT ls_u_bl = 0;
NALI_LB_UT *ls_u_p;
float *ls_urt_p;
NALI_LB_CT *ls_uc_p;

NALI_LB_MIT ls_m_bl = 0;
NALI_LB_MT *ls_m_p;
NALI_LB_CT *ls_mc_p;
float *ls_mrt_p;

NALI_LB_PT ls_net_bl = 0;
uint8_t ls_net_p[NALI_LB_NET_BL];

#define NALI_LS_STATE_ON 1
static uint8_t ls_state;
void ls_set()
{
	NALI_D_INFO("mtx_init %d", mtx_init(ls_mtx_t_p, mtx_plain))

	ls_state = NALI_LS_STATE_ON;

	ls_u_p = malloc(0);
	ls_urt_p = malloc(0);
	ls_uc_p = malloc(0);

	ls_m_p = malloc(0);
	ls_mc_p = malloc(0);
	ls_mrt_p = malloc(0);

	lsc_set();

	NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_USER, S_IRUSR | S_IWUSR | S_IXUSR))
	NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_USER_ITEM, S_IRUSR | S_IWUSR | S_IXUSR))
	NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_USER_TEAM, S_IRUSR | S_IWUSR | S_IXUSR))

	NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_MAP, S_IRUSR | S_IWUSR | S_IXUSR))

	NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, ls_loop, NULL))

	nls_set();
}

void ls_re()
{
	ls_u_bl = 0;
	ls_u_p = realloc(ls_u_p, 0);
	ls_urt_p = realloc(ls_urt_p, 0);
	ls_uc_p = realloc(ls_uc_p, 0);

	ls_m_bl = 0;
	ls_m_p = realloc(ls_m_p, 0);
	ls_mc_p = realloc(ls_mc_p, 0);
	ls_mrt_p = realloc(ls_mrt_p, 0);
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
		mtx_lock(ls_mtx_t_p);

		//read file
		//map
		//e

		//sync
		// lsc_sync_u();

		// for (NALI_LB_CT l_0 = 0; l_0 < ls_load_bl; ++l_0)
		// {
		// 	ls_load_p[l_0 * sizeof(NALI_LB_CT) * 3];
		// }

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

		mtx_unlock(ls_mtx_t_p);
	}

	mtx_lock(ls_mtx_t_p);

	lsc_free();

	free(ls_uc_p);
	free(ls_urt_p);
	free(ls_u_p);
	ls_u_bl = 0;

	ls_net_bl = 0;

	free(ls_mrt_p);
	free(ls_mc_p);
	free(ls_m_p);
	ls_m_bl = 0;

	mtx_destroy(ls_mtx_t_p);

	mtx_unlock(lb_mtx_t_p);

	return 0;
}

void ls_free()
{
	if (s_surface_state & NALI_S_S_EXIT_S)
	{
		return;
	}
	s_surface_state |= NALI_S_S_EXIT_S;

	mtx_lock(lb_mtx_t_p);
	mtx_lock(ls_mtx_t_p);

	nls_state |= NALI_NLS_FAIL;

	ls_state &= 0xFFu - NALI_LS_STATE_ON;
}