uint8_t smptr_cePnet[SMPTRlNET];
SMPTRtNET smptr_ceLnet = 0;

void smptr_ceMset()
{
	lckf_set();
	lcp_set();

	smptr_cemMset();
	nc_set();

	smpt_sfUstate |= SMPT_SFuS_RAW;
}

void smptr_ceMsend()
{
	clock_gettime(CLOCK_MONOTONIC, (struct timespec *)smptr_cePnet);
	smptr_ceLnet = sizeof(struct timespec);

	//SMPT_DBmN2L("smptr_ceLnet %d", smptr_ceLnet)

	smptr_ceuMsend();
}

static struct timespec Stsp_e = {0}, Stsp_s;
void smptr_ceMread()
{
	Stsp_s = *(struct timespec *)smptr_cePnet;
	//SMPT_DBmN2L("C tv_sec %ld", Stsp_s.tv_sec)
	//SMPT_DBmN2L("C tv_nsec %ld", Stsp_s.tv_nsec)

	if ((Stsp_s.tv_sec > Stsp_e.tv_sec) || (Stsp_s.tv_sec == Stsp_e.tv_sec && Stsp_s.tv_nsec > Stsp_e.tv_nsec))
	{
		smptr_ceLnet = sizeof(struct timespec);

		smptr_ceuMread();
		smptr_cemMread();

		Stsp_e = Stsp_s;
	}
}

void smptr_ceMloop()
{
	smptr_ceuMloop();
	smptr_cemMloop();
}

void smptr_ceMfree(uint32_t device)
{
	nc_free();

	#ifdef SMPT_CM_VK
		while (!(smpt_sfUstate & SMPT_SFuS_EXIT_RENDER))
		{
			SMPT_DBmR2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
			SMPT_DBmN2L("smpt_sfUstate %d", smpt_sfUstate)
		}

		SMPT_DBmR2L("vkQueueWaitIdle %d", vkQueueWaitIdle(smpt_rd_vkq_p[smpt_rd_vk_device][smpt_rd_vk_queue_g]))

		smptr_cemMfree();
		smpt_rd_vkw_dstsp_free(device);
		smpt_rd_vkw_dsts_lo_free(device);

		lcp_free(device);
		smpt_rd_vk_cmd_free();
	#endif
}
