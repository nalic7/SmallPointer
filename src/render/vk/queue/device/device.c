const char *smpt_rd_vkq_dv_ets_p[] =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

VkDevice *smpt_rd_vkq_dv_p;

void smpt_rd_vkq_dv_set()
{
	smpt_rd_vkq_dv_p = malloc(sizeof(VkDevice) * smpt_rd_vkq_dv_pscdv_bl);
}

void smpt_rd_vkq_dv_make(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = smpt_rd_vkq_dv_pscdv_p[device];
	uint32_t max_queue = smpt_rd_vkq_max_queue_p[device];

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
	SMPT_DB_N2L("vkphysicaldevicefeatures.samplerAnisotropy %d", vkphysicaldevicefeatures.samplerAnisotropy)

	SMPT_DB_R2L
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
				.enabledExtensionCount = sizeof(smpt_rd_vkq_dv_ets_p) / sizeof(smpt_rd_vkq_dv_ets_p[0]),
				.ppEnabledExtensionNames = smpt_rd_vkq_dv_ets_p,

				#ifdef SMPT_CM_VK_DEBUG
					.enabledLayerCount = sizeof(smpt_rd_vkq_dv_pscdv_it_layer_p) / sizeof(smpt_rd_vkq_dv_pscdv_it_layer_p[0]),
					.ppEnabledLayerNames = smpt_rd_vkq_dv_pscdv_it_layer_p,
				#else
					.enabledLayerCount = 0,
					.ppEnabledLayerNames = VK_NULL_HANDLE,
				#endif

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&smpt_rd_vkq_dv_p[device]
		)
	)

	free(vkdevicequeuecreateinfo_p);
}

void smpt_rd_vkq_dv_free()
{
	for (uint32_t d = 0; d < smpt_rd_vkq_dv_pscdv_bl; ++d)
	{
		vkDestroyDevice(smpt_rd_vkq_dv_p[d], VK_NULL_HANDLE);
	}

	free(smpt_rd_vkq_dv_p);
}