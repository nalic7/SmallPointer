#ifndef SMPT_RD_VK_FBF_H
	#define SMPT_RD_VK_FBF_H

	#define SMPT_RD_VK_FBF_MAKE(device, vkimageview_p, vkimageview_size, vkrenderpass, vkframebuffer_p) \
		SMPT_DB_R2L \
		( \
			"vkCreateFramebuffer %d", \
			vkCreateFramebuffer \
			( \
				smpt_rd_vkq_dv_p[device], \
				&(VkFramebufferCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO, \
					.renderPass = vkrenderpass, \
					.attachmentCount = vkimageview_size, \
					.pAttachments = vkimageview_p, \
					.width = smpt_rd_vk_swc_et2d.width, \
					.height = smpt_rd_vk_swc_et2d.height, \
					.layers = 1, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				vkframebuffer_p \
			) \
		)
#endif
