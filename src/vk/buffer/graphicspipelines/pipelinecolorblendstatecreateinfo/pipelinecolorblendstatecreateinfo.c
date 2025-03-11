void vk_setPipelineColorBlendStateCreateInfo(VkPipelineColorBlendStateCreateFlags vkpipelinecolorblendstatecreateflags, VkPipelineColorBlendStateCreateInfo* vkpipelinecolorblendstatecreateinfo_ptr)
{
	VkPipelineColorBlendAttachmentState vkpipelinecolorblendattachmentstate =
	{
		.blendEnable = VK_FALSE,
		.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
		.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
		.colorBlendOp = VK_BLEND_OP_ADD,
		.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
		.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
		.alphaBlendOp = VK_BLEND_OP_ADD,
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT
	};
	vkpipelinecolorblendstatecreateinfo_ptr->sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	vkpipelinecolorblendstatecreateinfo_ptr->logicOpEnable = VK_FALSE;
	vkpipelinecolorblendstatecreateinfo_ptr->logicOp = VK_LOGIC_OP_COPY;
	vkpipelinecolorblendstatecreateinfo_ptr->attachmentCount = 1;
	vkpipelinecolorblendstatecreateinfo_ptr->pAttachments = &vkpipelinecolorblendattachmentstate;
	vkpipelinecolorblendstatecreateinfo_ptr->blendConstants[0] = 0.0F;
	vkpipelinecolorblendstatecreateinfo_ptr->blendConstants[1] = 0.0F;
	vkpipelinecolorblendstatecreateinfo_ptr->blendConstants[2] = 0.0F;
	vkpipelinecolorblendstatecreateinfo_ptr->blendConstants[3] = 0.0F;
	vkpipelinecolorblendstatecreateinfo_ptr->flags = vkpipelinecolorblendstatecreateflags;
	vkpipelinecolorblendstatecreateinfo_ptr->pNext = VK_NULL_HANDLE;
}