#ifndef SMPT_RDhVKQ
	#define SMPT_RDhVKQ

	//! use all queue
	//.c select gpu index
	#define SMPT_RD_VKQuDV 0
	#define SMPT_RD_VKQuCP 0

	extern uint32_t *smpt_rd_vkqPmax_queue;
	extern uint32_t *smpt_rd_vkqPmax_queue_surface;
	extern uint32_t **smpt_rd_vkqPqueue_surface;

	extern VkQueue **smpt_rd_vkqP;

	void smpt_rd_vkqMset();
	void smpt_rd_vkqMadd(uint32_t device);
	void smpt_rd_vkqMget(uint32_t device);
	void smpt_rd_vkqMfree();
#endif
