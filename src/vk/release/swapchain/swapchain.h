#ifndef NALI_VK_SWAPCHAIN_H
#define NALI_VK_SWAPCHAIN_H

extern VkSwapchainKHR m_vkswapchainkhr;
extern VkExtent2D m_vkextent2d;
extern VkRenderPass m_vkrenderpass;

extern VkImage *m_vkswapchainkhr_vkimage_p;
extern VkImageView *m_vkswapchainkhr_vkimageview_p;
extern VkFramebuffer *m_vkswapchainkhr_vkframebuffer_p;

void vk_makeSwapchain(VkSharingMode vksharingmode);
void vk_freeSwapchain();

#endif