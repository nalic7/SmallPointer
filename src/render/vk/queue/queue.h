#ifndef _RD_VKQ_H
	#define _RD_VKQ_H

	extern uint32_t *_rd_vkq_max_queue_p;
	extern uint32_t *_rd_vkq_max_queue_surface_p;
	extern uint32_t **_rd_vkq_queue_surface_p;

	extern VkQueue **_rd_vkq_p;

	void _rd_vkq_set();
	void _rd_vkq_add(uint32_t device);
	void _rd_vkq_get(uint32_t device);
	void _rd_vkq_free();
#endif
