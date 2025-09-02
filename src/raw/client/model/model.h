#ifndef _RC_MD_H
#define _RC_MD_H

	//c1j1
	//c1j0
	//t1j1u1v1
	//t1j0u1v1
	#define NALI_LCS_A_BL 2

	#define NALI_LCP_VP_BL sizeof(float) * 16 * 2 * 2
	extern VkDeviceSize r_cep_a_p[NALI_LCS_A_BL];
	extern VkDeviceSize *r_cep_ai_p;
	extern uint32_t *r_cep_ai_l_p;

	extern uint32_t
		lcp_rgba_bl;

	extern uint8_t
		// lcm_max_j,

		*lcp_joint_count_p,
		lcp_joint_count_bl,
		**lcp_a_p;

	extern float **lcp_bp_p;

	//! lc_vkbuffer
	extern VkBuffer lcp_vkbuffer;
	//! lc_vkdevicememory
	extern VkDeviceMemory lcp_vkdevicememory;
	//! lc_vkbuffer_p
	extern void *lcp_vkbuffer_mp;
	//! lc_vkdevicesize
	extern VkDeviceSize *lcp_vkdevicesize_p;

	void lcp_set();
	void lcp_vk();
	void lcp_free(uint32_t device);
#endif
