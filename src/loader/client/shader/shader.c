#define NALI_D_SIZE 3

//s0-d
static VkDescriptorPoolSize vkdescriptorpoolsize_array[NALI_D_SIZE];
static VkDescriptorPool vkdescriptorpool;
VkDescriptorSetLayout lcs_vkdescriptorsetlayout;
VkDescriptorSet *lcs_vkdescriptorset_p;
//e0-d

//s0-ubo
static VkWriteDescriptorSet *vkwritedescriptorset_p;
static VkDescriptorBufferInfo *vkdescriptorbufferinfo_p;
// static VkDescriptorImageInfo vkdescriptorimageinfo;
//e0-ubo

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
				.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
			}
		},
		NALI_D_SIZE,
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
}

static void lc_setVkWriteDescriptorSet(VkDescriptorSet vkdescriptorset, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkWriteDescriptorSet *vkwritedescriptorset_p, uint8_t step)
{
	//VK_DESCRIPTOR_TYPE_STORAGE_BUFFER
	//r-bind
	vkdescriptorbufferinfo_p[0] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = 0,
		.range = NALI_LC_MVP_BL
	};
	vkds_setVkWriteDescriptorSet(vk_device, 0, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[0], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p);

	//r-bind
	// /l\ + step = size[x-1]
	uint32_t offset;
	if (step == 0)
	{
		offset = 0;
	}
	else
	{
		offset = lcm_joint_count_p[step - 1] * sizeof(float) * 16 * 2 + lcm_joint_count_p[step - 1] * sizeof(float) * 4 * 3;
	}
	vkdescriptorbufferinfo_p[1] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = NALI_LC_MVP_BL + lcm_rgba_bl + offset,
		.range = lcm_joint_count_p[step] * sizeof(float) * 16 * 2 + lcm_joint_count_p[step] * sizeof(float) * 4 * 3
	};
	vkds_setVkWriteDescriptorSet(vk_device, 1, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[1], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 1);

	//n-bind
	vkdescriptorbufferinfo_p[2] = (VkDescriptorBufferInfo)
	{
		.buffer = lc_vkbuffer,
		.offset = NALI_LC_MVP_BL,
		.range = lcm_rgba_bl
	};
	vkds_setVkWriteDescriptorSet(vk_device, 2, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[2], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 2);
}

void lcs_vk()
{
	//s0-d
	lcs_vkdescriptorset_p = malloc(sizeof(VkDescriptorSet) * lcm_joint_count_bl);
	setVkDescriptorPoolSize(vkdescriptorpoolsize_array);
	vkdsp_make(vk_device, vkdescriptorpoolsize_array, NALI_D_SIZE, &vkdescriptorpool);
	setVkDescriptorSetLayout(&lcs_vkdescriptorsetlayout);
	//e0-d

	VkDevice vkdevice = vkqd_vkdevice_p[vk_device];

	//s0-ubo
	vkdescriptorbufferinfo_p = malloc(sizeof(VkDescriptorBufferInfo) * lcm_joint_count_bl * NALI_D_SIZE);
	vkwritedescriptorset_p = malloc(sizeof(VkWriteDescriptorSet) * lcm_joint_count_bl * NALI_D_SIZE);
	for (uint32_t l_0 = 0; l_0 < lcm_joint_count_bl; ++l_0)
	{
		vkds_make(vk_device, vkdescriptorpool, &lcs_vkdescriptorsetlayout, 1, lcs_vkdescriptorset_p + l_0);

		lc_setVkWriteDescriptorSet(lcs_vkdescriptorset_p[l_0], vkdescriptorbufferinfo_p + l_0 * NALI_D_SIZE, vkwritedescriptorset_p, l_0);
	}
	//s1-update
	vkUpdateDescriptorSets(vkdevice, lcm_joint_count_bl * NALI_D_SIZE, vkwritedescriptorset_p, 0, VK_NULL_HANDLE);
	//e1-update
	//e0-ubo
}

void lcs_freeVk(uint32_t device)
{
	VkDevice vkdevice = vkqd_vkdevice_p[device];

	vkDestroyDescriptorSetLayout(vkdevice, lcs_vkdescriptorsetlayout, VK_NULL_HANDLE);
	vkDestroyDescriptorPool(vkdevice, vkdescriptorpool, VK_NULL_HANDLE);

	free(vkdescriptorbufferinfo_p);
	free(vkwritedescriptorset_p);
	free(lcs_vkdescriptorset_p);
}