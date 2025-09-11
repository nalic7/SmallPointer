struct SMPTRsU smptr_ceuSu = {0};
uint8_t smpt_ceuPinput[SMPT_IPuL] = {0};

struct SMPTRsU smptr_ceuSu0 = {0};

void smptr_ceuMset()
{
}

static double Ddelta = 0;
static struct timespec Stsp_s = {0}, Stsp_e;
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

void smptr_ceuMsend()
{
	memcpy(smptr_cePnet + smptr_ceLnet, smpt_ceuPinput, sizeof(uint8_t) * SMPT_IPuL);
	smptr_ceLnet += sizeof(uint8_t) * SMPT_IPuL;

	smpt_ceuPinput[0] &= 255 - SMPT_IPuPOINT_PX - SMPT_IPuPOINT_NX - SMPT_IPuPOINT_PY - SMPT_IPuPOINT_NY;
}

void smptr_ceuMread()
{
	smptr_ceuSu = *(struct SMPTRsU *)(smptr_cePnet + smptr_ceLnet);
	smptr_ceLnet += sizeof(struct SMPTRsU);

	//if (memcmp(smptr_ceuSu0, smptr_ceuSu, sizeof(struct SMPTRsU)))
}

void smptr_ceuMloop()
{
	for (uint8_t l0 = 0; l0 < 5; ++l0)
	{
		smptr_ceuSu0.Ptr[l0] += (smptr_ceuSu.Ptr[l0] - smptr_ceuSu0.Ptr[l0]) * Ddelta;
	}

	VkDevice vkdevice = smpt_rd_vkq_dv_p[smpt_rd_vk_device];

	memcpy(smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer], smptmPm4x4, sizeof(float) * 16);
	lb_u_update(smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer], smptr_ceuSu0.Ptr[4], Pr, q0_m4x4_array, q1_m4x4_array);

	smptm_v4Mq(smptr_ceuSu0.Ptr[3], 0, 0, Pr);
	smptm_v4Mq2m(Pr, q0_m4x4_array);
	memcpy(q1_m4x4_array, smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer], sizeof(float) * 16);
	smptm_m4x4Mm(q1_m4x4_array, q0_m4x4_array, smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer]);

	memcpy(q2_m4x4_array, smptmPm4x4, sizeof(float) * 16);

	q2_m4x4_array[12] = smptr_ceuSu0.Ptr[0];
	q2_m4x4_array[13] = smptr_ceuSu0.Ptr[1];
	q2_m4x4_array[14] = smptr_ceuSu0.Ptr[2];
	memcpy(q1_m4x4_array, smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer], sizeof(float) * 16);
	smptm_m4x4Mm(q2_m4x4_array, q1_m4x4_array, smptr_ce_mdPbuffer_map[1 + smpt_rd_vk_swc_image + smpt_rd_vk_swc_frame_buffer]);

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

void smptr_ceuMfree()
{
}
