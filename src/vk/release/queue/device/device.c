VkDevice *m_vkdevice_p;

void vk_initDevice()
{
	m_vkdevice_p = malloc(sizeof(VkDevice) * m_physical_device);
}

void vk_makeDevice(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[device];
	uint32_t max_queue = m_max_queue_p[device];

	VkDeviceQueueCreateInfo *vkdevicequeuecreateinfo_p = malloc(max_queue * sizeof(VkDeviceQueueCreateInfo));

	float queuepriority = 1.0F;

	for (uint32_t i = 0; i < max_queue; ++i)
	{
		VkDeviceQueueCreateInfo vkdevicequeuecreateinfo = 
		{
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = i,
			.queueCount = 1,
			.pQueuePriorities = &queuepriority,

			.flags = 0,
			.pNext = VK_NULL_HANDLE
		};
		vkdevicequeuecreateinfo_p[i] = vkdevicequeuecreateinfo;
	}

	// VkPhysicalDeviceFeatures vkphysicaldevicefeatures =
	// {
	// 	.samplerAnisotropy = 1
	// };

	VkPhysicalDeviceFeatures vkphysicaldevicefeatures;
	vkGetPhysicalDeviceFeatures(vkphysicaldevice, &vkphysicaldevicefeatures);
	info("vkphysicaldevicefeatures.samplerAnisotropy %d", vkphysicaldevicefeatures.samplerAnisotropy)

	VkDeviceCreateInfo vkdevicecreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.queueCreateInfoCount = max_queue,
		.pQueueCreateInfos = vkdevicequeuecreateinfo_p,
		.pEnabledFeatures = &vkphysicaldevicefeatures,
		.enabledExtensionCount = sizeof(deviceextensions) / sizeof(deviceextensions[0]),
		.ppEnabledExtensionNames = deviceextensions,

		#ifdef NALI_VK_DEBUG
			.enabledLayerCount = sizeof(ppEnabledLayerNames) / sizeof(ppEnabledLayerNames[0]),
			.ppEnabledLayerNames = ppEnabledLayerNames,
		#else
			.enabledLayerCount = 0,
			.ppEnabledLayerNames = VK_NULL_HANDLE,
		#endif

		.flags = 0,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateDevice(vkphysicaldevice, &vkdevicecreateinfo, VK_NULL_HANDLE, &m_vkdevice_p[device]);
}

void vk_freeDevice()
{
	for (uint32_t d = 0; d < m_physical_device; ++d)
	{
		vkDestroyDevice(m_vkdevice_p[d], VK_NULL_HANDLE);
	}

	free(m_vkdevice_p);
}