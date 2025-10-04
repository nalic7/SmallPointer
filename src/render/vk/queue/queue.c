struct SMPT_RD_VKQsINFO *smpt_rd_vkqPinfo;
uint32_t smpt_rd_vkqLinfo;

static const char *Pextension[] =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

void smpt_rd_vkqMset()
{
	for (uint32_t l0 = 0; l0 < smpt_rd_vkqLinfo; ++l0)
	{
		struct SMPT_RD_VKQsINFO *Pinfo = smpt_rd_vkqPinfo + l0;

		uint32_t Lqueue_family;
		vkGetPhysicalDeviceQueueFamilyProperties(Pinfo->Vvkphysicaldevice, &Lqueue_family, VK_NULL_HANDLE);
		VkQueueFamilyProperties *Pvkqueuefamilyproperties = malloc(Lqueue_family * sizeof(VkQueueFamilyProperties));
		vkGetPhysicalDeviceQueueFamilyProperties(Pinfo->Vvkphysicaldevice, &Lqueue_family, Pvkqueuefamilyproperties);

		VkBool32 Usurface_support;
		uint32_t
			Usf = 0xFFFFFFFF,
			Ugp = 0xFFFFFFFF,
			Ucp = 0xFFFFFFFF;
		for (uint32_t l1 = 0; l1 < Lqueue_family; ++l1)
		{
			VkQueueFamilyProperties vkqueuefamilyproperties = Pvkqueuefamilyproperties[l1];
			SMPT_DBmN2L("queueCount %d", vkqueuefamilyproperties.queueCount);
			SMPT_DBmN2L("queueFlags %d", vkqueuefamilyproperties.queueFlags);
			SMPT_DBmR2L("vkGetPhysicalDeviceSurfaceSupportKHR %d", vkGetPhysicalDeviceSurfaceSupportKHR(Pinfo->Vvkphysicaldevice, l1, smpt_rd_vk_sfVkhr, &Usurface_support))

			if (Usurface_support && Usf == 0xFFFFFFFF)
			{
				Usf = l1;
			}

			if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				if (Usurface_support)
				{
					Usf = l1;
					Ugp = l1;
				}
				else if (Ugp == 0xFFFFFFFF)
				{
					Ugp = l1;
				}

				if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_COMPUTE_BIT && Ucp != 0xFFFFFFFF && vkqueuefamilyproperties.queueCount > 1)
				{
					Ucp = l1;
				}
			}
			else if (vkqueuefamilyproperties.queueFlags & VK_QUEUE_COMPUTE_BIT && Ucp != 0xFFFFFFFF && Ucp != Ugp)
			{
				Ucp = l1;
			}
		}

		//! check
		uint8_t
			*Pqueue_family_index = malloc(sizeof(uint8_t));
			*Pqueue_count = malloc(sizeof(uint8_t));
		float **Pqueue_priorities = malloc(sizeof(float *));
		if (Usf == Ugp)
		{
			Pinfo->Sfamily.L = 1;
			Pinfo->Sfamily.Lsf = 1;
			Pinfo->Sfamily.Psf = malloc(sizeof(uint8_t));
			Pinfo->Ugp = 0;
			Pqueue_priorities[1] = realloc(Pqueue_priorities[1], sizeof(float) * 2);
			Pqueue_priorities[0][1] = 1.0F;
		}
		else
		{
			Pinfo->Sfamily.L = 2;
			Pinfo->Sfamily.Lsf = 2;
			Pinfo->Sfamily.Psf = malloc(sizeof(uint8_t) * 2);
			Pinfo->Sfamily.Psf[1] = Ugp;
			Pinfo->Ugp = 1;
			Pqueue_family_index = realloc(Pqueue_family_index, sizeof(uint8_t) * 2);
			Pqueue_family_index[1] = Ugp;
			Pqueue_count = realloc(Pqueue_count, sizeof(uint8_t) * 2);
			Pqueue_count[1] = 1;
			Pqueue_priorities = realloc(Pqueue_priorities, sizeof(float *) * 2);
			Pqueue_priorities[1][0] = 1.0F;
		}
		Pqueue_count[0] = 1;
		Pinfo->Sfamily.Psf[0] = Usf;
		Pinfo->Usf = 0;
		Pinfo->Ucp = Pinfo->Ugp;
		Pqueue_family_index[0] = Usf;
		Pqueue_priorities[0][0] = 1.0F;
		if (Ugp == Ucp)
		{
			Pqueue_priorities[Pinfo->Ucp] = realloc(Pqueue_priorities[Pinfo->Ucp], sizeof(float) * (Pqueue_count[Pinfo->Ucp] + 1));
			Pqueue_priorities[Pinfo->Ucp][Pqueue_count[Pinfo->Ucp]] = 1.0F;
			++Pqueue_count[Pinfo->Ucp];

			++Pinfo->Ucp;
		}
		else
		{
			++Pinfo->Sfamily.L;
			++Pinfo->Ucp;
			Pqueue_family_index = realloc(Pqueue_family_index, sizeof(uint8_t) * (Pinfo->Ucp + 1));
			Pqueue_family_index[Pinfo->Ucp] = Ucp;
			Pqueue_priorities = realloc(Pqueue_priorities, sizeof(float *) * (Pinfo->Ucp + 1));
			Pqueue_priorities[Pinfo->Ucp][0] = 1.0F;
			Pqueue_count = realloc(Pqueue_count, sizeof(uint8_t) * (Pinfo->Ucp + 1));
			Pqueue_count[Pinfo->Ucp] = 1;
		}

		VkDeviceQueueCreateInfo *Pvkdevicequeuecreateinfo = malloc(sizeof(VkDeviceQueueCreateInfo) * Pinfo->Sfamily.L);
		for (uint32_t l1 = 0; l1 < Pinfo->Sfamily.L; ++l1)
		{
			Pvkdevicequeuecreateinfo[l1] = (VkDeviceQueueCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
				.queueFamilyIndex = Pqueue_family_index[l1],
				.queueCount = Pqueue_count[l1],
				.pQueuePriorities = Pqueue_priorities[l1],
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
					.queueCreateInfoCount = Pinfo->Sfamily.L,
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
		Pinfo->Pvkcommandpool = malloc(sizeof(VkCommandPool) * Pinfo->Sfamily.L);
		for (uint32_t l1 = 0; l1 < Pinfo->Sfamily.L; ++l1)
		{
			for (uint32_t l2 = 0; l2 < Pqueue_count[l1]; ++l2)
			{
				Pinfo->Pvkqueue = realloc(Pinfo->Pvkqueue, sizeof(VkQueue) * (Lqueue + 1));
				vkGetDeviceQueue(Pinfo->Vvkdevice, Squeue.Pqueue_family_index[l1], l2, Pinfo->Pvkqueue + Lqueue);
				++Lqueue;
			}

			SMPT_DBmR2L
			(
				"vkCreateCommandPool %d",
				vkCreateCommandPool
				(
					Pinfo->Vvkdevice,
					&(VkCommandPoolCreateInfo)
					{
						.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
						.queueFamilyIndex = Pqueue_family_index[l1],
						.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
						.pNext = VK_NULL_HANDLE
					},
					VK_NULL_HANDLE,
					Pinfo->Pvkcommandpool + l1
				)
			)

			free(Pqueue_priorities[l1]);
		}
		free(Pqueue_priorities);
		free(Pqueue_count);
		free(Pqueue_family_index);

		free(Pvkdevicequeuecreateinfo);

		free(Pvkqueuefamilyproperties);
	}
}

void smpt_rd_vkqMfree()
{
	for (uint32_t l0 = 0; l0 < smpt_rd_vkqLinfo; ++l0)
	{
		struct SMPT_RD_VKQsINFO Sinfo = smpt_rd_vkqPinfo[l0];
		for (uint32_t l1 = 0; l1 < Sinfo.Sfamily.L; ++l1)
			vkDestroyCommandPool(Sinfo.Vvkdevice, Sinfo.Pvkcommandpool[l1], VK_NULL_HANDLE);
		free(Sinfo.Sfamily.Psf);
		free(Sinfo.Ptf);
		free(Sinfo.Pvkqueue);
		free(Sinfo.Pvkcommandpool);
		vkDestroyDevice(Sinfo.Vvkdevice, VK_NULL_HANDLE);
	}
}
