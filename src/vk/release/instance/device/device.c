void vk_makeDevice(uint32_t device, VkDeviceQueueCreateFlags vkdevicequeuecreateflags, VkDeviceCreateFlags vkdevicecreateflags)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[device];
	uint8_t max_graphics = m_max_graphic_p[device];
	// QueueList queuelist = vk_findQueue(vk, vkphysicaldevice);

	info("max_graphics %d", max_graphics)

	VkDeviceQueueCreateInfo *vkdevicequeuecreateinfo_p = malloc(max_graphics * sizeof(VkDeviceQueueCreateInfo));

	float queuepriority = 1.0F;

	// uint32_t queueFamilyIndex[] =
	// {
	//	 queuelist.all,
	//	 queuelist.now
	// };

	for (uint32_t i = 0; i < max_graphics; ++i)
	{
		info("use_graphic %d", m_graphic_p[device][i])
		VkDeviceQueueCreateInfo vkdevicequeuecreateinfo = 
		{
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = m_graphic_p[device][i],
			.queueCount = 1,
			.pQueuePriorities = &queuepriority,

			.flags = vkdevicequeuecreateflags,
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
		.queueCreateInfoCount = max_graphics,
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

		.flags = vkdevicecreateflags,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateDevice(vkphysicaldevice, &vkdevicecreateinfo, VK_NULL_HANDLE, &m_vkdevice_p[device]);

	m_vkqueue_p[device] = malloc(max_graphics * sizeof(VkQueue));

	for (uint32_t i = 0; i < max_graphics; ++i)
	{
		vkGetDeviceQueue(m_vkdevice_p[device], m_graphic_p[device][i], 0, &m_vkqueue_p[device][i]);
	}
}
