//.c select gpu index
uint32_t smpt_rd_vkUdevice = 0;
uint32_t smpt_rd_vkUqueue_g = 0;
uint32_t smpt_rd_vkUqueue_ct = 0;

float smpt_rd_vkFmax_sampler_anisotropy;
uint8_t
	smpt_rd_vkUnon_coherent_atom_size,
	smpt_rd_vkUsample_count;

#ifdef SMPT_CM_DEBUG
	static void einfo(uint32_t d)
	{
		VkPhysicalDevice vkphysicaldevice = smpt_rd_vkq_dv_pscdvP[d];

		uint32_t extension = 0;
		SMPT_DBmR2L("vkEnumerateDeviceExtensionProperties %d", vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extension, VK_NULL_HANDLE))

		VkExtensionProperties *Pvkextensionproperties = malloc(extension * sizeof(VkExtensionProperties));
		SMPT_DBmR2L("vkEnumerateDeviceExtensionProperties %d", vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extension, Pvkextensionproperties))

		uint32_t Ldevice_extension = sizeof(smpt_rd_vkq_dvPets) / sizeof(smpt_rd_vkq_dvPets[0]);
		uint32_t device_extension = 0;
		for (uint32_t x = 0; x < extension; ++x)
		{
			VkExtensionProperties vkextensionproperties = Pvkextensionproperties[x];
			for (uint32_t y = 0; y < Ldevice_extension; ++y)
			{
				if (!strcmp(smpt_rd_vkq_dvPets[y], vkextensionproperties.extensionName))
				{
					++device_extension;
				}
			}
		}
		SMPT_DBmN2L("extension %d", extension)
		for (uint32_t x = 0; x < extension; ++x)
		{
			VkExtensionProperties vkextensionproperties = Pvkextensionproperties[x];
			SMPT_DBmN2L("extensionName %s", vkextensionproperties.extensionName)
		}

		free(Pvkextensionproperties);
		SMPT_DBmN2L("device_extension_support %d", device_extension == Ldevice_extension)
	}

	static void ieinfo()
	{
		uint32_t count = 0;
		SMPT_DBmR2L("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, VK_NULL_HANDLE))

		VkExtensionProperties *Pvkextensionproperties = malloc(sizeof(VkExtensionProperties) * count);

		SMPT_DBmR2L("vkEnumerateInstanceExtensionProperties %d", vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, Pvkextensionproperties))

		for (uint32_t i = 0; i < count; ++i)
		{
			SMPT_DBmN2L("%d %s", i, Pvkextensionproperties[i].extensionName)
		}

		free(Pvkextensionproperties);
	}
#endif

static void vkinfo(uint32_t device)
{
	VkPhysicalDeviceProperties vkphysicaldeviceproperties;
	vkGetPhysicalDeviceProperties(smpt_rd_vkq_dv_pscdvP[device], &vkphysicaldeviceproperties);
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

	SMPT_DBmR2L("maxSamplerAnisotropy %f", smpt_rd_vkFmax_sampler_anisotropy = vkphysicaldeviceproperties.limits.maxSamplerAnisotropy)

	SMPT_DBmR2L("framebufferColorSampleCounts %d", smpt_rd_vkUsample_count = vkphysicaldeviceproperties.limits.framebufferColorSampleCounts)
	SMPT_DBmN2L("framebufferDepthSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferDepthSampleCounts)
	smpt_rd_vkUsample_count &= vkphysicaldeviceproperties.limits.framebufferDepthSampleCounts;

	if (smpt_rd_vkUsample_count & VK_SAMPLE_COUNT_64_BIT)
	{
		smpt_rd_vkUsample_count = VK_SAMPLE_COUNT_64_BIT;
	}
	else if (smpt_rd_vkUsample_count & VK_SAMPLE_COUNT_32_BIT)
	{
		smpt_rd_vkUsample_count = VK_SAMPLE_COUNT_32_BIT;
	}
	else if (smpt_rd_vkUsample_count & VK_SAMPLE_COUNT_16_BIT)
	{
		smpt_rd_vkUsample_count = VK_SAMPLE_COUNT_16_BIT;
	}
	else if (smpt_rd_vkUsample_count & VK_SAMPLE_COUNT_8_BIT)
	{
		smpt_rd_vkUsample_count = VK_SAMPLE_COUNT_8_BIT;
	}
	else if (smpt_rd_vkUsample_count & VK_SAMPLE_COUNT_4_BIT)
	{
		smpt_rd_vkUsample_count = VK_SAMPLE_COUNT_4_BIT;
	}
	else if (smpt_rd_vkUsample_count & VK_SAMPLE_COUNT_2_BIT)
	{
		smpt_rd_vkUsample_count = VK_SAMPLE_COUNT_2_BIT;
	}
	else if (smpt_rd_vkUsample_count & VK_SAMPLE_COUNT_1_BIT)
	{
		smpt_rd_vkUsample_count = VK_SAMPLE_COUNT_1_BIT;
	}
	else
	{
		smpt_rd_vkUsample_count = 0;
	}

	SMPT_DBmR2L("nonCoherentAtomSize %d", smpt_rd_vkUnon_coherent_atom_size = vkphysicaldeviceproperties.limits.nonCoherentAtomSize)
}

void smpt_rd_vkMset()
{
	#ifdef SMPT_CM_DEBUG
		ieinfo();
	#endif

	smpt_rd_vkq_dv_pscdv_itMmake();

	#ifdef SMPT_CM_VK_DEBUG
		smpt_rd_vksmpt_dbMmake();
	#endif

	smpt_rd_vkq_dv_pscdvMmake();

	smpt_rd_vkqMset();
	smpt_rd_vkq_dvMset();
	smpt_rd_vk_cmpMset();

	smpt_rd_vk_sfMmake();

	//! use dgpu as offload
	for (uint32_t l0 = 0; l0 < smpt_rd_vkq_dv_pscdvL; ++l0)
	{
		SMPT_DBmN2L("device %d", l0)
		#ifdef SMPT_CM_DEBUG
			einfo(l0);
		#endif
		vkinfo(l0);

		smpt_rd_vkqMadd(l0);
		smpt_rd_vkq_dvMmake(l0);

		smpt_rd_vkqMget(l0);

		smpt_rd_vk_cmpMmake(l0);
	}

	smpt_rd_vk_swcMmake(smpt_rd_vkqPmax_queue_surface[smpt_rd_vkUdevice] == 1 ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT);

	while (!(smpt_sfUstate & SMPT_SFuS_RAW))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	smptr_ce_mdMvk();
	smptr_ceaMvk();
	smpt_rd_vkw_dsts_loMmake(smpt_rd_vkUdevice);
	smpt_rd_vkw_dstspMmake(smpt_rd_vkUdevice);

	smpt_rd_vk_cmdMset();
	SMPT_DBmR2L("thrd_create %d", thrd_create(&(thrd_t){}, smpt_rd_vk_cmdMloop, NULL))
}

void smpt_rd_vkMfree()
{
	smpt_rd_vk_cmpMfree();

	smpt_rd_vk_swcMfree();

	smpt_rd_vkq_dvMfree();
	smpt_rd_vkqMfree();
	smpt_rd_vkq_dv_pscdvMfree();

	#ifdef SMPT_CM_VK_DEBUG
		smpt_rd_vksmpt_dbMfree();
	#endif

	smpt_rd_vk_sfMfree();
	smpt_rd_vkq_dv_pscdv_itMfree();
}
