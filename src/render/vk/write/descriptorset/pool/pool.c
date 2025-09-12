VkDescriptorPool smpt_rd_vkw_dstsp;

void smpt_rd_vkw_dstsp_make(uint32_t device)
{
	VkDescriptorPoolSize vkdescriptorpoolsize =
	{
		.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = SMPTRmMI * SMPT_RD_VKW_DSTSLO_L
	};

	SMPT_DBmR2L
	(
		"vkCreateDescriptorPool %d",
		vkCreateDescriptorPool
		(
			smpt_rd_vkq_dv_p[device],
			&(VkDescriptorPoolCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
				.poolSizeCount = 1,
				.pPoolSizes = &vkdescriptorpoolsize,
				.maxSets = SMPTRmMI,

				.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&smpt_rd_vkw_dstsp
		)
	)
}

void smpt_rd_vkw_dstsp_free(uint32_t device)
{
	vkDestroyDescriptorPool(smpt_rd_vkq_dv_p[device], smpt_rd_vkw_dstsp, VK_NULL_HANDLE);
}
