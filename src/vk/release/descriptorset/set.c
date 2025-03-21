void vk_makeDescriptorSet(uint32_t device, VkDescriptorPool *vkdescriptorpool_p, VkDescriptorSetLayout *vkdescriptorsetlayout_p, VkDescriptorSet *vkdescriptorset_p)
{
	VkDescriptorSetAllocateInfo vkdescriptorsetallocateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
		.descriptorPool = *vkdescriptorpool_p,
		.descriptorSetCount = 1,
		.pSetLayouts = vkdescriptorsetlayout_p,
		.pNext = VK_NULL_HANDLE
	};

	vkAllocateDescriptorSets(m_vkdevice_p[device], &vkdescriptorsetallocateinfo, vkdescriptorset_p);
}

void update(uint32_t device, VkDeviceSize vkdevicesize, VkBuffer *vkbuffer_p, VkDescriptorSet *vkdescriptorset_p)
{
	VkDescriptorBufferInfo vkdescriptorbufferinfo =
	{
		.buffer = *vkbuffer_p,
		.offset = 0,
		.range = vkdevicesize
	};
	VkWriteDescriptorSet vkwritedescriptorset =
	{
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.dstSet = *vkdescriptorset_p,
		.dstBinding = 0,
		.dstArrayElement = 0,
		.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,//VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
		.descriptorCount = 1,

		.pImageInfo = VK_NULL_HANDLE,
		.pBufferInfo = &vkdescriptorbufferinfo,
		.pTexelBufferView = VK_NULL_HANDLE,

		.pNext = VK_NULL_HANDLE
	};
	vkUpdateDescriptorSets(m_vkdevice_p[device], 1, &vkwritedescriptorset, 0, VK_NULL_HANDLE);
}

float nali_uniform[] =
{
	//m4x4
	//m4x4
	//m4x4
};

//VkBufferCreateInfo
//.size = sizeof(nali_uniform)
//.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT