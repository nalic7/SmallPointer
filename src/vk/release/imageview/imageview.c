void vk_makeImageView(uint32_t device, VkImage *image_p, VkFormat vkformat, VkImageAspectFlags vkimageaspectflags, VkImageViewCreateFlags vkimageviewcreateflags, VkImageView *vkimageview_p)
{
	VkImageViewCreateInfo vkimageviewcreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.image = *image_p,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = vkformat,
		.subresourceRange.aspectMask = vkimageaspectflags,
		.subresourceRange.baseMipLevel = 0,
		.subresourceRange.levelCount = 1,
		.subresourceRange.baseArrayLayer = 0,
		.subresourceRange.layerCount = 1,

		.components.r = VK_COMPONENT_SWIZZLE_IDENTITY,
		.components.g = VK_COMPONENT_SWIZZLE_IDENTITY,
		.components.b = VK_COMPONENT_SWIZZLE_IDENTITY,
		.components.a = VK_COMPONENT_SWIZZLE_IDENTITY,

		.flags = vkimageviewcreateflags,
		.pNext = VK_NULL_HANDLE
	};
	vkCreateImageView(m_vkdevice_p[device], &vkimageviewcreateinfo, VK_NULL_HANDLE, vkimageview_p);
}
