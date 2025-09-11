struct SMPTR_SVtNET smptr_svPnet[SMPT_NWuU];

FILE *smptr_svPfile;

void smptr_svMset()
{
	SMPT_DBmR2L("mkdir %d", mkdir(NALI_F_SAVE, S_IRUSR | S_IWUSR | S_IXUSR))

	smptr_svuMset();
	smptr_svmMset();

	ns_set();
	smptr_svMfread();

	SMPT_DBmR2L("thrd_create %d", thrd_create(&(thrd_t){}, smptr_svMloop, NULL))
}

void smptr_svMsend(SMPT_NWtU u)
{
//	SMPT_DBmN2L("S u %d", u)
//	SMPT_DBmN2L("S smptr_svPnet[u].Lnet %d", smptr_svPnet[u].Lnet)
	clock_gettime(CLOCK_MONOTONIC, (struct timespec *)smptr_svPnet[u].Pnet);
	smptr_svPnet[u].Lnet = sizeof(struct timespec);

	smptr_svuMsend(u);
	smptr_svmMsend(u);
//	SMPT_DBmN2L("S smptr_svPnet[u].Lnet %d", smptr_svPnet[u].Lnet)
}

static struct timespec Ptsp_e[SMPT_NWuU] = {0}, Ptsp_s[SMPT_NWuU];
void smptr_svMread(SMPT_NWtU u)
{
	Ptsp_s[u] = *(struct timespec *)smptr_svPnet[u].Pnet;
	//SMPT_DBmN2L("S tv_sec %ld", Ptsp_s[u].tv_sec)
	//SMPT_DBmN2L("S tv_nsec %ld", Ptsp_s[u].tv_nsec)

	if ((Ptsp_s[u].tv_sec > Ptsp_e[u].tv_sec) || (Ptsp_s[u].tv_sec == Ptsp_e[u].tv_sec && Ptsp_s[u].tv_nsec > Ptsp_e[u].tv_nsec))
	{
		//SMPT_DBmN2L("W")
		smptr_svPnet[u].Lnet = sizeof(struct timespec);

		smptr_svuMread(u);

		Ptsp_e[u] = Ptsp_s[u];
	}
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
	smptr_svMfsend();
	smpt_sfUstate |= SMPT_SFuS_EXIT_SERVER;
	return 0;
}

void smptr_svMfread()
{
	SMPT_DBmR2L("fopen %p", smptr_svPfile = fopen(NALI_F_SAVE_SPACE, "rb"))

	smptr_svuMfread();
	smptr_svmMfread();

	if (smptr_svPfile)
	{
		fclose(smptr_svPfile);
	}
}

void smptr_svMfsend()
{
	SMPT_DBmR2L("fopen %p", smptr_svPfile = fopen(NALI_F_SAVE_SPACE, "wb"))

	smptr_svuMfsend();
	smptr_svmMfsend();

	fclose(smptr_svPfile);
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
