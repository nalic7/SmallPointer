#ifndef _VKQ_DV_PSCDV_IT_H
	#define _VKQ_DV_PSCDV_IT_H

	extern VkInstance _vkq_dv_pscdv_it;

	#ifdef _CM_VK_DEBUG
		extern const char *_vkq_dv_pscdv_it_layer_p[1];
	#endif

	void _vkq_dv_pscdv_it_make();
	void _vkq_dv_pscdv_it_free();
#endif
