void smpt_rd_vk_pl_loMmake(uint32_t device, VkPipelineLayout *Pvkpipelinelayout)
{
	SMPT_DBmR2L
	(
		"vkCreatePipelineLayout %d",
		vkCreatePipelineLayout
		(
			smpt_rd_vkq_dvP[device],
			&(VkPipelineLayoutCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,

				.setLayoutCount = 1,
				.pSetLayouts = &smpt_rd_vkw_dsts_loV,

				.pushConstantRangeCount = 0,
				.pPushConstantRanges = VK_NULL_HANDLE,

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			Pvkpipelinelayout
		)
	)
}
