void vk_makeGraphicsPipeline(uint32_t device, VkPipelineShaderStageCreateInfo *vkpipelineshaderstagecreateinfo_p, VkRenderPass vkrenderpass, VkPipelineLayout vkpipelinelayout, VkPipeline *vkpipeline_p)
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

	VK_setVkPipelineColorBlendAttachmentState(vkpipelinecolorblendattachmentstate)
	VK_setPipelineColorBlendStateCreateInfo(&vkpipelinecolorblendattachmentstate, vkpipelinecolorblendstatecreateinfo)

	VK_setVkDynamicState(vkdynamicstate_array)
	VK_setPipelineDynamicStateCreateInfo(vkdynamicstate_array, 2, vkpipelinedynamicstatecreateinfo)

	VkPipelineDepthStencilStateCreateInfo vkpipelinedepthstencilstatecreateinfo;
	vk_setPipelineDepthStencilStateCreateInfo(&vkpipelinedepthstencilstatecreateinfo);

	nali_info
	(
		"vkCreateGraphicsPipelines %d",
		vkCreateGraphicsPipelines
		(
			vkdevice,
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