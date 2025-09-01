const char *_rd_vkq_dv_ets_p[] =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

VkDevice *_rd_vkq_dv_p;

void _rd_vkq_dv_set()
{
	_rd_vkq_dv_p = malloc(sizeof(VkDevice) * _rd_vkq_dv_pscdv_bl);
}

void _rd_vkq_dv_make(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = _rd_vkq_dv_pscdv_p[device];
	uint32_t max_queue = _rd_vkq_max_queue_p[device];

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
	_DB_N2L("vkphysicaldevicefeatures.samplerAnisotropy %d", vkphysicaldevicefeatures.samplerAnisotropy)

	_DB_R2L
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
				.enabledExtensionCount = sizeof(_rd_vkq_dv_ets_p) / sizeof(_rd_vkq_dv_ets_p[0]),
				.ppEnabledExtensionNames = _rd_vkq_dv_ets_p,

				#ifdef _CM_VK_DEBUG
					.enabledLayerCount = sizeof(_rd_vkq_dv_pscdv_it_layer_p) / sizeof(_rd_vkq_dv_pscdv_it_layer_p[0]),
					.ppEnabledLayerNames = _rd_vkq_dv_pscdv_it_layer_p,
				#else
					.enabledLayerCount = 0,
					.ppEnabledLayerNames = VK_NULL_HANDLE,
				#endif

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&_rd_vkq_dv_p[device]
		)
	)

	free(vkdevicequeuecreateinfo_p);
}

void _rd_vkq_dv_free()
{
	for (uint32_t d = 0; d < _rd_vkq_dv_pscdv_bl; ++d)
	{
		vkDestroyDevice(_rd_vkq_dv_p[d], VK_NULL_HANDLE);
	}

	free(_rd_vkq_dv_p);
}