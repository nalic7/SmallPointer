VkCommandPool **vkcbcp_vkcommandpool_p;

void vkcbcp_set()
{
	vkcbcp_vkcommandpool_p = malloc(sizeof(VkCommandPool *) * vkqdpd_physical_device);
}

void vkcbcp_make(uint32_t device)
{
	uint32_t max_queue = vkq_max_queue_p[device];
	vkcbcp_vkcommandpool_p[device] = malloc(sizeof(VkCommandPool) * max_queue);

	for (uint32_t q = 0; q < max_queue; ++q)
	{
		nali_info
		(
			"vkCreateCommandPool %d",
			vkCreateCommandPool
			(
				vkqd_vkdevice_p[device],
				&(VkCommandPoolCreateInfo)
				{
					.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
					.queueFamilyIndex = q,
					.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
					.pNext = VK_NULL_HANDLE
				},
				VK_NULL_HANDLE,
				&vkcbcp_vkcommandpool_p[device][q]
			)
		)
	}
}

void vkcbcp_free()
{
	for (uint32_t d = 0; d < vkqdpd_physical_device; ++d)
	{
		for (uint32_t q = 0; q < vkq_max_queue_p[d]; ++q)
		{
			vkDestroyCommandPool(vkqd_vkdevice_p[d], vkcbcp_vkcommandpool_p[d][q], VK_NULL_HANDLE);
		}
		free(vkcbcp_vkcommandpool_p[d]);
	}

	free(vkcbcp_vkcommandpool_p);
}