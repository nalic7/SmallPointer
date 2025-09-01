VkCommandPool **_rd_vk_cmp_p;

void _rd_vk_cmp_set()
{
	_rd_vk_cmp_p = malloc(sizeof(VkCommandPool *) * _rd_vkq_dv_pscdv_bl);
}

void _rd_vk_cmp_make(uint32_t device)
{
	uint32_t max_queue = _rd_vkq_max_queue_p[device];
	_rd_vk_cmp_p[device] = malloc(sizeof(VkCommandPool) * max_queue);

	for (uint32_t q = 0; q < max_queue; ++q)
	{
		_DB_R2L
		(
			"vkCreateCommandPool %d",
			vkCreateCommandPool
			(
				_rd_vkq_dv_p[device],
				&(VkCommandPoolCreateInfo)
				{
					.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
					.queueFamilyIndex = q,
					.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
					.pNext = VK_NULL_HANDLE
				},
				VK_NULL_HANDLE,
				&_rd_vk_cmp_p[device][q]
			)
		)
	}
}

void _rd_vk_cmp_free()
{
	for (uint32_t d = 0; d < _rd_vkq_dv_pscdv_bl; ++d)
	{
		for (uint32_t q = 0; q < _rd_vkq_max_queue_p[d]; ++q)
		{
			vkDestroyCommandPool(_rd_vkq_dv_p[d], _rd_vk_cmp_p[d][q], VK_NULL_HANDLE);
		}
		free(_rd_vk_cmp_p[d]);
	}

	free(_rd_vk_cmp_p);
}