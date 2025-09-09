#ifndef SMPTR_CEhMD
	#define SMPTR_CEhMD

	//c1j1
	//c1j0
	//t1j1u1v1
	//t1j0u1v1
	#define NALI_LCS_A_BL 2

	extern VkDeviceSize r_cep_a_p[NALI_LCS_A_BL];
	extern VkDeviceSize *r_cep_ai_p;
	extern uint32_t *r_cep_ai_l_p;

	extern uint32_t
		lcp_rgba_bl;

	extern uint8_t
		*lcp_joint_count_p,
		lcp_joint_count_bl,
		**lcp_a_p;

	extern float **lcp_bp_p;

	#ifdef SMPT_CM_VK
		extern VkBuffer *smptr_ce_mdPvkbuffer;
		extern VkDeviceMemory *smptr_ce_mdPvkdevicememory;
		extern void **smptr_ce_mdPbuffer_map;
		extern VkDeviceSize *smptr_ce_mdPvkdevicesize;
	#endif

	void lcp_set();
	void lcp_vk();
	void lcp_free(uint32_t device);
#endif
