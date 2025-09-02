#ifndef SMPT_RD_VKQ_H
	#define SMPT_RD_VKQ_H

	extern uint32_t *smpt_rd_vkq_max_queue_p;
	extern uint32_t *smpt_rd_vkq_max_queue_surface_p;
	extern uint32_t **smpt_rd_vkq_queue_surface_p;

	extern VkQueue **smpt_rd_vkq_p;

	void smpt_rd_vkq_set();
	void smpt_rd_vkq_add(uint32_t device);
	void smpt_rd_vkq_get(uint32_t device);
	void smpt_rd_vkq_free();
#endif
