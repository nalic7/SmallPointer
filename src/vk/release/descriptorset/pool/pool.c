void vk_makeDescriptorPool(uint32_t device, VkDescriptorPoolCreateFlags vkdescriptorpoolcreateflags, VkDescriptorPool *vkdescriptorpool_p)
{
	VkDescriptorPoolSize vkdescriptorpoolsize =
	{
		.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = 1
	};

	VkDescriptorPoolCreateInfo vkdescriptorpoolcreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.poolSizeCount = 1,
		.pPoolSizes = &vkdescriptorpoolsize,
		.maxSets = 1,

		.flags = vkdescriptorpoolcreateflags,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateDescriptorPool(m_vkdevice_p[device], &vkdescriptorpoolcreateinfo, VK_NULL_HANDLE, vkdescriptorpool_p);
}