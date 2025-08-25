//.c select gpu index
uint32_t vk_device = 0;
uint32_t vk_queue_g = 0;
uint32_t vk_queue_ct = 0;

uint8_t vk_non_coherent_atom_size;

#ifdef _CM_DEBUG
	static void einfo(uint32_t d)
	{
		VkPhysicalDevice vkphysicaldevice = _vkq_dv_pscdv_p[d];

		uint32_t extensions = 0;
		_DB_R2L("vkEnumerateDeviceExtensionProperties %d", vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, VK_NULL_HANDLE))

		VkExtensionProperties *vkextensionproperties_p = malloc(extensions * sizeof(VkExtensionProperties));
		_DB_R2L("vkEnumerateDeviceExtensionProperties %d", vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, vkextensionproperties_p))

		uint32_t device_extensions_size = sizeof(_vkq_dv_ets_p) / sizeof(_vkq_dv_ets_p[0]);
		uint32_t device_extensions = 0;
		for (uint32_t x = 0; x < extensions; ++x)
		{
			VkExtensionProperties vkextensionproperties = vkextensionproperties_p[x];
			for (uint32_t y = 0; y < device_extensions_size; ++y)
			{
				if (!strcmp(_vkq_dv_ets_p[y], vkextensionproperties.extensionName))
				{
					++device_extensions;
				}
			}
		}
		_DB_N2L("extensions %d", extensions)
		for (uint32_t x = 0; x < extensions; ++x)
		{
			VkExtensionProperties vkextensionproperties = vkextensionproperties_p[x];
			_DB_N2L("extensionName %s", vkextensionproperties.extensionName)
		}

		free(vkextensionproperties_p);
		_DB_N2L("device_extension_support %d", device_extensions == device_extensions_size)
	}

	static void ieinfo()
	{
		uint32_t count = 0;
		_DB_R2L("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, VK_NULL_HANDLE))

		VkExtensionProperties *vkextensionproperties_p = malloc(sizeof(VkExtensionProperties) * count);

		_DB_R2L("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, vkextensionproperties_p))

		for (uint32_t i = 0; i < count; ++i)
		{
			_DB_N2L("%d %s", i, vkextensionproperties_p[i].extensionName)
		}

		free(vkextensionproperties_p);
	}

	static void vkinfo(uint32_t device)
	{
		VkPhysicalDeviceProperties vkphysicaldeviceproperties;
		vkGetPhysicalDeviceProperties(_vkq_dv_pscdv_p[device], &vkphysicaldeviceproperties);
		_DB_N2L("Name %s", vkphysicaldeviceproperties.deviceName)
		_DB_N2L
		(
			"Vulkan MAJOR MINOR PATCH %d.%d.%d",
			VK_VERSION_MAJOR(vkphysicaldeviceproperties.apiVersion),
			VK_VERSION_MINOR(vkphysicaldeviceproperties.apiVersion),
			VK_VERSION_PATCH(vkphysicaldeviceproperties.apiVersion)
		)
		_DB_N2L("maxUniformBufferRange %d", vkphysicaldeviceproperties.limits.maxUniformBufferRange)
		_DB_N2L("maxPerStageDescriptorUniformBuffers %d", vkphysicaldeviceproperties.limits.maxPerStageDescriptorUniformBuffers)
		_DB_N2L("maxDescriptorSetUniformBuffers %d", vkphysicaldeviceproperties.limits.maxDescriptorSetUniformBuffers)
		_DB_N2L("maxStorageBufferRange %d", vkphysicaldeviceproperties.limits.maxStorageBufferRange)
		_DB_N2L("maxPerStageDescriptorStorageBuffers %d", vkphysicaldeviceproperties.limits.maxPerStageDescriptorStorageBuffers)
		_DB_N2L("maxDescriptorSetStorageBuffers %d", vkphysicaldeviceproperties.limits.maxDescriptorSetStorageBuffers)

		_DB_N2L("maxPerStageResources %d", vkphysicaldeviceproperties.limits.maxPerStageResources)

		_DB_N2L("maxSamplerAnisotropy %f", vkphysicaldeviceproperties.limits.maxSamplerAnisotropy)

		//VkSampleCountFlagBits
		_DB_N2L("framebufferColorSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferColorSampleCounts)
		_DB_N2L("framebufferDepthSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferDepthSampleCounts)

		_DB_R2L("nonCoherentAtomSize %d", vk_non_coherent_atom_size = vkphysicaldeviceproperties.limits.nonCoherentAtomSize)
	}

	static void dginfo()
	{
		// uint32_t device_group;
		// _DB_R2L("vkEnumeratePhysicalDeviceGroups %d", vkEnumeratePhysicalDeviceGroups(_vkq_dv_pscdv_it, &device_group, 0))
		// VkPhysicalDeviceGroupProperties *vkphysicaldevicegroupproperties_p = malloc(sizeof(VkPhysicalDeviceGroupProperties) * device_group);
		// _DB_R2L("vkEnumeratePhysicalDeviceGroups %d", vkEnumeratePhysicalDeviceGroups(_vkq_dv_pscdv_it, &device_group, vkphysicaldevicegroupproperties_p))
		// _DB_N2L("device_group %d", device_group)
		// for (uint32_t u = 0; u < device_group; ++u)
		// {
		// 	_DB_N2L("physicalDeviceCount %d", vkphysicaldevicegroupproperties_p[u].physicalDeviceCount)
		// }
		// free(vkphysicaldevicegroupproperties_p);
	}

	static void pminfo(uint32_t device)
	{
		// VkPeerMemoryFeatureFlags vkpeermemoryfeatureflags;
		// vkGetDeviceGroupPeerMemoryFeatures(_vkq_dv_p[device], 0, 1, VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT, &vkpeermemoryfeatureflags);
		// //VkPeerMemoryFeatureFlagBits
		// _DB_N2L("vkpeermemoryfeatureflags %d", vkpeermemoryfeatureflags)
	}
#endif

void _vk_set()
{
	#ifdef _CM_DEBUG
		ieinfo();
	#endif

	_vkq_dv_pscdv_it_make();

	#ifdef _CM_DEBUG
		dginfo();
	#endif

	#ifdef _CM_DEBUG
		_vk_db_make();
	#endif

	_vkq_dv_pscdv_make();

	_vkq_set();
	_vkq_dv_set();
	_vk_cmp_set();

	_vk_sf_make();

	for (uint32_t d = 0; d < _vkq_dv_pscdv_bl; ++d)
	{
		_DB_N2L("device %d", d)
		#ifdef _CM_DEBUG
			einfo(d);
			vkinfo(d);
		#endif

		_vkq_add(d);
		_vkq_dv_make(d);

		#ifdef _CM_DEBUG
			pminfo(d);
		#endif

		_vkq_get(d);

		_vk_cmp_make(d);
	}

	_vk_swc_make(_vkq_max_queue_surface_p[vk_device] == 1 ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT);
}

void _vk_free()
{
	lc_freeVk(vk_device);

	_vk_cmp_free();

	_vk_swc_free();

	_vkq_dv_free();
	_vkq_free();
	_vkq_dv_pscdv_free();

	#ifdef _CM_DEBUG
		_vk_db_free();
	#endif

	_vk_sf_free();
	_vkq_dv_pscdv_it_free();
}
