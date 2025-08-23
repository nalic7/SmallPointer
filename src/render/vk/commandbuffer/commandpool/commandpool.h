#ifndef _VK_COMMANDPOOL_H
#define _VK_COMMANDPOOL_H

extern VkCommandPool **vkcbcp_vkcommandpool_p;

void vkcbcp_set();
void vkcbcp_make(uint32_t device);
void vkcbcp_free();

#endif