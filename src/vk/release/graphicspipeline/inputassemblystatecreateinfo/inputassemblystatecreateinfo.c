void vk_setPipelineInputAssemblyStateCreateInfo(VkPipelineInputAssemblyStateCreateFlags vkpipelineinputassemblystatecreateflags, VkPipelineInputAssemblyStateCreateInfo *vkpipelineinputassemblystatecreateinfo_p)
{
	*vkpipelineinputassemblystatecreateinfo_p = (VkPipelineInputAssemblyStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		.primitiveRestartEnable = VK_FALSE,
		.flags = vkpipelineinputassemblystatecreateflags,
		.pNext = VK_NULL_HANDLE
	};
}