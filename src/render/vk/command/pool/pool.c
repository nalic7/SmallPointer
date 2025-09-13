VkCommandPool **smpt_rd_vk_cmpP;

void smpt_rd_vk_cmpMset()
{
	smpt_rd_vk_cmpP = malloc(sizeof(VkCommandPool *) * smpt_rd_vkq_dv_pscdvL);
}

void smpt_rd_vk_cmpMmake(uint32_t device)
{
	uint32_t max_queue = smpt_rd_vkqPmax_queue[device];
	smpt_rd_vk_cmpP[device] = malloc(sizeof(VkCommandPool) * max_queue);

	for (uint32_t q = 0; q < max_queue; ++q)
	{
		SMPT_DBmR2L
		(
			"vkCreateCommandPool %d",
			vkCreateCommandPool
			(
				smpt_rd_vkq_dvP[device],
				&(VkCommandPoolCreateInfo)
				{
					.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
					.queueFamilyIndex = q,
					.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
					.pNext = VK_NULL_HANDLE
				},
				VK_NULL_HANDLE,
				&smpt_rd_vk_cmpP[device][q]
			)
		)
	}
}

void smpt_rd_vk_cmpMfree()
{
	for (uint32_t d = 0; d < smpt_rd_vkq_dv_pscdvL; ++d)
	{
		for (uint32_t q = 0; q < smpt_rd_vkqPmax_queue[d]; ++q)
		{
			vkDestroyCommandPool(smpt_rd_vkq_dvP[d], smpt_rd_vk_cmpP[d][q], VK_NULL_HANDLE);
		}
		free(smpt_rd_vk_cmpP[d]);
	}

	free(smpt_rd_vk_cmpP);
}