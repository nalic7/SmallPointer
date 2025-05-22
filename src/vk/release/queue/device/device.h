#ifndef NALI_VK_DEVICEQUEUE_H
#define NALI_VK_DEVICEQUEUE_H

extern const char *vkqd_deviceextensions[1];

extern VkDevice *vkqd_vkdevice_p;

void vkqd_set();
void vkqd_make(uint32_t device);
void vkqd_free();

#endif