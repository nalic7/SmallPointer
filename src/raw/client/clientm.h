#ifndef _RCM_H
#define RCM_H

// extern void (*lcm_fp[_RB_N_MAX])();

//.i 2p
extern VkBuffer *lcm_vkbuffer_p;
extern void **lcm_vkbuffer_mp;
extern VkDeviceMemory *lcm_vkdevicememory_p;

extern LB_M **lcm_lb_m_p;
extern _RB_MIT *lcm_bl_p;

extern _RB_MIT lcm_ds_bl;

void lcm_set();
void lcm_update();
void lcm_read();
void lcm_re();
void lcm_freeVk(int32_t device);
void lcm_free();

#endif
