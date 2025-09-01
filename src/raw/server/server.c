FILE *ls_file_p;

_RB_PT ls_net_bl;
uint8_t ls_net_p[_RB_NET_BL];

#define _RS_STATE_ON 1
static uint8_t ls_state;

void ls_set()
{
	_DB_R2L("mkdir %d", mkdir(NALI_F_SAVE, S_IRUSR | S_IWUSR | S_IXUSR))

	ls_state = _RS_STATE_ON;

	ns_set();

	ls_open();

	#ifdef _CM_CLIENT
		_DB_R2L("thrd_create %d", thrd_create(&(thrd_t){}, ls_loop, NULL))
	#else
		ls_loop();
	#endif
}

static void ls_send()
{
	clock_gettime(CLOCK_MONOTONIC, (struct timespec *)ls_net_p);

	for (_RB_UT l_0 = 0; l_0 < _RB_UM; ++l_0)
	{
		ls_net_bl = sizeof(struct timespec);

		lsu_send(l_0);
		lsm_send(l_0);

		ns_send(l_0);
	}
}

static struct timespec ls_time = {0};
static struct timespec l_time;
void ls_read(_RB_UT u)
{
	l_time = *(struct timespec *)ls_net_p;

	if ((l_time.tv_sec > ls_time.tv_sec) || (l_time.tv_sec == ls_time.tv_sec && l_time.tv_nsec > ls_time.tv_nsec))
	{
		ls_net_bl = sizeof(struct timespec);

		lsu_read(u);

		ls_time = l_time;
	}
}

void ls_open()
{
	_DB_R2L("fopen %p", ls_file_p = fopen(NALI_F_SAVE_SPACE, "rb"))

	lsu_open();
	lsm_open();

	if (ls_file_p)
	{
		fclose(ls_file_p);
	}
}

void ls_save()
{
	_DB_R2L("fopen %p", ls_file_p = fopen(NALI_F_SAVE_SPACE, "wb"))

	lsu_save();
	lsm_save();

	fclose(ls_file_p);
}

static _RB_CT ls_load_bl = 0;
static _RB_CT *ls_load_p;
#ifdef _CM_CLIENT
	int ls_loop(void *p)
#else
	void ls_loop()
#endif
{
	//rand_r
	//use in thread only
	srand(time(NULL));

	uint8_t tick = 0;
	struct timespec tick_start, tick_end, tick_sleep = {0};
	double sleep;
	clock_gettime(CLOCK_MONOTONIC, &tick_start);
	while (ls_state & _RS_STATE_ON)
	{
		//read file
		//map
		//e

		//sync
		// lsc_sync_u();

		// for (_RB_CT l_0 = 0; l_0 < ls_load_bl; ++l_0)
		// {
		// 	ls_load_p[l_0 * sizeof(_RB_CT) * 3];
		// }

		ns_get();
		lsu_update();
		lsm_update();
		ls_send();
		ns_check();

		if (++tick == _RS_MAX_RW)
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

	ls_save();

	ns_free();

	lsm_free();

	mtx_unlock(lb_mtx_t_p);

	#ifdef _CM_CLIENT
		return 0;
	#endif
}

void ls_free()
{
	mtx_lock(lb_mtx_t_p);

	ls_state &= 0xFFu - _RS_STATE_ON;
}
