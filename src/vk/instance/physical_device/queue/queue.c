void vk_makeQueue(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_ptr[device];
	// QueueList queuelist =
	// {
	//	 .graphics_size = 0
	// };

	uint32_t queuefamilies = 0;

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &queuefamilies, VK_NULL_HANDLE);

	VkQueueFamilyProperties* vkqueuefamilyproperties_ptr = malloc(queuefamilies * sizeof(VkQueueFamilyProperties));

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &queuefamilies, vkqueuefamilyproperties_ptr);

	m_max_graphics_ptr[device] = 0;

	// int i = 0;
	info("queue_families %d", queuefamilies)

	for (uint32_t i = 0; i < queuefamilies; i++)
	{
		VkQueueFamilyProperties vkqueuefamilyproperties = vkqueuefamilyproperties_ptr[i];
		if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			// {
			//	 // queuelist.all = i;
			//	 // queuelist.set |= 1;
			//	 queuelist.graphics = realloc(queuelist.graphics, (queuelist.graphics_size + 1) * sizeof(uint32_t));
			//	 queuelist.graphics[queuelist.graphics_size++] = i;
			// }

			VkBool32 nowsurfacesupport = 0;

			vkGetPhysicalDeviceSurfaceSupportKHR(vkphysicaldevice, i, m_vksurfacekhr, &nowsurfacesupport);

			if (nowsurfacesupport)
			{
				// queuelist.now = i;
				// queuelist.set |= 2;
				info("index/size %d", m_max_graphics_ptr[device])
				info("byte size %ld", (m_max_graphics_ptr[device] + 1) * sizeof(uint32_t))
				m_graphics_ptr[device] = realloc(m_graphics_ptr[device], (m_max_graphics_ptr[device] + 1) * sizeof(uint32_t));
				m_graphics_ptr[device][m_max_graphics_ptr[device]++] = i;
				info("new_size %d", m_max_graphics_ptr[device])
			}

			// if ((queuelist.set & 3) == 3)
			// {
			//	 break;
			// }

			// ++i;
		}
	}

	info("queuelist_max_graphics %d", m_max_graphics_ptr[device])

	free(vkqueuefamilyproperties_ptr);

	// return queuelist;
}
