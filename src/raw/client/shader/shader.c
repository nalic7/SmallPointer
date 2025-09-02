struct smptr_ce_sd_st smptr_ce_sd_st_p[SMPTRB_MIM];

uint32_t smptr_ce_sd_sti_l = 0;
struct smptr_ce_sd_sti *smptr_ce_sd_sti_p;

#ifdef SMPT_CM_VK
	SMPTRB_MIT lcm_ds_bl = 0;
	VkBuffer *lcm_vkbuffer_p;
	void **lcm_vkbuffer_mp;
	VkDeviceMemory *lcm_vkdevicememory_p;
#endif

void smptr_ce_sd_set()
{
	smptr_ce_sd_sti_p = malloc(0);

	#ifdef SMPT_CM_VK
		lcm_vkbuffer_p = malloc(0);
		lcm_vkbuffer_mp = malloc(0);
		lcm_vkdevicememory_p = malloc(0);
	#endif
}

void smptr_ce_sd_free(uint32_t device)
{
	#ifdef SMPT_CM_VK
		//! avoid 0
		for (uint8_t l_0 = 0; l_0 < smpt_rd_vk_swc_image; ++l_0)
		{
			for (uint8_t l_1 = 0; l_1 < lcm_ds_bl; ++l_1)
			{
				VkDevice vkdevice = smpt_rd_vkq_dv_p[device];
				vkUnmapMemory(smpt_rd_vkq_dv_p[device], lcm_vkdevicememory_p[l_0 + l_1 * smpt_rd_vk_swc_image]);
				vkDestroyBuffer(vkdevice, lcm_vkbuffer_p[l_0 + l_1 * smpt_rd_vk_swc_image], VK_NULL_HANDLE);
				vkFreeMemory(vkdevice, lcm_vkdevicememory_p[l_0 + l_1 * smpt_rd_vk_swc_image], VK_NULL_HANDLE);
			}
		}
		free(lcm_vkdevicememory_p);
		free(lcm_vkbuffer_p);
		free(lcm_vkbuffer_mp);
	#endif

	free(smptr_ce_sd_sti_p);
}
