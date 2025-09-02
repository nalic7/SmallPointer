#ifndef SMPT_RD_VK_PL_MT_H
	#define SMPT_RD_VK_PL_MT_H

	#define SMPT_RD_VK_PL_MT_SPSACAIF(name) \
		VkPipelineMultisampleStateCreateInfo name = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO, \
			.sampleShadingEnable = SMPT_RD_VK_SAMPLE_S, \
			.rasterizationSamples = SMPT_RD_VK_SAMPLE_C, \
			.minSampleShading = SMPT_RD_VK_SAMPLE_V, \
			.pSampleMask = VK_NULL_HANDLE, \
			.alphaToCoverageEnable = VK_FALSE, \
			.alphaToOneEnable = VK_FALSE, \
			.flags = 0, \
			.pNext = VK_NULL_HANDLE \
		};
#endif
