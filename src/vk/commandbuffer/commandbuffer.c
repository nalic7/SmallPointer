void vk_makeCommandBuffer(uint32_t device, uint32_t graphic, VkCommandBuffer* vkcommandbuffer_ptr, uint32_t size)
{
	VkCommandBufferAllocateInfo vkcommandbufferallocateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.commandPool = m_vkcommandpool_ptr[device][graphic],
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.pNext = VK_NULL_HANDLE,
		.commandBufferCount = size
	};
	vkAllocateCommandBuffers(m_vkdevice_ptr[device], &vkcommandbufferallocateinfo, vkcommandbuffer_ptr);
}
