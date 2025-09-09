void smptr_svMset()
{
	smptr_svuMset();
	smptr_svmMset();
	SMPT_DBmR2L("thrd_create %d", thrd_create(&(thrd_t){}, smptr_svMloop, NULL))
}

void smptr_svMread()
{
	smptr_svuMread();
}

int smptr_svMloop(void *P)
{
	uint8_t Urw = 0;
	struct timespec Stsp_s, Stsp_e, Stsp_n = {0};
	double Dn;
	clock_gettime(CLOCK_MONOTONIC, &Stsp_s);
	while (!(_sf_state & _SF_S_EXIT))
	{
		smptr_svMread();

		smptr_svmMloop();
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
	_sf_state |= _SF_S_EXIT_SERVER;
	return 0;
}

void smptr_svMfree()
{
	while (!(_sf_state & _SF_S_EXIT_SERVER))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	smptr_svmMfree();
	smptr_svuMfree();
}
