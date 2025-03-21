void vk_setPipelineMultisampleStateCreateInfo(VkPipelineMultisampleStateCreateFlags vkpipelinemultisamplestatecreateflags, VkPipelineMultisampleStateCreateInfo *vkpipelinemultisamplestatecreateinfo_p)
{
	*vkpipelinemultisamplestatecreateinfo_p = (VkPipelineMultisampleStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.sampleShadingEnable = VK_FALSE,
		.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
		.minSampleShading = 0,
		.pSampleMask = VK_NULL_HANDLE,
		.alphaToCoverageEnable = VK_FALSE,
		.alphaToOneEnable = VK_FALSE,
		.flags = vkpipelinemultisamplestatecreateflags,
		.pNext = VK_NULL_HANDLE
	};
}