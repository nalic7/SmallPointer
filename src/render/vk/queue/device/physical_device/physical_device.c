uint32_t vkqdpd_physical_device;
VkPhysicalDevice *vkqdpd_vkphysicaldevice_p;

void vkqdpd_make()
{
	#ifdef _VK_SGPU
		vkqdpd_physical_device = 1;
	#else
		NALI_D_INFO("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(vkqdpdi_vkinstance, &vkqdpd_physical_device, VK_NULL_HANDLE))
		NALI_D_LOG("physical_device %d", vkqdpd_physical_device)

		// if (!physical_device)
		// {
		// 	error("vkEnumeratePhysicalDevices_0")
		// }
	#endif

	vkqdpd_vkphysicaldevice_p = malloc(sizeof(VkPhysicalDevice) * vkqdpd_physical_device);

	NALI_D_INFO("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(vkqdpdi_vkinstance, &vkqdpd_physical_device, vkqdpd_vkphysicaldevice_p))
}

void vkqdpd_free()
{
	free(vkqdpd_vkphysicaldevice_p);
}
