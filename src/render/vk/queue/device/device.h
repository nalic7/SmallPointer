#ifndef _VKQ_DV_H
#define _VKQ_DV_H
	extern const char *_vkq_dv_ets_p[1];

	extern VkDevice *_vkq_dv_p;

	void _vkq_dv_set();
	void _vkq_dv_make(uint32_t device);
	void _vkq_dv_free();
#endif
