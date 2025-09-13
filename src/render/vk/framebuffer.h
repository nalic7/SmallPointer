#ifndef SMPT_RD_VKhFBF
	#define SMPT_RD_VKhFBF

	#define SMPT_RD_VK_FBFmMAKE(device, vkimageview_p, vkimageview_size, vkrenderpass, vkframebuffer_p) \
		SMPT_DBmR2L \
		( \
			"vkCreateFramebuffer %d", \
			vkCreateFramebuffer \
			( \
				smpt_rd_vkq_dvP[device], \
				&(VkFramebufferCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO, \
					.renderPass = vkrenderpass, \
					.attachmentCount = vkimageview_size, \
					.pAttachments = vkimageview_p, \
					.width = smpt_rd_vk_swcVet2d.width, \
					.height = smpt_rd_vk_swcVet2d.height, \
					.layers = 1, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				vkframebuffer_p \
			) \
		)
#endif
