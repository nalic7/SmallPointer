void vk_setPipelineInputAssemblyStateCreateInfo(VkPipelineInputAssemblyStateCreateInfo *vkpipelineinputassemblystatecreateinfo_p)
{
	*vkpipelineinputassemblystatecreateinfo_p = (VkPipelineInputAssemblyStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		.primitiveRestartEnable = VK_FALSE,
		.flags = 0,
		.pNext = VK_NULL_HANDLE
	};
}