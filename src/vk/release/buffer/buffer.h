#ifndef NALI_VK_BUFFER_H
#define NALI_VK_BUFFER_H

uint32_t vk_findMemoryType(uint32_t device, uint32_t typefilter, VkMemoryPropertyFlags vkmemorypropertyflags);
void vk_makeBuffer(uint32_t device, VkDeviceSize vkdevicesize, VkBufferUsageFlags vkbufferusageflags, VkMemoryPropertyFlags vkmemorypropertyflags, VkBuffer *vkbuffer_p, VkDeviceMemory *vkdevicememory_p);
void vk_mapBuffer(uint32_t device, VkDeviceSize vkdevicesize, void *buffer_data_p, VkDeviceMemory *vkdevicememory_p);

#endif