void vk_makeDescriptorSetPool(uint32_t device, VkDescriptorPoolCreateFlags vkdescriptorpoolcreateflags, VkDescriptorPoolSize *vkdescriptorpoolsize_p, uint32_t vkdescriptorpoolsize_size, VkDescriptorPool *vkdescriptorpool_p)
{
	VkDescriptorPoolCreateInfo vkdescriptorpoolcreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.poolSizeCount = vkdescriptorpoolsize_size,
		.pPoolSizes = vkdescriptorpoolsize_p,
		.maxSets = 1,

		.flags = vkdescriptorpoolcreateflags,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateDescriptorPool(m_vkdevice_p[device], &vkdescriptorpoolcreateinfo, VK_NULL_HANDLE, vkdescriptorpool_p);
}