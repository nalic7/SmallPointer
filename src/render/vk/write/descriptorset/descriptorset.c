void smpt_rd_vkw_dsts_make(uint32_t device, VkDescriptorSet *vkdescriptorset_p)
{
	SMPT_DB_R2L
	(
		"vkAllocateDescriptorSets %d",
		vkAllocateDescriptorSets
		(
			smpt_rd_vkq_dv_p[device],
			&(VkDescriptorSetAllocateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
				.descriptorPool = smpt_rd_vkw_dstsp,
				.descriptorSetCount = 1,
				.pSetLayouts = &smpt_rd_vkw_dsts_lo,
				.pNext = VK_NULL_HANDLE
			},
			vkdescriptorset_p
		)
	)
}
