#ifndef NALI_VK_GRAPHICSPIPELINE_INPUTASSEMBLYSTATECREATEINFO_H
#define NALI_VK_GRAPHICSPIPELINE_INPUTASSEMBLYSTATECREATEINFO_H

#define VK_setPipelineInputAssemblyStateCreateInfo(name) \
	VkPipelineInputAssemblyStateCreateInfo name = \
	{ \
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO, \
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST, \
		.primitiveRestartEnable = VK_FALSE, \
		.flags = 0, \
		.pNext = VK_NULL_HANDLE \
	};

#endif