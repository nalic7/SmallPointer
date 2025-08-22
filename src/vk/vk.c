//.c select gpu index
uint32_t vk_device = 0;
uint32_t vk_queue_g = 0;
uint32_t vk_queue_ct = 0;

uint8_t vk_non_coherent_atom_size;

#ifdef C_NALI_DEBUG

static void einfo(uint32_t d)
{
	VkPhysicalDevice vkphysicaldevice = vkqdpd_vkphysicaldevice_p[d];

	uint32_t extensions = 0;
	NALI_D_INFO("vkEnumerateDeviceExtensionProperties %d", vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, VK_NULL_HANDLE))

	VkExtensionProperties *vkextensionproperties_p = malloc(extensions * sizeof(VkExtensionProperties));
	NALI_D_INFO("vkEnumerateDeviceExtensionProperties %d", vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, vkextensionproperties_p))

	uint32_t device_extensions_size = sizeof(vkqd_deviceextensions) / sizeof(vkqd_deviceextensions[0]);
	uint32_t device_extensions = 0;
	for (uint32_t x = 0; x < extensions; ++x)
	{
		VkExtensionProperties vkextensionproperties = vkextensionproperties_p[x];
		for (uint32_t y = 0; y < device_extensions_size; ++y)
		{
			if (!strcmp(vkqd_deviceextensions[y], vkextensionproperties.extensionName))
			{
				++device_extensions;
			}
		}
	}
	NALI_D_LOG("extensions %d", extensions)
	for (uint32_t x = 0; x < extensions; ++x)
	{
		VkExtensionProperties vkextensionproperties = vkextensionproperties_p[x];
		NALI_D_LOG("extensionName %s", vkextensionproperties.extensionName)
	}

	free(vkextensionproperties_p);
	NALI_D_LOG("device_extension_support %d", device_extensions == device_extensions_size)
}

static void ieinfo()
{
	uint32_t count = 0;
	NALI_D_INFO("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, VK_NULL_HANDLE))

	VkExtensionProperties *vkextensionproperties_p = malloc(sizeof(VkExtensionProperties) * count);

	NALI_D_INFO("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, vkextensionproperties_p))

	for (uint32_t i = 0; i < count; ++i)
	{
		NALI_D_LOG("%d %s", i, vkextensionproperties_p[i].extensionName)
	}

	free(vkextensionproperties_p);
}

static void vkinfo(uint32_t device)
{
	VkPhysicalDeviceProperties vkphysicaldeviceproperties;
	vkGetPhysicalDeviceProperties(vkqdpd_vkphysicaldevice_p[device], &vkphysicaldeviceproperties);
	NALI_D_LOG("Name %s", vkphysicaldeviceproperties.deviceName)
	NALI_D_LOG
	(
		"Vulkan MAJOR MINOR PATCH %d.%d.%d",
		VK_VERSION_MAJOR(vkphysicaldeviceproperties.apiVersion),
		VK_VERSION_MINOR(vkphysicaldeviceproperties.apiVersion),
		VK_VERSION_PATCH(vkphysicaldeviceproperties.apiVersion)
	)
	NALI_D_LOG("maxUniformBufferRange %d", vkphysicaldeviceproperties.limits.maxUniformBufferRange)
	NALI_D_LOG("maxPerStageDescriptorUniformBuffers %d", vkphysicaldeviceproperties.limits.maxPerStageDescriptorUniformBuffers)
	NALI_D_LOG("maxDescriptorSetUniformBuffers %d", vkphysicaldeviceproperties.limits.maxDescriptorSetUniformBuffers)
	NALI_D_LOG("maxStorageBufferRange %d", vkphysicaldeviceproperties.limits.maxStorageBufferRange)
	NALI_D_LOG("maxPerStageDescriptorStorageBuffers %d", vkphysicaldeviceproperties.limits.maxPerStageDescriptorStorageBuffers)
	NALI_D_LOG("maxDescriptorSetStorageBuffers %d", vkphysicaldeviceproperties.limits.maxDescriptorSetStorageBuffers)

	NALI_D_LOG("maxPerStageResources %d", vkphysicaldeviceproperties.limits.maxPerStageResources)

	NALI_D_LOG("maxSamplerAnisotropy %f", vkphysicaldeviceproperties.limits.maxSamplerAnisotropy)

	//VkSampleCountFlagBits
	NALI_D_LOG("framebufferColorSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferColorSampleCounts)
	NALI_D_LOG("framebufferDepthSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferDepthSampleCounts)

	NALI_D_INFO("nonCoherentAtomSize %d", vk_non_coherent_atom_size = vkphysicaldeviceproperties.limits.nonCoherentAtomSize)
}

static void dginfo()
{
	// uint32_t device_group;
	// NALI_D_INFO("vkEnumeratePhysicalDeviceGroups %d", vkEnumeratePhysicalDeviceGroups(vkqdpdi_vkinstance, &device_group, 0))
	// VkPhysicalDeviceGroupProperties *vkphysicaldevicegroupproperties_p = malloc(sizeof(VkPhysicalDeviceGroupProperties) * device_group);
	// NALI_D_INFO("vkEnumeratePhysicalDeviceGroups %d", vkEnumeratePhysicalDeviceGroups(vkqdpdi_vkinstance, &device_group, vkphysicaldevicegroupproperties_p))
	// NALI_D_LOG("device_group %d", device_group)
	// for (uint32_t u = 0; u < device_group; ++u)
	// {
	// 	NALI_D_LOG("physicalDeviceCount %d", vkphysicaldevicegroupproperties_p[u].physicalDeviceCount)
	// }
	// free(vkphysicaldevicegroupproperties_p);
}

static void pminfo(uint32_t device)
{
	// VkPeerMemoryFeatureFlags vkpeermemoryfeatureflags;
	// vkGetDeviceGroupPeerMemoryFeatures(vkqd_vkdevice_p[device], 0, 1, VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT, &vkpeermemoryfeatureflags);
	// //VkPeerMemoryFeatureFlagBits
	// NALI_D_LOG("vkpeermemoryfeatureflags %d", vkpeermemoryfeatureflags)
}

#endif

void vk_set()
{
	#ifdef C_NALI_DEBUG
		ieinfo();
	#endif

	vkqdpdi_make();

	#ifdef C_NALI_DEBUG
		dginfo();
	#endif

	#ifdef C_NALI_VK_DEBUG
		vkd_make();
	#endif

	vkqdpd_make();

	vkq_set();
	vkqd_set();
	vkcbcp_set();

	vk_makeSurface();

	for (uint32_t d = 0; d < vkqdpd_physical_device; ++d)
	{
		NALI_D_LOG("device %d", d)
		#ifdef C_NALI_DEBUG
			einfo(d);
			vkinfo(d);
		#endif

		vkq_setQueue(d);
		vkqd_make(d);

		#ifdef C_NALI_DEBUG
			pminfo(d);
		#endif

		vkq_getQueue(d);

		vkcbcp_make(d);
	}

	vksc_make(vkq_max_queue_surface_p[vk_device] == 1 ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT);
}

void vk_free()
{
	lc_freeVk(vk_device);

	vkcbcp_free();

	vksc_free();

	vkqd_free();
	vkq_free();
	vkqdpd_free();

	#ifdef C_NALI_VK_DEBUG
		vkd_free();
	#endif

	vk_freeSurface();
	vkqdpdi_free();
}
