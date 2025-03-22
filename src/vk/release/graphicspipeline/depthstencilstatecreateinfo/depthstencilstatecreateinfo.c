void vk_setPipelineDepthStencilStateCreateInfo(VkPipelineDepthStencilStateCreateFlags vkpipelinedepthstencilstatecreateflags, VkPipelineDepthStencilStateCreateInfo *vkpipelinedepthstencilstatecreateinfo_p)
{
	*vkpipelinedepthstencilstatecreateinfo_p = (VkPipelineDepthStencilStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.depthTestEnable = VK_TRUE,
		.depthWriteEnable = VK_TRUE,
		.depthCompareOp = VK_COMPARE_OP_LESS,
		.depthBoundsTestEnable = VK_FALSE,
		.stencilTestEnable = VK_FALSE,

		//VkStencilOpState
		.front = {0},
		.back = {0},
		.minDepthBounds = 0.0F,
		.maxDepthBounds = 1.0F,

		.flags = vkpipelinedepthstencilstatecreateflags,
		.pNext = VK_NULL_HANDLE
	};
}