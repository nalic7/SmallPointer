void _vk_dspsp_make(uint32_t device, VkDescriptorPoolSize *vkdescriptorpoolsize_p, uint32_t vkdescriptorpoolsize_size, VkDescriptorPool *vkdescriptorpool_p)
{
	_DB_R2L
	(
		"vkCreateDescriptorPool %d",
		vkCreateDescriptorPool
		(
			_vkq_dv_p[device],
			&(VkDescriptorPoolCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
				.poolSizeCount = vkdescriptorpoolsize_size,
				.pPoolSizes = vkdescriptorpoolsize_p,
				.maxSets = NALI_LB_MIM,

				.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkdescriptorpool_p
		)
	)
}
