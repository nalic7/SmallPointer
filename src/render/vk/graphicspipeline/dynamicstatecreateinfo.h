#ifndef _VK_GRAPHICSPIPELINE_DYNAMICSTATECREATEINFO_H
#define _VK_GRAPHICSPIPELINE_DYNAMICSTATECREATEINFO_H

//VK_DYNAMIC_STATE_CULL_MODE
//VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE
//VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE
//VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE
#define vk_setVkDynamicState(name) \
	VkDynamicState name[] = \
	{ \
		VK_DYNAMIC_STATE_VIEWPORT, \
		VK_DYNAMIC_STATE_SCISSOR \
	};

#define vk_setPipelineDynamicStateCreateInfo(vkdynamicstate_p, vkdynamicstate_p_size, name) \
	VkPipelineDynamicStateCreateInfo name = \
	{ \
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO, \
		.dynamicStateCount = vkdynamicstate_p_size, \
		.pDynamicStates = vkdynamicstate_p, \
		.flags = 0, \
		.pNext = VK_NULL_HANDLE \
	};

#endif