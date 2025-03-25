#ifndef NALI_VK_H
#define NALI_VK_H

extern VkInstance m_vkinstance;

//D
extern uint32_t m_max_device;

extern VkPhysicalDevice *m_vkphysicaldevice_p;
extern uint8_t *m_max_graphic_p;
extern uint32_t **m_graphic_p;
extern VkQueue **m_vkqueue_p;

extern VkDevice *m_vkdevice_p;
//D

//S
extern VkSurfaceKHR m_vksurfacekhr;

extern VkSwapchainKHR *m_vkswapchainkhr_p;

extern VkSurfaceCapabilitiesKHR *m_vksurfacecapabilitieskhr_p;

extern uint32_t *m_vksurfaceformatkhr_image_p;
extern VkSurfaceFormatKHR **m_vksurfaceformatkhr_p;
extern uint32_t *m_vkswapchainkhr_format_p;

extern VkPresentModeKHR **m_vkpresentmodekhr_p;
extern uint32_t *m_vkswapchainkhr_present_mode_p;

extern VkImage **m_vkswapchainkhr_vkimage_p;
extern VkExtent2D *m_vkswapchainkhr_vkextent2d_p;
// extern VkFormat *m_vkswapchainkhr_vkformat_p;
extern VkRenderPass *m_vkswapchainkhr_vkrenderpass_p;
// extern VkRenderPass **m_vkswapchainkhr_vkrenderpass_p;
extern VkImageView **m_vkswapchainkhr_vkimageview_color_p;

extern VkImageView *m_vkswapchainkhr_vkimageview_depth_p;
extern VkImage *m_vkswapchainkhr_vkimage_depth_p;
extern VkDeviceMemory *m_vkswapchainkhr_vkdevicememory_depth_p;

extern VkFramebuffer **m_vkswapchainkhr_vkframebuffer_p;

extern VkFence **m_vkfence_p;
extern VkSemaphore ***m_vksemaphore_p;

extern VkCommandPool **m_vkcommandpool_p;
//S

extern uint32_t m_device;
extern uint32_t m_queue_graphic;
extern uint32_t m_queue_render;

#ifdef NALI_VK_DEBUG
	extern VkDebugUtilsMessengerEXT m_vkdebugutilsmessengerext;
#endif

#define NALI_VK_COLOR_FORMAT_BYTE 4
#define NALI_VK_COLOR_FORMAT VK_FORMAT_R8G8B8A8_UNORM
#define NALI_VK_DEPTH_FORMAT VK_FORMAT_D32_SFLOAT//VK_FORMAT_D16_UNORM

void vk_init();
int vk_loop(void *arg);

#endif