void smpt_rd_vkw_dstsMmake(uint32_t device, VkDescriptorSet *Pvkdescriptorset)
{
	SMPT_DBmR2L
	(
		"vkAllocateDescriptorSets %d",
		vkAllocateDescriptorSets
		(
			smpt_rd_vkq_dvP[device],
			&(VkDescriptorSetAllocateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
				.descriptorPool = smpt_rd_vkw_dstspV,
				.descriptorSetCount = 1,
				.pSetLayouts = &smpt_rd_vkw_dsts_loV,
				.pNext = VK_NULL_HANDLE
			},
			Pvkdescriptorset
		)
	)
}
