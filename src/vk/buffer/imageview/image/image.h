#ifndef NALI_VK_IMAGE_H
#define NALI_VK_IMAGE_H

void vk_makeImage(uint32_t device, VkFormat vkformat, VkExtent3D vkextent3d, VkImageCreateFlags vkimagecreateflags, VkImageUsageFlags vkimageusageflags, VkImage* vkimage_p);

#endif
