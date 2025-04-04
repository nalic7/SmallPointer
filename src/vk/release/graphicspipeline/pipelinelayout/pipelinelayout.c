void vk_makePipelineLayout(uint32_t device, VkDescriptorSetLayout *vkdescriptorsetlayout_p, uint32_t vkdescriptorsetlayout_size, VkPipelineLayout *vkpipelinelayout_p)
{
	nali_info
	(
		"vkCreatePipelineLayout %d",
		vkCreatePipelineLayout
		(
			m_vkdevice_p[device],
			&(VkPipelineLayoutCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,

				.setLayoutCount = vkdescriptorsetlayout_size,
				.pSetLayouts = vkdescriptorsetlayout_p,
		
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