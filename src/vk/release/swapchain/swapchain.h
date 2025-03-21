#ifndef NALI_VK_SWAPCHAIN_H
#define NALI_VK_SWAPCHAIN_H

void vk_makeSwapchain(uint32_t device, VkSwapchainCreateFlagsKHR vkswapchaincreateflagskhr);
void vk_reSwapchain(uint32_t device, VkSwapchainCreateFlagsKHR vkswapchaincreateflagskhr, VkSurfaceFormatKHR *vksurfaceformatkhr_p, VkPresentModeKHR *vkpresentmodekhr_p, uint8_t max_graphics);
void vk_cleanSwapchain(uint32_t device);

#endif