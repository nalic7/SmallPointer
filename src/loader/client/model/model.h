#ifndef NALI_LOADER_CLIENT_MODEL_H
#define NALI_LOADER_CLIENT_MODEL_H

extern uint32_t
	*m_ji_p,
	*m_ai_index_count_p,
	
	m_max_joint,
	m_rgba_bl;

extern VkDeviceSize *m_ai_vkdevicesize_p;

extern uint8_t m_joint_count_bl;

void lcm_init();
void lcm_vk();

#endif