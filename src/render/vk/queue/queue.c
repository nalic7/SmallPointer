uint32_t *vkq_max_queue_p;
uint32_t *vkq_max_queue_surface_p;

uint32_t **vkq_queue_surface_p = NULL;
VkQueue **vkq_vkqueue_p;

void vkq_set()
{
	vkq_max_queue_p = malloc(sizeof(uint32_t) * vkqdpd_physical_device);
	vkq_max_queue_surface_p = malloc(sizeof(uint32_t) * vkqdpd_physical_device);

	vkq_queue_surface_p = malloc(sizeof(uint32_t*) * vkqdpd_physical_device);
	for (uint32_t d = 0; d < vkqdpd_physical_device; ++d)
	{
		vkq_queue_surface_p[d] = malloc(0);
	}
	vkq_vkqueue_p = malloc(sizeof(VkQueue*) * vkqdpd_physical_device);
}

void vkq_setQueue(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = vkqdpd_vkphysicaldevice_p[device];

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &vkq_max_queue_p[device], VK_NULL_HANDLE);

	VkQueueFamilyProperties *vkqueuefamilyproperties_p = malloc(vkq_max_queue_p[device] * sizeof(VkQueueFamilyProperties));

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &vkq_max_queue_p[device], vkqueuefamilyproperties_p);

	NALI_D_LOG("max_queue %d", vkq_max_queue_p[device])

	vkq_max_queue_surface_p[device] = 0;

	VkBool32 surface_support;
	for (uint32_t i = 0; i < vkq_max_queue_p[device]; i++)
	{
		VkQueueFamilyProperties vkqueuefamilyproperties = vkqueuefamilyproperties_p[i];
		NALI_D_INFO("vkGetPhysicalDeviceSurfaceSupportKHR %d", vkGetPhysicalDeviceSurfaceSupportKHR(vkphysicaldevice, i, vks_vksurfacekhr, &surface_support))

		NALI_D_LOG("queue %d vkqueuefamilyproperties.queueFlags %d", i, vkqueuefamilyproperties.queueFlags);
		if (surface_support)
		{
			if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				vk_queue_g = i;
			}
			else if (vkqueuefamilyproperties.queueFlags & (VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT))
			{
				vk_queue_ct = i;
			}

			vkq_queue_surface_p[device] = realloc(vkq_queue_surface_p[device], (vkq_max_queue_surface_p[device] + 1) * sizeof(uint32_t));
			vkq_queue_surface_p[device][vkq_max_queue_surface_p[device]++] = i;
			NALI_D_LOG("surface_1 %d", i);
			// m_queue_render = i;
		}
		else
		{
			NALI_D_LOG("surface_0 %d", i);
		}

		// if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_TRANSFER_BIT)
		// {
		// 	info("VK_QUEUE_TRANSFER_BIT %d", i);
		// }

		//check image format here
		#ifdef C_NALI_DEBUG
			VkFormatProperties vkformatproperties;
			vkGetPhysicalDeviceFormatProperties(vkphysicaldevice, _VK_COLOR_FORMAT, &vkformatproperties);
			if (vkformatproperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			{
				NALI_D_LOG("_VK_COLOR_FORMAT VK_FORMAT_FEATURE_BLIT_SRC_BIT %d", i)
			}
			if (vkformatproperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT)
			{
				NALI_D_LOG("_VK_COLOR_FORMAT VK_FORMAT_FEATURE_BLIT_DST_BIT %d", i)
			}

			vkGetPhysicalDeviceFormatProperties(vkphysicaldevice, _VK_DEPTH_FORMAT, &vkformatproperties);
			if (vkformatproperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			{
				NALI_D_LOG("_VK_DEPTH_FORMAT VK_FORMAT_FEATURE_BLIT_SRC_BIT %d", i)
			}
			if (vkformatproperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT)
			{
				NALI_D_LOG("_VK_DEPTH_FORMAT VK_FORMAT_FEATURE_BLIT_DST_BIT %d", i)
			}
		#endif
	}

	NALI_D_LOG("vkq_max_queue_surface_p[device] %d", vkq_max_queue_surface_p[device])

	free(vkqueuefamilyproperties_p);
}

void vkq_getQueue(uint32_t device)
{
	uint32_t max_queue = vkq_max_queue_p[device];
	vkq_vkqueue_p[device] = malloc(max_queue * sizeof(VkQueue));

	for (uint32_t i = 0; i < max_queue; ++i)
	{
		vkGetDeviceQueue(vkqd_vkdevice_p[device], i, 0, &vkq_vkqueue_p[device][i]);
	}
}

void vkq_free()
{
	for (uint32_t d = 0; d < vkqdpd_physical_device; ++d)
	{
		free(vkq_queue_surface_p[d]);
		free(vkq_vkqueue_p[d]);
	}

	free(vkq_max_queue_p);
	free(vkq_max_queue_surface_p);

	free(vkq_queue_surface_p);
	free(vkq_vkqueue_p);
}