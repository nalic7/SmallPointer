#ifndef NALI_VK_IMAGEVIEW_H
#define NALI_VK_IMAGEVIEW_H

void vk_makeImageView(uint32_t device, VkImage vkimage, VkFormat vkformat, VkImageAspectFlags vkimageaspectflags, uint32_t mipmap, VkImageView *vkimageview_p);

#endif
