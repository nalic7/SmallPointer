#ifndef NALI_LOADER_CLIENT_MODEL_H
#define NALI_LOADER_CLIENT_MODEL_H

#define NALI_LCM_BONE_BL 22
#define NALI_LCM_VP_BL sizeof(float) * 16 * 2 * 2
#define NALI_LCM_P_BL 1024*1024*4

extern uint32_t
	lcm_rgba_bl;

extern uint8_t
	// lcm_max_j,

	*lcm_joint_count_p,
	lcm_joint_count_bl;

extern float
	**lcm_bp_p,
	**lcm_a_p;

extern VkDeviceSize *lcm_vkdevicesize_p;

void lcm_set();
void lcm_vk();

#endif