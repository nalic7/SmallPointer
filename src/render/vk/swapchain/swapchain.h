#ifndef _RD_VK_SWC_H
	#define _RD_VK_SWC_H

	extern VkSwapchainKHR _rd_vk_swc_khr;
	extern VkExtent2D _rd_vk_swc_et2d;
	extern VkRenderPass _rd_vk_swc_rdp;

	extern VkImage *_rd_vk_swc_im_p;
	extern VkImageView *_rd_vk_swc_imv_p;
	extern VkFramebuffer *_rd_vk_swc_fbf_p;

	extern uint8_t _rd_vk_swc_image;
	extern uint8_t _rd_vk_swc_frame;
	extern uint8_t _rd_vk_swc_frame_buffer;

	void _rd_vk_swc_make(VkSharingMode vksharingmode);
	void _rd_vk_swc_free();
#endif
