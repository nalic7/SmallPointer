#ifndef NALI_VK_H
#define NALI_VK_H

extern uint32_t m_device;
extern uint32_t m_queue_graphic;
extern uint32_t m_queue_render;

extern float m_limits_max_sampler_anisotropy;

#define NALI_VK_COLOR_FORMAT_BYTE 4
#define NALI_VK_COLOR_FORMAT VK_FORMAT_R8G8B8A8_UNORM
#define NALI_VK_DEPTH_FORMAT VK_FORMAT_D32_SFLOAT//VK_FORMAT_D16_UNORM

#define NALI_VK_SAMPLE_S VK_TRUE
#define NALI_VK_SAMPLE_C VK_SAMPLE_COUNT_8_BIT
#define NALI_VK_SAMPLE_V 1.0F

void vk_init();
int vk_loop(void *arg);

#endif