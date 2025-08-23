#ifndef _VK_GRAPHICSPIPELINE_VIEWPORTSTATECREATEINFO_H
#define _VK_GRAPHICSPIPELINE_VIEWPORTSTATECREATEINFO_H

// .pViewports = &(VkViewport)
// {
// 	.x = 0,
// 	.y = 0,
// 	.width = vksc_vkextent2d.width,
// 	.height = vksc_vkextent2d.height,
// 	.minDepth = 0.0F,
// 	.maxDepth = 1.0F
// },
// .pScissors = &(VkRect2D)
// {
// 	.offset = {.x = 0, .y = 0},
// 	.extent = vksc_vkextent2d
// },
#define VK_setPipelineViewportStateCreateInfo(name) \
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