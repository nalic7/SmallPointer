#ifndef NALI_VK_H
#define NALI_VK_H

// typedef struct
// {
extern VkInstance m_vkinstance;

//D
extern uint32_t m_max_device;

extern VkPhysicalDevice* m_vkphysicaldevice_ptr;
extern uint8_t* m_max_graphic_ptr;
extern uint32_t** m_graphic_ptr;
extern VkQueue** m_vkqueue_ptr;

extern VkDevice* m_vkdevice_ptr;
//D

//S
extern VkSurfaceKHR m_vksurfacekhr;

extern VkSwapchainKHR* m_vkswapchainkhr_ptr;

extern VkSurfaceCapabilitiesKHR* m_vksurfacecapabilitieskhr_ptr;

extern uint32_t* m_vksurfaceformatkhr_image_ptr;
extern VkSurfaceFormatKHR** m_vksurfaceformatkhr_ptr;
extern uint32_t* m_vkswapchainkhr_format_ptr;

extern VkPresentModeKHR** m_vkpresentmodekhr_ptr;
extern uint32_t* m_vkswapchainkhr_present_mode_ptr;

extern VkImage** m_vkswapchainkhr_vkimage_ptr;
extern VkExtent2D* m_vkswapchainkhr_vkextent2d_ptr;
extern VkFormat* m_vkswapchainkhr_vkformat_ptr;
extern VkRenderPass* m_vkswapchainkhr_vkrenderpass_ptr;
// extern VkRenderPass** m_vkswapchainkhr_vkrenderpass_ptr;
extern VkImageView** m_vkswapchainkhr_vkimageview_ptr;
extern VkFramebuffer** m_vkswapchainkhr_vkframebuffer_ptr;

extern VkFence** m_vkfence_ptr;
extern VkSemaphore*** m_vksemaphore_ptr;

extern VkCommandPool** m_vkcommandpool_ptr;
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
