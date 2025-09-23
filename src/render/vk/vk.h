#ifndef SMPT_RDhVK
	#define SMPT_RDhVK

	//! clean
	extern uint32_t smpt_rd_vkUqueue_g;
	extern uint32_t smpt_rd_vkUqueue_ct;

	extern float smpt_rd_vkFmax_sampler_anisotropy;
	extern uint8_t
		smpt_rd_vkUnon_coherent_atom_size,
		smpt_rd_vkUsample_count;

	void smpt_rd_vkMset();
	void smpt_rd_vkMfree();
#endif
