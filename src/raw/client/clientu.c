void smptr_ceuMset()
{
}

static double Ddelta = 0;
static struct timespec Stsp_s = {0}, Stsp_e;
static float
	smptr_ceuPt[3] = {0},
	smptr_ceuPr[2] = {0},
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
void smptr_ceuMloop()
{
	if (smpt_ipPs[1] & SMPT_IPuKEY_SPACE)
		smptr_ceuPt[1] -= 2 * Ddelta;
	if (smpt_ipPs[1] & SMPT_IPuKEY_LEFT_SHIFT)
		smptr_ceuPt[1] += 2 * Ddelta;

	if (smpt_ipPs[0] & SMPT_IPuPOINT_PX)
		smptr_ceuPr[1] += 2.5 * Ddelta;
	if (smpt_ipPs[0] & SMPT_IPuPOINT_NX)
		smptr_ceuPr[1] -= 2.5 * Ddelta;
	if (smpt_ipPs[0] & SMPT_IPuPOINT_PY)
		smptr_ceuPr[0] += 2.5 * Ddelta;
	if (smpt_ipPs[0] & SMPT_IPuPOINT_NY)
		smptr_ceuPr[0] -= 2.5 * Ddelta;
	smpt_ipPs[0] &= 255 - SMPT_IPuPOINT_PX - SMPT_IPuPOINT_NX - SMPT_IPuPOINT_PY - SMPT_IPuPOINT_NY;

	if (smptr_ceuPr[0] > NALI_M_D2R(90.0F))
	{
		smptr_ceuPr[0] = NALI_M_D2R(90.0F);
	}
	else if (smptr_ceuPr[0] < NALI_M_D2R(-90.0F))
	{
		smptr_ceuPr[0] = NALI_M_D2R(-90.0F);
	}

	VkDevice vkdevice = smpt_rd_vkq_dv_p[smpt_rd_vk_device];

	memcpy(smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer], smptmPm4x4, sizeof(float) * 16);
		lb_u_update(smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer], smptr_ceuPr[1], Pr, q0_m4x4_array, q1_m4x4_array);

		//.i fix t
		if (smpt_ipPs[0] & SMPT_IPuKEY_A)
			Pr[0] -= 2 * Ddelta;
		if (smpt_ipPs[0] & SMPT_IPuKEY_D)
			Pr[0] += 2 * Ddelta;
		if (smpt_ipPs[0] & SMPT_IPuKEY_W)
			Pr[2] += 2 * Ddelta;
		if (smpt_ipPs[0] & SMPT_IPuKEY_S)
			Pr[2] -= 2 * Ddelta;
		Pr[3] = 0;
		smptm_v4Mm4(smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer], Pr, q1_m4x4_array);
		smptr_ceuPt[0] += q1_m4x4_array[0];
		smptr_ceuPt[2] += q1_m4x4_array[2];

		smptm_v4Mq(smptr_ceuPr[0], 0, 0, Pr);
		//smptm_v4Mq(smptr_ceuPr[0], smptr_ceuPr[1], 0, Pr);
		//smptm_v4Mq(smptr_ceuPr[0], smptr_ceuPr[1], NALI_M_D2R(-180), Pr);
		smptm_v4Mq2m(Pr, q0_m4x4_array);
		memcpy(q1_m4x4_array, smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer], sizeof(float) * 16);
		smptm_m4x4Mm(q1_m4x4_array, q0_m4x4_array, smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer]);

		memcpy(q2_m4x4_array, smptmPm4x4, sizeof(float) * 16);

		q2_m4x4_array[12] = smptr_ceuPt[0];
		q2_m4x4_array[13] = smptr_ceuPt[1];
		q2_m4x4_array[14] = smptr_ceuPt[2];
		memcpy(q1_m4x4_array, smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer], sizeof(float) * 16);
		smptm_m4x4Mm(q2_m4x4_array, q1_m4x4_array, smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer]);

	//smptm_v4Mq(0, NALI_M_D2R(-45), NALI_M_D2R(-180), Pr);
	//smptm_v4Mq(smptr_ceuPr[0], smptr_ceuPr[1], NALI_M_D2R(-180), Pr);
	//smptm_v4Mq(smptr_ceuPr[0], 0, NALI_M_D2R(-180), Pr);
//	smptm_v4Mq(0, smptr_ceuPr[1], NALI_M_D2R(-180), Pr);
//	smptm_v3Mq2m(smptr_ceuPt, smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer]);
	//smptm_v4Mq2m(Pr, smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer]);
//	((float *)smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer])[12] = smptr_ceuPt[0];
//	((float *)smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer])[13] = smptr_ceuPt[1];
//	((float *)smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer])[14] = smptr_ceuPt[2];
	vkFlushMappedMemoryRanges(vkdevice, 1, &(VkMappedMemoryRange)
	{
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = smptr_ce_mdPvkdevicememory[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer],
		.offset = 0,
		.size = sizeof(float) * 16,
		.pNext = VK_NULL_HANDLE
	});

	clock_gettime(CLOCK_MONOTONIC, &Stsp_e);
	Ddelta = Stsp_e.tv_sec + (double)Stsp_e.tv_nsec / 1e9 - Stsp_s.tv_sec - (double)Stsp_s.tv_nsec / 1e9;
	Stsp_s = Stsp_e;
}

void smptr_ceuMsend()
{
}

void smptr_ceuMfree()
{
}
