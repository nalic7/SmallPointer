#define NALI_D_SIZE 6

//s0-d
static VkDescriptorPoolSize vkdescriptorpoolsize_array[NALI_D_SIZE];
static VkDescriptorPool vkdescriptorpool;
VkDescriptorSetLayout m_vkdescriptorsetlayout;
VkDescriptorSet m_vkdescriptorset;
//e0-d

//s0-ubo
static VkWriteDescriptorSet *vkwritedescriptorset_p;
static uint32_t vkwritedescriptorset_size;
static VkDescriptorBufferInfo *vkdescriptorbufferinfo_p;
// static VkDescriptorImageInfo vkdescriptorimageinfo;
//e0-ubo

void lc_setVkDescriptorSetLayout(VkDescriptorSetLayout *vkdescriptorsetlayout_p)
{
	vk_makeDescriptorSetLayout
	(
		m_device,
		(VkDescriptorSetLayoutBinding[])
		{
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
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.pImmutableSamplers = VK_NULL_HANDLE,
				.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
			},
			{
				.binding = 2,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.pImmutableSamplers = VK_NULL_HANDLE,
				.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
			},
			{
				.binding = 3,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.pImmutableSamplers = VK_NULL_HANDLE,
				.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
			},
			{
				.binding = 4,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.pImmutableSamplers = VK_NULL_HANDLE,
				.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
			},
			{
				.binding = 5,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.pImmutableSamplers = VK_NULL_HANDLE,
				.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
			}
		},
		NALI_D_SIZE,
		vkdescriptorsetlayout_p
	);
}
void lc_setVkDescriptorPoolSize(VkDescriptorPoolSize *vkdescriptorpoolsize_p)
{
	vkdescriptorpoolsize_p[0] = (VkDescriptorPoolSize)
	{
		.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = 1
	};
	vkdescriptorpoolsize_p[1] = (VkDescriptorPoolSize)
	{
		.type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		.descriptorCount = 1
	};
	vkdescriptorpoolsize_p[2] = vkdescriptorpoolsize_p[1];
	vkdescriptorpoolsize_p[3] = vkdescriptorpoolsize_p[1];
	vkdescriptorpoolsize_p[4] = vkdescriptorpoolsize_p[1];
	vkdescriptorpoolsize_p[5] = vkdescriptorpoolsize_p[1];
}

void lc_setVkWriteDescriptorSet(VkDescriptorSet vkdescriptorset, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkWriteDescriptorSet *vkwritedescriptorset_p, uint8_t step)
{
	//r-bind
	vkdescriptorbufferinfo_p[0] = (VkDescriptorBufferInfo)
	{
		.buffer = m_vkbuffer_p,
		.offset = 0,
		.range = NALI_LC_MVP_SIZE
	};
	vk_setVkWriteDescriptorSet(m_device, 0, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[0], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p);

	//r-bind
	// /l\ + step = size[x-1]
	uint32_t offset;
	if (step == 0)
	{
		offset = 0;
	}
	else
	{
		offset = m_ji_p[step - 1];
	}

	vkdescriptorbufferinfo_p[1] = (VkDescriptorBufferInfo)
	{
		.buffer = m_vkbuffer_p,
		.offset = NALI_LC_MVP_SIZE + m_rgba_size + m_max_joint * sizeof(float) * 3 + m_max_joint * sizeof(float) * 4 + m_max_joint * sizeof(float) * 3 + offset,
		.range = m_ji_p[step]
	};
	vk_setVkWriteDescriptorSet(m_device, 1, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[1], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 1);

	//n-bind
	vkdescriptorbufferinfo_p[2] = (VkDescriptorBufferInfo)
	{
		.buffer = m_vkbuffer_p,
		.offset = NALI_LC_MVP_SIZE + m_rgba_size,
		.range = m_max_joint * sizeof(float) * 3
	};
	vk_setVkWriteDescriptorSet(m_device, 2, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[2], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 2);

	//n-bind
	vkdescriptorbufferinfo_p[3] = (VkDescriptorBufferInfo)
	{
		.buffer = m_vkbuffer_p,
		.offset = NALI_LC_MVP_SIZE + m_rgba_size + m_max_joint * sizeof(float) * 3,
		.range = m_max_joint * sizeof(float) * 4
	};
	vk_setVkWriteDescriptorSet(m_device, 3, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[3], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 3);

	//n-bind
	vkdescriptorbufferinfo_p[4] = (VkDescriptorBufferInfo)
	{
		.buffer = m_vkbuffer_p,
		.offset = NALI_LC_MVP_SIZE + m_rgba_size + m_max_joint * sizeof(float) * 3 + m_max_joint * sizeof(float) * 4,
		.range = m_max_joint * sizeof(float) * 3
	};
	vk_setVkWriteDescriptorSet(m_device, 4, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[4], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 4);

	//n-bind
	vkdescriptorbufferinfo_p[5] = (VkDescriptorBufferInfo)
	{
		.buffer = m_vkbuffer_p,
		.offset = NALI_LC_MVP_SIZE,
		.range = m_rgba_size
	};
	vk_setVkWriteDescriptorSet(m_device, 5, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[5], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 5);
}

void lcs_vk()
{
	//s0-d
	lc_setVkDescriptorPoolSize(vkdescriptorpoolsize_array);
	vk_makeDescriptorSetPool(m_device, vkdescriptorpoolsize_array, NALI_D_SIZE, &vkdescriptorpool);
	lc_setVkDescriptorSetLayout(&m_vkdescriptorsetlayout);
	vk_makeDescriptorSet(m_device, vkdescriptorpool, &m_vkdescriptorsetlayout, 1, &m_vkdescriptorset);
	//e0-d

	VkDevice vkdevice = m_vkdevice_p[m_device];

	//s0-ubo
	vkdescriptorbufferinfo_p = malloc(sizeof(VkDescriptorBufferInfo) * m_joint_count_size * 6);
	vkwritedescriptorset_p = malloc(sizeof(VkWriteDescriptorSet) * m_joint_count_size * 6);
	for (uint32_t l_0 = 0; l_0 < m_joint_count_size; ++l_0)
	{
		lc_setVkWriteDescriptorSet(m_vkdescriptorset, vkdescriptorbufferinfo_p + l_0 * 6, vkwritedescriptorset_p, l_0);
	}
	//s1-update
	vkUpdateDescriptorSets(vkdevice, vkwritedescriptorset_size, vkwritedescriptorset_p, 0, VK_NULL_HANDLE);
	//e1-update
	//e0-ubo
}

void lcs_freeVk(uint32_t device)
{
	VkDevice vkdevice = m_vkdevice_p[device];

	vkDestroyDescriptorSetLayout(vkdevice, m_vkdescriptorsetlayout, VK_NULL_HANDLE);
	vkDestroyDescriptorPool(vkdevice, vkdescriptorpool, VK_NULL_HANDLE);

	free(vkdescriptorbufferinfo_p);
	free(vkwritedescriptorset_p);
}