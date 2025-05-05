#ifndef NALI_LOADER_CLIENT_H
#define NALI_LOADER_CLIENT_H

#define NALI_MAX_BONE 40
#define NALI_MAX_JOINT 20
#define NALI_MAX_RGBA 8

#define NALI_LC_V0 sizeof(float) * 16
#define NALI_LC_V1 sizeof(float) * (4 + 3 + 3) * NALI_MAX_JOINT + sizeof(uint32_t) * (1 + 1) * NALI_MAX_JOINT + sizeof(uint32_t) * NALI_MAX_BONE
#define NALI_LC_V2 sizeof(float) * 3 * NALI_MAX_JOINT
#define NALI_LC_V3 sizeof(float) * 4 * NALI_MAX_JOINT
#define NALI_LC_V4 sizeof(float) * 3 * NALI_MAX_JOINT
#define NALI_LC_V5 sizeof(float) * 4 * NALI_MAX_RGBA

#define NALI_LC_V NALI_LC_V0 + NALI_LC_V1 + NALI_LC_V2 + NALI_LC_V3 + NALI_LC_V4 + NALI_LC_V5

extern VkBuffer m_vkbuffer;
extern VkDeviceMemory m_vkdevicememory;
extern void *m_vkbuffer_p;

void lc_init();

void lc_initVK();
void lc_clearVK(uint32_t device);

#endif