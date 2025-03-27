void vk_makeGraphicsPipeline(uint32_t device, VkPipelineShaderStageCreateInfo *vkpipelineshaderstagecreateinfo_p, VkRenderPass *vkrenderpass_p, VkPipelineLayout *vkpipelinelayout_p, VkPipeline *vkpipeline_p)
{
	VkDevice vkdevice = m_vkdevice_p[device];

	VkVertexInputBindingDescription vkvertexinputbindingdescription_array;
	VkVertexInputAttributeDescription vkvertexinputattributedescription_array[2];
	lc_setVkVertexInputBindingDescription(&vkvertexinputbindingdescription_array);
	lc_setVkVertexInputAttributeDescription(vkvertexinputattributedescription_array);
	VkPipelineVertexInputStateCreateInfo vkpipelinevertexinputstatecreateinfo;
	vk_setPipelineVertexInputStateCreateInfo(&vkvertexinputbindingdescription_array, vkvertexinputattributedescription_array, 2, &vkpipelinevertexinputstatecreateinfo);

	VkPipelineInputAssemblyStateCreateInfo vkpipelineinputassemblystatecreateinfo;
	vk_setPipelineInputAssemblyStateCreateInfo(&vkpipelineinputassemblystatecreateinfo);

	VkPipelineViewportStateCreateInfo vkpipelineviewportstatecreateinfo;
	vk_setPipelineViewportStateCreateInfo(device, &vkpipelineviewportstatecreateinfo);

	VkPipelineRasterizationStateCreateInfo vkpipelinerasterizationstatecreateinfo;
	vk_setPipelineRasterizationStateCreateInfo(&vkpipelinerasterizationstatecreateinfo);

	VkPipelineMultisampleStateCreateInfo vkpipelinemultisamplestatecreateinfo;
	vk_setPipelineMultisampleStateCreateInfo(&vkpipelinemultisamplestatecreateinfo);

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
	VkPipelineColorBlendStateCreateInfo vkpipelinecolorblendstatecreateinfo;
	vk_setPipelineColorBlendStateCreateInfo(&vkpipelinecolorblendattachmentstate, &vkpipelinecolorblendstatecreateinfo);

	VkDynamicState vkdynamicstate_array[] =
	{
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};
	VkPipelineDynamicStateCreateInfo vkpipelinedynamicstatecreateinfo;
	vk_setPipelineDynamicStateCreateInfo(vkdynamicstate_array, 2, &vkpipelinedynamicstatecreateinfo);

	VkPipelineDepthStencilStateCreateInfo vkpipelinedepthstencilstatecreateinfo;
	vk_setPipelineDepthStencilStateCreateInfo(&vkpipelinedepthstencilstatecreateinfo);

	VkGraphicsPipelineCreateInfo vkgraphicspipelinecreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.stageCount = 2,
		.pStages = vkpipelineshaderstagecreateinfo_p,
		.pVertexInputState = &vkpipelinevertexinputstatecreateinfo,
		.pInputAssemblyState = &vkpipelineinputassemblystatecreateinfo,
		.pTessellationState = VK_NULL_HANDLE,
		.pViewportState = &vkpipelineviewportstatecreateinfo,
		.pRasterizationState = &vkpipelinerasterizationstatecreateinfo,
		.pMultisampleState = &vkpipelinemultisamplestatecreateinfo,
		.pDepthStencilState = &vkpipelinedepthstencilstatecreateinfo,
		.pColorBlendState = &vkpipelinecolorblendstatecreateinfo,
		.pDynamicState = &vkpipelinedynamicstatecreateinfo,
		.layout = *vkpipelinelayout_p,
		.renderPass = *vkrenderpass_p,
		.subpass = 0,
		.basePipelineHandle = VK_NULL_HANDLE,

		.basePipelineIndex = 0,

		.flags = 0,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateGraphicsPipelines(vkdevice, VK_NULL_HANDLE, 1, &vkgraphicspipelinecreateinfo, VK_NULL_HANDLE, vkpipeline_p);
}