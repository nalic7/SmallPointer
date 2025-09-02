#ifndef SMPT_RD_VK_SWC_H
	#define SMPT_RD_VK_SWC_H

	extern VkSwapchainKHR smpt_rd_vk_swc_khr;
	extern VkExtent2D smpt_rd_vk_swc_et2d;
	extern VkRenderPass smpt_rd_vk_swc_rdp;

	extern VkImage *smpt_rd_vk_swc_im_p;
	extern VkImageView *smpt_rd_vk_swc_imv_p;
	extern VkFramebuffer *smpt_rd_vk_swc_fbf_p;

	extern uint8_t smpt_rd_vk_swc_image;
	extern uint8_t smpt_rd_vk_swc_frame;
	extern uint8_t smpt_rd_vk_swc_frame_buffer;

	void smpt_rd_vk_swc_make(VkSharingMode vksharingmode);
	void smpt_rd_vk_swc_free();
#endif
