void smptr_svmMset()
{
	//! test
//{0, 3, 5}
	smptrPm = realloc(smptrPm, sizeof(struct SMPTRsM));
	smptrPm[0].m = 0;
	smptrPm[0].l = 9;
	smptrPm[0].k = 0;
	smptrPm[0].t = 0;

	smptrPm[0].Pa = malloc(sizeof(SMPTRtMA) * smptrPm[0].l);
	smptrPm[0].Pa[0] = SMPTReMAc + SMPTReM_POMI_PAPI;
	smptrPm[0].Pa[1] = SMPTReMA_FE0000_000;
	smptrPm[0].Pa[2] = SMPTReMA_FE0000_001;
	smptrPm[0].Pa[3] = SMPTReMA_FE00_000;
	smptrPm[0].Pa[4] = SMPTReMA_FE00_001;
	smptrPm[0].Pa[5] = SMPTReMA_FE0_000;
	smptrPm[0].Pa[6] = SMPTReMA_FE0_001;
	smptrPm[0].Pa[7] = SMPTReMA_M0;
	smptrPm[0].Pa[8] = SMPTReMA_IShovel;
	++smptrLm;
}

void smptr_svmMloop()
{
}

void smptr_svmMfree()
{
}
