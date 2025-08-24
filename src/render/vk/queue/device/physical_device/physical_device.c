uint32_t _vkq_dv_pscdv_bl;
VkPhysicalDevice *_vkq_dv_pscdv_p;

void _vkq_dv_pscdv_make()
{
	#ifdef _VK_SGPU
		_vkq_dv_pscdv_bl = 1;
	#else
		NALI_D_INFO("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(_vkq_dv_pscdv_it, &_vkq_dv_pscdv_bl, VK_NULL_HANDLE))
		NALI_D_LOG("physical_device %d", _vkq_dv_pscdv_bl)

		// if (!physical_device)
		// {
		// 	error("vkEnumeratePhysicalDevices_0")
		// }
	#endif

	_vkq_dv_pscdv_p = malloc(sizeof(VkPhysicalDevice) * _vkq_dv_pscdv_bl);

	NALI_D_INFO("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(_vkq_dv_pscdv_it, &_vkq_dv_pscdv_bl, _vkq_dv_pscdv_p))
}

void _vkq_dv_pscdv_free()
{
	free(_vkq_dv_pscdv_p);
}
