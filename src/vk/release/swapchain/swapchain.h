#ifndef NALI_VK_SWAPCHAIN_H
#define NALI_VK_SWAPCHAIN_H

extern VkSwapchainKHR *m_vkswapchainkhr_p;

extern uint32_t *m_vkswapchainkhr_format_p;

extern VkPresentModeKHR **m_vkpresentmodekhr_p;
extern uint32_t *m_vkswapchainkhr_present_mode_p;

extern VkImage **m_vkswapchainkhr_vkimage_p;
extern VkExtent2D *m_vkswapchainkhr_vkextent2d_p;
// extern VkFormat *m_vkswapchainkhr_vkformat_p;
extern VkRenderPass *m_vkswapchainkhr_vkrenderpass_p;
// extern VkRenderPass **m_vkswapchainkhr_vkrenderpass_p;
extern VkImageView **m_vkswapchainkhr_vkimageview_p;

extern VkFramebuffer **m_vkswapchainkhr_vkframebuffer_p;

extern VkSurfaceCapabilitiesKHR *m_vksurfacecapabilitieskhr_p;
// extern uint32_t *m_vksurfaceformatkhr_image_p;
extern VkSurfaceFormatKHR **m_vksurfaceformatkhr_p;

void vk_initSwapchain();
void vk_makeSwapchain(uint32_t device, VkSharingMode vksharingmode);
void vk_reSwapchain(uint32_t device);
void vk_freeSwapchain();

#endif