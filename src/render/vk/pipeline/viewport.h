#ifndef _RD_VK_PL_VP_H
	#define _RD_VK_PL_VP_H

	#define _RD_VK_PL_VP_SACAIF(name) \
		VkPipelineViewportStateCreateInfo name = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, \
			.viewportCount = 1, \
			.pViewports = VK_NULL_HANDLE, \
			.scissorCount = 1, \
			.pScissors = VK_NULL_HANDLE, \
			.flags = 0, \
			.pNext = VK_NULL_HANDLE \
		};
#endif
