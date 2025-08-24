void vkgpl_make(uint32_t device, VkPipelineShaderStageCreateInfo *vkpipelineshaderstagecreateinfo_p, VkRenderPass vkrenderpass, VkPipelineLayout vkpipelinelayout, VkPipeline *vkpipeline_p)
{
	LCS_setVkVertexInputBindingDescription(vkvertexinputbindingdescription)
	LCS_setVkVertexInputAttributeDescription(vkvertexinputattributedescription_array)
	vk_setPipelineVertexInputStateCreateInfo(&vkvertexinputbindingdescription, vkvertexinputattributedescription_array, 2, vkpipelinevertexinputstatecreateinfo)

	vk_setPipelineInputAssemblyStateCreateInfo(vkpipelineinputassemblystatecreateinfo)

	vk_setPipelineViewportStateCreateInfo(vkpipelineviewportstatecreateinfo)

	vk_setPipelineRasterizationStateCreateInfo(vkpipelinerasterizationstatecreateinfo)
	vk_setPipelineMultisampleStateCreateInfo(vkpipelinemultisamplestatecreateinfo)

	vk_setVkPipelineColorBlendAttachmentState(vkpipelinecolorblendattachmentstate)
	vk_setPipelineColorBlendStateCreateInfo(&vkpipelinecolorblendattachmentstate, vkpipelinecolorblendstatecreateinfo)

	vk_setVkDynamicState(vkdynamicstate_array)
	vk_setPipelineDynamicStateCreateInfo(vkdynamicstate_array, 2, vkpipelinedynamicstatecreateinfo)

	vk_setPipelineDepthStencilStateCreateInfo(vkpipelinedepthstencilstatecreateinfo)

	NALI_D_INFO
	(
		"vkCreateGraphicsPipelines %d",
		vkCreateGraphicsPipelines
		(
			_vkq_dv_p[device],
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
