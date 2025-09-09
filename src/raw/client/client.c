SMPTRtNET smptr_ceLnet = 0;
uint8_t smptr_cePnet[SMPTRlNET];

void smptr_ceMset()
{
	lckf_set();
	lcp_set();

	smptr_cemMset();
	#ifndef SMPT_CM_RAW
		nc_set();
	#endif

	_sf_state |= _SF_S_RAW;
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

#ifndef SMPT_CM_RAW
	static struct timespec lc_time = {0};
	static struct timespec l_time;
#endif
void smptr_ceMread()
{
	#ifdef SMPT_CM_RAW
		smpt_rd_vk_swc_frame_buffer = (smpt_rd_vk_swc_frame_buffer + 1) % smpt_rd_vk_swc_image;
		smptr_cemMread();
	#else
		l_time = *(struct timespec *)smptr_cePnet;

		if ((l_time.tv_sec > lc_time.tv_sec) || (l_time.tv_sec == lc_time.tv_sec && l_time.tv_nsec > lc_time.tv_nsec))
		{
			smpt_rd_vk_swc_frame_buffer = (smpt_rd_vk_swc_frame_buffer + 1) % smpt_rd_vk_swc_image;
			smptr_ceLnet = sizeof(struct timespec);

			smptr_cemMread();

			lc_time = l_time;
		}
	#endif
}

void smptr_ceMfree(uint32_t device)
{
	#ifndef SMPT_CM_RAW
		nc_free();
	#endif

	#ifdef SMPT_CM_VK
		while (!(_sf_state & _SF_S_EXIT_RENDER))
		{
			SMPT_DBmN2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
			SMPT_DBmN2L("_sf_state %d", _sf_state)
		}

		SMPT_DBmR2L("vkQueueWaitIdle %d", vkQueueWaitIdle(smpt_rd_vkq_p[smpt_rd_vk_device][smpt_rd_vk_queue_g]))

		smptr_cemMfree();
		smpt_rd_vkw_dstsp_free(device);
		smpt_rd_vkw_dsts_lo_free(device);

		lcp_free(device);
		smpt_rd_vk_cmd_free();
	#endif
}
