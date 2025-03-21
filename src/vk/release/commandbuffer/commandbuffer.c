void vk_makeCommandBuffer(uint32_t device, uint32_t graphic, VkCommandBuffer *vkcommandbuffer_p, uint32_t size)
{
	VkCommandBufferAllocateInfo vkcommandbufferallocateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.commandPool = m_vkcommandpool_p[device][graphic],
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandBufferCount = size,
		.pNext = VK_NULL_HANDLE
	};
	vkAllocateCommandBuffers(m_vkdevice_p[device], &vkcommandbufferallocateinfo, vkcommandbuffer_p);
}
