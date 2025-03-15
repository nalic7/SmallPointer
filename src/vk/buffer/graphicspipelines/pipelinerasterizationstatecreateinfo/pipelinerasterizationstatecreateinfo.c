void vk_setPipelineRasterizationStateCreateInfo(VkPipelineRasterizationStateCreateFlags vkpipelinerasterizationstatecreateflags, VkPipelineRasterizationStateCreateInfo* vkpipelinerasterizationstatecreateinfo_ptr)
{
	*vkpipelinerasterizationstatecreateinfo_ptr = (VkPipelineRasterizationStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.depthClampEnable = VK_FALSE,
		.rasterizerDiscardEnable = VK_FALSE,
		.polygonMode = VK_POLYGON_MODE_FILL,
		.cullMode = VK_CULL_MODE_BACK_BIT,
		.frontFace = VK_FRONT_FACE_CLOCKWISE,
		.depthBiasEnable = VK_FALSE,
		.depthBiasConstantFactor = 0,
		.depthBiasClamp = 0,
		.depthBiasSlopeFactor = 0,
		.lineWidth = 1.0F,
		.flags = vkpipelinerasterizationstatecreateflags,
		.pNext = VK_NULL_HANDLE
	};
}