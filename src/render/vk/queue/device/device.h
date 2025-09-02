#ifndef SMPT_RD_VKQ_DV_H
	#define SMPT_RD_VKQ_DV_H

	extern const char *smpt_rd_vkq_dv_ets_p[1];

	extern VkDevice *smpt_rd_vkq_dv_p;

	void smpt_rd_vkq_dv_set();
	void smpt_rd_vkq_dv_make(uint32_t device);
	void smpt_rd_vkq_dv_free();
#endif
