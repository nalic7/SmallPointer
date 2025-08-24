uint32_t *_vkq_max_queue_p;
uint32_t *_vkq_max_queue_surface_p;

uint32_t **_vkq_queue_surface_p = NULL;
VkQueue **_vkq_p;

void _vkq_set()
{
	_vkq_max_queue_p = malloc(sizeof(uint32_t) * _vkq_dv_pscdv_bl);
	_vkq_max_queue_surface_p = malloc(sizeof(uint32_t) * _vkq_dv_pscdv_bl);

	_vkq_queue_surface_p = malloc(sizeof(uint32_t*) * _vkq_dv_pscdv_bl);
	for (uint32_t d = 0; d < _vkq_dv_pscdv_bl; ++d)
	{
		_vkq_queue_surface_p[d] = malloc(0);
	}
	_vkq_p = malloc(sizeof(VkQueue*) * _vkq_dv_pscdv_bl);
}

void _vkq_add(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = _vkq_dv_pscdv_p[device];

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &_vkq_max_queue_p[device], VK_NULL_HANDLE);

	VkQueueFamilyProperties *vkqueuefamilyproperties_p = malloc(_vkq_max_queue_p[device] * sizeof(VkQueueFamilyProperties));

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &_vkq_max_queue_p[device], vkqueuefamilyproperties_p);

	NALI_D_LOG("max_queue %d", _vkq_max_queue_p[device])

	_vkq_max_queue_surface_p[device] = 0;

	VkBool32 surface_support;
	for (uint32_t i = 0; i < _vkq_max_queue_p[device]; i++)
	{
		VkQueueFamilyProperties vkqueuefamilyproperties = vkqueuefamilyproperties_p[i];
		NALI_D_INFO("vkGetPhysicalDeviceSurfaceSupportKHR %d", vkGetPhysicalDeviceSurfaceSupportKHR(vkphysicaldevice, i, _vk_sf_khr, &surface_support))

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

			_vkq_queue_surface_p[device] = realloc(_vkq_queue_surface_p[device], (_vkq_max_queue_surface_p[device] + 1) * sizeof(uint32_t));
			_vkq_queue_surface_p[device][_vkq_max_queue_surface_p[device]++] = i;
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
		#ifdef _CM_DEBUG
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

	NALI_D_LOG("_vkq_max_queue_surface_p[device] %d", _vkq_max_queue_surface_p[device])

	free(vkqueuefamilyproperties_p);
}

void _vkq_get(uint32_t device)
{
	uint32_t max_queue = _vkq_max_queue_p[device];
	_vkq_p[device] = malloc(max_queue * sizeof(VkQueue));

	for (uint32_t i = 0; i < max_queue; ++i)
	{
		vkGetDeviceQueue(_vkq_dv_p[device], i, 0, &_vkq_p[device][i]);
	}
}

void _vkq_free()
{
	for (uint32_t d = 0; d < _vkq_dv_pscdv_bl; ++d)
	{
		free(_vkq_queue_surface_p[d]);
		free(_vkq_p[d]);
	}

	free(_vkq_max_queue_p);
	free(_vkq_max_queue_surface_p);

	free(_vkq_queue_surface_p);
	free(_vkq_p);
}