#ifndef NALI_LOADER_CLIENT_M_H
#define NALI_LOADER_CLIENT_M_H

// extern void (*lcm_fp[NALI_LB_N_MAX])();

//.i 2p
extern VkBuffer *lcm_vkbuffer_p;
extern void **lcm_vkbuffer_mp;
extern VkDeviceMemory *lcm_vkdevicememory_p;

extern LB_M **lcm_lb_m_p;
extern NALI_LB_MIT *lcm_bl_p;

extern NALI_LB_MIT lcm_ds_bl;

void lcm_set();
void lcm_update();
void lcm_read();
void lcm_re();
void lcm_freeVk(int32_t device);
void lcm_free();

#endif
