#ifndef NALI_VK_SWAPCHAIN_H
#define NALI_VK_SWAPCHAIN_H

extern VkSwapchainKHR vksc_vkswapchainkhr;
extern VkExtent2D vksc_vkextent2d;
extern VkRenderPass vksc_vkrenderpass;

extern VkImage *vksc_vkswapchainkhr_vkimage_p;
extern VkImageView *vksc_vkswapchainkhr_vkimageview_p;
extern VkFramebuffer *vksc_vkswapchainkhr_vkframebuffer_p;

extern uint8_t vksc_image;
extern uint8_t vksc_frame;
extern uint8_t vksc_buffer_frame;

//extern VkSurfaceTransformFlagBitsKHR m_vksurfacetransformflagbitskhr;

void vksc_make(VkSharingMode vksharingmode);
void vksc_free();

#endif
