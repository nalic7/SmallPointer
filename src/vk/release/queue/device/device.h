#ifndef NALI_VK_DEVICEQUEUE_H
#define NALI_VK_DEVICEQUEUE_H

extern VkDevice *m_vkdevice_p;

void vk_initDevice();
void vk_makeDevice(uint32_t device);
void vk_freeDevice();

#endif