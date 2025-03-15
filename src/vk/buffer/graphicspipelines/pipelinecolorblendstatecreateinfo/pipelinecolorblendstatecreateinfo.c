void vk_setPipelineColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState* vkpipelinecolorblendattachmentstate_ptr, VkPipelineColorBlendStateCreateFlags vkpipelinecolorblendstatecreateflags, VkPipelineColorBlendStateCreateInfo* vkpipelinecolorblendstatecreateinfo_ptr)
{
	*vkpipelinecolorblendstatecreateinfo_ptr = (VkPipelineColorBlendStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.logicOpEnable = VK_FALSE,
		.logicOp = VK_LOGIC_OP_COPY,
		.attachmentCount = 1,
		.pAttachments = vkpipelinecolorblendattachmentstate_ptr,
		.blendConstants[0] = 0.0F,
		.blendConstants[1] = 0.0F,
		.blendConstants[2] = 0.0F,
		.blendConstants[3] = 0.0F,
		.flags = vkpipelinecolorblendstatecreateflags,
		.pNext = VK_NULL_HANDLE
	};
}