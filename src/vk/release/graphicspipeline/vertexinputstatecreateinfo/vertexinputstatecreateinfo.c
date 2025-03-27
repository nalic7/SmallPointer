void vk_setPipelineVertexInputStateCreateInfo(VkVertexInputBindingDescription *vkvertexinputbindingdescription_p, VkVertexInputAttributeDescription *vkvertexinputattributedescription_p, uint8_t vkvertexinputattributedescription_size, VkPipelineVertexInputStateCreateInfo *vkpipelinevertexinputstatecreateinfo_p)
{
	*vkpipelinevertexinputstatecreateinfo_p = (VkPipelineVertexInputStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.vertexBindingDescriptionCount = 1,
		.pVertexBindingDescriptions = vkvertexinputbindingdescription_p,
		.vertexAttributeDescriptionCount = vkvertexinputattributedescription_size,
		.pVertexAttributeDescriptions = vkvertexinputattributedescription_p,
		.flags = 0,
		.pNext = VK_NULL_HANDLE
	};
}