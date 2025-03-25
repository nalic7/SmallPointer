void vk_setBufferImageCopy(uint32_t width, uint32_t height, VkBufferImageCopy *vkbufferimagecopy_p)
{
	*vkbufferimagecopy_p = (VkBufferImageCopy)
	{
		.imageSubresource = (VkImageSubresourceLayers)
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.mipLevel = 0,
			.baseArrayLayer = 0,
			.layerCount = 1
		},
		.imageExtent = (VkExtent3D)
		{
			.width = width,
			.height = height,
			.depth = 1
		},
		.bufferOffset = 0,
		.bufferRowLength = 0,
		.bufferImageHeight = 0,
		.imageOffset = 0
	};
}