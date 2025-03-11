void vk_makeGraphicsPipeline(uint32_t device, VkPipelineCreateFlags vkpipelinecreateflags, VkRenderPass* vkrenderpass_ptr, VkPipelineLayout* vkpipelinelayout_ptr, VkPipeline* vkpipeline_ptr)
{
	VkDevice vkdevice = m_vkdevice_ptr[device];

	vk_makePipelineLayout(device, 0, vkpipelinelayout_ptr);

	VkShaderModule vkshadermodule_vert;
	VkShaderModule vkshadermodule_frag;
	VkPipelineShaderStageCreateInfo vkpipelineshaderstagecreateinfo_array[2];
	vk_setVkPipelineShaderStageCreateInfo(device, 0, 0, &vkshadermodule_vert, &vkshadermodule_frag, vkpipelineshaderstagecreateinfo_array);

	VkPipelineVertexInputStateCreateInfo vkpipelinevertexinputstatecreateinfo;
	vk_setPipelineVertexInputStateCreateInfo(0, &vkpipelinevertexinputstatecreateinfo);

	VkPipelineInputAssemblyStateCreateInfo vkpipelineinputassemblystatecreateinfo;
	vk_setPipelineInputAssemblyStateCreateInfo(0, &vkpipelineinputassemblystatecreateinfo);

	VkPipelineViewportStateCreateInfo vkpipelineviewportstatecreateinfo;
	vk_setPipelineViewportStateCreateInfo(device, 0, &vkpipelineviewportstatecreateinfo);

	VkPipelineRasterizationStateCreateInfo vkpipelinerasterizationstatecreateinfo;
	vk_setPipelineRasterizationStateCreateInfo(0, &vkpipelinerasterizationstatecreateinfo);

	VkPipelineMultisampleStateCreateInfo vkpipelinemultisamplestatecreateinfo;
	vk_setPipelineMultisampleStateCreateInfo(0, &vkpipelinemultisamplestatecreateinfo);

	VkPipelineColorBlendStateCreateInfo vkpipelinecolorblendstatecreateinfo;
	vk_setPipelineColorBlendStateCreateInfo(0, &vkpipelinecolorblendstatecreateinfo);

	VkPipelineDynamicStateCreateInfo vkpipelinedynamicstatecreateinfo;
	vk_setPipelineDynamicStateCreateInfo(0, &vkpipelinedynamicstatecreateinfo);

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
		.layout = *vkpipelinelayout_ptr,
		.renderPass = *vkrenderpass_ptr,
		.subpass = 0,
		.basePipelineHandle = VK_NULL_HANDLE,

		.basePipelineIndex = 0,

		.flags = vkpipelinecreateflags,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateGraphicsPipelines(vkdevice, VK_NULL_HANDLE, 1, &vkgraphicspipelinecreateinfo, VK_NULL_HANDLE, vkpipeline_ptr);

	vkDestroyShaderModule(vkdevice, vkshadermodule_frag, VK_NULL_HANDLE);
	vkDestroyShaderModule(vkdevice, vkshadermodule_vert, VK_NULL_HANDLE);
}