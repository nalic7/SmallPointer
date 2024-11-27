const char* deviceextensions[] =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

// char deviceSuitable(uint32_t device)
// {
//	 VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_ptr[device];
//	 // QueueList queuelist = vk_findQueue(vk, vkphysicaldevice);
//	 vk_findQueue(device);
//	 // m_queuelist_ptr = realloc(m_queuelist_ptr, (i + 1) * sizeof(QueueList));
//	 // m_queuelist_ptr[i] = queuelist;

//	 //
//	 uint32_t extensions = 0;
//	 vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, VK_NULL_HANDLE);

//	 VkExtensionProperties *vkextensionproperties_ptr = malloc(extensions * sizeof(VkExtensionProperties));
//	 vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, vkextensionproperties_ptr);

//	 uint32_t device_extensions_size = sizeof(deviceextensions) / sizeof(deviceextensions[0]);
//	 uint32_t device_extensions = 0;
//	 for (uint32_t x = 0; x < extensions; ++x)
//	 {
//		 VkExtensionProperties vkextensionproperties = vkextensionproperties_ptr[x];
//		 for (uint32_t y = 0; y < device_extensions_size; ++y)
//		 {
//			 // int result = strcmp(deviceextensions[y], vkextensionproperties.extensionName);
//			 // info("match %s %s", deviceextensions[y], vkextensionproperties.extensionName)
//			 // info("strcmp %d", result)
//			 // if (result == 0)
//			 if (strcmp(deviceextensions[y], vkextensionproperties.extensionName) == 0)
//			 {
//				 ++device_extensions;
//			 }
//		 }
//	 }
//	 info("extensions %d", extensions)
//	 for (uint32_t x = 0; x < extensions; ++x)
//	 {
//		 VkExtensionProperties vkextensionproperties = vkextensionproperties_ptr[x];
//		 info("extensionName %s", vkextensionproperties.extensionName)
//	 }

//	 free(vkextensionproperties_ptr);
//	 char extensionssupported = device_extensions == device_extensions_size;
//	 info("device_extension_support %d", extensionssupported)
//	 //

//	 // char swapchainadequate;
//	 // if (extensionssupported)
//	 // {
//	 //	 // SwapchainSupportDetails swapchainsupportdetails = vk_querySwapChainSupport(vk, vkphysicaldevice);
//	 //	 // swapchainadequate = (swapchainsupportdetails.set & 3) == 3;
//	 //	 // swapchainadequate = swapchainsupportdetails.format != 0 && swapchainsupportdetails.present_mode;
//	 //	 swapchainadequate = m_vkswapchainkhr_format_ptr[device] != 0 && m_vkswapchainkhr_present_mode_ptr[device];
//	 // }

//	 VkPhysicalDeviceFeatures vkphysicaldevicefeatures;

//	 vkGetPhysicalDeviceFeatures(vkphysicaldevice, &vkphysicaldevicefeatures);

//	 return /* (queuelist.set & 3) == 3 &&  */extensionssupported/*  && swapchainadequate && vkphysicaldevicefeatures.samplerAnisotropy */;
// }

void vk_makePhysicalDevice()
{
	uint32_t devices = 0;

	vkEnumeratePhysicalDevices(m_vkinstance, &devices, VK_NULL_HANDLE);
	info("physical_devices %d", devices)

	if (!devices)
	{
		error("vkEnumeratePhysicalDevices_0")
	}

	m_max_device = devices;
	m_vkphysicaldevice_ptr = malloc(sizeof(VkPhysicalDevice) * devices);
	m_vkqueue_graphics_ptr = malloc(sizeof(VkQueue*) * devices);
	m_graphics_ptr = malloc(sizeof(uint32_t*) * devices);
	m_max_graphics_ptr = malloc(sizeof(uint8_t) * devices);

	vkEnumeratePhysicalDevices(m_vkinstance, &devices, m_vkphysicaldevice_ptr);

	// for (uint32_t i = 0; i < devices; i++)
	// {
	//	 m_graphics_ptr[i] = malloc(sizeof(uint32_t));

	//	 // m_vkqueue_graphics_ptr[i] = malloc(sizeof(VkQueue));

	//	 // VkPhysicalDevice vkphysicaldevice = vkphysicaldevice_ptr[i];
	//	 info("device_i %d", i)
	//	 if (!deviceSuitable(i))
	//	 {
	//		 info("device_not_support %d", i)
	//		 // m_vkphysicaldevice_ptr = &vkphysicaldevice;
	//		 // break;
	//	 }
	// }

	// m_vkphysicaldevice_ptr = vkphysicaldevice_ptr;

	// free(all_vkphysicaldevice);
}
