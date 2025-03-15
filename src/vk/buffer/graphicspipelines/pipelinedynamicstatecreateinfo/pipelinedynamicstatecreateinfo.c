void vk_setPipelineDynamicStateCreateInfo(VkDynamicState* vkdynamicstate_ptr, uint32_t vkdynamicstate_ptr_size, VkPipelineDynamicStateCreateFlags vkpipelinedynamicstatecreateflags, VkPipelineDynamicStateCreateInfo* vkpipelinedynamicstatecreateinfo_ptr)
{
	*vkpipelinedynamicstatecreateinfo_ptr = (VkPipelineDynamicStateCreateInfo)
	{
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.dynamicStateCount = vkdynamicstate_ptr_size,
		.pDynamicStates = vkdynamicstate_ptr,
		.flags = vkpipelinedynamicstatecreateflags,
		.pNext = VK_NULL_HANDLE
	};
}