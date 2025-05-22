void vkcb_make(uint32_t device, uint32_t graphic, VkCommandBuffer *vkcommandbuffer_p, uint32_t size)
{
	nali_info
	(
		"vkAllocateCommandBuffers %d",
		vkAllocateCommandBuffers
		(
			vkqd_vkdevice_p[device],
			&(VkCommandBufferAllocateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
				.commandPool = vkcbcp_vkcommandpool_p[device][graphic],
				.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
				.commandBufferCount = size,
				.pNext = VK_NULL_HANDLE
			},
			vkcommandbuffer_p
		)
	)
}