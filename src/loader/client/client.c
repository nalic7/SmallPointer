NALI_LB_PT lc_net_bl = 0;
uint8_t lc_net_p[NALI_LB_NET_BL];

// float lc_delta = 0;

void lc_set()
{
	lcs_set();
	lckf_set();
	lcp_set();

	lcm_set();
	nc_set();

	s_state |= NALI_S_S_DATA_ABLE;
}

void lc_vk()
{
	while (!(s_state & NALI_S_S_DATA_ABLE))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	lcp_vk();
	lcs_vk();

	vk_cmd_draw_set();
	#ifdef C_NALI_S_ANDROID
		NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, vk_cmd_draw_loop, NULL))
	#else
		vk_cmd_draw_loop();
	#endif
}

static void lc_send()
{
	//! won't send time
	clock_gettime(CLOCK_MONOTONIC, (struct timespec *)lc_net_p);
	lc_net_bl = sizeof(struct timespec);

	lcu_send();

	nc_send();
}

static struct timespec lc_time = {0};
static struct timespec l_time;
void lc_read()
{
	l_time = *(struct timespec *)lc_net_p;

	if ((l_time.tv_sec > lc_time.tv_sec) || (l_time.tv_sec == lc_time.tv_sec && l_time.tv_nsec > lc_time.tv_nsec))
	{
		lc_net_bl = sizeof(struct timespec);

		lcm_re();

		lcu_read();
		lcm_read();

		lc_time = l_time;
	}
}

void lc_freeloop()
{
	nc_free();

	lcm_free();
	lcp_free();
	lcs_free();

	mtx_unlock(lb_mtx_t_p);
}

void lc_freeVk(uint32_t device)
{
	lcm_freeVk(device);
	lcs_freeVk(device);
	lcp_freeVk(device);
}

void lc_free()
{
	if (s_state & NALI_S_S_EXIT_C)
	{
		return;
	}
	s_state |= NALI_S_S_EXIT_C;

	mtx_lock(lb_mtx_t_p);

	s_state |= NALI_S_S_CLEAN;
}
