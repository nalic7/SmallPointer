struct SMPTRsU smptr_svuSu[SMPT_NWlU];
uint8_t *smptr_svuPm[SMPT_NWlU];

void smptr_svuMset()
{
	for (SMPT_NWtU l0 = 0; l0 < SMPT_NWlU; ++l0)
		smptr_svuPm[l0] = malloc(0);
}

void smptr_svuMloop()
{
	//! test look
	for (SMPT_NWtU l0 = 0; l0 < SMPT_NWlU; ++l0)
	{
		smptr_svuPm[l0] = realloc(smptr_svuPm[l0], sizeof(uint8_t) * smptr_svmLm);
		memset(smptr_svuPm[l0], 0, sizeof(uint8_t) * smptr_svmLm);

		float *Ptr_u = smptr_svuSu[l0].Ptr;
		for (SMPTRtMI l1 = 0; l1 < smptr_svmLm; ++l1)
		{
			float Pt_m[3];
			for (SMPTRtMI l2 = 0; l2 < 3; ++l2)
			{
				Pt_m[l2] = smptr_svmPm[l1].Sm0.Ptr[l2] + Ptr_u[l2];
			}
			float
				yaw = SMPTMmXZ2YAW(Pt_m[0], Pt_m[2]),
				pitch = SMPTMmXYZ2PITCH(Pt_m[0], Pt_m[1], Pt_m[2]);
			//if (SMPTMmIN_C(pitch, Ptr_u[3], SMPTMmD2R(45)) && SMPTMmIN_C(yaw, Ptr_u[4], SMPTMmD2R(90)))
			if (SMPTMmIN_C(yaw, Ptr_u[4], SMPTMmD2R(90+45)))
			{
				smptr_svuPm[l0][l1 / 8] |= 1 << (l1 % 8);
			}
		}
	}
}

void smptr_svuMsend(SMPT_NWtU u)
{
	memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, &smptr_svuSu[u], sizeof(struct SMPTRsU));
	smptr_svPnet[u].Lnet += sizeof(struct SMPTRsU);
}

void smptr_svuMread(SMPT_NWtU u)
{
	memcpy(&smptr_svuSu[u], smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, sizeof(struct SMPTRsU));
	smptr_svPnet[u].Lnet += sizeof(struct SMPTRsU);
}

void smptr_svuMfread()
{
	if (smptr_svPfile)
	{
		fread(smptr_svuSu, sizeof(struct SMPTRsU), SMPT_NWlU, smptr_svPfile);
	}
	else
	{
		memset(smptr_svuSu, 0, sizeof(struct SMPTRsU) * SMPT_NWlU);
	}
}

void smptr_svuMfsend()
{
	fwrite(smptr_svuSu, sizeof(struct SMPTRsU), SMPT_NWlU, smptr_svPfile);
}

void smptr_svuMfree()
{
	for (SMPT_NWtU l0 = 0; l0 < SMPT_NWlU; ++l0)
		free(smptr_svuPm[l0]);
}
