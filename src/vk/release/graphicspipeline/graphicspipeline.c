void vkgpl_make(uint32_t device, VkPipelineShaderStageCreateInfo *vkpipelineshaderstagecreateinfo_p, VkRenderPass vkrenderpass, VkPipelineLayout vkpipelinelayout, VkPipeline *vkpipeline_p)
{
	LC_setVkVertexInputBindingDescription(vkvertexinputbindingdescription)
	LC_setVkVertexInputAttributeDescription(vkvertexinputattributedescription_array)
	VK_setPipelineVertexInputStateCreateInfo(&vkvertexinputbindingdescription, vkvertexinputattributedescription_array, 2, vkpipelinevertexinputstatecreateinfo)

	VK_setPipelineInputAssemblyStateCreateInfo(vkpipelineinputassemblystatecreateinfo)

	VK_setPipelineViewportStateCreateInfo(vkpipelineviewportstatecreateinfo)

	VK_setPipelineRasterizationStateCreateInfo(vkpipelinerasterizationstatecreateinfo)
	VK_setPipelineMultisampleStateCreateInfo(vkpipelinemultisamplestatecreateinfo)

	VK_setVkPipelineColorBlendAttachmentState(vkpipelinecolorblendattachmentstate)
	VK_setPipelineColorBlendStateCreateInfo(&vkpipelinecolorblendattachmentstate, vkpipelinecolorblendstatecreateinfo)

	VK_setVkDynamicState(vkdynamicstate_array)
	VK_setPipelineDynamicStateCreateInfo(vkdynamicstate_array, 2, vkpipelinedynamicstatecreateinfo)

	VK_setPipelineDepthStencilStateCreateInfo(vkpipelinedepthstencilstatecreateinfo)

	NALI_D_INFO
	(
		"vkCreateGraphicsPipelines %d",
		vkCreateGraphicsPipelines
		(
			vkqd_vkdevice_p[device],
			VK_NULL_HANDLE,
			1,
			&(VkGraphicsPipelineCreateInfo)
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
				.layout = vkpipelinelayout,
				.renderPass = vkrenderpass,
				.subpass = 0,
				.basePipelineHandle = VK_NULL_HANDLE,

				.basePipelineIndex = 0,

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkpipeline_p
		)
	)
}