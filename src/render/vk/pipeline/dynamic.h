#ifndef _RD_VK_PL_DNM_H
	#define _RD_VK_PL_DNM_H

	//VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE
	#define _RD_VK_PL_DNM_SET(name) \
		VkDynamicState name[] = \
		{ \
			VK_DYNAMIC_STATE_VIEWPORT, \
			VK_DYNAMIC_STATE_SCISSOR \
		};

	#define _RD_VK_PL_DNM_SACAIF(vkdynamicstate_p, vkdynamicstate_p_size, name) \
		VkPipelineDynamicStateCreateInfo name = \
		{ \
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO, \
			.dynamicStateCount = vkdynamicstate_p_size, \
			.pDynamicStates = vkdynamicstate_p, \
			.flags = 0, \
			.pNext = VK_NULL_HANDLE \
		};
#endif
