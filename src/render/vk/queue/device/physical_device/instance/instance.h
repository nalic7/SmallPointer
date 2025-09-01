#ifndef _RD_VKQ_DV_PSCDV_IT_H
	#define _RD_VKQ_DV_PSCDV_IT_H

	extern VkInstance _rd_vkq_dv_pscdv_it;

	#ifdef _CM_VK_DEBUG
		extern const char *_rd_vkq_dv_pscdv_it_layer_p[1];
	#endif

	void _rd_vkq_dv_pscdv_it_make();
	void _rd_vkq_dv_pscdv_it_free();
#endif
