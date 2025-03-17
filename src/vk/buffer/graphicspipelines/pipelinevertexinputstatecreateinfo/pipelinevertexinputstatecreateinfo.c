// void test()
// {
// 	VkVertexInputBindingDescription vkvertexinputbindingdescription =
// 	{
// 		.binding = 0,
// 		.stride = sizeof(uint8_t),
// 		.inputRate = VK_VERTEX_INPUT_RATE_INSTANCE
// 	};

// 	VkVertexInputBindingDescription vkvertexinputbindingdescription =
// 	{
// 		.binding = 0,
// 		.stride = sizeof(float) * 2 * 3,
// 		.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
// 	};

// 	VkVertexInputAttributeDescription vkvertexinputattributedescription =
// 	{
// 		.binding = 0,
// 		.location = 0,
// 		.format = VK_FORMAT_R32G32_SFLOAT,
// 		.offset = 0
// 	};

// 	VkVertexInputAttributeDescription vkvertexinputattributedescription =
// 	{
// 		.binding = 0,
// 		.location = 1,
// 		.format = VK_FORMAT_R32G32B32_SFLOAT,
// 		.offset = sizeof(float) * 2
// 	};
// }

void vk_setPipelineVertexInputStateCreateInfo(VkPipelineVertexInputStateCreateFlags vkpipelinevertexinputstatecreateflags, VkPipelineVertexInputStateCreateInfo* vkpipelinevertexinputstatecreateinfo_p)
{
	// VkVertexInputBindingDescription* vkvertexinputbindingdescription_p;
	// VkVertexInputAttributeDescription* vkvertexinputattributedescription_p;
	*vkpipelinevertexinputstatecreateinfo_p = (VkPipelineVertexInputStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
		.vertexBindingDescriptionCount = 0,
		.pVertexBindingDescriptions = VK_NULL_HANDLE,//vkvertexinputbindingdescription_p,
		.vertexAttributeDescriptionCount = 0,
		.pVertexAttributeDescriptions = VK_NULL_HANDLE,//vkvertexinputattributedescription_p,
		.flags = vkpipelinevertexinputstatecreateflags,
		.pNext = VK_NULL_HANDLE
	};
}