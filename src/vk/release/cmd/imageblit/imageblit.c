// void vk_setImageBlit(uint32_t width, uint32_t height, uint32_t i, VkImageBlit *vkimageblit_p)
void vk_setImageBlit(VkImageBlit *vkimageblit_p)
{
	*vkimageblit_p = (VkImageBlit)
	{
		// .srcOffsets =
		// {
		// 	{0, 0, 0},
		// 	{width, height, 1}
		// },
		.srcSubresource = (VkImageSubresourceLayers)
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			// .mipLevel = i - 1,
			.baseArrayLayer = 0,
			.layerCount = 1
		},
		// .dstOffsets =
		// {
		// 	{0, 0, 0},
		// 	{width > 1 ? width / 2 : 1, height > 1 ? height / 2 : 1, 1}
		// },
		.dstSubresource = (VkImageSubresourceLayers)
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			// .mipLevel = i,
			.baseArrayLayer = 0,
			.layerCount = 1
		},
	};
}