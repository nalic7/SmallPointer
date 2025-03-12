void vk_makeImageView(uint32_t device, VkImage* image_ptr, VkFormat* vkformat_ptr, VkImageAspectFlags vkimageaspectflags, VkImageViewCreateFlags vkimageviewcreateflags, VkImageView* vkimageview_ptr)
{
	VkImageViewCreateInfo vkimageviewcreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.image = *image_ptr,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = *vkformat_ptr,
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
	vkCreateImageView(m_vkdevice_ptr[device], &vkimageviewcreateinfo, VK_NULL_HANDLE, vkimageview_ptr);
}
