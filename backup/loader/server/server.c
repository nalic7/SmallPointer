FILE *ls_file_p;

mtx_t *ls_mtx_t_p = &(mtx_t){};

NALI_LB_PT ls_net_bl;
uint8_t ls_net_p[NALI_LB_NET_BL];

#define NALI_LS_STATE_ON 1
static uint8_t ls_state;
void ls_set()
{
	NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE, S_IRUSR | S_IWUSR | S_IXUSR))
	NALI_D_INFO("fopen %d", ls_file_p = fopen(NALI_F_SAVE_SPACE, "rb"))
	if (ls_file_p)
	{
		uint32_t data_bl;
		uint8_t *data_p = f_read1(ls_file_p, &data_bl);
		free(data_p);
	}
	NALI_D_INFO("fopen %d", ls_file_p = fopen(NALI_F_SAVE_SPACE, "wb"))

	NALI_D_INFO("mtx_init %d", mtx_init(ls_mtx_t_p, mtx_plain))

	ls_state = NALI_LS_STATE_ON;

	lsu_set();

	lsm_set();

	// NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_USER, S_IRUSR | S_IWUSR | S_IXUSR))
	// NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_USER_ITEM, S_IRUSR | S_IWUSR | S_IXUSR))
	// NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_USER_TEAM, S_IRUSR | S_IWUSR | S_IXUSR))

	// NALI_D_INFO("mkdir %d", mkdir(NALI_F_SAVE_MAP, S_IRUSR | S_IWUSR | S_IXUSR))

	NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, ls_loop, NULL))

	nls_set();
}

void ls_re()
{
	fclose(ls_file_p);

	lsu_re();
	lsm_re();
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

	fclose(ls_file_p);

	lsu_free();
	lsm_free();

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

	nls_state |= NALI_NS_FAIL;

	ls_state &= 0xFFu - NALI_LS_STATE_ON;
}