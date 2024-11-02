#ifndef NALI_VK_IMAGEVIEW_H
#define NALI_VK_IMAGEVIEW_H

void vk_makeImageView(uint32_t device, VkImage image, VkFormat vkformat, VkImageAspectFlags vkimageaspectflags, VkImageView* vkimageview_ptr);

#endif
