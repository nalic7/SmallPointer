#ifndef _VK_GRAPHICSPIPELINE_MULTISAMPLESTATECREATEINFO_H
#define _VK_GRAPHICSPIPELINE_MULTISAMPLESTATECREATEINFO_H

#define vk_setPipelineMultisampleStateCreateInfo(name) \
	VkPipelineMultisampleStateCreateInfo name = \
	{ \
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO, \
		.sampleShadingEnable = _VK_SAMPLE_S, \
		.rasterizationSamples = _VK_SAMPLE_C, \
		.minSampleShading = _VK_SAMPLE_V, \
		.pSampleMask = VK_NULL_HANDLE, \
		.alphaToCoverageEnable = VK_FALSE, \
		.alphaToOneEnable = VK_FALSE, \
		.flags = 0, \
		.pNext = VK_NULL_HANDLE \
	};

#endif