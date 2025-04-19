#ifndef NALI_VK_GRAPHICSPIPELINE_VERTEXINPUTSTATECREATEINFO_H
#define NALI_VK_GRAPHICSPIPELINE_VERTEXINPUTSTATECREATEINFO_H

#define VK_setPipelineVertexInputStateCreateInfo(vkvertexinputbindingdescription_p, vkvertexinputattributedescription_p, vkvertexinputattributedescription_size, name) \
	VkPipelineVertexInputStateCreateInfo name = \
	{ \
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO, \
		.vertexBindingDescriptionCount = 1, \
		.pVertexBindingDescriptions = vkvertexinputbindingdescription_p, \
		.vertexAttributeDescriptionCount = vkvertexinputattributedescription_size, \
		.pVertexAttributeDescriptions = vkvertexinputattributedescription_p, \
		.flags = 0, \
		.pNext = VK_NULL_HANDLE \
	};

#endif