void vk_setPipelineColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState* vkpipelinecolorblendattachmentstate_p, VkPipelineColorBlendStateCreateFlags vkpipelinecolorblendstatecreateflags, VkPipelineColorBlendStateCreateInfo* vkpipelinecolorblendstatecreateinfo_p)
{
	*vkpipelinecolorblendstatecreateinfo_p = (VkPipelineColorBlendStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.logicOpEnable = VK_FALSE,
		.logicOp = VK_LOGIC_OP_COPY,
		.attachmentCount = 1,
		.pAttachments = vkpipelinecolorblendattachmentstate_p,
		.blendConstants[0] = 0.0F,
		.blendConstants[1] = 0.0F,
		.blendConstants[2] = 0.0F,
		.blendConstants[3] = 0.0F,
		.flags = vkpipelinecolorblendstatecreateflags,
		.pNext = VK_NULL_HANDLE
	};
}