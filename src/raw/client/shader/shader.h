#ifndef SMPT_R_CE_SD_H
	#define SMPT_R_CE_SD_H

	struct smptr_ce_sd_st
	{
		VkDescriptorSet *vkdescriptorset_p;
	};
	extern struct smptr_ce_sd_st smptr_ce_sd_st_p[SMPTRB_MIM];

	struct smptr_ce_sd_sti
	{
		SMPTRB_MIT mi;
		SMPTRB_MAT ma;
		uint8_t mab;
		float d;
	};
	extern uint32_t smptr_ce_sd_sti_l;
	extern struct smptr_ce_sd_sti *smptr_ce_sd_sti_p;

	#ifdef SMPT_CM_VK
		extern SMPTRB_MIT lcm_ds_bl;
		extern VkBuffer *lcm_vkbuffer_p;
		extern void **lcm_vkbuffer_mp;
		extern VkDeviceMemory *lcm_vkdevicememory_p;
	#endif

	void smptr_ce_sd_set();
	void smptr_ce_sd_free(uint32_t device);
#endif
