//.c select gpu index
uint32_t smpt_rd_vk_device = 0;
uint32_t smpt_rd_vk_queue_g = 0;
uint32_t smpt_rd_vk_queue_ct = 0;

uint8_t smpt_rd_vk_non_coherent_atom_size;

#ifdef SMPT_CM_DEBUG
	static void einfo(uint32_t d)
	{
		VkPhysicalDevice vkphysicaldevice = smpt_rd_vkq_dv_pscdv_p[d];

		uint32_t extensions = 0;
		SMPT_DBmR2L("vkEnumerateDeviceExtensionProperties %d", vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, VK_NULL_HANDLE))

		VkExtensionProperties *vkextensionproperties_p = malloc(extensions * sizeof(VkExtensionProperties));
		SMPT_DBmR2L("vkEnumerateDeviceExtensionProperties %d", vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, vkextensionproperties_p))

		uint32_t device_extensions_size = sizeof(smpt_rd_vkq_dv_ets_p) / sizeof(smpt_rd_vkq_dv_ets_p[0]);
		uint32_t device_extensions = 0;
		for (uint32_t x = 0; x < extensions; ++x)
		{
			VkExtensionProperties vkextensionproperties = vkextensionproperties_p[x];
			for (uint32_t y = 0; y < device_extensions_size; ++y)
			{
				if (!strcmp(smpt_rd_vkq_dv_ets_p[y], vkextensionproperties.extensionName))
				{
					++device_extensions;
				}
			}
		}
		SMPT_DBmN2L("extensions %d", extensions)
		for (uint32_t x = 0; x < extensions; ++x)
		{
			VkExtensionProperties vkextensionproperties = vkextensionproperties_p[x];
			SMPT_DBmN2L("extensionName %s", vkextensionproperties.extensionName)
		}

		free(vkextensionproperties_p);
		SMPT_DBmN2L("device_extension_support %d", device_extensions == device_extensions_size)
	}

	static void ieinfo()
	{
		uint32_t count = 0;
		SMPT_DBmR2L("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, VK_NULL_HANDLE))

		VkExtensionProperties *vkextensionproperties_p = malloc(sizeof(VkExtensionProperties) * count);

		SMPT_DBmR2L("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, vkextensionproperties_p))

		for (uint32_t i = 0; i < count; ++i)
		{
			SMPT_DBmN2L("%d %s", i, vkextensionproperties_p[i].extensionName)
		}

		free(vkextensionproperties_p);
	}

	static void vkinfo(uint32_t device)
	{
		VkPhysicalDeviceProperties vkphysicaldeviceproperties;
		vkGetPhysicalDeviceProperties(smpt_rd_vkq_dv_pscdv_p[device], &vkphysicaldeviceproperties);
		SMPT_DBmN2L("Name %s", vkphysicaldeviceproperties.deviceName)
		SMPT_DBmN2L
		(
			"Vulkan MAJOR MINOR PATCH %d.%d.%d",
			VK_VERSION_MAJOR(vkphysicaldeviceproperties.apiVersion),
			VK_VERSION_MINOR(vkphysicaldeviceproperties.apiVersion),
			VK_VERSION_PATCH(vkphysicaldeviceproperties.apiVersion)
		)
		SMPT_DBmN2L("maxUniformBufferRange %d", vkphysicaldeviceproperties.limits.maxUniformBufferRange)
		SMPT_DBmN2L("maxPerStageDescriptorUniformBuffers %d", vkphysicaldeviceproperties.limits.maxPerStageDescriptorUniformBuffers)
		SMPT_DBmN2L("maxDescriptorSetUniformBuffers %d", vkphysicaldeviceproperties.limits.maxDescriptorSetUniformBuffers)
		SMPT_DBmN2L("maxStorageBufferRange %d", vkphysicaldeviceproperties.limits.maxStorageBufferRange)
		SMPT_DBmN2L("maxPerStageDescriptorStorageBuffers %d", vkphysicaldeviceproperties.limits.maxPerStageDescriptorStorageBuffers)
		SMPT_DBmN2L("maxDescriptorSetStorageBuffers %d", vkphysicaldeviceproperties.limits.maxDescriptorSetStorageBuffers)

		SMPT_DBmN2L("maxPerStageResources %d", vkphysicaldeviceproperties.limits.maxPerStageResources)

		SMPT_DBmN2L("maxSamplerAnisotropy %f", vkphysicaldeviceproperties.limits.maxSamplerAnisotropy)

		//VkSampleCountFlagBits
		SMPT_DBmN2L("framebufferColorSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferColorSampleCounts)
		SMPT_DBmN2L("framebufferDepthSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferDepthSampleCounts)

		SMPT_DBmR2L("nonCoherentAtomSize %d", smpt_rd_vk_non_coherent_atom_size = vkphysicaldeviceproperties.limits.nonCoherentAtomSize)
	}

	static void dginfo()
	{
		// uint32_t device_group;
		// SMPT_DBmR2L("vkEnumeratePhysicalDeviceGroups %d", vkEnumeratePhysicalDeviceGroups(smpt_rd_vkq_dv_pscdv_it, &device_group, 0))
		// VkPhysicalDeviceGroupProperties *vkphysicaldevicegroupproperties_p = malloc(sizeof(VkPhysicalDeviceGroupProperties) * device_group);
		// SMPT_DBmR2L("vkEnumeratePhysicalDeviceGroups %d", vkEnumeratePhysicalDeviceGroups(smpt_rd_vkq_dv_pscdv_it, &device_group, vkphysicaldevicegroupproperties_p))
		// SMPT_DBmN2L("device_group %d", device_group)
		// for (uint32_t u = 0; u < device_group; ++u)
		// {
		// 	SMPT_DBmN2L("physicalDeviceCount %d", vkphysicaldevicegroupproperties_p[u].physicalDeviceCount)
		// }
		// free(vkphysicaldevicegroupproperties_p);
	}

	static void pminfo(uint32_t device)
	{
		// VkPeerMemoryFeatureFlags vkpeermemoryfeatureflags;
		// vkGetDeviceGroupPeerMemoryFeatures(smpt_rd_vkq_dv_p[device], 0, 1, VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT, &vkpeermemoryfeatureflags);
		// //VkPeerMemoryFeatureFlagBits
		// SMPT_DBmN2L("vkpeermemoryfeatureflags %d", vkpeermemoryfeatureflags)
	}
#endif

void smpt_rd_vk_set()
{
	#ifdef SMPT_CM_DEBUG
		ieinfo();
	#endif

	smpt_rd_vkq_dv_pscdv_it_make();

	#ifdef SMPT_CM_DEBUG
		dginfo();
	#endif

	#ifdef SMPT_CM_VK_DEBUG
		smpt_rd_vksmpt_db_make();
	#endif

	smpt_rd_vkq_dv_pscdv_make();

	smpt_rd_vkq_set();
	smpt_rd_vkq_dv_set();
	smpt_rd_vk_cmp_set();

	smpt_rd_vk_sf_make();

	for (uint32_t d = 0; d < smpt_rd_vkq_dv_pscdv_bl; ++d)
	{
		SMPT_DBmN2L("device %d", d)
		#ifdef SMPT_CM_DEBUG
			einfo(d);
			vkinfo(d);
		#endif

		smpt_rd_vkq_add(d);
		smpt_rd_vkq_dv_make(d);

		#ifdef SMPT_CM_DEBUG
			pminfo(d);
		#endif

		smpt_rd_vkq_get(d);

		smpt_rd_vk_cmp_make(d);
	}

	smpt_rd_vk_swcMmake(smpt_rd_vkq_max_queue_surface_p[smpt_rd_vk_device] == 1 ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT);

	while (!(smpt_sfUstate & SMPT_SFuS_RAW))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	lcp_vk();
	smpt_rd_vkw_dsts_lo_make(smpt_rd_vk_device);
	smpt_rd_vkw_dstsp_make(smpt_rd_vk_device);

	smpt_rd_vk_cmd_set();
	SMPT_DBmR2L("thrd_create %d", thrd_create(&(thrd_t){}, smpt_rd_vk_cmd_loop, NULL))
}

void smpt_rd_vk_free()
{
	smpt_rd_vk_cmp_free();

	smpt_rd_vk_swcMfree();

	smpt_rd_vkq_dv_free();
	smpt_rd_vkq_free();
	smpt_rd_vkq_dv_pscdv_free();

	#ifdef SMPT_CM_VK_DEBUG
		smpt_rd_vksmpt_db_free();
	#endif

	smpt_rd_vk_sf_free();
	smpt_rd_vkq_dv_pscdv_it_free();
}
