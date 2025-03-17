#ifndef NALI_VK_H
#define NALI_VK_H

// typedef struct
// {
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
extern VkFormat *m_vkswapchainkhr_vkformat_p;
extern VkRenderPass *m_vkswapchainkhr_vkrenderpass_p;
// extern VkRenderPass **m_vkswapchainkhr_vkrenderpass_p;
extern VkImageView **m_vkswapchainkhr_vkimageview_p;
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
// } vk;

// extern vk m_vk;

void vk_init();

#endif
