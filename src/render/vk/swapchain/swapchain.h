#ifndef _VK_SWC_H
	#define _VK_SWC_H

	extern VkSwapchainKHR _vk_swc_khr;
	extern VkExtent2D _vk_swc_et2d;
	extern VkRenderPass _vk_swc_rdp;

	extern VkImage *_vk_swc_im_p;
	extern VkImageView *_vk_swc_imv_p;
	extern VkFramebuffer *_vk_swc_fbf_p;

	extern uint8_t _vk_swc_image;
	extern uint8_t _vk_swc_frame;
	extern uint8_t _vk_swc_frame_buffer;

	void _vk_swc_make(VkSharingMode vksharingmode);
	void _vk_swc_free();
#endif
