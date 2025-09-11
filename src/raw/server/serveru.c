struct SMPTRsU smptr_svuSu[SMPT_NWuU];
uint8_t smpt_svuPinput[SMPT_NWuU][SMPT_IPuL] = {0};

void smptr_svuMset()
{
}

void smptr_svuMsend(SMPT_NWtU u)
{
	memcpy(smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, smptr_svuSu + u, sizeof(struct SMPTRsU));
	smptr_svPnet[u].Lnet += sizeof(struct SMPTRsU);
}

static float
	Pm4x4[16],
	Pr[4],
	q0_m4x4_array[16] =
	{
		1.0F, 0.0F, 0.0F, 0.0F,
		0.0F, 1.0F, 0.0F, 0.0F,
		0.0F, 0.0F, 1.0F, 0.0F,
		0.0F, 0.0F, 0.0F, 1.0F
	},
	q1_m4x4_array[16],
	Ddelta = 0.005;
void smptr_svuMread(SMPT_NWtU u)
{
	memcpy(smpt_svuPinput[u], smptr_svPnet[u].Pnet + smptr_svPnet[u].Lnet, sizeof(uint8_t) * SMPT_IPuL);
	smptr_svPnet[u].Lnet += sizeof(uint8_t) * SMPT_IPuL;

	if (smpt_svuPinput[u][1] & SMPT_IPuKEY_SPACE)
		smptr_svuSu[u].Ptr[1] -= 2 * Ddelta;
	if (smpt_svuPinput[u][1] & SMPT_IPuKEY_LEFT_SHIFT)
		smptr_svuSu[u].Ptr[1] += 2 * Ddelta;

	if (smpt_svuPinput[u][0] & SMPT_IPuPOINT_PX)
		smptr_svuSu[u].Ptr[4] += 2.5 * Ddelta;
	if (smpt_svuPinput[u][0] & SMPT_IPuPOINT_NX)
		smptr_svuSu[u].Ptr[4] -= 2.5 * Ddelta;
	if (smpt_svuPinput[u][0] & SMPT_IPuPOINT_PY)
		smptr_svuSu[u].Ptr[3] += 2.5 * Ddelta;
	if (smpt_svuPinput[u][0] & SMPT_IPuPOINT_NY)
		smptr_svuSu[u].Ptr[3] -= 2.5 * Ddelta;

	if (smptr_svuSu[u].Ptr[3] > NALI_M_D2R(90.0F))
	{
		smptr_svuSu[u].Ptr[3] = NALI_M_D2R(90.0F);
	}
	else if (smptr_svuSu[u].Ptr[3] < NALI_M_D2R(-90.0F))
	{
		smptr_svuSu[u].Ptr[3] = NALI_M_D2R(-90.0F);
	}

	memcpy(Pm4x4, smptmPm4x4, sizeof(float) * 16);
	lb_u_update(Pm4x4, smptr_svuSu[u].Ptr[4], Pr, q0_m4x4_array, q1_m4x4_array);
	//.i fix t
	if (smpt_svuPinput[u][0] & SMPT_IPuKEY_A)
		Pr[0] -= 2 * Ddelta;
	if (smpt_svuPinput[u][0] & SMPT_IPuKEY_D)
		Pr[0] += 2 * Ddelta;
	if (smpt_svuPinput[u][0] & SMPT_IPuKEY_W)
		Pr[2] += 2 * Ddelta;
	if (smpt_svuPinput[u][0] & SMPT_IPuKEY_S)
		Pr[2] -= 2 * Ddelta;
	Pr[3] = 0;
	smptm_v4Mm4(Pm4x4, Pr, q1_m4x4_array);
	smptr_svuSu[u].Ptr[0] += q1_m4x4_array[0];
	smptr_svuSu[u].Ptr[2] += q1_m4x4_array[2];
}

void smptr_svuMfread()
{
	if (smptr_svPfile)
	{
		fread(smptr_svuSu, sizeof(struct SMPTRsU), SMPT_NWuU, smptr_svPfile);
	}
	else
	{
		memset(smptr_svuSu, 0, sizeof(struct SMPTRsU) * SMPT_NWuU);
	}
}

void smptr_svuMfsend()
{
	fwrite(smptr_svuSu, sizeof(struct SMPTRsU), SMPT_NWuU, smptr_svPfile);
}

void smptr_svuMfree()
{
}
