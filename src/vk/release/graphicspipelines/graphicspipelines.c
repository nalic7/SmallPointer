void vk_makeGraphicsPipeline(uint32_t device, VkPipelineCreateFlags vkpipelinecreateflags, VkRenderPass *vkrenderpass_p, VkPipelineLayout *vkpipelinelayout_p, VkPipeline *vkpipeline_p)
{
	VkDevice vkdevice = m_vkdevice_p[device];

	vk_makePipelineLayout(device, 0, vkpipelinelayout_p);

	VkShaderModule vkshadermodule_vert;
	VkShaderModule vkshadermodule_frag;
	VkPipelineShaderStageCreateInfo vkpipelineshaderstagecreateinfo_array[2];
	vk_setVkPipelineShaderStageCreateInfo(device, 0, 0, &vkshadermodule_vert, &vkshadermodule_frag, vkpipelineshaderstagecreateinfo_array);

	VkVertexInputBindingDescription vkvertexinputbindingdescription_array;
	VkVertexInputAttributeDescription vkvertexinputattributedescription_array[2];
	lc_setVkVertexInputBindingDescription(&vkvertexinputbindingdescription_array);
	lc_setVkVertexInputAttributeDescription(vkvertexinputattributedescription_array);
	VkPipelineVertexInputStateCreateInfo vkpipelinevertexinputstatecreateinfo;
	vk_setPipelineVertexInputStateCreateInfo(0, &vkvertexinputbindingdescription_array, vkvertexinputattributedescription_array, 2, &vkpipelinevertexinputstatecreateinfo);

	VkPipelineInputAssemblyStateCreateInfo vkpipelineinputassemblystatecreateinfo;
	vk_setPipelineInputAssemblyStateCreateInfo(0, &vkpipelineinputassemblystatecreateinfo);

	VkPipelineViewportStateCreateInfo vkpipelineviewportstatecreateinfo;
	vk_setPipelineViewportStateCreateInfo(device, 0, &vkpipelineviewportstatecreateinfo);

	VkPipelineRasterizationStateCreateInfo vkpipelinerasterizationstatecreateinfo;
	vk_setPipelineRasterizationStateCreateInfo(0, &vkpipelinerasterizationstatecreateinfo);

	VkPipelineMultisampleStateCreateInfo vkpipelinemultisamplestatecreateinfo;
	vk_setPipelineMultisampleStateCreateInfo(0, &vkpipelinemultisamplestatecreateinfo);

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
	vk_setPipelineColorBlendStateCreateInfo(&vkpipelinecolorblendattachmentstate, 0, &vkpipelinecolorblendstatecreateinfo);

	VkDynamicState vkdynamicstate_array[] =
	{
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};
	VkPipelineDynamicStateCreateInfo vkpipelinedynamicstatecreateinfo;
	vk_setPipelineDynamicStateCreateInfo(vkdynamicstate_array, 2, 0, &vkpipelinedynamicstatecreateinfo);

	VkGraphicsPipelineCreateInfo vkgraphicspipelinecreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.stageCount = 2,
		.pStages = vkpipelineshaderstagecreateinfo_array,
		.pVertexInputState = &vkpipelinevertexinputstatecreateinfo,
		.pInputAssemblyState = &vkpipelineinputassemblystatecreateinfo,
		.pTessellationState = VK_NULL_HANDLE,
		.pViewportState = &vkpipelineviewportstatecreateinfo,
		.pRasterizationState = &vkpipelinerasterizationstatecreateinfo,
		.pMultisampleState = &vkpipelinemultisamplestatecreateinfo,
		.pDepthStencilState = VK_NULL_HANDLE,
		.pColorBlendState = &vkpipelinecolorblendstatecreateinfo,
		.pDynamicState = &vkpipelinedynamicstatecreateinfo,
		.layout = *vkpipelinelayout_p,
		.renderPass = *vkrenderpass_p,
		.subpass = 0,
		.basePipelineHandle = VK_NULL_HANDLE,

		.basePipelineIndex = 0,

		.flags = vkpipelinecreateflags,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateGraphicsPipelines(vkdevice, VK_NULL_HANDLE, 1, &vkgraphicspipelinecreateinfo, VK_NULL_HANDLE, vkpipeline_p);

	vkDestroyShaderModule(vkdevice, vkshadermodule_frag, VK_NULL_HANDLE);
	vkDestroyShaderModule(vkdevice, vkshadermodule_vert, VK_NULL_HANDLE);
}