VkDescriptorPool smpt_rd_vkw_dstspP[2];

void smpt_rd_vkw_dstspMfree()
{
	vkDestroyDescriptorPool(smpt_rd_vkq_dvP[SMPT_RD_VKQuDV], smpt_rd_vkw_dstspP[0], VK_NULL_HANDLE);
	vkDestroyDescriptorPool(smpt_rd_vkq_dvP[SMPT_RD_VKQuCP], smpt_rd_vkw_dstspP[1], VK_NULL_HANDLE);
}
