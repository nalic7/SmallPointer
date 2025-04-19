#ifndef NALI_VK_GRAPHICSPIPELINE_MULTISAMPLESTATECREATEINFO_H
#define NALI_VK_GRAPHICSPIPELINE_MULTISAMPLESTATECREATEINFO_H

#define VK_setPipelineMultisampleStateCreateInfo(name) \
	VkPipelineMultisampleStateCreateInfo name = \
	{ \
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO, \
		.sampleShadingEnable = NALI_VK_SAMPLE_S, \
		.rasterizationSamples = NALI_VK_SAMPLE_C, \
		.minSampleShading = NALI_VK_SAMPLE_V, \
		.pSampleMask = VK_NULL_HANDLE, \
		.alphaToCoverageEnable = VK_FALSE, \
		.alphaToOneEnable = VK_FALSE, \
		.flags = 0, \
		.pNext = VK_NULL_HANDLE \
	};

#endif