#ifndef NALI_LOADER_CLIENT_H
#define NALI_LOADER_CLIENT_H

extern NALI_LCS_DSIT *lc_dsi_p;
extern uint8_t *lc_a_p;

//VkBuffer
//static / dynamic
//name data start end
//rgba s_d-s_s-s_e
//mvp d_d-s_s-s_e
//a-s d_d-s_s-d_e
//a-r d_d-s_s-d_e
//a-t d_d-s_s-d_e
//b s_d-d_s-d_e
//iv s_d-s_s-s_e
//av s_d-s_s-s_e
//? d_d-d_s-d_e

// #define NALI_LC_MVP_BL sizeof(float) * 16 * 2

extern VkBuffer lc_vkbuffer;
extern VkDeviceMemory lc_vkdevicememory;
extern void *lc_vkbuffer_p;
extern VkDeviceSize lc_vkdevicesize;

extern mtx_t *lc_mtx_t_p;

extern NALI_LB_PT lc_net_bl;
extern uint8_t lc_net_p[NALI_LB_NET_BL];

void lc_set();
void lc_re();

void lc_vk();
void lc_freeloop();
void lc_freeVk(uint32_t device);
void lc_free();

#endif