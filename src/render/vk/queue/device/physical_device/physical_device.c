uint32_t smpt_rd_vkq_dv_pscdv_bl;
VkPhysicalDevice *smpt_rd_vkq_dv_pscdv_p;

void smpt_rd_vkq_dv_pscdv_make()
{
	SMPT_DBmR2L("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(smpt_rd_vkq_dv_pscdv_it, &smpt_rd_vkq_dv_pscdv_bl, VK_NULL_HANDLE))
	SMPT_DBmN2L("physical_device %d", smpt_rd_vkq_dv_pscdv_bl)

	smpt_rd_vkq_dv_pscdv_p = malloc(sizeof(VkPhysicalDevice) * smpt_rd_vkq_dv_pscdv_bl);

	SMPT_DBmR2L("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(smpt_rd_vkq_dv_pscdv_it, &smpt_rd_vkq_dv_pscdv_bl, smpt_rd_vkq_dv_pscdv_p))
}

void smpt_rd_vkq_dv_pscdv_free()
{
	free(smpt_rd_vkq_dv_pscdv_p);
}
