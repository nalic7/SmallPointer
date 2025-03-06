const char* ppEnabledExtensionNames[] =
{
	VK_KHR_SURFACE_EXTENSION_NAME,
	VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,

	#ifdef NALI_VK_DEBUG
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME
	#endif
};

#ifdef NALI_VK_DEBUG
	const char* ppEnabledLayerNames[] =
	{
		"VK_LAYER_KHRONOS_validation"
	};
#endif

void vk_makeInstance()
{
	VkApplicationInfo vkapplicationinfo =
	{
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName = "",
		.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
		.pEngineName = "",
		.engineVersion = VK_MAKE_VERSION(1, 0, 0),
		.apiVersion = VK_API_VERSION_1_0,
		.pNext = VK_NULL_HANDLE
	};

	VkInstanceCreateInfo vkinstancecreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pApplicationInfo = &vkapplicationinfo,
		.enabledExtensionCount = sizeof(ppEnabledExtensionNames) / sizeof(ppEnabledExtensionNames[0]),
		.ppEnabledExtensionNames = ppEnabledExtensionNames,
		.flags = 0,
		.pNext = VK_NULL_HANDLE,

		#ifdef NALI_VK_DEBUG
			.enabledLayerCount = sizeof(ppEnabledLayerNames) / sizeof(ppEnabledLayerNames[0]),
			.ppEnabledLayerNames = ppEnabledLayerNames
		#else
			.enabledLayerCount = 0,
			.ppEnabledLayerNames = VK_NULL_HANDLE
		#endif
	};

	if (vkCreateInstance(&vkinstancecreateinfo, VK_NULL_HANDLE, &m_vkinstance) != VK_SUCCESS)
	{
		error("vkCreateInstance")
	}
}
