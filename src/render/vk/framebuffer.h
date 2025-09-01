#ifndef _RD_VK_FBF_H
	#define _RD_VK_FBF_H

	#define _RD_VK_FBF_MAKE(device, vkimageview_p, vkimageview_size, vkrenderpass, vkframebuffer_p) \
		_DB_R2L \
		( \
			"vkCreateFramebuffer %d", \
			vkCreateFramebuffer \
			( \
				_rd_vkq_dv_p[device], \
				&(VkFramebufferCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO, \
					.renderPass = vkrenderpass, \
					.attachmentCount = vkimageview_size, \
					.pAttachments = vkimageview_p, \
					.width = _rd_vk_swc_et2d.width, \
					.height = _rd_vk_swc_et2d.height, \
					.layers = 1, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				vkframebuffer_p \
			) \
		)
#endif
