void vk_setPipelineDynamicStateCreateInfo(VkDynamicState* vkdynamicstate_p, uint32_t vkdynamicstate_p_size, VkPipelineDynamicStateCreateFlags vkpipelinedynamicstatecreateflags, VkPipelineDynamicStateCreateInfo* vkpipelinedynamicstatecreateinfo_p)
{
	*vkpipelinedynamicstatecreateinfo_p = (VkPipelineDynamicStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.dynamicStateCount = vkdynamicstate_p_size,
		.pDynamicStates = vkdynamicstate_p,
		.flags = vkpipelinedynamicstatecreateflags,
		.pNext = VK_NULL_HANDLE
	};
}