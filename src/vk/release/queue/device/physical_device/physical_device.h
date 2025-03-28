#ifndef NALI_VK_PHYSICAL_DEVICE_H
#define NALI_VK_PHYSICAL_DEVICE_H

extern uint32_t m_physical_device;
extern VkPhysicalDevice *m_vkphysicaldevice_p;

extern const char *deviceextensions[1];

void vk_makePhysicalDevice();
void vk_freePhysicalDevice();

#endif