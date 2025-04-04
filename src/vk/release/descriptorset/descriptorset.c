void vk_makeDescriptorSet(uint32_t device, VkDescriptorPool vkdescriptorpool, VkDescriptorSetLayout *vkdescriptorsetlayout_p, uint32_t vkdescriptorsetlayout_size, VkDescriptorSet *vkdescriptorset_p)
{
	nali_info
	(
		"vkAllocateDescriptorSets %d",
		vkAllocateDescriptorSets
		(
			m_vkdevice_p[device],
			&(VkDescriptorSetAllocateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
				.descriptorPool = vkdescriptorpool,
				.descriptorSetCount = vkdescriptorsetlayout_size,
				.pSetLayouts = vkdescriptorsetlayout_p,
				.pNext = VK_NULL_HANDLE
			},
			vkdescriptorset_p
		)
	)
}

void vk_setVkWriteDescriptorSet(uint32_t device, uint32_t bind, VkDescriptorImageInfo *vkdescriptorimageinfo_p, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkDescriptorType vkdescriptortype, VkDescriptorSet vkdescriptorset, VkWriteDescriptorSet *vkwritedescriptorset_p)
{
	*vkwritedescriptorset_p = (VkWriteDescriptorSet)
	{
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.dstSet = vkdescriptorset,
		.dstBinding = bind,
		.dstArrayElement = 0,
		.descriptorType = vkdescriptortype,//VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
		.descriptorCount = 1,

		.pImageInfo = vkdescriptorimageinfo_p,
		.pBufferInfo = vkdescriptorbufferinfo_p,
		.pTexelBufferView = VK_NULL_HANDLE,

		.pNext = VK_NULL_HANDLE
	};
	// vkUpdateDescriptorSets(m_vkdevice_p[device], 1, &vkwritedescriptorset, 0, VK_NULL_HANDLE);
}