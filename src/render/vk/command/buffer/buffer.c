void smpt_rd_vk_cm_bfMmake(uint32_t device, uint32_t graphic, VkCommandBuffer *vkcommandbuffer_p, uint32_t size)
{
	SMPT_DBmR2L
	(
		"vkAllocateCommandBuffers %d",
		vkAllocateCommandBuffers
		(
			smpt_rd_vkq_dvP[device],
			&(VkCommandBufferAllocateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
				.commandPool = smpt_rd_vk_cmpP[device][graphic],
				.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
				.commandBufferCount = size,
				.pNext = VK_NULL_HANDLE
			},
			vkcommandbuffer_p
		)
	)
}