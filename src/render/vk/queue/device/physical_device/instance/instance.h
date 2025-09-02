#ifndef SMPT_RD_VKQ_DV_PSCDV_IT_H
	#define SMPT_RD_VKQ_DV_PSCDV_IT_H

	extern VkInstance smpt_rd_vkq_dv_pscdv_it;

	#ifdef SMPT_CM_VK_DEBUG
		extern const char *smpt_rd_vkq_dv_pscdv_it_layer_p[1];
	#endif

	void smpt_rd_vkq_dv_pscdv_it_make();
	void smpt_rd_vkq_dv_pscdv_it_free();
#endif
