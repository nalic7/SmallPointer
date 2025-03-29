uint32_t m_physical_device;
VkPhysicalDevice *m_vkphysicaldevice_p;

const char *deviceextensions[] =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

void vk_makePhysicalDevice()
{
	#ifdef NALI_VK_SGPU
		m_physical_device = 1;
	#else
		vkEnumeratePhysicalDevices(m_vkinstance, &m_physical_device, VK_NULL_HANDLE);
		info("physical_device %d", m_physical_device)

		// if (!physical_device)
		// {
		// 	error("vkEnumeratePhysicalDevices_0")
		// }
	#endif

	m_vkphysicaldevice_p = malloc(sizeof(VkPhysicalDevice) * m_physical_device);

	vkEnumeratePhysicalDevices(m_vkinstance, &m_physical_device, m_vkphysicaldevice_p);
}

void vk_freePhysicalDevice()
{
	free(m_vkphysicaldevice_p);
}