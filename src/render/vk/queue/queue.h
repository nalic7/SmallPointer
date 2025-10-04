#ifndef SMPT_RD_VKhQ
	#define SMPT_RD_VKhQ

	#define SMPT_RD_VKQuMAIN 0
	#define SMPT_RD_VKQuOFF 1
	struct SMPT_RD_VKQsFAMILY
	{
		uint8_t
			*Psf,
			Lsf;
			L;
	};
	struct SMPT_RD_VKQsINFO
	{
		VkCommandBuffer *Pvkcommandbuffer;
		VkCommandPool *Pvkcommandpool;

		float Fmax_sampler_anisotropy;
		uint8_t
			Unon_coherent_atom_size,
			Usample_count,
			//.i gp -> shader / buffer / image
			//.i cp -> shader
			//.i tf -> buffer / image
			Ugp,
			Usf,
			Ucp;
		struct SMPT_RD_VKQsFAMILY Sfamily;
		VkQueue *Pvkqueue;
		VkDevice Vvkdevice;
		VkPhysicalDevice Vvkphysicaldevice;
	};
	extern struct SMPT_RD_VKQsINFO *smpt_rd_vkqPinfo;
	extern uint32_t smpt_rd_vkqLinfo;

	void smpt_rd_vkqMset();
	void smpt_rd_vkqMfree();
#endif
