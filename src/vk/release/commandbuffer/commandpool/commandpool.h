#ifndef NALI_VK_COMMANDPOOL_H
#define NALI_VK_COMMANDPOOL_H

extern VkCommandPool **m_vkcommandpool_p;

void vk_initCommandPool();
void vk_makeCommandPool(uint32_t device);
void vk_freeCommandPool();

#endif