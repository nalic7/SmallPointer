uint32_t *m_max_queue_p;
uint32_t *m_max_queue_surface_p;

uint32_t **m_queue_surface_p;
VkQueue **m_vkqueue_p;

void vk_initQueue()
{
	m_max_queue_p = malloc(sizeof(uint32_t) * m_physical_device);
	m_max_queue_surface_p = malloc(sizeof(uint32_t) * m_physical_device);

	m_queue_surface_p = malloc(sizeof(uint32_t*) * m_physical_device);
	m_vkqueue_p = malloc(sizeof(VkQueue*) * m_physical_device);
}

void vk_setQueue(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[device];

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &m_max_queue_p[device], VK_NULL_HANDLE);

	VkQueueFamilyProperties *vkqueuefamilyproperties_p = malloc(m_max_queue_p[device] * sizeof(VkQueueFamilyProperties));

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &m_max_queue_p[device], vkqueuefamilyproperties_p);

	nali_log("max_queue %d", m_max_queue_p[device])

	m_max_queue_surface_p[device] = 0;

	m_queue_surface_p[device] = malloc(0);

	VkBool32 surface_support;
	for (uint32_t i = 0; i < m_max_queue_p[device]; i++)
	{
		VkQueueFamilyProperties vkqueuefamilyproperties = vkqueuefamilyproperties_p[i];
		nali_info("vkGetPhysicalDeviceSurfaceSupportKHR %d", vkGetPhysicalDeviceSurfaceSupportKHR(vkphysicaldevice, i, m_vksurfacekhr, &surface_support))

		nali_log("queue %d vkqueuefamilyproperties.queueFlags %d", i, vkqueuefamilyproperties.queueFlags);
		if (surface_support)
		{
			if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				m_queue_g = i;
			}
			else if (vkqueuefamilyproperties.queueFlags & (VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT))
			{
				m_queue_ct = i;
			}

			m_queue_surface_p[device] = realloc(m_queue_surface_p[device], (m_max_queue_surface_p[device] + 1) * sizeof(uint32_t));
			m_queue_surface_p[device][m_max_queue_surface_p[device]++] = i;
			nali_log("surface_1 %d", i);
			// m_queue_render = i;
		}
		else
		{
			nali_log("surface_0 %d", i);
		}

		// if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_TRANSFER_BIT)
		// {
		// 	info("VK_QUEUE_TRANSFER_BIT %d", i);
		// }

		//check image format here
		#ifdef NALI_DEBUG
			VkFormatProperties vkformatproperties;
			vkGetPhysicalDeviceFormatProperties(vkphysicaldevice, NALI_VK_COLOR_FORMAT, &vkformatproperties);
			if (vkformatproperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			{
				nali_log("NALI_VK_COLOR_FORMAT VK_FORMAT_FEATURE_BLIT_SRC_BIT %d", i)
			}
			if (vkformatproperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT)
			{
				nali_log("NALI_VK_COLOR_FORMAT VK_FORMAT_FEATURE_BLIT_DST_BIT %d", i)
			}

			vkGetPhysicalDeviceFormatProperties(vkphysicaldevice, NALI_VK_DEPTH_FORMAT, &vkformatproperties);
			if (vkformatproperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			{
				nali_log("NALI_VK_DEPTH_FORMAT VK_FORMAT_FEATURE_BLIT_SRC_BIT %d", i)
			}
			if (vkformatproperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT)
			{
				nali_log("NALI_VK_DEPTH_FORMAT VK_FORMAT_FEATURE_BLIT_DST_BIT %d", i)
			}
		#endif
	}

	nali_log("m_max_queue_surface_p[device] %d", m_max_queue_surface_p[device])

	free(vkqueuefamilyproperties_p);
}

void vk_getQueue(uint32_t device)
{
	uint32_t max_queue = m_max_queue_p[device];
	m_vkqueue_p[device] = malloc(max_queue * sizeof(VkQueue));

	for (uint32_t i = 0; i < max_queue; ++i)
	{
		vkGetDeviceQueue(m_vkdevice_p[device], i, 0, &m_vkqueue_p[device][i]);
	}
}

void vk_freeQueue()
{
	for (uint32_t d = 0; d < m_physical_device; ++d)
	{
		free(m_queue_surface_p[d]);
		free(m_vkqueue_p[d]);
	}

	free(m_max_queue_p);
	free(m_max_queue_surface_p);

	free(m_queue_surface_p);
	free(m_vkqueue_p);
}