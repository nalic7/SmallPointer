void vk_setImageMemoryBarrier(VkImageLayout src_vkimagelayout, VkImageLayout dst_vkimagelayout, VkImage vkimage, VkAccessFlags src_vkaccessflags, VkAccessFlags dst_vkaccessflags, VkImageMemoryBarrier *vkimagememorybarrier_p)
{
	*vkimagememorybarrier_p = (VkImageMemoryBarrier)
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
		.oldLayout = src_vkimagelayout,
		.newLayout = dst_vkimagelayout,
		.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
		.image = vkimage,

		.subresourceRange = (VkImageSubresourceRange)
		{
			.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
			.baseMipLevel = 0,
			.levelCount = 1,
			.baseArrayLayer = 0,
			.layerCount = 1
		},

		.srcAccessMask = src_vkaccessflags,
		.dstAccessMask = dst_vkaccessflags,

		.pNext = VK_NULL_HANDLE
	};
}