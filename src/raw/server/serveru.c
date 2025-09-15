struct SMPTRsU smptr_svuSu[SMPT_NWlU];
uint8_t *smptr_svuPm[SMPT_NWlU];

void smptr_svuMset()
{
	SMPT_DBmN2L("SMPTMmD2R(45) %f", SMPTMmD2R(45))
	SMPT_DBmN2L("SMPTMmD2R(90) %f", SMPTMmD2R(90))
	SMPT_DBmN2L("SMPTMmD2R(180) %f", SMPTMmD2R(180))
	SMPT_DBmN2L("SMPTMmD2R(360) %f", SMPTMmD2R(360))

	SMPT_DBmN2L("SMPTMmXZ2YAW(0, 1) %f", SMPTMmXZ2YAW(0, 1))
	SMPT_DBmN2L("SMPTMmXYZ2PITCH(0, 0, 1) %f", SMPTMmXYZ2PITCH(0, 0, 1))

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
		//.i fix Pr_u
		float Pr_u[] =
		{
			Ptr_u[3] + SMPTMmD2R(45),
			Ptr_u[4] + SMPTMmD2R(180)
		};
		SMPT_DBmN2L("Pr_u[0] %f", Pr_u[0])
		SMPT_DBmN2L("Pr_u[1] %f", Pr_u[1])
		for (SMPTRtMI l1 = 0; l1 < smptr_svmLm; ++l1)
		{
			float Pt_m[3];
			for (SMPTRtMI l2 = 0; l2 < 3; ++l2)
			{
				Pt_m[l2] = smptr_svmPm[l1].Sm0.Ptr[l2] + Ptr_u[l2];
				SMPT_DBmN2L("l2 %d", l2)
				SMPT_DBmN2L("Ptr_u[l2] %f", Ptr_u[l2])
				SMPT_DBmN2L("smptr_svmPm[l1].Sm0.Ptr[l2] %f", smptr_svmPm[l1].Sm0.Ptr[l2])
			}
			float
				yaw = SMPTMmXZ2YAW(Pt_m[0], Pt_m[2]),
				pitch = SMPTMmXYZ2PITCH(Pt_m[0], Pt_m[1], Pt_m[2]);
			SMPT_DBmN2L("yaw %f", yaw)
			SMPT_DBmN2L("pitch %f", pitch)
			float Fyaw2 = fabsf(Pr_u[1] - yaw);
			if (Fyaw2 >= SMPTMmD2R(180))
				Fyaw2 = SMPTMmD2R(360) - Fyaw2;
			float Fpitch2 = fabsf(Pr_u[0] - pitch);
			SMPT_DBmN2L("Fyaw2 %f", Fyaw2)
			SMPT_DBmN2L("Fpitch2 %f", Fpitch2)
			if (Fyaw2 <= SMPTMmD2R(45) && Fpitch2 <= SMPTMmD2R(45))
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
