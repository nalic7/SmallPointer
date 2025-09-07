SMPTRB_PT smptr_ceLnet = 0;
uint8_t smptr_cePnet[SMPTRB_NET_BL];

// float lc_delta = 0;

void lc_set()
{
	lckf_set();
	lcp_set();

	smptr_cemMset();
	#ifndef SMPT_CM_RAW
		nc_set();
	#endif

	_sf_state |= _SF_S_RAW;
}

void lc_vk()
{
	while (!(_sf_state & _SF_S_RAW))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	lcp_vk();
	smpt_rd_vkw_dsts_lo_make(smpt_rd_vk_device);
	smpt_rd_vkw_dstsp_make(smpt_rd_vk_device);

	smpt_rd_vk_cmd_set();
	SMPT_DB_R2L("thrd_create %d", thrd_create(&(thrd_t){}, smpt_rd_vk_cmd_loop, NULL))
}

static void lc_send()
{
	//! won't send time
	clock_gettime(CLOCK_MONOTONIC, (struct timespec *)smptr_cePnet);
	smptr_ceLnet = sizeof(struct timespec);

	//! net
	//lcu_send();

	//! net
	//nc_send();
}

static struct timespec lc_time = {0};
static struct timespec l_time;
void lc_read()
{
	l_time = *(struct timespec *)smptr_cePnet;

	if ((l_time.tv_sec > lc_time.tv_sec) || (l_time.tv_sec == lc_time.tv_sec && l_time.tv_nsec > lc_time.tv_nsec))
	{
		smptr_ceLnet = sizeof(struct timespec);

		//! net
		//lcm_re();

		//! net
		//lcu_read();
		//lcm_read();

		lc_time = l_time;
	}
}

void lc_free(uint32_t device)
{
	#if SMPT_CM_CLIENT && SMPT_CM_SERVER
		mtx_lock(lb_mtx_t_p);
	#endif

	#ifndef SMPT_CM_RAW
		nc_free();
	#endif

	#ifdef SMPT_CM_VK
		while (!(_sf_state & _SF_S_EXIT_RENDER))
		{
			SMPT_DB_N2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
			SMPT_DB_N2L("_sf_state %d", _sf_state)
		}

		SMPT_DB_R2L("vkQueueWaitIdle %d", vkQueueWaitIdle(smpt_rd_vkq_p[smpt_rd_vk_device][smpt_rd_vk_queue_g]))

		smptr_cemMfree();
		smpt_rd_vkw_dstsp_free(device);
		smpt_rd_vkw_dsts_lo_free(device);

		lcp_free(device);
		smpt_rd_vk_cmd_free();
	#endif

	#if SMPT_CM_CLIENT && SMPT_CM_SERVER
		mtx_unlock(lb_mtx_t_p);
	#endif
}
