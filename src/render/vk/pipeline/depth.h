#ifndef SMPT_RD_VK_PLD_H
	#define SMPT_RD_VK_PLD_H

	#define SMPT_RD_VK_PLD_SC_SACAIF(name) \
		VkPipelineDepthStencilStateCreateInfo name = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO, \
			.depthTestEnable = VK_TRUE, \
			.depthWriteEnable = VK_TRUE, \
			.depthCompareOp = VK_COMPARE_OP_LESS, \
			.depthBoundsTestEnable = VK_FALSE, \
			.stencilTestEnable = VK_FALSE, \
			.front = {0}, \
			.back = {0}, \
			.minDepthBounds = 0.0F, \
			.maxDepthBounds = 1.0F, \
			.flags = 0, \
			.pNext = VK_NULL_HANDLE \
		};
#endif
