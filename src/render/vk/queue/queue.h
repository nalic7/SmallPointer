#ifndef SMPT_RDhVKQ
	#define SMPT_RDhVKQ

	struct SMPT_RD_VKQsINFO
	{
		float Fmax_sampler_anisotropy;
		uint8_t
			Unon_coherent_atom_size,
			Usample_count,
			//.i gp+sf -> shader / draw / image
			//.i cp -> data
			//.i tf -> image
			Ugp,
			Usf,
			Ucp,
			Utf;
		VkQueue *Pvkqueue;
		//.i 0 draw
		//.i 1 offload
		VkDevice Vvkdevice;
		VkPhysicalDevice Vvkphysicaldevice;
	};
	extern struct SMPT_RD_VKQsINFO *smpt_rd_vkqPinfo;
	extern uint32_t smpt_rd_vkqLinfo;

	void smpt_rd_vkqMset();
	void smpt_rd_vkqMfree();
#endif
