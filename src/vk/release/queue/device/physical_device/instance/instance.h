#ifndef NALI_VK_INSTANCE_H
#define NALI_VK_INSTANCE_H

extern VkInstance vkqdpdi_vkinstance;

// extern const char *vkqdpdi_ppEnabledExtensionNames[
// #ifdef NALI_VK_DEBUG
// 	3
// #else
// 	2
// #endif
// ];
#ifdef NALI_VK_DEBUG
	extern const char *vkqdpdi_ppEnabledLayerNames[1];
#endif

void vkqdpdi_make();
void vkqdpdi_free();

#endif