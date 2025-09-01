#ifndef _RD_VKQ_DV_H
	#define _RD_VKQ_DV_H

	extern const char *_rd_vkq_dv_ets_p[1];

	extern VkDevice *_rd_vkq_dv_p;

	void _rd_vkq_dv_set();
	void _rd_vkq_dv_make(uint32_t device);
	void _rd_vkq_dv_free();
#endif
