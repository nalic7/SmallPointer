VkDescriptorPool _rd_vkw_dstsp;

void _rd_vkw_dstsp_make(uint32_t device)
{
	VkDescriptorPoolSize vkdescriptorpoolsize =
	{
		.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = _RB_MIM * _RD_VKW_DSTSLO_L
	};

	_DB_R2L
	(
		"vkCreateDescriptorPool %d",
		vkCreateDescriptorPool
		(
			_rd_vkq_dv_p[device],
			&(VkDescriptorPoolCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
				.poolSizeCount = 1,
				.pPoolSizes = &vkdescriptorpoolsize,
				.maxSets = _RB_MIM,

				.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&_rd_vkw_dstsp
		)
	)
}

void _rd_vkw_dstsp_free(uint32_t device)
{
	vkDestroyDescriptorPool(_rd_vkq_dv_p[device], _rd_vkw_dstsp, VK_NULL_HANDLE);
}
