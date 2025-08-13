#ifndef NALI_LOADER_CLIENT_POSE_H
#define NALI_LOADER_CLIENT_POSE_H

#define NALI_LCP_BONE_BL 52
#define NALI_LCP_VP_BL sizeof(float) * 16 * 2 * 2

extern uint32_t
	lcp_rgba_bl;

extern uint8_t
	// lcm_max_j,

	*lcp_joint_count_p,
	lcp_joint_count_bl,
	**lcp_a_p;

extern float **lcp_bp_p;

extern VkDeviceSize *lcp_vkdevicesize_p;

void lcp_set();
void lcp_vk();
void lcp_free();

#endif
