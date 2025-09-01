uint32_t _rd_vkq_dv_pscdv_bl;
VkPhysicalDevice *_rd_vkq_dv_pscdv_p;

void _rd_vkq_dv_pscdv_make()
{
	_DB_R2L("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(_rd_vkq_dv_pscdv_it, &_rd_vkq_dv_pscdv_bl, VK_NULL_HANDLE))
	_DB_N2L("physical_device %d", _rd_vkq_dv_pscdv_bl)

	_rd_vkq_dv_pscdv_p = malloc(sizeof(VkPhysicalDevice) * _rd_vkq_dv_pscdv_bl);

	_DB_R2L("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(_rd_vkq_dv_pscdv_it, &_rd_vkq_dv_pscdv_bl, _rd_vkq_dv_pscdv_p))
}

void _rd_vkq_dv_pscdv_free()
{
	free(_rd_vkq_dv_pscdv_p);
}
