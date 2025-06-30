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

uint8_t
	**lcs_a_p[NALI_V_A_BL],
	*lcs_a_bl1_p[NALI_V_A_BL];

NALI_LCS_DSIT
	lcs_a_bl0_p[NALI_V_A_BL] = {0};

VkDeviceSize *lcs_i_p;
uint32_t *lcs_ic_p;

VkDeviceSize 
	lcs_a_vkdevicesize_p[NALI_V_A_BL],
	*lcs_b_vkdevicesize_p[NALI_V_A_BL];

VkDescriptorPool lcs_vkdescriptorpool;
VkDescriptorSetLayout lcs_vkdescriptorsetlayout;
VkDescriptorSet *lcs_vkdescriptorset_p[NALI_V_A_BL];
uint32_t lcs_vkdescriptorset_bl[NALI_V_A_BL] = {0};

// VkMappedMemoryRange *lcs_vkmappedmemoryrange_p;
// uint16_t lcs_vkmappedmemoryrange_bl = 0;

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

void lcs_setVkWriteDescriptorSet(VkDescriptorSet vkdescriptorset, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkWriteDescriptorSet *vkwritedescriptorset_p, VkDeviceSize *v_b_vkdevicesize_p, uint8_t mj)
{
	//VK_DESCRIPTOR_TYPE_STORAGE_BUFFER
	//r-bind
	vkdescriptorbufferinfo_p[0] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = v_b_vkdevicesize_p[0],
		.range = sizeof(float) * 16 * 2
	};
	vkds_setVkWriteDescriptorSet(vk_device, 0, VK_NULL_HANDLE, vkdescriptorbufferinfo_p, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p);

	//n-bind
	//mj = lcm_joint_count_p[ji]
	vkdescriptorbufferinfo_p[1] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = v_b_vkdevicesize_p[1],
		.range = mj * sizeof(float) * 16 * 2
	};
	vkds_setVkWriteDescriptorSet(vk_device, 1, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[1], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 1);

	//r-bind
	vkdescriptorbufferinfo_p[2] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = v_b_vkdevicesize_p[2],
		.range = mj * sizeof(float) * 4 * 3
	};
	vkds_setVkWriteDescriptorSet(vk_device, 2, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[2], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 2);

	//n-bind
	vkdescriptorbufferinfo_p[3] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = v_b_vkdevicesize_p[3],
		.range = lcp_rgba_bl
	};
	vkds_setVkWriteDescriptorSet(vk_device, 3, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[3], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 3);

	//r-bind
	vkdescriptorbufferinfo_p[4] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = v_b_vkdevicesize_p[4],
		.range = lcp_rgba_bl
	};
	vkds_setVkWriteDescriptorSet(vk_device, 4, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[4], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 4);
}

void lcs_set()
{
	// lcs_vkmappedmemoryrange_p = malloc(0);

	for (uint8_t l_0 = 0; l_0 < NALI_V_A_BL; ++l_0)
	{
		lcs_vkdescriptorset_p[l_0] = malloc(0);

		lcs_a_p[l_0] = malloc(0);
		lcs_a_bl1_p[l_0] = malloc(0);
		lcs_b_vkdevicesize_p[l_0] = malloc(0);
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

	for (uint8_t l_0 = 0; l_0 < NALI_V_A_BL; ++l_0)
	{
		free(lcs_vkdescriptorset_p[l_0]);
	}

	// free(lcs_vkmappedmemoryrange_p);
}

void lcs_free()
{
	for (uint8_t l_0 = 0; l_0 < NALI_V_A_BL; ++l_0)
	{
		for (uint16_t l_1 = 0; l_1 < lcs_a_bl0_p[l_0]; ++l_1)
		{
			free(lcs_a_p[l_0][l_1]);
		}
		free(lcs_a_bl1_p[l_0]);
		free(lcs_a_p[l_0]);

		free(lcs_b_vkdevicesize_p[l_0]);
	}

	free(lcs_i_p);
	free(lcs_ic_p);
}