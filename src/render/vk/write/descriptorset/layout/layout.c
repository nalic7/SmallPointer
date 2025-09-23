VkDescriptorSetLayout smpt_rd_vkw_dsts_loP[2];


void smpt_rd_vkw_dsts_loMfree()
{
	vkDestroyDescriptorSetLayout(smpt_rd_vkq_dvP[SMPT_RD_VKQuDV], smpt_rd_vkw_dsts_loP[0], VK_NULL_HANDLE);
	vkDestroyDescriptorSetLayout(smpt_rd_vkq_dvP[SMPT_RD_VKQuCP], smpt_rd_vkw_dsts_loP[1], VK_NULL_HANDLE);
}
