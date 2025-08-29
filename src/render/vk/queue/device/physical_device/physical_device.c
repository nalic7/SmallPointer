uint32_t _vkq_dv_pscdv_bl;
VkPhysicalDevice *_vkq_dv_pscdv_p;

void _vkq_dv_pscdv_make()
{
	_DB_R2L("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(_vkq_dv_pscdv_it, &_vkq_dv_pscdv_bl, VK_NULL_HANDLE))
	_DB_N2L("physical_device %d", _vkq_dv_pscdv_bl)

	_vkq_dv_pscdv_p = malloc(sizeof(VkPhysicalDevice) * _vkq_dv_pscdv_bl);

	_DB_R2L("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(_vkq_dv_pscdv_it, &_vkq_dv_pscdv_bl, _vkq_dv_pscdv_p))
}

void _vkq_dv_pscdv_free()
{
	free(_vkq_dv_pscdv_p);
}
