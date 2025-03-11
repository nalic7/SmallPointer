void vk_makePipelineLayout(uint32_t device, VkPipelineLayoutCreateFlags vkpipelinelayoutcreateflags, VkPipelineLayout* vkpipelinelayout_ptr)
{
	VkPipelineLayoutCreateInfo vkpipelinelayoutcreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,

		.setLayoutCount = 0,
		.pSetLayouts = VK_NULL_HANDLE,

		.pushConstantRangeCount = 0,
		.pPushConstantRanges = VK_NULL_HANDLE,

		.flags = vkpipelinelayoutcreateflags,
		.pNext = VK_NULL_HANDLE
	};

	vkCreatePipelineLayout(m_vkdevice_ptr[device], &vkpipelinelayoutcreateinfo, VK_NULL_HANDLE, vkpipelinelayout_ptr);
}