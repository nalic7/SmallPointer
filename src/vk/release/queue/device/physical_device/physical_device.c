uint32_t vkqdpd_physical_device;
VkPhysicalDevice *vkqdpd_vkphysicaldevice_p;

void vkqdpd_make()
{
	#ifdef NALI_VK_SGPU
		vkqdpd_physical_device = 1;
	#else
		nali_info("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(vkqdpdi_vkinstance, &m_physical_device, VK_NULL_HANDLE))
		info("physical_device %d", m_physical_device)

		// if (!physical_device)
		// {
		// 	error("vkEnumeratePhysicalDevices_0")
		// }
	#endif

	vkqdpd_vkphysicaldevice_p = malloc(sizeof(VkPhysicalDevice) * vkqdpd_physical_device);

	nali_info("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(vkqdpdi_vkinstance, &vkqdpd_physical_device, vkqdpd_vkphysicaldevice_p))
}

void vkqdpd_free()
{
	free(vkqdpd_vkphysicaldevice_p);
}