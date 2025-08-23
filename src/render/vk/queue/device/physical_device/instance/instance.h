#ifndef _VK_INSTANCE_H
#define _VK_INSTANCE_H

extern VkInstance vkqdpdi_vkinstance;

// extern const char *vkqdpdi_ppEnabledExtensionNames[
// #ifdef C__VK_DEBUG
// 	3
// #else
// 	2
// #endif
// ];
#ifdef C__VK_DEBUG
	extern const char *vkqdpdi_ppEnabledLayerNames[1];
#endif

void vkqdpdi_make();
void vkqdpdi_free();

#endif