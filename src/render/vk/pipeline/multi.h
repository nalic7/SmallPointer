#ifndef SMPT_RD_VK_PLhMT
	#define SMPT_RD_VK_PLhMT

	#define SMPT_RD_VK_PL_MTmSPSACAIF(name) \
		VkPipelineMultisampleStateCreateInfo name = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO, \
			.sampleShadingEnable = smpt_rd_vkUsample_count ? VK_TRUE : VK_FALSE, \
			.rasterizationSamples = smpt_rd_vkUsample_count, \
			.minSampleShading = 1.0F, \
			.pSampleMask = VK_NULL_HANDLE, \
			.alphaToCoverageEnable = VK_FALSE, \
			.alphaToOneEnable = VK_FALSE, \
			.flags = 0, \
			.pNext = VK_NULL_HANDLE \
		};
#endif
