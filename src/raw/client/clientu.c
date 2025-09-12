struct SMPTRsU smptr_ceuSu = {0};
uint8_t smpt_ceuPinput[SMPT_IPuL] = {0};
float smpt_ceuPpoint[2] = {0};

//! use on m
//static struct SMPTRsU smptr_ceuSu0 = {0}, smptr_ceuSu1 = {0}, smptr_ceuSu2 = {0};
//static uint8_t smptr_ceuUu0 = 0;
//static float smptr_ceuPu1[sizeof(smptr_ceuSu0.Ptr)] = {0};

void smptr_ceuMset()
{
}

static float
	Pr[4],

	q0_m4x4_array[16] =
	{
		1.0F, 0.0F, 0.0F, 0.0F,
		0.0F, 1.0F, 0.0F, 0.0F,
		0.0F, 0.0F, 1.0F, 0.0F,
		0.0F, 0.0F, 0.0F, 1.0F
	},
	q1_m4x4_array[16],
	q2_m4x4_array[16];

static uint8_t state = 0;
void smptr_ceuMsend()
{
	if (!(state & 1))
		return;
	memcpy(smptr_cePnet + smptr_ceLnet, &smptr_ceuSu, sizeof(struct SMPTRsU));
	smptr_ceLnet += sizeof(struct SMPTRsU);
}

void smptr_ceuMread()
{
	if (!(state & 1))
	{
		memcpy(&smptr_ceuSu, smptr_cePnet + smptr_ceLnet, sizeof(struct SMPTRsU));
		state |= 1;
	}
	smptr_ceLnet += sizeof(struct SMPTRsU);
}

void smptr_ceuMloop()
{
	if (!(state & 1))
		return;
	//! use on m
//	if (memcmp(smptr_ceuSu2.Ptr, smptr_ceuSu.Ptr, sizeof(smptr_ceuSu.Ptr)))
//	{
//		smptr_ceuUu0 = 0;
//		for (uint8_t l0 = 0; l0 < 4; ++l0)
//		{
//			smptr_ceuPu1[l0] = (smptr_ceuSu.Ptr[l0] - smptr_ceuSu0.Ptr[l0]) * SMPTR_CEuDELTA;
//		}
//		smptr_ceuPu1[4] = fmodf((smptr_ceuSu.Ptr[4] - smptr_ceuSu0.Ptr[4] + M_PI), 2 * M_PI);
//		if (smptr_ceuPu1[4] < 0)
//		{
//			smptr_ceuPu1[4] += 2 * M_PI;
//		}
//		smptr_ceuPu1[4] -= M_PI;
//		smptr_ceuPu1[4] *= SMPTR_CEuDELTA;
//		memcpy(smptr_ceuSu2.Ptr, smptr_ceuSu.Ptr, sizeof(smptr_ceuSu.Ptr));
//	}
//	if (smptr_ceuUu0 != SMPTR_CEuFPS)
//	{
//		for (uint8_t l0 = 0; l0 < 5; ++l0)
//		{
//			smptr_ceuSu0.Ptr[l0] += smptr_ceuPu1[l0];
//		}
//		smptr_ceuSu0.Ptr[4] = SMPTMmNORM_NF(smptr_ceuSu0.Ptr[4], SMPTMmD2R(360));
//		++smptr_ceuUu0;
//	}
	float *Pbuffer = smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer];

	if (smpt_ceuPinput[0] & SMPT_IPuKEY_SPACE)
		smptr_ceuSu.Ptr[1] -= 2 * smptr_ceDdelta;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_LEFT_SHIFT)
		smptr_ceuSu.Ptr[1] += 2 * smptr_ceDdelta;

	smptr_ceuSu.Ptr[4] += smpt_ceuPpoint[0] * smptr_ceDdelta;
	smptr_ceuSu.Ptr[3] += smpt_ceuPpoint[1] * smptr_ceDdelta;
	memset(smpt_ceuPpoint, 0, sizeof(float) * 2);

	if (smptr_ceuSu.Ptr[3] > SMPTMmD2R(90.0F))
	{
		smptr_ceuSu.Ptr[3] = SMPTMmD2R(90.0F);
	}
	else if (smptr_ceuSu.Ptr[3] < SMPTMmD2R(-90.0F))
	{
		smptr_ceuSu.Ptr[3] = SMPTMmD2R(-90.0F);
	}
	smptr_ceuSu.Ptr[4] = SMPTMmNORM_NF(smptr_ceuSu.Ptr[4], SMPTMmD2R(360));

	VkDevice vkdevice = smpt_rd_vkq_dv_p[smpt_rd_vk_device];

	memcpy(Pbuffer, smptmPm4x4, sizeof(float) * 16);

	smptm_v4Mq(0, 0, SMPTMmD2R(180), Pr);
	smptm_v4Mq2m(Pr, q0_m4x4_array);
	memcpy(q1_m4x4_array, Pbuffer, sizeof(float) * 16);
	smptm_m4x4Mm(q1_m4x4_array, q0_m4x4_array, Pbuffer);

	smptm_v4Mq(0, smptr_ceuSu.Ptr[4], 0, Pr);
	smptm_v4Mq2m(Pr, q0_m4x4_array);
	memcpy(q1_m4x4_array, Pbuffer, sizeof(float) * 16);
	smptm_m4x4Mm(q1_m4x4_array, q0_m4x4_array, Pbuffer);

	//.i fix t
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_A)
		Pr[0] -= 2 * smptr_ceDdelta;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_D)
		Pr[0] += 2 * smptr_ceDdelta;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_W)
		Pr[2] += 2 * smptr_ceDdelta;
	if (smpt_ceuPinput[0] & SMPT_IPuKEY_S)
		Pr[2] -= 2 * smptr_ceDdelta;
	Pr[3] = 0;
	smptm_v4Mm4(Pbuffer, Pr, q1_m4x4_array);
	smptr_ceuSu.Ptr[0] += q1_m4x4_array[0];
	smptr_ceuSu.Ptr[2] += q1_m4x4_array[2];

	smptm_v4Mq(smptr_ceuSu.Ptr[3], 0, 0, Pr);
	smptm_v4Mq2m(Pr, q0_m4x4_array);
	memcpy(q1_m4x4_array, Pbuffer, sizeof(float) * 16);
	smptm_m4x4Mm(q1_m4x4_array, q0_m4x4_array, Pbuffer);

	memcpy(q2_m4x4_array, smptmPm4x4, sizeof(float) * 16);

	q2_m4x4_array[12] = smptr_ceuSu.Ptr[0];
	q2_m4x4_array[13] = smptr_ceuSu.Ptr[1];
	q2_m4x4_array[14] = smptr_ceuSu.Ptr[2];
	memcpy(q1_m4x4_array, Pbuffer, sizeof(float) * 16);
	smptm_m4x4Mm(q2_m4x4_array, q1_m4x4_array, Pbuffer);

	vkFlushMappedMemoryRanges(vkdevice, 1, &(VkMappedMemoryRange)
	{
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = smptr_ce_mdPvkdevicememory[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer],
		.offset = 0,
		.size = sizeof(float) * 16,
		.pNext = VK_NULL_HANDLE
	});
}

void smptr_ceuMfree()
{
}
