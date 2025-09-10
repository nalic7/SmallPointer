struct SMPTR_SVtNET smptr_svPnet[SMPT_NWuU];

void smptr_svMset()
{
	smptr_svuMset();
	smptr_svmMset();

	ns_set();

	SMPT_DBmR2L("thrd_create %d", thrd_create(&(thrd_t){}, smptr_svMloop, NULL))
}

void smptr_svMsend(SMPT_NWtU u)
{
//	SMPT_DBmN2L("S u %d", u)
//	SMPT_DBmN2L("S smptr_svPnet[u].Lnet %d", smptr_svPnet[u].Lnet)
	clock_gettime(CLOCK_MONOTONIC, (struct timespec *)smptr_svPnet[u].Pnet);
	smptr_svPnet[u].Lnet = sizeof(struct timespec);
	smptr_svmMsend(u);
//	SMPT_DBmN2L("S smptr_svPnet[u].Lnet %d", smptr_svPnet[u].Lnet)
}

void smptr_svMread()
{
	smptr_svuMread();
	//get u from ns
}

int smptr_svMloop(void *P)
{
	uint8_t Urw = 0;
	struct timespec Stsp_s, Stsp_e, Stsp_n = {0};
	double Dn;
	clock_gettime(CLOCK_MONOTONIC, &Stsp_s);
	while (!(smpt_sfUstate & SMPT_SFuS_EXIT))
	{
		#ifdef SMPT_CM_UDP
			ns_get();
		#endif

		smptr_svmMloop();

		for (SMPT_NWtU l0 = 0; l0 < SMPT_NWuU; ++l0)
		{
			#ifdef SMPT_CM_UDP
				ns_send(l0);
			#endif
		}

		if (++Urw == SMPTRuRW)
		{
			clock_gettime(CLOCK_MONOTONIC, &Stsp_e);
			Dn = Stsp_e.tv_sec + (double)Stsp_e.tv_nsec / 1e9 - Stsp_s.tv_sec - (double)Stsp_s.tv_nsec / 1e9;
			SMPT_DBmN2L("s %f", Stsp_s.tv_sec + (double)Stsp_s.tv_nsec / 1e9)
			SMPT_DBmN2L("e %f", Stsp_e.tv_sec + (double)Stsp_e.tv_nsec / 1e9)
			SMPT_DBmN2L("Dn %f", Dn)
			if (Dn < 1.0)
			{
				Stsp_n.tv_nsec = (1.0 - Dn) * 1e9;
				thrd_sleep(&Stsp_n, NULL);
			}
			Urw = 0;
			clock_gettime(CLOCK_MONOTONIC, &Stsp_s);
		}
	}
	smpt_sfUstate |= SMPT_SFuS_EXIT_SERVER;
	return 0;
}

void smptr_svMfree()
{
	while (!(smpt_sfUstate & SMPT_SFuS_EXIT_SERVER))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	smptr_svmMfree();
	smptr_svuMfree();

	ns_free();
}
