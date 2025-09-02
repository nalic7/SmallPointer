uint32_t *smpt_rd_vkq_max_queue_p;
uint32_t *smpt_rd_vkq_max_queue_surface_p;

uint32_t **smpt_rd_vkq_queue_surface_p = NULL;
VkQueue **smpt_rd_vkq_p;

void smpt_rd_vkq_set()
{
	smpt_rd_vkq_max_queue_p = malloc(sizeof(uint32_t) * smpt_rd_vkq_dv_pscdv_bl);
	smpt_rd_vkq_max_queue_surface_p = malloc(sizeof(uint32_t) * smpt_rd_vkq_dv_pscdv_bl);

	smpt_rd_vkq_queue_surface_p = malloc(sizeof(uint32_t*) * smpt_rd_vkq_dv_pscdv_bl);
	for (uint32_t d = 0; d < smpt_rd_vkq_dv_pscdv_bl; ++d)
	{
		smpt_rd_vkq_queue_surface_p[d] = malloc(0);
	}
	smpt_rd_vkq_p = malloc(sizeof(VkQueue*) * smpt_rd_vkq_dv_pscdv_bl);
}

void smpt_rd_vkq_add(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = smpt_rd_vkq_dv_pscdv_p[device];

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &smpt_rd_vkq_max_queue_p[device], VK_NULL_HANDLE);

	VkQueueFamilyProperties *vkqueuefamilyproperties_p = malloc(smpt_rd_vkq_max_queue_p[device] * sizeof(VkQueueFamilyProperties));

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &smpt_rd_vkq_max_queue_p[device], vkqueuefamilyproperties_p);

	SMPT_DB_N2L("max_queue %d", smpt_rd_vkq_max_queue_p[device])

	smpt_rd_vkq_max_queue_surface_p[device] = 0;

	VkBool32 surface_support;
	for (uint32_t i = 0; i < smpt_rd_vkq_max_queue_p[device]; i++)
	{
		VkQueueFamilyProperties vkqueuefamilyproperties = vkqueuefamilyproperties_p[i];
		SMPT_DB_R2L("vkGetPhysicalDeviceSurfaceSupportKHR %d", vkGetPhysicalDeviceSurfaceSupportKHR(vkphysicaldevice, i, smpt_rd_vk_sf_khr, &surface_support))

		SMPT_DB_N2L("queue %d vkqueuefamilyproperties.queueFlags %d", i, vkqueuefamilyproperties.queueFlags);
		if (surface_support)
		{
			if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				smpt_rd_vk_queue_g = i;
			}
			else if (vkqueuefamilyproperties.queueFlags & (VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT))
			{
				smpt_rd_vk_queue_ct = i;
			}

			smpt_rd_vkq_queue_surface_p[device] = realloc(smpt_rd_vkq_queue_surface_p[device], (smpt_rd_vkq_max_queue_surface_p[device] + 1) * sizeof(uint32_t));
			smpt_rd_vkq_queue_surface_p[device][smpt_rd_vkq_max_queue_surface_p[device]++] = i;
			SMPT_DB_N2L("surface_1 %d", i);
			// m_queue_render = i;
		}
		else
		{
			SMPT_DB_N2L("surface_0 %d", i);
		}

		// if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_TRANSFER_BIT)
		// {
		// 	info("VK_QUEUE_TRANSFER_BIT %d", i);
		// }

		//check image format here
		#ifdef SMPT_CM_DEBUG
			VkFormatProperties vkformatproperties;
			vkGetPhysicalDeviceFormatProperties(vkphysicaldevice, SMPT_RD_VK_COLOR_FORMAT, &vkformatproperties);
			if (vkformatproperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			{
				SMPT_DB_N2L("_VK_COLOR_FORMAT VK_FORMAT_FEATURE_BLIT_SRC_BIT %d", i)
			}
			if (vkformatproperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT)
			{
				SMPT_DB_N2L("_VK_COLOR_FORMAT VK_FORMAT_FEATURE_BLIT_DST_BIT %d", i)
			}

			vkGetPhysicalDeviceFormatProperties(vkphysicaldevice, SMPT_RD_VK_DEPTH_FORMAT, &vkformatproperties);
			if (vkformatproperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_SRC_BIT)
			{
				SMPT_DB_N2L("_VK_DEPTH_FORMAT VK_FORMAT_FEATURE_BLIT_SRC_BIT %d", i)
			}
			if (vkformatproperties.optimalTilingFeatures & VK_FORMAT_FEATURE_BLIT_DST_BIT)
			{
				SMPT_DB_N2L("_VK_DEPTH_FORMAT VK_FORMAT_FEATURE_BLIT_DST_BIT %d", i)
			}
		#endif
	}

	SMPT_DB_N2L("_vkq_max_queue_surface_p[device] %d", smpt_rd_vkq_max_queue_surface_p[device])

	free(vkqueuefamilyproperties_p);
}

void smpt_rd_vkq_get(uint32_t device)
{
	uint32_t max_queue = smpt_rd_vkq_max_queue_p[device];
	smpt_rd_vkq_p[device] = malloc(max_queue * sizeof(VkQueue));

	for (uint32_t i = 0; i < max_queue; ++i)
	{
		vkGetDeviceQueue(smpt_rd_vkq_dv_p[device], i, 0, &smpt_rd_vkq_p[device][i]);
	}
}

void smpt_rd_vkq_free()
{
	for (uint32_t d = 0; d < smpt_rd_vkq_dv_pscdv_bl; ++d)
	{
		free(smpt_rd_vkq_queue_surface_p[d]);
		free(smpt_rd_vkq_p[d]);
	}

	free(smpt_rd_vkq_max_queue_p);
	free(smpt_rd_vkq_max_queue_surface_p);

	free(smpt_rd_vkq_queue_surface_p);
	free(smpt_rd_vkq_p);
}