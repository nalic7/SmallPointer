const char *vkqd_deviceextensions[] =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

VkDevice *vkqd_vkdevice_p;

void vkqd_set()
{
	vkqd_vkdevice_p = malloc(sizeof(VkDevice) * vkqdpd_physical_device);
}

void vkqd_make(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = vkqdpd_vkphysicaldevice_p[device];
	uint32_t max_queue = vkq_max_queue_p[device];

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
	NALI_D_LOG("vkphysicaldevicefeatures.samplerAnisotropy %d", vkphysicaldevicefeatures.samplerAnisotropy)

	NALI_D_INFO
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
				.enabledExtensionCount = sizeof(vkqd_deviceextensions) / sizeof(vkqd_deviceextensions[0]),
				.ppEnabledExtensionNames = vkqd_deviceextensions,

				#ifdef C_NALI_VK_DEBUG
					.enabledLayerCount = sizeof(vkqdpdi_ppEnabledLayerNames) / sizeof(vkqdpdi_ppEnabledLayerNames[0]),
					.ppEnabledLayerNames = vkqdpdi_ppEnabledLayerNames,
				#else
					.enabledLayerCount = 0,
					.ppEnabledLayerNames = VK_NULL_HANDLE,
				#endif

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&vkqd_vkdevice_p[device]
		)
	)

	free(vkdevicequeuecreateinfo_p);
}

void vkqd_free()
{
	for (uint32_t d = 0; d < vkqdpd_physical_device; ++d)
	{
		vkDestroyDevice(vkqd_vkdevice_p[d], VK_NULL_HANDLE);
	}

	free(vkqd_vkdevice_p);
}