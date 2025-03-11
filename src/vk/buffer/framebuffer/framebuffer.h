#ifndef NALI_VK_FRAMEBUFFER_H
#define NALI_VK_FRAMEBUFFER_H

void vk_makeFrameBuffer(uint32_t device, VkFramebufferCreateFlags vkframebuffercreateflags, VkImageView* vkimageview_ptr, VkRenderPass* vkrenderpass_ptr, VkFramebuffer* vkframebuffer_ptr);

#endif