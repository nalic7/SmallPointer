#ifndef SMPT_RD_VKW_DSTSLO_H
	#define SMPT_RD_VKW_DSTSLO_H

	#define SMPT_RD_VKW_DSTSLO_L 5

	extern VkDescriptorSetLayout smpt_rd_vkw_dsts_lo;

	void smpt_rd_vkw_dsts_lo_make(uint32_t device);
	void smpt_rd_vkw_dsts_lo_free(uint32_t device);
#endif
