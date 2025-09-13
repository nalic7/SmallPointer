uint8_t smptr_cePnet[SMPTRlNET];
SMPTRtNET smptr_ceLnet = 0;

double smptr_ceDdelta = 0;

void smptr_ceMset()
{
	lckf_set();
	lcp_set();

	smptr_cemMset();

	#ifdef SMPT_CM_UDP
		smpt_nw_udp_ceMset();
	#endif

	smpt_sfUstate |= SMPT_SFuS_RAW;
}

void smptr_ceMsend()
{
	clock_gettime(CLOCK_MONOTONIC, (struct timespec *)smptr_cePnet);
	smptr_ceLnet = sizeof(struct timespec);

	//SMPT_DBmN2L("smptr_ceLnet %d", smptr_ceLnet)

	smptr_ceuMsend();
}

static struct timespec Stsp_s = {0}, Stsp_e;
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

static struct timespec Stsp_ds = {0}, Stsp_de;
void smptr_ceMloop()
{
	smptr_ceuMloop();
	smptr_cemMloop();

	clock_gettime(CLOCK_MONOTONIC, &Stsp_de);
	smptr_ceDdelta = Stsp_de.tv_sec + (double)Stsp_de.tv_nsec / 1e9 - Stsp_ds.tv_sec - (double)Stsp_ds.tv_nsec / 1e9;
	Stsp_ds = Stsp_de;
}

void smptr_ceMfree(uint32_t device)
{
	#ifdef SMPT_CM_UDP
		smpt_nw_udp_ceMfree();
	#endif

	#ifdef SMPT_CM_VK
		while (!(smpt_sfUstate & SMPT_SFuS_EXIT_RENDER))
		{
			SMPT_DBmR2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
			SMPT_DBmN2L("smpt_sfUstate %d", smpt_sfUstate)
		}

		SMPT_DBmR2L("vkQueueWaitIdle %d", vkQueueWaitIdle(smpt_rd_vkqP[smpt_rd_vkUdevice][smpt_rd_vkUqueue_g]))

		smptr_cemMfree();
		smpt_rd_vkw_dstspMfree(device);
		smpt_rd_vkw_dsts_loMfree(device);

		lcp_free(device);
		smpt_rd_vk_cmdMfree();
	#endif
}
