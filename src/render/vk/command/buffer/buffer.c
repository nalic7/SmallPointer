void _rd_vk_cm_bf_make(uint32_t device, uint32_t graphic, VkCommandBuffer *vkcommandbuffer_p, uint32_t size)
{
	_DB_R2L
	(
		"vkAllocateCommandBuffers %d",
		vkAllocateCommandBuffers
		(
			_rd_vkq_dv_p[device],
			&(VkCommandBufferAllocateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
				.commandPool = _rd_vk_cmp_p[device][graphic],
				.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
				.commandBufferCount = size,
				.pNext = VK_NULL_HANDLE
			},
			vkcommandbuffer_p
		)
	)
}