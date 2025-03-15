void vk_setPipelineVertexInputStateCreateInfo(VkPipelineVertexInputStateCreateFlags vkpipelinevertexinputstatecreateflags, VkPipelineVertexInputStateCreateInfo* vkpipelinevertexinputstatecreateinfo_ptr)
{
	*vkpipelinevertexinputstatecreateinfo_ptr = (VkPipelineVertexInputStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.vertexBindingDescriptionCount = 0,
		.pVertexBindingDescriptions = VK_NULL_HANDLE,
		.vertexAttributeDescriptionCount = 0,
		.pVertexAttributeDescriptions = VK_NULL_HANDLE,
		.flags = vkpipelinevertexinputstatecreateflags,
		.pNext = VK_NULL_HANDLE
	};
}