void _vk_pl_lo_make(uint32_t device, VkPipelineLayout *vkpipelinelayout_p)
{
	_DB_R2L
	(
		"vkCreatePipelineLayout %d",
		vkCreatePipelineLayout
		(
			_vkq_dv_p[device],
			&(VkPipelineLayoutCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,

				.setLayoutCount = 1,
				.pSetLayouts = &_rd_vk_dstslo,

				.pushConstantRangeCount = 0,
				.pPushConstantRanges = VK_NULL_HANDLE,

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkpipelinelayout_p
		)
	)
}
