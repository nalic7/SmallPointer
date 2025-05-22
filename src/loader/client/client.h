#ifndef NALI_LOADER_CLIENT_H
#define NALI_LOADER_CLIENT_H

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

#define NALI_LC_MVP_BL sizeof(float) * 16 * 2

extern VkBuffer lc_vkbuffer;
extern VkDeviceMemory lc_vkdevicememory;
extern void *lc_vkbuffer_p;
extern VkDeviceSize lc_vkdevicesize;

void lc_set();

void lc_vk();
void lc_freeVk(uint32_t device);

#endif