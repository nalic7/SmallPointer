mtx_t *lcs_mtx_t_p = &(mtx_t){};

float m_vp_float_array[] =
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
	**v_a_p_array[NALI_V_A_BL],
	*v_a_bl1_p_array[NALI_V_A_BL];

uint16_t
	v_a_bl0_array[NALI_V_A_BL] = {0};

uint32_t *v_i_p;

VkDeviceSize 
	v_a_vkdevicesize_array[NALI_V_A_BL],
	*v_b_vkdevicesize_p_array[NALI_V_A_BL];

float **v_s_p_array[NALI_V_A_BL];

static VkDescriptorPool vkdescriptorpool;
VkDescriptorSetLayout lcs_vkdescriptorsetlayout;
VkDescriptorSet *lcs_vkdescriptorset_p[NALI_V_A_BL];

VkMappedMemoryRange *lcs_vkmappedmemoryrange_p;
uint16_t lcs_vkmappedmemoryrange_bl = 0;

VkDeviceSize 
	*lcs_add_vkdevicesize_p[NALI_V_A_BL];

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

static void setVkWriteDescriptorSet(VkDescriptorSet vkdescriptorset, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkWriteDescriptorSet *vkwritedescriptorset_p, VkDeviceSize *v_b_vkdevicesize_p, uint8_t j)
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
	vkdescriptorbufferinfo_p[1] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = v_b_vkdevicesize_p[1],
		.range = lcm_joint_count_p[j] * sizeof(float) * 16 * 2
	};
	vkds_setVkWriteDescriptorSet(vk_device, 1, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[1], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 1);

	//r-bind
	vkdescriptorbufferinfo_p[2] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = v_b_vkdevicesize_p[2],
		.range = lcm_joint_count_p[j] * sizeof(float) * 4 * 3
	};
	vkds_setVkWriteDescriptorSet(vk_device, 2, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[2], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 2);

	//n-bind
	vkdescriptorbufferinfo_p[3] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = v_b_vkdevicesize_p[3],
		.range = lcm_rgba_bl
	};
	vkds_setVkWriteDescriptorSet(vk_device, 3, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[3], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 3);

	//r-bind
	vkdescriptorbufferinfo_p[4] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = v_b_vkdevicesize_p[4],
		.range = lcm_rgba_bl
	};
	vkds_setVkWriteDescriptorSet(vk_device, 4, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[4], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 4);
}

//lcm_vkdevicesize
static void flush(uint8_t a, uint8_t ds_bl, uint8_t *ds_p, uint8_t *j_p)
{
	uint32_t l0;
	uint32_t l_offset;
	uint32_t l_size;
	for (uint32_t l_0 = 0; l_0 < ds_bl; ++l_0)
	{
		l0 = lcm_vkdevicesize_p[lcm_joint_count_bl - 1] + NALI_LCM_BONE_BL * sizeof(float) * 4 * 4 * v_a_bl0_array[a];
		v_s_p_array[a][ds_p[l_0]] = lc_vkbuffer_p + l0;
		for (uint32_t l_1 = 0; l_1 < 4; ++l_1)
		{
			((float *)(lc_vkbuffer_p + l0))[l_1] = 1.0F;
		}
		l0 += sizeof(float) * 4;
		l_offset = l0;

		//UBOA
		memcpy(lc_vkbuffer_p + l0, lcm_a_p[l_0], sizeof(float) * 4 * 3 * lcm_joint_count_p[j_p[l_0]]);

		l_size = l0 + sizeof(float) * 4 * 3 * lcm_joint_count_p[j_p[l_0]];

		lcs_vkmappedmemoryrange_p = realloc(lcs_vkmappedmemoryrange_p, sizeof(VkMappedMemoryRange) * (lcs_vkmappedmemoryrange_bl + 1));
		lcs_vkmappedmemoryrange_p[lcs_vkmappedmemoryrange_bl++] = (VkMappedMemoryRange)
		{
			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
			.memory = lc_vkdevicememory,
			.offset = l_offset,
			.size = (l_size + 63) & ~63,
			.pNext = VK_NULL_HANDLE
		};
	}
}

void lcs_set()
{
	NALI_D_INFO("mtx_init %d", mtx_init(lcs_mtx_t_p, mtx_plain))

	lcs_vkmappedmemoryrange_p = malloc(0);

	for (uint8_t l_0 = 0; l_0 < NALI_V_A_BL; ++l_0)
	{
		lcs_vkdescriptorset_p[l_0] = malloc(0);

		v_a_p_array[l_0] = malloc(0);
		v_a_bl1_p_array[l_0] = malloc(0);
		v_b_vkdevicesize_p_array[l_0] = malloc(0);
		v_s_p_array[l_0] = malloc(0);

		lcs_add_vkdevicesize_p[l_0] = malloc(0);
	}
}

static void add(uint8_t a)
{
	mtx_lock(lcs_mtx_t_p);

	lcs_vkdescriptorset_p[a] = realloc(lcs_vkdescriptorset_p[a], sizeof(VkDescriptorSet) * (v_a_bl0_array[a] + 1));
	VkWriteDescriptorSet vkwritedescriptorset_array[lcs_add_i_bl_p[l_0] * NALI_LCS_D_SIZE];
	VkDescriptorBufferInfo vkdescriptorbufferinfo_array[lcs_add_i_bl_p[l_0] * NALI_LCS_D_SIZE];

	v_a_p_array[l_0] = realloc(v_a_p_array[l_0], sizeof(uint8_t *) * (v_a_bl0_array[l_0] + lcs_add_i_bl_p[l_0]));
	v_a_bl1_p_array[l_0] = realloc(v_a_bl1_p_array[l_0], v_a_bl0_array[l_0] + lcs_add_i_bl_p[l_0]);
	v_b_vkdevicesize_p_array[l_0] = realloc(v_b_vkdevicesize_p_array[l_0], sizeof(VkDeviceSize) * NALI_LCS_D_SIZE * (v_a_bl0_array[l_0] + lcs_add_i_bl_p[l_0]));
	v_s_p_array[l_0] = realloc(v_s_p_array[l_0], sizeof(float *) * (v_a_bl0_array[l_0] + lcs_add_i_bl_p[l_0]));
	for (uint8_t l_1 = 0; l_1 < lcs_add_i_bl_p[l_0]; ++l_1)
	{
		vkds_make(vk_device, vkdescriptorpool, &lcs_vkdescriptorsetlayout, 1, lcs_vkdescriptorset_p[l_0] + v_a_bl0_array[l_0] + lcs_add_ds_p[l_0][l_1]);

		setVkWriteDescriptorSet(lcs_vkdescriptorset_p[l_0][v_a_bl0_array[l_0] + lcs_add_ds_p[l_0][l_1]], vkdescriptorbufferinfo_array + l_1 * NALI_LCS_D_SIZE, vkwritedescriptorset_array + l_1 * NALI_LCS_D_SIZE, lcs_add_vkdevicesize_p[l_0] + l_1 * NALI_LCS_D_SIZE, lcs_add_j_p[l_0][l_1]);

		v_a_p_array[l_0][lcs_add_ds_p[l_0][l_1]] = lcs_add_a_p[l_0][l_1];
		v_a_bl1_p_array[l_0][lcs_add_ds_p[l_0][l_1]] = lcs_add_a_bl_p[l_0][l_1];
		memcpy(v_b_vkdevicesize_p_array[l_0] + lcs_add_ds_p[l_0][l_1] * NALI_LCS_D_SIZE, lcs_add_vkdevicesize_p[l_0] + l_1 * NALI_LCS_D_SIZE, sizeof(VkDeviceSize) * NALI_LCS_D_SIZE);
	}
	vkUpdateDescriptorSets(vkqd_vkdevice_p[vk_device], lcs_add_i_bl_p[l_0] * NALI_LCS_D_SIZE, vkwritedescriptorset_array, 0, VK_NULL_HANDLE);
	v_a_bl0_array[l_0] += lcs_add_i_bl_p[l_0];

	flush(l_0, lcs_add_i_bl_p[l_0], lcs_add_ds_p[l_0], lcs_add_j_p[l_0]);

	lcs_add_ds_p[l_0] = realloc(lcs_add_ds_p[l_0], 0);
	lcs_add_j_p[l_0] = realloc(lcs_add_j_p[l_0], 0);
	lcs_add_a_p[l_0] = realloc(lcs_add_a_p[l_0], 0);
	lcs_add_a_bl_p[l_0] = realloc(lcs_add_a_bl_p[l_0], 0);
	lcs_add_vkdevicesize_p[l_0] = realloc(lcs_add_vkdevicesize_p[l_0], 0);

	lcs_add_i_bl_p[l_0] = 0;

	mtx_unlock(lcs_mtx_t_p);
}

void lcs_loop()
{
	// vkResetDescriptorPool();

	// flush(lcs_update_vkdescriptorset_i_bl, lcs_update_vkdescriptorset_b_p, lcs_update_vkdescriptorset_j_p);
	// lcs_update_vkdescriptorset_i_bl = 0;

	// if (lcs_edit_vkdescriptorset_i_bl)
	// {
	// 	VkDescriptorSet free_vkdescriptorset_array[lcs_edit_vkdescriptorset_i_bl];
	// 	VkWriteDescriptorSet vkwritedescriptorset_array[lcs_add_vkdescriptorset_i_bl * NALI_LCS_D_SIZE];
	// 	VkDescriptorBufferInfo vkdescriptorbufferinfo_array[lcs_add_vkdescriptorset_i_bl * NALI_LCS_D_SIZE];
	// 	for (uint8_t l_0 = 0; l_0 < lcs_edit_vkdescriptorset_i_bl; ++l_0)
	// 	{
	// 		free_vkdescriptorset_array[l_0] = lcs_vkdescriptorset_p[v_a_bl + lcs_edit_vkdescriptorset_b_p[l_0]];

	// 		vkds_make(vk_device, vkdescriptorpool, &lcs_vkdescriptorsetlayout, 1, lcs_vkdescriptorset_array + v_a_bl + lcs_edit_vkdescriptorset_b_p[l_0]);

	// 		setVkWriteDescriptorSet(lcs_vkdescriptorset_p[v_a_bl + lcs_edit_vkdescriptorset_b_p[l_0]], vkdescriptorbufferinfo_array + l_0 * NALI_LCS_D_SIZE, vkwritedescriptorset_array + l_0 * NALI_LCS_D_SIZE, lcs_edit_vkdescriptorset_b_p[l_0]);
	// 	}
	// 	vkUpdateDescriptorSets(vkqd_vkdevice_p[vk_device], lcs_edit_vkdescriptorset_i_bl * NALI_LCS_D_SIZE, vkwritedescriptorset_array, 0, VK_NULL_HANDLE);

	// 	vkFreeDescriptorSets(vkqd_vkdevice_p[vk_device], vkdescriptorpool, lcs_edit_vkdescriptorset_i_bl, free_vkdescriptorset_array);

	// 	flush(lcs_edit_vkdescriptorset_i_bl, lcs_edit_vkdescriptorset_b_p, lcs_edit_vkdescriptorset_j_p);

	// 	free(lcs_edit_vkdescriptorset_b_p);
	// 	lcs_edit_vkdescriptorset_i_bl = 0;
	// }

	// if (lcs_free_vkdescriptorset_i_bl)
	// {
	// 	VkDescriptorSet free_vkdescriptorset_array[lcs_free_vkdescriptorset_i_bl];
	// 	VkDescriptorSet *new_vkdescriptorset_p = malloc(sizeof(VkDescriptorSet) * (v_a_bl - lcs_free_vkdescriptorset_i_bl));
	// 	uint8_t *new_v_a_bl_p = malloc(v_a_bl - lcs_free_vkdescriptorset_i_bl);
	// 	uint8_t l0 = 0, l1 = 0;

	// 	uint8_t ***new_v_a_p = malloc(sizeof(uint8_t **) * (v_a_bl - lcs_free_vkdescriptorset_i_bl));
	// 	for (uint16_t l_0 = 0; l_0 < v_a_bl; ++l_0)
	// 	{
	// 		if (l_0 == lcs_free_vkdescriptorset_i_p[l_0])
	// 		{
	// 			free(v_a_p[lcs_free_vkdescriptorset_a_p[l0]][l_0]);
	// 			v_a_p[lcs_free_vkdescriptorset_a_p[l0]][l_0] = NULL;
	// 			free_vkdescriptorset_array[l0++] = lcs_vkdescriptorset_array[l_0];
	// 		}
	// 		else
	// 		{
	// 			new_v_a_bl_p[l1] = v_a_bl_p[l_0];
	// 			new_vkdescriptorset_p[l1++] = lcs_vkdescriptorset_array[l_0];
	// 		}
	// 	}
	// 	l0 = 0;
	// 	l1 = 0;
	// 	for (uint8_t l_0 = 0; l_0 < NALI_V_A_BL; ++l_0)
	// 	{
	// 		for (uint16_t l_1 = 0; l_1 < v_a_bl; ++l_1)
	// 		{
	// 			if (v_a_p[l_0][l_1])
	// 			{
	// 				new_v_a_p[l0][l1] = v_a_p[l_0][l_1];
	// 			}
	// 		}
	// 	}

	// 	vkFreeDescriptorSets(vkqd_vkdevice_p[vk_device], vkdescriptorpool, lcs_free_vkdescriptorset_i_bl, free_vkdescriptorset_array);

	// 	free(lcs_vkdescriptorset_array);
	// 	lcs_vkdescriptorset_array = new_vkdescriptorset_p;
	// 	v_a_bl -= lcs_free_vkdescriptorset_i_bl;

	// 	free(lcs_free_vkdescriptorset_i_p);

	// 	free(lcs_free_vkdescriptorset_a_p);

	// 	free(v_a_bl_p);
	// 	v_a_bl_p = new_v_a_bl_p;
	// 	lcs_free_vkdescriptorset_i_bl = 0;
	// }

	for (uint8_t l_0 = 0; l_0 < NALI_V_A_BL; ++l_0)
	{
		if (lcs_add_i_bl_p[l_0])
		{
			
		}
	}

	//pre data only | test
	for (uint8_t l_0 = 0; l_0 < lcs_write_fp_bl; ++l_0)
	{
		lcs_write_fp[l_0](l_0);
		//write without flush
		//write and flush
	}

	if (lcs_vkmappedmemoryrange_bl)
	{
		vkFlushMappedMemoryRanges(vkqd_vkdevice_p[vk_device], lcs_vkmappedmemoryrange_bl, lcs_vkmappedmemoryrange_p);
		lcs_vkmappedmemoryrange_p = realloc(lcs_vkmappedmemoryrange_p, 0);
		lcs_vkmappedmemoryrange_bl = 0;
	}
}

void lcs_vk()
{
	VkDescriptorPoolSize vkdescriptorpoolsize_array[NALI_LCS_D_SIZE];
	setVkDescriptorPoolSize(vkdescriptorpoolsize_array);
	vkdsp_make(vk_device, vkdescriptorpoolsize_array, NALI_LCS_D_SIZE, &vkdescriptorpool);
	setVkDescriptorSetLayout(&lcs_vkdescriptorsetlayout);
}

void lcs_freeVk(uint32_t device)
{
	VkDevice vkdevice = vkqd_vkdevice_p[device];

	vkDestroyDescriptorSetLayout(vkdevice, lcs_vkdescriptorsetlayout, VK_NULL_HANDLE);
	vkDestroyDescriptorPool(vkdevice, vkdescriptorpool, VK_NULL_HANDLE);

	for (uint8_t l_0 = 0; l_0 < NALI_V_A_BL; ++l_0)
	{
		free(lcs_vkdescriptorset_p[l_0]);

		free(lcs_add_ds_p[l_0]);
		free(lcs_add_j_p[l_0]);
		free(lcs_add_a_p[l_0]);
		free(lcs_add_a_bl_p[l_0]);

		free(lcs_add_vkdevicesize_p[l_0]);
	}

	free(lcs_vkmappedmemoryrange_p);

	free(lcs_write_fp);
}

void lcs_free()
{
	for (uint8_t l_0 = 0; l_0 < NALI_V_A_BL; ++l_0)
	{
		for (uint16_t l_1 = 0; l_1 < v_a_bl0_array[l_0]; ++l_1)
		{
			free(v_a_p_array[l_0][l_1]);
		}
		free(v_a_bl1_p_array[l_0]);
		free(v_a_p_array[l_0]);

		free(v_b_vkdevicesize_p_array[l_0]);

		free(v_s_p_array[l_0]);
	}

	free(v_i_p);

	mtx_destroy(lcs_mtx_t_p);
}