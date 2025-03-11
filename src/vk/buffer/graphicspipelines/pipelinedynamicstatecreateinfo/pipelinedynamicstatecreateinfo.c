void vk_setPipelineDynamicStateCreateInfo(VkPipelineDynamicStateCreateFlags vkpipelinedynamicstatecreateflags, VkPipelineDynamicStateCreateInfo* vkpipelinedynamicstatecreateinfo_ptr)
{
	VkDynamicState vkdynamicstate_array[] =
	{
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};
	vkpipelinedynamicstatecreateinfo_ptr->sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	vkpipelinedynamicstatecreateinfo_ptr->dynamicStateCount = sizeof(vkdynamicstate_array) / sizeof(VkDynamicState);
	vkpipelinedynamicstatecreateinfo_ptr->pDynamicStates = vkdynamicstate_array;
	vkpipelinedynamicstatecreateinfo_ptr->flags = vkpipelinedynamicstatecreateflags;
	vkpipelinedynamicstatecreateinfo_ptr->pNext = VK_NULL_HANDLE;
}