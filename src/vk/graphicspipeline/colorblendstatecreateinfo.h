#ifndef NALI_VK_GRAPHICSPIPELINE_COLORBLENDSTATECREATEINFO_H
#define NALI_VK_GRAPHICSPIPELINE_COLORBLENDSTATECREATEINFO_H

#define VK_setVkPipelineColorBlendAttachmentState(name) \
	VkPipelineColorBlendAttachmentState name = \
	{ \
		.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT, \
		/* .blendEnable = VK_FALSE, */ \
		.blendEnable = VK_TRUE, \
		.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA, \
		.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA, \
		.colorBlendOp = VK_BLEND_OP_ADD, \
		.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE, \
		.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO, \
		.alphaBlendOp = VK_BLEND_OP_ADD, \
	};

#define VK_setPipelineColorBlendStateCreateInfo(vkpipelinecolorblendattachmentstate_p, name) \
	VkPipelineColorBlendStateCreateInfo name = \
	{ \
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO, \
		.logicOpEnable = VK_FALSE, \
		.logicOp = VK_LOGIC_OP_COPY, \
		.attachmentCount = 1, \
		.pAttachments = vkpipelinecolorblendattachmentstate_p, \
		.blendConstants[0] = 0.0F, \
		.blendConstants[1] = 0.0F, \
		.blendConstants[2] = 0.0F, \
		.blendConstants[3] = 0.0F, \
		.flags = 0, \
		.pNext = VK_NULL_HANDLE \
	};

#endif