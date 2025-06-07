void vkdsp_make(uint32_t device, VkDescriptorPoolSize *vkdescriptorpoolsize_p, uint32_t vkdescriptorpoolsize_size, VkDescriptorPool *vkdescriptorpool_p)
{
	NALI_D_INFO
	(
		"vkCreateDescriptorPool %d",
		vkCreateDescriptorPool
		(
			vkqd_vkdevice_p[device],
			&(VkDescriptorPoolCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
				.poolSizeCount = vkdescriptorpoolsize_size,
				.pPoolSizes = vkdescriptorpoolsize_p,
				.maxSets = 1,

				.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkdescriptorpool_p
		)
	)
}