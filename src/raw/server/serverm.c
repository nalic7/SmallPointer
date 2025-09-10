struct SMPTRsM *smptr_svmPm;
SMPTRtM smptr_svmLm = 0;

void smptr_svmMset()
{
	smptr_svmPm = malloc(0);

	//! test
	smptr_svmPm = realloc(smptr_svmPm, sizeof(struct SMPTRsM));
	smptr_svmPm[0].m = SMPTReM_POMI_PAPI;
	smptr_svmPm[0].k = SMPTReMK_POMI_WALK_LOOP;
	smptr_svmPm[0].t = 0;

	smptr_svmPm[0].l = 9;
	smptr_svmPm[0].Pa = malloc(sizeof(SMPTRtMA) * smptr_svmPm[0].l);
	smptr_svmPm[0].Pa[0] = SMPTReMAc + SMPTReM_POMI_PAPI;
	smptr_svmPm[0].Pa[1] = SMPTReMA_FE0000_000;
	smptr_svmPm[0].Pa[2] = SMPTReMA_FE0000_001;
	smptr_svmPm[0].Pa[3] = SMPTReMA_FE00_000;
	smptr_svmPm[0].Pa[4] = SMPTReMA_FE00_001;
	smptr_svmPm[0].Pa[5] = SMPTReMA_FE0_000;
	smptr_svmPm[0].Pa[6] = SMPTReMA_FE0_001;
	smptr_svmPm[0].Pa[7] = SMPTReMA_M0;
	smptr_svmPm[0].Pa[8] = SMPTReMA_IShovel;
	++smptr_svmLm;
}

void smptr_svmMloop()
{
}

void smptr_svmMsend(SMPT_NWtU u)
{
	//! cull m
	//.i send data
	*(SMPTRtMI *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = smptr_svmLm;
	smptr_svPnet[u].Lnet += sizeof(SMPTRtMI);

	for (SMPTRtMI l0 = 0; l0 < smptr_svmLm; ++l0)
	{
		struct SMPTRsM m = smptr_svmPm[l0];

		*(SMPTRtM *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = m.m;
		smptr_svPnet[u].Lnet += sizeof(SMPTRtM);

		if (m.m != SMPTRvM)
		{
			*(uint8_t *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = m.l;
			smptr_svPnet[u].Lnet += sizeof(uint8_t);

			memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, m.Pa, sizeof(SMPTRtMA) * m.l);
			smptr_svPnet[u].Lnet += sizeof(SMPTRtMA) * m.l;

			*(SMPTRtMK *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = m.k;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtMK);

			*(SMPTRtMT *)(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet) = m.t;
			smptr_svPnet[u].Lnet += sizeof(SMPTRtMT);
		}
	}
}

void smptr_svmMfree()
{
	for (SMPTRtMI l0 = 0; l0 < smptr_svmLm; ++l0)
	{
		if (smptr_svmPm[l0].m != SMPTRvM)
		{
			free(smptr_svmPm[l0].Pa);
		}
	}
	free(smptr_svmPm);
}
