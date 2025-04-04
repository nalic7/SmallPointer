void vk_makeDescriptorSetPool(uint32_t device, VkDescriptorPoolSize *vkdescriptorpoolsize_p, uint32_t vkdescriptorpoolsize_size, VkDescriptorPool *vkdescriptorpool_p)
{
	nali_info
	(
		"vkCreateDescriptorPool %d",
		vkCreateDescriptorPool
		(
			m_vkdevice_p[device],
			&(VkDescriptorPoolCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
				.poolSizeCount = vkdescriptorpoolsize_size,
				.pPoolSizes = vkdescriptorpoolsize_p,
				.maxSets = 1,
		
				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkdescriptorpool_p
		)
	)
}