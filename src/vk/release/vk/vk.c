uint32_t m_device = 0;
uint32_t m_queue_g = 0;
uint32_t m_queue_ct = 0;

#ifdef NALI_DEBUG

static void einfo(uint32_t d)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[d];

	uint32_t extensions = 0;
	nali_info("vkEnumerateDeviceExtensionProperties %d", vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, VK_NULL_HANDLE))

	VkExtensionProperties *vkextensionproperties_p = malloc(extensions * sizeof(VkExtensionProperties));
	nali_info("vkEnumerateDeviceExtensionProperties %d", vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, vkextensionproperties_p))

	uint32_t device_extensions_size = sizeof(deviceextensions) / sizeof(deviceextensions[0]);
	uint32_t device_extensions = 0;
	for (uint32_t x = 0; x < extensions; ++x)
	{
		VkExtensionProperties vkextensionproperties = vkextensionproperties_p[x];
		for (uint32_t y = 0; y < device_extensions_size; ++y)
		{
			if (!strcmp(deviceextensions[y], vkextensionproperties.extensionName))
			{
				++device_extensions;
			}
		}
	}
	nali_log("extensions %d", extensions)
	for (uint32_t x = 0; x < extensions; ++x)
	{
		VkExtensionProperties vkextensionproperties = vkextensionproperties_p[x];
		nali_log("extensionName %s", vkextensionproperties.extensionName)
	}

	free(vkextensionproperties_p);
	nali_log("device_extension_support %d", device_extensions == device_extensions_size)
}

static void ieinfo()
{
	uint32_t count = 0;
	nali_info("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, VK_NULL_HANDLE))

	VkExtensionProperties *vkextensionproperties_p = malloc(sizeof(VkExtensionProperties) * count);

	nali_info("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, vkextensionproperties_p))

	for (uint32_t i = 0; i < count; ++i)
	{
		nali_log("%d %s", i, vkextensionproperties_p[i].extensionName)
	}

	free(vkextensionproperties_p);
}

static void vkinfo(uint32_t device)
{
	VkPhysicalDeviceProperties vkphysicaldeviceproperties;
	vkGetPhysicalDeviceProperties(m_vkphysicaldevice_p[device], &vkphysicaldeviceproperties);
	nali_log("Name %s", vkphysicaldeviceproperties.deviceName)
	nali_log
	(
		"Vulkan MAJOR MINOR PATCH %d.%d.%d",
		VK_VERSION_MAJOR(vkphysicaldeviceproperties.apiVersion),
		VK_VERSION_MINOR(vkphysicaldeviceproperties.apiVersion),
		VK_VERSION_PATCH(vkphysicaldeviceproperties.apiVersion)
	)
	nali_log("maxUniformBufferRange %d", vkphysicaldeviceproperties.limits.maxUniformBufferRange)
	nali_log("maxPerStageDescriptorUniformBuffers %d", vkphysicaldeviceproperties.limits.maxPerStageDescriptorUniformBuffers)
	nali_log("maxDescriptorSetUniformBuffers %d", vkphysicaldeviceproperties.limits.maxDescriptorSetUniformBuffers)
	nali_log("maxStorageBufferRange %d", vkphysicaldeviceproperties.limits.maxStorageBufferRange)
	nali_log("maxPerStageDescriptorStorageBuffers %d", vkphysicaldeviceproperties.limits.maxPerStageDescriptorStorageBuffers)
	nali_log("maxDescriptorSetStorageBuffers %d", vkphysicaldeviceproperties.limits.maxDescriptorSetStorageBuffers)

	nali_log("maxPerStageResources %d", vkphysicaldeviceproperties.limits.maxPerStageResources)

	nali_log("maxSamplerAnisotropy %f", vkphysicaldeviceproperties.limits.maxSamplerAnisotropy)

	//VkSampleCountFlagBits
	nali_log("framebufferColorSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferColorSampleCounts)
	nali_log("framebufferDepthSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferDepthSampleCounts)
}

static void dginfo()
{
	// uint32_t device_group;
	// nali_info("vkEnumeratePhysicalDeviceGroups %d", vkEnumeratePhysicalDeviceGroups(m_vkinstance, &device_group, 0))
	// VkPhysicalDeviceGroupProperties *vkphysicaldevicegroupproperties_p = malloc(sizeof(VkPhysicalDeviceGroupProperties) * device_group);
	// nali_info("vkEnumeratePhysicalDeviceGroups %d", vkEnumeratePhysicalDeviceGroups(m_vkinstance, &device_group, vkphysicaldevicegroupproperties_p))
	// nali_log("device_group %d", device_group)
	// for (uint32_t u = 0; u < device_group; ++u)
	// {
	// 	nali_log("physicalDeviceCount %d", vkphysicaldevicegroupproperties_p[u].physicalDeviceCount)
	// }
	// free(vkphysicaldevicegroupproperties_p);
}

static void pminfo(uint32_t device)
{
	// VkPeerMemoryFeatureFlags vkpeermemoryfeatureflags;
	// vkGetDeviceGroupPeerMemoryFeatures(m_vkdevice_p[device], 0, 1, VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT, &vkpeermemoryfeatureflags);
	// //VkPeerMemoryFeatureFlagBits
	// nali_log("vkpeermemoryfeatureflags %d", vkpeermemoryfeatureflags)
}

#endif

void vk_init()
{
	#ifdef NALI_DEBUG
		ieinfo();
	#endif

	vk_makeInstance();

	#ifdef NALI_DEBUG
		dginfo();
	#endif

	#ifdef NALI_VK_DEBUG
		vk_makeDebug();
	#endif

	vk_makePhysicalDevice();

	vk_initQueue();
	vk_initDevice();
	vk_initCommandPool();

	VK_makeSurface

	for (uint32_t d = 0; d < m_physical_device; ++d)
	{
		nali_log("device %d", d)
		#ifdef NALI_DEBUG
			einfo(d);
			vkinfo(d);
		#endif

		vk_setQueue(d);
		vk_makeDevice(d);

		#ifdef NALI_DEBUG
			pminfo(d);
		#endif

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

	VK_freeSurface
	vk_freeInstance();
}