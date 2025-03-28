#ifndef NALI_VK_INSTANCE_H
#define NALI_VK_INSTANCE_H

extern VkInstance m_vkinstance;

extern const char *ppEnabledExtensionNames[
#ifdef NALI_VK_DEBUG
	3
#else
	2
#endif
];
#ifdef NALI_VK_DEBUG
	extern const char *ppEnabledLayerNames[1];
#endif

void vk_makeInstance();
void vk_freeInstance();

#endif
