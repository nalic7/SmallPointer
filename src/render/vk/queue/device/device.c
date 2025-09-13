const char *smpt_rd_vkq_dvPets[] =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

VkDevice *smpt_rd_vkq_dvP;

void smpt_rd_vkq_dvMset()
{
	smpt_rd_vkq_dvP = malloc(sizeof(VkDevice) * smpt_rd_vkq_dv_pscdvL);
}

void smpt_rd_vkq_dvMmake(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = smpt_rd_vkq_dv_pscdvP[device];
	uint32_t max_queue = smpt_rd_vkqPmax_queue[device];

	VkDeviceQueueCreateInfo *vkdevicequeuecreateinfo_p = malloc(max_queue * sizeof(VkDeviceQueueCreateInfo));

	float queuepriority = 1.0F;

	for (uint32_t i = 0; i < max_queue; ++i)
	{
		vkdevicequeuecreateinfo_p[i] = (VkDeviceQueueCreateInfo)
		{
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = i,
			.queueCount = 1,
			.pQueuePriorities = &queuepriority,

			.flags = 0,
			.pNext = VK_NULL_HANDLE
		};
	}

	// VkPhysicalDeviceFeatures vkphysicaldevicefeatures =
	// {
	// 	.samplerAnisotropy = 1
	// };

	VkPhysicalDeviceFeatures vkphysicaldevicefeatures;
	vkGetPhysicalDeviceFeatures(vkphysicaldevice, &vkphysicaldevicefeatures);
	SMPT_DBmN2L("vkphysicaldevicefeatures.samplerAnisotropy %d", vkphysicaldevicefeatures.samplerAnisotropy)

	SMPT_DBmR2L
	(
		"vkCreateDevice %d",
		vkCreateDevice
		(
			vkphysicaldevice,
			&(VkDeviceCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
				.queueCreateInfoCount = max_queue,
				.pQueueCreateInfos = vkdevicequeuecreateinfo_p,
				.pEnabledFeatures = &vkphysicaldevicefeatures,
				.enabledExtensionCount = sizeof(smpt_rd_vkq_dvPets) / sizeof(smpt_rd_vkq_dvPets[0]),
				.ppEnabledExtensionNames = smpt_rd_vkq_dvPets,

				#ifdef SMPT_CM_VK_DEBUG
					.enabledLayerCount = sizeof(smpt_rd_vkq_dv_pscdv_itPlayer) / sizeof(smpt_rd_vkq_dv_pscdv_itPlayer[0]),
					.ppEnabledLayerNames = smpt_rd_vkq_dv_pscdv_itPlayer,
				#else
					.enabledLayerCount = 0,
					.ppEnabledLayerNames = VK_NULL_HANDLE,
				#endif

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&smpt_rd_vkq_dvP[device]
		)
	)

	free(vkdevicequeuecreateinfo_p);
}

void smpt_rd_vkq_dvMfree()
{
	for (uint32_t d = 0; d < smpt_rd_vkq_dv_pscdvL; ++d)
	{
		vkDestroyDevice(smpt_rd_vkq_dvP[d], VK_NULL_HANDLE);
	}

	free(smpt_rd_vkq_dvP);
}