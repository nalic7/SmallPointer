#ifndef NALI_VK_FRAMEBUFFER_H
#define NALI_VK_FRAMEBUFFER_H

void vk_makeFrameBuffer(uint32_t device, VkFramebufferCreateFlags vkframebuffercreateflags, VkImageView *vkimageview_p, uint32_t vkimageview_size, VkRenderPass *vkrenderpass_p, VkFramebuffer *vkframebuffer_p);

#endif