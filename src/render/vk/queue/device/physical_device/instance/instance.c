VkInstance smpt_rd_vkq_dv_pscdv_it;

static const char *extension_p[] =
{
	VK_KHR_SURFACE_EXTENSION_NAME,
	#ifdef SMPT_CM_ST_ANDROID
		VK_KHR_ANDROID_SURFACE_EXTENSION_NAME,
	#endif
	#ifdef SMPT_CM_DRM
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_DISPLAY_EXTENSION_NAME,
	#endif
	#ifdef SMPT_CM_WL
		VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME,
	#endif

	#ifdef SMPT_CM_DEBUG
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME
	#endif
};

#ifdef SMPT_CM_VK_DEBUG
	const char *smpt_rd_vkq_dv_pscdv_it_layer_p[] =
	{
		"VK_LAYER_KHRONOS_validation"
	};
#endif

void smpt_rd_vkq_dv_pscdv_it_make()
{
	SMPT_DB_R2L
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
					.pApplicationName = VK_NULL_HANDLE,
					.applicationVersion = VK_MAKE_VERSION(1, 0, 0),
					.pEngineName = VK_NULL_HANDLE,
					.engineVersion = VK_MAKE_VERSION(1, 0, 0),
					.apiVersion = SMPT_RD_VK_VERSION,

					.pNext = VK_NULL_HANDLE
				},
				.enabledExtensionCount = sizeof(extension_p) / sizeof(extension_p[0]),
				.ppEnabledExtensionNames = extension_p,

				.flags = 0,
				.pNext = VK_NULL_HANDLE,

				#ifdef SMPT_CM_VK_DEBUG
					.enabledLayerCount = sizeof(smpt_rd_vkq_dv_pscdv_it_layer_p) / sizeof(smpt_rd_vkq_dv_pscdv_it_layer_p[0]),
					.ppEnabledLayerNames = smpt_rd_vkq_dv_pscdv_it_layer_p
				#else
					.enabledLayerCount = 0,
					.ppEnabledLayerNames = VK_NULL_HANDLE
				#endif
			},
			VK_NULL_HANDLE,
			&smpt_rd_vkq_dv_pscdv_it
		)
	)
}

void smpt_rd_vkq_dv_pscdv_it_free()
{
	vkDestroyInstance(smpt_rd_vkq_dv_pscdv_it, NULL);
}
