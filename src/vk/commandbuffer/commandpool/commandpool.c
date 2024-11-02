void vk_makeCommandPool(uint32_t device, uint32_t graphic)
{
	VkCommandPoolCreateInfo vkcommandpoolcreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.queueFamilyIndex = m_graphics_ptr[device][graphic],
		.flags = 0,//VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
		.pNext = VK_NULL_HANDLE
	};
	vkCreateCommandPool(m_vkdevice_ptr[device], &vkcommandpoolcreateinfo, VK_NULL_HANDLE, &m_vkcommandpool_ptr[device][graphic]);
}
