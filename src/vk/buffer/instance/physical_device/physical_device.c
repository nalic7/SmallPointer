const char* deviceextensions[] =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

void vk_makePhysicalDevice()
{
	uint32_t physical_device;

	#ifdef SGPU
		physical_device = 1;
	#else
		vkEnumeratePhysicalDevices(m_vkinstance, &physical_device, VK_NULL_HANDLE);
		info("physical_device %d", physical_device)

		// if (!physical_device)
		// {
		// 	error("vkEnumeratePhysicalDevices_0")
		// }
	#endif
	m_max_device = physical_device;

	m_vkphysicaldevice_ptr = malloc(sizeof(VkPhysicalDevice) * physical_device);
	m_vkqueue_ptr = malloc(sizeof(VkQueue*) * physical_device);
	m_graphic_ptr = malloc(sizeof(uint32_t*) * physical_device);
	m_max_graphic_ptr = malloc(sizeof(uint8_t) * physical_device);

	vkEnumeratePhysicalDevices(m_vkinstance, &physical_device, m_vkphysicaldevice_ptr);
}
