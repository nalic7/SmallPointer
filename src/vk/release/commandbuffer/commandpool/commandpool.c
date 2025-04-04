VkCommandPool **m_vkcommandpool_p;

void vk_initCommandPool()
{
	m_vkcommandpool_p = malloc(sizeof(VkCommandPool *) * m_physical_device);
}

void vk_makeCommandPool(uint32_t device)
{
	uint32_t max_queue = m_max_queue_p[device];
	m_vkcommandpool_p[device] = malloc(sizeof(VkCommandPool) * max_queue);

	for (uint32_t q = 0; q < max_queue; ++q)
	{
		nali_info
		(
			"vkCreateCommandPool %d",
			vkCreateCommandPool
			(
				m_vkdevice_p[device],
				&(VkCommandPoolCreateInfo)
				{
					.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
					.queueFamilyIndex = q,
					.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
					.pNext = VK_NULL_HANDLE
				},
				VK_NULL_HANDLE,
				&m_vkcommandpool_p[device][q]
			)
		)
	}
}

void vk_freeCommandPool()
{
	for (uint32_t d = 0; d < m_physical_device; ++d)
	{
		for (uint32_t q = 0; q < m_max_queue_p[d]; ++q)
		{
			vkDestroyCommandPool(m_vkdevice_p[d], m_vkcommandpool_p[d][q], VK_NULL_HANDLE);
		}
		free(m_vkcommandpool_p[d]);
	}

	free(m_vkcommandpool_p);
}