#ifndef _RD_VK_IMV_H
	#define _RD_VK_IMV_H

	//mipmap 1
	#define _RD_VK_IMV_MAKE(device, vkimage, vkformat, vkimageaspectflags, mipmap, vkimageview_p) \
		_DB_R2L \
		( \
			"vkCreateImageView %d", \
			vkCreateImageView \
			( \
				_rd_vkq_dv_p[device], \
				&(VkImageViewCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO, \
					.image = vkimage, \
					.viewType = VK_IMAGE_VIEW_TYPE_2D, \
					.format = vkformat, \
					.subresourceRange.aspectMask = vkimageaspectflags, \
					.subresourceRange.baseMipLevel = 0, \
					.subresourceRange.levelCount = mipmap, \
					.subresourceRange.baseArrayLayer = 0, \
					.subresourceRange.layerCount = 1, \
					.components.r = VK_COMPONENT_SWIZZLE_IDENTITY, \
					.components.g = VK_COMPONENT_SWIZZLE_IDENTITY, \
					.components.b = VK_COMPONENT_SWIZZLE_IDENTITY, \
					.components.a = VK_COMPONENT_SWIZZLE_IDENTITY, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				vkimageview_p \
			) \
		)
#endif
