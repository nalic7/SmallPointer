VkDescriptorPool smpt_rd_vkw_dstspV;

void smpt_rd_vkw_dstspMmake(uint32_t device)
{
	VkDescriptorPoolSize vkdescriptorpoolsize =
	{
		.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = SMPTRlMI * SMPT_RD_VKW_DSTS_LOl
	};

	SMPT_DBmR2L
	(
		"vkCreateDescriptorPool %d",
		vkCreateDescriptorPool
		(
			smpt_rd_vkq_dvP[device],
			&(VkDescriptorPoolCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
				.poolSizeCount = 1,
				.pPoolSizes = &vkdescriptorpoolsize,
				.maxSets = SMPTRlMI,

				.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&smpt_rd_vkw_dstspV
		)
	)
}

void smpt_rd_vkw_dstspMfree(uint32_t device)
{
	vkDestroyDescriptorPool(smpt_rd_vkq_dvP[device], smpt_rd_vkw_dstspV, VK_NULL_HANDLE);
}
