float lcs_float_p[] =
{
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

// NALI_LCS_DSIT lcs_a_bl_p[NALI_LCS_A_BL] = {0};

VkDeviceSize *lcs_ib_p;
uint32_t *lcs_ic_p;

VkDeviceSize lcs_a_vkdevicesize_p[NALI_LCS_A_BL];
	// *lcs_b_vkdevicesize_p[NALI_LCS_A_BL];

VkDescriptorPool lcs_vkdescriptorpool;
VkDescriptorSetLayout lcs_vkdescriptorsetlayout;

lcs__ lcs___p[NALI_LB_MIM];
// NALI_LB_MIT *lcs__i_p[NALI_LCS_A_BL];

// VkMappedMemoryRange *lcs_vkmappedmemoryrange_p;
// uint16_t lcs_vkmappedmemoryrange_bl = 0;

uint32_t lcs_s_bl;
lcs_s *lcs_s_p;

static void setVkDescriptorSetLayout(VkDescriptorSetLayout *vkdescriptorsetlayout_p)
{
	vkdslo_make
	(
		vk_device,
		(VkDescriptorSetLayoutBinding[])
		{
			//VK_DESCRIPTOR_TYPE_STORAGE_BUFFER
			{
				.binding = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.pImmutableSamplers = VK_NULL_HANDLE,
				.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
			},
			{
				.binding = 1,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.pImmutableSamplers = VK_NULL_HANDLE,
				.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
			},
			{
				.binding = 2,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.pImmutableSamplers = VK_NULL_HANDLE,
				.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
			},
			{
				.binding = 3,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.pImmutableSamplers = VK_NULL_HANDLE,
				.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
			},
			{
				.binding = 4,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.pImmutableSamplers = VK_NULL_HANDLE,
				.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
			}
		},
		NALI_LCS_D_SIZE,
		vkdescriptorsetlayout_p
	);
}
static void setVkDescriptorPoolSize(VkDescriptorPoolSize *vkdescriptorpoolsize_p)
{
	vkdescriptorpoolsize_p[0] = (VkDescriptorPoolSize)
	{
		.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = 1
	};
	vkdescriptorpoolsize_p[1] = vkdescriptorpoolsize_p[0];
	vkdescriptorpoolsize_p[2] = vkdescriptorpoolsize_p[0];
	vkdescriptorpoolsize_p[3] = vkdescriptorpoolsize_p[0];
	vkdescriptorpoolsize_p[4] = vkdescriptorpoolsize_p[0];
}

//m -> j
void lcs_setVkWriteDescriptorSet(VkDescriptorSet vkdescriptorset, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkWriteDescriptorSet *vkwritedescriptorset_p, NALI_LB_MIT ds, uint8_t j, uint8_t mj)
{
	//VK_DESCRIPTOR_TYPE_STORAGE_BUFFER
	//r-bind
	//gui / world
	vkdescriptorbufferinfo_p[0] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = sizeof(float) * 16 * 2,
		.range = sizeof(float) * 16 * 2
	};
	vkds_setVkWriteDescriptorSet(vk_device, 0, VK_NULL_HANDLE, vkdescriptorbufferinfo_p, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p);

	//n-bind
	//mj = lcm_joint_count_p[ji]
	//bone
	vkdescriptorbufferinfo_p[1] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = lcp_vkdevicesize_p[j],
		.range = mj * sizeof(float) * 16 * 2
	};
	vkds_setVkWriteDescriptorSet(vk_device, 1, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[1], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 1);

	//r-bind
	//animate
	vkdescriptorbufferinfo_p[2] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = lcp_vkdevicesize_p[lcp_joint_count_bl + 1] + NALI_LCP_BONE_BL * (sizeof(float) * 4 + sizeof(float) * 4 * 3) * ds + sizeof(float) * 4,
		.range = mj * sizeof(float) * 4 * 3
	};
	vkds_setVkWriteDescriptorSet(vk_device, 2, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[2], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 2);

	//n-bind
	//src color
	vkdescriptorbufferinfo_p[3] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = NALI_LCP_VP_BL,
		.range = lcp_rgba_bl
	};
	vkds_setVkWriteDescriptorSet(vk_device, 3, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[3], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 3);

	//r-bind
	//mix color
	vkdescriptorbufferinfo_p[4] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = lcp_vkdevicesize_p[lcp_joint_count_bl + 1] + NALI_LCP_BONE_BL * (sizeof(float) * 4 + sizeof(float) * 4 * 3) * ds,
		.range = lcp_rgba_bl
	};
	vkds_setVkWriteDescriptorSet(vk_device, 4, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[4], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 4);
}

void lcs_set()
{
	lcs_s_p = malloc(0);
	// lcs_vkmappedmemoryrange_p = malloc(0);

	// for (uint8_t l_0 = 0; l_0 < NALI_LCS_A_BL; ++l_0)
	// {
	// 	lcs_b_vkdevicesize_p[l_0] = malloc(0);
	// }

	//init unused value
	for (NALI_LB_MIT l_0 = 0; l_0 < NALI_LB_MIM; ++l_0)
	{
		//ch can pass with _update
		lcs___p[l_0].m.mi = NALI_LB_MIN;
		lcs___p[l_0].m.state = 0;
		// lsm__update_p[l_0].ms = NALI_LB_MSM;
		lcs___p[l_0].m.m = NALI_LB_MN;
		lcs___p[l_0].m.aki = NALI_LB_AKIN;
	}
}

// void lcs_loop()
// {
// 	if (lcs_vkmappedmemoryrange_bl)
// 	{
// 		vkFlushMappedMemoryRanges(vkqd_vkdevice_p[vk_device], lcs_vkmappedmemoryrange_bl, lcs_vkmappedmemoryrange_p);
// 		lcs_vkmappedmemoryrange_p = realloc(lcs_vkmappedmemoryrange_p, 0);
// 		lcs_vkmappedmemoryrange_bl = 0;
// 	}
// }

void lcs_vk()
{
	VkDescriptorPoolSize vkdescriptorpoolsize_p[NALI_LCS_D_SIZE];
	setVkDescriptorPoolSize(vkdescriptorpoolsize_p);
	vkdsp_make(vk_device, vkdescriptorpoolsize_p, NALI_LCS_D_SIZE, &lcs_vkdescriptorpool);
	setVkDescriptorSetLayout(&lcs_vkdescriptorsetlayout);
}

void lcs_freeVk(uint32_t device)
{
	VkDevice vkdevice = vkqd_vkdevice_p[device];

	vkDestroyDescriptorSetLayout(vkdevice, lcs_vkdescriptorsetlayout, VK_NULL_HANDLE);
	vkDestroyDescriptorPool(vkdevice, lcs_vkdescriptorpool, VK_NULL_HANDLE);

	// free(lcs_vkmappedmemoryrange_p);
}

void lcs_free()
{
	free(lcs_s_p);
	// for (uint8_t l_0 = 0; l_0 < NALI_LCS_A_BL; ++l_0)
	// {
	// 	free(lcs_b_vkdevicesize_p[l_0]);
	// }

	free(lcs_ib_p);
	free(lcs_ic_p);
}