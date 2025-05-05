void lc_setVkVertexInputBindingDescription(VkVertexInputBindingDescription *vkvertexinputbindingdescription_p)
{
	vkvertexinputbindingdescription_p[0] = (VkVertexInputBindingDescription)
	{
		.binding = 0,
		.stride = sizeof(float) * 3 + sizeof(uint32_t),
		.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
	};
}
void lc_setVkVertexInputAttributeDescription(VkVertexInputAttributeDescription *vkvertexinputattributedescription_p)
{
	vkvertexinputattributedescription_p[0] = (VkVertexInputAttributeDescription)
	{
		.binding = 0,
		.location = 0,
		.format = VK_FORMAT_R32G32B32_SFLOAT,
		.offset = 0
	};
	vkvertexinputattributedescription_p[1] = (VkVertexInputAttributeDescription)
	{
		.binding = 0,
		.location = 1,
		.format = VK_FORMAT_R32_UINT,
		.offset = sizeof(float) * 3
	};
}

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
		6,
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

void lc_setVkWriteDescriptorSet(VkDescriptorSet vkdescriptorset, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkWriteDescriptorSet *vkwritedescriptorset_p)
{
	vkdescriptorbufferinfo_p[0] = (VkDescriptorBufferInfo)
	{
		.buffer = m_vkbuffer_p,
		.offset = 0,
		.range = NALI_LC_V0
	};
	vk_setVkWriteDescriptorSet(m_device, 0, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[0], VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p);

	vkdescriptorbufferinfo_p[1] = (VkDescriptorBufferInfo)
	{
		.buffer = m_vkbuffer_p,
		.offset = NALI_LC_V0,
		.range = NALI_LC_V1
	};
	vk_setVkWriteDescriptorSet(m_device, 1, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[1], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, vkdescriptorset, vkwritedescriptorset_p);

	vkdescriptorbufferinfo_p[2] = (VkDescriptorBufferInfo)
	{
		.buffer = m_vkbuffer_p,
		.offset = NALI_LC_V0 + NALI_LC_V1,
		.range = NALI_LC_V2
	};
	vk_setVkWriteDescriptorSet(m_device, 1, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[2], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, vkdescriptorset, vkwritedescriptorset_p);

	vkdescriptorbufferinfo_p[3] = (VkDescriptorBufferInfo)
	{
		.buffer = m_vkbuffer_p,
		.offset = NALI_LC_V0 + NALI_LC_V1 + NALI_LC_V2,
		.range = NALI_LC_V3
	};
	vk_setVkWriteDescriptorSet(m_device, 1, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[3], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, vkdescriptorset, vkwritedescriptorset_p);

	vkdescriptorbufferinfo_p[4] = (VkDescriptorBufferInfo)
	{
		.buffer = m_vkbuffer_p,
		.offset = NALI_LC_V0 + NALI_LC_V1 + NALI_LC_V2 + NALI_LC_V3,
		.range = NALI_LC_V4
	};
	vk_setVkWriteDescriptorSet(m_device, 1, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[4], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, vkdescriptorset, vkwritedescriptorset_p);

	vkdescriptorbufferinfo_p[5] = (VkDescriptorBufferInfo)
	{
		.buffer = m_vkbuffer_p,
		.offset = NALI_LC_V0 + NALI_LC_V1 + NALI_LC_V2 + NALI_LC_V3 + NALI_LC_V4,
		.range = NALI_LC_V5
	};
	vk_setVkWriteDescriptorSet(m_device, 1, VK_NULL_HANDLE, &vkdescriptorbufferinfo_p[5], VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, vkdescriptorset, vkwritedescriptorset_p);
}