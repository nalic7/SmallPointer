void vk_makeQueue(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_ptr[device];

	uint32_t queuefamilies = 0;

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &queuefamilies, VK_NULL_HANDLE);

	VkQueueFamilyProperties* vkqueuefamilyproperties_ptr = malloc(queuefamilies * sizeof(VkQueueFamilyProperties));

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &queuefamilies, vkqueuefamilyproperties_ptr);

	m_max_graphics_ptr[device] = 0;

	info("queue_families %d", queuefamilies)

	for (uint32_t i = 0; i < queuefamilies; i++)
	{
		VkQueueFamilyProperties vkqueuefamilyproperties = vkqueuefamilyproperties_ptr[i];
		if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			VkBool32 surface_support;

			vkGetPhysicalDeviceSurfaceSupportKHR(vkphysicaldevice, i, m_vksurfacekhr, &surface_support);

			if (surface_support)
			{
				info("index/size %d", m_max_graphics_ptr[device])
				info("byte size %ld", (m_max_graphics_ptr[device] + 1) * sizeof(uint32_t))
				m_graphics_ptr[device] = realloc(m_graphics_ptr[device], (m_max_graphics_ptr[device] + 1) * sizeof(uint32_t));
				m_graphics_ptr[device][m_max_graphics_ptr[device]++] = i;
				info("new_size %d", m_max_graphics_ptr[device])
			}
			else
			{
				info("no_surface %d", i);
			}
		}
	}

	info("queuelist_max_graphics %d", m_max_graphics_ptr[device])

	free(vkqueuefamilyproperties_ptr);
}
