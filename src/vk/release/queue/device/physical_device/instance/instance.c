VkInstance vkqdpdi_vkinstance = VK_NULL_HANDLE;

static const char *ppEnabledExtensionNames[] =
{
	VK_KHR_SURFACE_EXTENSION_NAME,
	#ifdef C_NALI_S_ANDROID
		VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
	#else
		VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
	#endif

	// VK_KHR_DEVICE_GROUP_CREATION_EXTENSION_NAME,
	// VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME,

	#ifdef C_NALI_VK_DEBUG
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME
	#endif
};

#ifdef C_NALI_VK_DEBUG
	const char *vkqdpdi_ppEnabledLayerNames[] =
	{
		"VK_LAYER_KHRONOS_validation"
	};
#endif

void vkqdpdi_make()
{
	NALI_D_INFO
	(
		"vkCreateInstance %d",
		vkCreateInstance
		(
			&(VkInstanceCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
				.pApplicationInfo = &(VkApplicationInfo)
				{
					.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
					.pApplicationName = "nali",
					.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
					.pEngineName = "vk",
					.engineVersion = VK_MAKE_VERSION(1, 0, 0),
					.apiVersion = NALI_VK_VERSION,

					.pNext = VK_NULL_HANDLE
				},
				.enabledExtensionCount = sizeof(ppEnabledExtensionNames) / sizeof(ppEnabledExtensionNames[0]),
				.ppEnabledExtensionNames = ppEnabledExtensionNames,

				.flags = 0,
				.pNext = VK_NULL_HANDLE,

				#ifdef C_NALI_VK_DEBUG
					.enabledLayerCount = sizeof(vkqdpdi_ppEnabledLayerNames) / sizeof(vkqdpdi_ppEnabledLayerNames[0]),
					.ppEnabledLayerNames = vkqdpdi_ppEnabledLayerNames
				#else
					.enabledLayerCount = 0,
					.ppEnabledLayerNames = VK_NULL_HANDLE
				#endif
			},
			VK_NULL_HANDLE,
			&vkqdpdi_vkinstance
		)
	)
}

void vkqdpdi_free()
{
	vkDestroyInstance(vkqdpdi_vkinstance, NULL);
	vkqdpdi_vkinstance = VK_NULL_HANDLE;
}