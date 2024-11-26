void vk_makeDevice(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_ptr[device];
	unsigned char max_graphics = m_max_graphics_ptr[device];
	// QueueList queuelist = vk_findQueue(vk, vkphysicaldevice);

	info("max_graphics %d", max_graphics)

	VkDeviceQueueCreateInfo* vkdevicequeuecreateinfo_ptr = malloc(max_graphics * sizeof(VkDeviceQueueCreateInfo));

	float queuepriority = 1.0F;

	// uint32_t queueFamilyIndex[] =
	// {
	//	 queuelist.all,
	//	 queuelist.now
	// };

	for (uint32_t i = 0; i < max_graphics; ++i)
	{
		info("use_graphic %d", m_graphics_ptr[device][i])
		VkDeviceQueueCreateInfo vkdevicequeuecreateinfo = 
		{
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = m_graphics_ptr[device][i],
			.queueCount = 1,
			.pQueuePriorities = &queuepriority
		};
		vkdevicequeuecreateinfo_ptr[i] = vkdevicequeuecreateinfo;
	}

	VkPhysicalDeviceFeatures vkphysicaldevicefeatures =
	{
		.samplerAnisotropy = 1
	};

	VkDeviceCreateInfo vkdevicecreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.queueCreateInfoCount = max_graphics,
		.pQueueCreateInfos = vkdevicequeuecreateinfo_ptr,
		.pEnabledFeatures = &vkphysicaldevicefeatures,
		.enabledExtensionCount = sizeof(deviceextensions) / sizeof(deviceextensions[0]),
		.ppEnabledExtensionNames = deviceextensions,

		.enabledLayerCount = sizeof(ppEnabledLayerNames) / sizeof(ppEnabledLayerNames[0]),
		.ppEnabledLayerNames = ppEnabledLayerNames
	};

	if (vkCreateDevice(vkphysicaldevice, &vkdevicecreateinfo, VK_NULL_HANDLE, &m_vkdevice_ptr[device]) != VK_SUCCESS)
	{
		error("vkCreateDevice");
	}

	m_vkqueue_graphics_ptr[device] = malloc(max_graphics * sizeof(VkQueue));

	for (uint32_t i = 0; i < max_graphics; ++i)
	{
		vkGetDeviceQueue(m_vkdevice_ptr[device], m_graphics_ptr[device][i], 0, &m_vkqueue_graphics_ptr[device][i]);
	}
}
