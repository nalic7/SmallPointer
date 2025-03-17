void vk_setPipelineViewportStateCreateInfo(uint32_t device, VkPipelineViewportStateCreateFlags vkpipelineviewportstatecreateflags, VkPipelineViewportStateCreateInfo* vkpipelineviewportstatecreateinfo_p)
{
	VkExtent2D vkextent2d = m_vkswapchainkhr_vkextent2d_p[device];
	VkViewport vkviewport =
	{
		.x = 0,
		.y = 0,
		.width = vkextent2d.width,
		.height = vkextent2d.height,
		.minDepth = 0.0F,
		.maxDepth = 1.0F
	};
	VkRect2D vkrect2d =
	{
		.offset = {0, 0},
		.extent = vkextent2d
	};
	*vkpipelineviewportstatecreateinfo_p = (VkPipelineViewportStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.viewportCount = 1,
		.pViewports = &vkviewport,
		.scissorCount = 1,
		.pScissors = &vkrect2d,
		.flags = vkpipelineviewportstatecreateflags,
		.pNext = VK_NULL_HANDLE
	};
}