#ifndef NALI_VK_IMAGEVIEW_H
#define NALI_VK_IMAGEVIEW_H

void vk_makeImageView(uint32_t device, VkImage* image_ptr, VkFormat* vkformat_ptr, VkImageAspectFlags vkimageaspectflags, VkImageViewCreateFlags vkimageviewcreateflags, VkImageView* vkimageview_ptr);

#endif
