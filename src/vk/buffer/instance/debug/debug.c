VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT vkdebugutilsmessageseverityflagbitsext, VkDebugUtilsMessageTypeFlagsEXT vkdebugutilsmessagetypeflagsext, const VkDebugUtilsMessengerCallbackDataEXT* vkdebugutilsmessengercallbackdataext, void* data)
{
	info(">vk_debug: %s", vkdebugutilsmessengercallbackdataext->pMessage)
	return 0;
}

VkResult createDebugUtilsMessengerEXT(VkInstance vkinstance, const VkDebugUtilsMessengerCreateInfoEXT* vkdebugutilsmessengercreateinfoext, const VkAllocationCallbacks* vkallocationcallbacks, VkDebugUtilsMessengerEXT* vkdebugutilsmessengerext)
{
	PFN_vkCreateDebugUtilsMessengerEXT pfn_vkcreatedebugutilsmessengerext = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(vkinstance, "vkCreateDebugUtilsMessengerEXT");

	if (pfn_vkcreatedebugutilsmessengerext)
	{
		return pfn_vkcreatedebugutilsmessengerext(vkinstance, vkdebugutilsmessengercreateinfoext, vkallocationcallbacks, vkdebugutilsmessengerext);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void vk_makeDebug(VkDebugUtilsMessengerCreateFlagsEXT vkdebugutilsmessengercreateflagsext)
{
	VkDebugUtilsMessengerCreateInfoEXT vkdebugutilsmessengercreateinfoext =
	{
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
		.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
		.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
		.pfnUserCallback = debugCallback,

		.flags = vkdebugutilsmessengercreateflagsext,
		.pNext = VK_NULL_HANDLE,
		.pUserData = VK_NULL_HANDLE
	};

	// if (vkCreateDebugUtilsMessengerEXT(vk->vkinstance, &vkdebugutilsmessengercreateinfoext, VK_NULL_HANDLE, &vk->vkdebugutilsmessengerext) != VK_SUCCESS)
	if (createDebugUtilsMessengerEXT(m_vkinstance, &vkdebugutilsmessengercreateinfoext, VK_NULL_HANDLE, &m_vkdebugutilsmessengerext) != VK_SUCCESS)
	{
		error("vkCreateDebugUtilsMessengerEXT")
	}
}
