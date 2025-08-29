VkDescriptorPool _rd_vk_dstsp;

void _vk_dspsp_make(uint32_t device)
{
	VkDescriptorPoolSize vkdescriptorpoolsize =
	{
		.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = NALI_LB_MIM * _RD_VK_DSTSLO_L
	};

	_DB_R2L
	(
		"vkCreateDescriptorPool %d",
		vkCreateDescriptorPool
		(
			_vkq_dv_p[device],
			&(VkDescriptorPoolCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
				.poolSizeCount = 1,
				.pPoolSizes = &vkdescriptorpoolsize,
				.maxSets = NALI_LB_MIM,

				.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&_rd_vk_dstsp
		)
	)
}

void _rd_vk_dstsp_free(uint32_t device)
{
	vkDestroyDescriptorPool(_vkq_dv_p[device], _rd_vk_dstsp, VK_NULL_HANDLE);
}
