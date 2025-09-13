VkPhysicalDevice *smpt_rd_vkq_dv_pscdvP;
uint32_t smpt_rd_vkq_dv_pscdvL;

void smpt_rd_vkq_dv_pscdvMmake()
{
	SMPT_DBmR2L("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(smpt_rd_vkq_dv_pscdv_itV, &smpt_rd_vkq_dv_pscdvL, VK_NULL_HANDLE))
	SMPT_DBmN2L("physical_device %d", smpt_rd_vkq_dv_pscdvL)

	smpt_rd_vkq_dv_pscdvP = malloc(sizeof(VkPhysicalDevice) * smpt_rd_vkq_dv_pscdvL);

	SMPT_DBmR2L("vkEnumeratePhysicalDevices %d", vkEnumeratePhysicalDevices(smpt_rd_vkq_dv_pscdv_itV, &smpt_rd_vkq_dv_pscdvL, smpt_rd_vkq_dv_pscdvP))
}

void smpt_rd_vkq_dv_pscdvMfree()
{
	free(smpt_rd_vkq_dv_pscdvP);
}
