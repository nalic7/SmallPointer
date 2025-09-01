void _rd_vkw_dsts_make(uint32_t device, VkDescriptorSet *vkdescriptorset_p)
{
	_DB_R2L
	(
		"vkAllocateDescriptorSets %d",
		vkAllocateDescriptorSets
		(
			_rd_vkq_dv_p[device],
			&(VkDescriptorSetAllocateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
				.descriptorPool = _rd_vkw_dstsp,
				.descriptorSetCount = 1,
				.pSetLayouts = &_rd_vkw_dsts_lo,
				.pNext = VK_NULL_HANDLE
			},
			vkdescriptorset_p
		)
	)
}
