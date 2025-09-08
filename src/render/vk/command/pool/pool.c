VkCommandPool **smpt_rd_vk_cmp_p;

void smpt_rd_vk_cmp_set()
{
	smpt_rd_vk_cmp_p = malloc(sizeof(VkCommandPool *) * smpt_rd_vkq_dv_pscdv_bl);
}

void smpt_rd_vk_cmp_make(uint32_t device)
{
	uint32_t max_queue = smpt_rd_vkq_max_queue_p[device];
	smpt_rd_vk_cmp_p[device] = malloc(sizeof(VkCommandPool) * max_queue);

	for (uint32_t q = 0; q < max_queue; ++q)
	{
		SMPT_DBmR2L
		(
			"vkCreateCommandPool %d",
			vkCreateCommandPool
			(
				smpt_rd_vkq_dv_p[device],
				&(VkCommandPoolCreateInfo)
				{
					.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
					.queueFamilyIndex = q,
					.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
					.pNext = VK_NULL_HANDLE
				},
				VK_NULL_HANDLE,
				&smpt_rd_vk_cmp_p[device][q]
			)
		)
	}
}

void smpt_rd_vk_cmp_free()
{
	for (uint32_t d = 0; d < smpt_rd_vkq_dv_pscdv_bl; ++d)
	{
		for (uint32_t q = 0; q < smpt_rd_vkq_max_queue_p[d]; ++q)
		{
			vkDestroyCommandPool(smpt_rd_vkq_dv_p[d], smpt_rd_vk_cmp_p[d][q], VK_NULL_HANDLE);
		}
		free(smpt_rd_vk_cmp_p[d]);
	}

	free(smpt_rd_vk_cmp_p);
}