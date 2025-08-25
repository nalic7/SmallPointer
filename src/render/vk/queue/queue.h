#ifndef _VKQ_H
	#define _VKQ_H

	extern uint32_t *_vkq_max_queue_p;
	extern uint32_t *_vkq_max_queue_surface_p;
	extern uint32_t **_vkq_queue_surface_p;

	extern VkQueue **_vkq_p;

	void _vkq_set();
	void _vkq_add(uint32_t device);
	void _vkq_get(uint32_t device);
	void _vkq_free();
#endif
