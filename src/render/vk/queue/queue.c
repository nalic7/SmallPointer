struct SMPT_RD_VKQsINFO *smpt_rd_vkqPinfo;
uint32_t smpt_rd_vkqLinfo;

static const char *Pextension[] =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct sQUEUE
{
	float **Pqueue_priorities;
	uint8_t
		*Pqueue_priorities_size,
		*Pqueue_family_index,
		Lqueue_family_index;
};

#define SMPT_RD_VKQmFIND_SET \
	uint8_t \
		Umove = 0, \
		*Pqueue_family_index = malloc(0), \
		Lqueue_family_index = 0;

#define SMPT_RD_VKQmFIND_INDEX \
	++Lqueue_family_index; \
	Pqueue_family_index = realloc(Pqueue_family_index, sizeof(uint8_t) * Lqueue_family_index); \
	Pqueue_family_index[Lqueue_family_index - 1] = l0; \
	for (uint8_t l1 = 0; l1 < Pqueue->Lqueue_family_index; ++l1) \
	{ \
		if (Pqueue->Pqueue_family_index[l1] == l0) \
		{ \
			Umove |= 1; \
			break; \
		} \
	} \
	if (!Umove) \
	{ \
		free(Pqueue_family_index); \
		++Pqueue->Lqueue_family_index; \
		Pqueue->Pqueue_family_index = realloc(Pqueue->Pqueue_family_index, sizeof(uint8_t) * Pqueue->Lqueue_family_index); \
		Pqueue->Pqueue_family_index[Lqueue_family_index - 1] = l0; \
		Pqueue->Pqueue_priorities_size = realloc(Pqueue->Pqueue_priorities_size, sizeof(uint8_t) * Pqueue->Lqueue_family_index); \
		Pqueue->Pqueue_priorities_size[Pqueue->Lqueue_family_index - 1] = 1; \
		Pqueue->Pqueue_priorities = realloc(Pqueue->Pqueue_priorities, sizeof(float *) * Pqueue->Lqueue_family_index); \
		Pqueue->Pqueue_priorities[Pqueue->Lqueue_family_index - 1] = malloc(sizeof(float)); \
		Pqueue->Pqueue_priorities[Pqueue->Lqueue_family_index - 1][0] = 1.0F; \
		*Pq = l0; \
		return; \
	} \
	Umove &= 255 - 1;

#define SMPT_RD_VKQmFIND_FIX \
	for (uint32_t l0 = 0; l0 < Pqueue->Lqueue_family_index; ++l0) \
	{ \
		for (uint32_t l1 = 0; l1 < Lqueue_family_index; ++l1) \
		{ \
			if (Pqueue->Pqueue_family_index[l0] == Pqueue_family_index[l1] && Pvkqueuefamilyproperties[Pqueue_family_index[l1]].queueCount > Pqueue->Pqueue_priorities_size[l0]) \
			{ \
				++Pqueue->Pqueue_priorities_size[l0]; \
				Pqueue->Pqueue_priorities[l0] = realloc(Pqueue->Pqueue_priorities[l0], sizeof(float) * Pqueue->Pqueue_priorities_size[l0]); \
				Pqueue->Pqueue_priorities[l0][Pqueue->Pqueue_priorities_size[l0] - 1] = 1.0F; \
				*Pq = Pqueue_family_index[l1]; \
				break; \
			} \
		} \
	} \
	*Pq = Pqueue_family_index[0]; \
	free(Pqueue_family_index);

static void Mfind_queue_surface(VkPhysicalDevice Vvkphysicaldevice, VkQueueFamilyProperties *Pvkqueuefamilyproperties, uint32_t Lqueue_family, struct sQUEUE *Pqueue, uint8_t *Pq)
{
	SMPT_RD_VKQmFIND_SET
	VkBool32 Usurface_support;
	for (uint32_t l0 = 0; l0 < Lqueue_family; ++l0)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(Pinfo->Vvkphysicaldevice, l0, smpt_rd_vk_sfVkhr, &Usurface_support);
		if (Usurface_support)
		{
			SMPT_RD_VKQmFIND_INDEX
		}
	}
	SMPT_RD_VKQmFIND_FIX
}

static void Mfind_queue_bit(VkQueueFamilyProperties *Pvkqueuefamilyproperties, uint32_t Lqueue_family, VkQueueFlagBits Vvkqueueflagbits, struct sQUEUE *Pqueue, uint8_t *Pq)
{
	SMPT_RD_VKQmFIND_SET
	for (uint32_t l0 = 0; l0 < Lqueue_family; ++l0)
	{
		VkQueueFamilyProperties vkqueuefamilyproperties = Pvkqueuefamilyproperties[l0];
		if (vkqueuefamilyproperties.queueFlags & Vvkqueueflagbits)
		{
			SMPT_RD_VKQmFIND_INDEX
		}
	}
	SMPT_RD_VKQmFIND_FIX
}

void smpt_rd_vkqMset()
{
	for (uint32_t l0 = 0; l0 < smpt_rd_vkqLinfo; ++l0)
	{
		struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + l0;

		uint32_t Lqueue_family;
		vkGetPhysicalDeviceQueueFamilyProperties(Pinfo->Vvkphysicaldevice, &Lqueue_family, VK_NULL_HANDLE);
		VkQueueFamilyProperties *Pvkqueuefamilyproperties = malloc(Lqueue_family * sizeof(VkQueueFamilyProperties));
		vkGetPhysicalDeviceQueueFamilyProperties(Pinfo->Vvkphysicaldevice, &Lqueue_family, Pvkqueuefamilyproperties);

		#ifdef SMPT_CM_DEBUG
			VkBool32 Usurface_support;
			for (uint32_t l1 = 0; l1 < Lqueue_family; ++l1)
			{
				VkQueueFamilyProperties vkqueuefamilyproperties = Pvkqueuefamilyproperties[l1];
				SMPT_DBmN2L("queueCount %d", vkqueuefamilyproperties.queueCount);
				SMPT_DBmN2L("queueFlags %d", vkqueuefamilyproperties.queueFlags);
				SMPT_DBmR2L("vkGetPhysicalDeviceSurfaceSupportKHR %d", vkGetPhysicalDeviceSurfaceSupportKHR(Pinfo->Vvkphysicaldevice, l1, smpt_rd_vk_sfVkhr, &Usurface_support))
			}
		#endif
		//! debug
		while (1)
		{
			thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
		}

		struct sQUEUE Squeue =
		{
			.Pqueue_priorities = malloc(0);
			.Pqueue_priorities_size = malloc(0);
			.Pqueue_family_index = malloc(0);
			.Lqueue_family_index = 0;
		};
		Mfind_queue_bit(Pvkqueuefamilyproperties, Lqueue_family, VK_QUEUE_GRAPHICS_BIT, &Squeue, &Pinfo->Ugp);
		Mfind_queue_surface(Pinfo->Vvkphysicaldevice, Pvkqueuefamilyproperties, Lqueue_family, &Squeue, &Pinfo->Usf);
		Mfind_queue_bit(Pvkqueuefamilyproperties, Lqueue_family, VK_QUEUE_COMPUTE_BIT, &Squeue, &Pinfo->Ucp);
		Mfind_queue_bit(Pvkqueuefamilyproperties, Lqueue_family, VK_QUEUE_TRANSFER_BIT, &Squeue, &Pinfo->Utf);

		VkDeviceQueueCreateInfo *Pvkdevicequeuecreateinfo = malloc(sizeof(VkDeviceQueueCreateInfo) * Squeue.Lqueue_family_index);
		for (uint32_t l1 = 0; l1 < Squeue.Lqueue_family_index; ++l1)
		{
			Pvkdevicequeuecreateinfo[l1] = (VkDeviceQueueCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				.queueFamilyIndex = Squeue.Pqueue_family_index[l1],
				.queueCount = Squeue.Pqueue_priorities_size[l1],
				.pQueuePriorities = Squeue.Pqueue_priorities[l1],
				.flags = 0,
				.pNext = VK_NULL_HANDLE
			};
		}
		SMPT_DBmR2L
		(
			"vkCreateDevice %d",
			vkCreateDevice
			(
				Pinfo->Vvkphysicaldevice,
				&(VkDeviceCreateInfo)
				{
					.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
					.queueCreateInfoCount = Squeue.Lqueue_family_index,
					.pQueueCreateInfos = Pvkdevicequeuecreateinfo,
					.pEnabledFeatures = &vkphysicaldevicefeatures,
					.enabledExtensionCount = sizeof(Pextension) / sizeof(Pextension[0]),
					.ppEnabledExtensionNames = Pextension,

					#ifdef SMPT_CM_VK_DEBUG
						.enabledLayerCount = sizeof(smpt_rd_vk_dbPlayer) / sizeof(smpt_rd_vk_dbPlayer[0]),
						.ppEnabledLayerNames = smpt_rd_vk_dbPlayer,
					#else
						.enabledLayerCount = 0,
						.ppEnabledLayerNames = VK_NULL_HANDLE,
					#endif

					.flags = 0,
					.pNext = VK_NULL_HANDLE
				},
				VK_NULL_HANDLE,
				&Pinfo->Vvkdevice
			)
		)
		uint8_t Lqueue = 0;
		Pinfo->Pvkqueue = malloc(0);
		for (uint32_t l1 = 0; l1 < Squeue.Lqueue_family_index; ++l1)
		{
			for (uint32_t l2 = 0; l2 < Squeue.Pqueue_priorities_size[l1]; ++l2)
			{
				Pinfo->Pvkqueue = realloc(Pinfo->Pvkqueue, sizeof(VkQueue) * (Lqueue + 1));
				vkGetDeviceQueue(Pinfo->Vvkdevice, Squeue.Pqueue_family_index[l1], l2, Pinfo->Pvkqueue + Lqueue);
				++Lqueue;
				//! fix qindex here
			}

			free(Squeue.Pqueue_priorities[l1]);
		}
		free(Squeue.Pqueue_priorities);
		free(Squeue.Pqueue_priorities_size);
		free(Squeue.Pqueue_family_index);

		free(Pvkdevicequeuecreateinfo);

		free(Pvkqueuefamilyproperties);
	}
}

void smpt_rd_vkqMfree()
{
	for (uint32_t l0 = 0; l0 < smpt_rd_vkqLinfo; ++l0)
	{
		free(smpt_rd_vkqPinfo[l0].Pvkqueue);
		vkDestroyDevice(smpt_rd_vkq_dvP[l0], VK_NULL_HANDLE);
	}
}
