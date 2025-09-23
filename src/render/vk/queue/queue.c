//! clean
uint32_t *smpt_rd_vkqPmax_queue;
uint32_t *smpt_rd_vkqPmax_queue_surface;

uint32_t **smpt_rd_vkqPqueue_surface = NULL;
VkQueue **smpt_rd_vkqP;

void smpt_rd_vkqMset()
{
	smpt_rd_vkqPmax_queue = malloc(sizeof(uint32_t) * smpt_rd_vkq_dv_pscdvL);
	smpt_rd_vkqPmax_queue_surface = malloc(sizeof(uint32_t) * smpt_rd_vkq_dv_pscdvL);

	smpt_rd_vkqPqueue_surface = malloc(sizeof(uint32_t*) * smpt_rd_vkq_dv_pscdvL);
	for (uint32_t d = 0; d < smpt_rd_vkq_dv_pscdvL; ++d)
	{
		smpt_rd_vkqPqueue_surface[d] = malloc(0);
	}
	smpt_rd_vkqP = malloc(sizeof(VkQueue*) * smpt_rd_vkq_dv_pscdvL);
}

void smpt_rd_vkqMadd(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = smpt_rd_vkq_dv_pscdvP[device];

	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &smpt_rd_vkqPmax_queue[device], VK_NULL_HANDLE);
	VkQueueFamilyProperties *vkqueuefamilyproperties_p = malloc(smpt_rd_vkqPmax_queue[device] * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(vkphysicaldevice, &smpt_rd_vkqPmax_queue[device], vkqueuefamilyproperties_p);

	SMPT_DBmN2L("max_queue %d", smpt_rd_vkqPmax_queue[device])

	smpt_rd_vkqPmax_queue_surface[device] = 0;

	VkBool32 surface_support;
	for (uint32_t i = 0; i < smpt_rd_vkqPmax_queue[device]; i++)
	{
		VkQueueFamilyProperties vkqueuefamilyproperties = vkqueuefamilyproperties_p[i];
		SMPT_DBmR2L("vkGetPhysicalDeviceSurfaceSupportKHR %d", vkGetPhysicalDeviceSurfaceSupportKHR(vkphysicaldevice, i, smpt_rd_vk_sfVkhr, &surface_support))

		SMPT_DBmN2L("queue %d vkqueuefamilyproperties.queueFlags %d", i, vkqueuefamilyproperties.queueFlags);
		if (surface_support)
		{
			if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				smpt_rd_vkUqueue_g = i;
			}
			else if (vkqueuefamilyproperties.queueFlags & (VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT))
			{
				smpt_rd_vkUqueue_ct = i;
			}

			smpt_rd_vkqPqueue_surface[device] = realloc(smpt_rd_vkqPqueue_surface[device], (smpt_rd_vkqPmax_queue_surface[device] + 1) * sizeof(uint32_t));
			smpt_rd_vkqPqueue_surface[device][smpt_rd_vkqPmax_queue_surface[device]++] = i;
			SMPT_DBmN2L("surface_1 %d", i);
		}
	}

	SMPT_DBmN2L("_vkq_max_queue_surface_p[device] %d", smpt_rd_vkqPmax_queue_surface[device])

	free(vkqueuefamilyproperties_p);
}

void smpt_rd_vkqMget(uint32_t device)
{
	uint32_t max_queue = smpt_rd_vkqPmax_queue[device];
	smpt_rd_vkqP[device] = malloc(max_queue * sizeof(VkQueue));

	for (uint32_t i = 0; i < max_queue; ++i)
	{
		vkGetDeviceQueue(smpt_rd_vkq_dvP[device], i, 0, &smpt_rd_vkqP[device][i]);
	}
}

void smpt_rd_vkqMfree()
{
	for (uint32_t d = 0; d < smpt_rd_vkq_dv_pscdvL; ++d)
	{
		free(smpt_rd_vkqPqueue_surface[d]);
		free(smpt_rd_vkqP[d]);
	}

	free(smpt_rd_vkqPmax_queue);
	free(smpt_rd_vkqPmax_queue_surface);

	free(smpt_rd_vkqPqueue_surface);
	free(smpt_rd_vkqP);
}
