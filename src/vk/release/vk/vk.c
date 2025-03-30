float m_limits_max_sampler_anisotropy;

uint32_t m_device = 0;
uint32_t m_queue_g = 0;
uint32_t m_queue_ct = 0;

static void einfo(uint32_t d)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[d];

	uint32_t extensions = 0;
	vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, VK_NULL_HANDLE);

	VkExtensionProperties *vkextensionproperties_p = malloc(extensions *sizeof(VkExtensionProperties));
	vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, vkextensionproperties_p);

	uint32_t device_extensions_size = sizeof(deviceextensions) / sizeof(deviceextensions[0]);
	uint32_t device_extensions = 0;
	for (uint32_t x = 0; x < extensions; ++x)
	{
		VkExtensionProperties vkextensionproperties = vkextensionproperties_p[x];
		for (uint32_t y = 0; y < device_extensions_size; ++y)
		{
			if (strcmp(deviceextensions[y], vkextensionproperties.extensionName) == 0)
			{
				++device_extensions;
			}
		}
	}
	info("extensions %d", extensions)
	for (uint32_t x = 0; x < extensions; ++x)
	{
		VkExtensionProperties vkextensionproperties = vkextensionproperties_p[x];
		info("extensionName %s", vkextensionproperties.extensionName)
	}

	free(vkextensionproperties_p);
	char extensionssupported = device_extensions == device_extensions_size;
	info("device_extension_support %d", extensionssupported)
}

static void ieinfo()
{
	uint32_t count = 0;
	vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, VK_NULL_HANDLE);

	VkExtensionProperties *vkextensionproperties_p = malloc(sizeof(VkExtensionProperties) * count);
	if (vkextensionproperties_p == VK_NULL_HANDLE)
	{
		error("VkExtensionProperties VK_NULL_HANDLE")
	}

	VkResult vkresult = vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, vkextensionproperties_p);
	if (vkresult != VK_SUCCESS)
	{
		error("vkEnumerateInstanceExtensionProperties %d", vkresult)
	}

	for (uint32_t i = 0; i < count; ++i)
	{
		info("%d %s", i, vkextensionproperties_p[i].extensionName)
	}

	free(vkextensionproperties_p);
}

static void vkinfo(uint32_t device)
{
	VkPhysicalDeviceProperties vkphysicaldeviceproperties;
	vkGetPhysicalDeviceProperties(m_vkphysicaldevice_p[device], &vkphysicaldeviceproperties);
	info("Name %s", vkphysicaldeviceproperties.deviceName)
	info
	(
		"Vulkan MAJOR MINOR PATCH %d.%d.%d", 
		VK_VERSION_MAJOR(vkphysicaldeviceproperties.apiVersion),
		VK_VERSION_MINOR(vkphysicaldeviceproperties.apiVersion),
		VK_VERSION_PATCH(vkphysicaldeviceproperties.apiVersion)
	)
	m_limits_max_sampler_anisotropy = vkphysicaldeviceproperties.limits.maxSamplerAnisotropy;
	info("maxSamplerAnisotropy %f", m_limits_max_sampler_anisotropy)

	//VkSampleCountFlagBits
	info("framebufferColorSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferColorSampleCounts);
	info("framebufferDepthSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferDepthSampleCounts);
}

void vk_init()
{
	ieinfo();

	vk_makeInstance();

	//s0-dginfo
	uint32_t device_group;
	vkEnumeratePhysicalDeviceGroups(m_vkinstance, &device_group, 0);
	VkPhysicalDeviceGroupProperties *vkphysicaldevicegroupproperties_p = malloc(sizeof(VkPhysicalDeviceGroupProperties) * device_group);
	vkEnumeratePhysicalDeviceGroups(m_vkinstance, &device_group, vkphysicaldevicegroupproperties_p);
	info("device_group %d", device_group)
	for (uint32_t u = 0; u < device_group; ++u)
	{
		info("physicalDeviceCount %d", vkphysicaldevicegroupproperties_p[u].physicalDeviceCount)
	}
	free(vkphysicaldevicegroupproperties_p);
	//e0-dginfo

	vk_makeSurface();

	#ifdef NALI_VK_DEBUG
		vk_makeDebug();
	#endif

	vk_makePhysicalDevice();

	vk_initQueue();
	vk_initDevice();

	vk_initCommandPool();

	for (uint32_t d = 0; d < m_physical_device; ++d)
	{
		info("device %d", d)
		einfo(d);
		vkinfo(d);

		vk_setQueue(d);
		vk_makeDevice(d);

		//s0-pminfo
		VkPeerMemoryFeatureFlags vkpeermemoryfeatureflags;
		vkGetDeviceGroupPeerMemoryFeatures(m_vkdevice_p[d], 0, 1, VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT, &vkpeermemoryfeatureflags);
		//VkPeerMemoryFeatureFlagBits
		info("vkpeermemoryfeatureflags %d", vkpeermemoryfeatureflags)
		//e0-pminfo

		vk_getQueue(d);

		vk_makeCommandPool(d);
	}

	vk_makeSwapchain(m_max_queue_surface_p[m_device] == 1 ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT);
}

void vk_clean()
{
	lc_clearVK(m_device);

	vk_freeCommandPool();

	vk_freeSwapchain();

	vk_freeDevice();
	vk_freeQueue();
	vk_freePhysicalDevice();

	#ifdef NALI_VK_DEBUG
		vk_freeDebug();
	#endif

	vk_freeSurface();
	vk_freeInstance();
}