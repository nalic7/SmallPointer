void vk_makeImage(uint32_t device, VkFormat vkformat, VkExtent3D vkextent3d, VkImageUsageFlags vkimageusageflags, VkImage* vkimage_ptr)
{
	VkImageCreateInfo vkimagecreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
		.imageType = VK_IMAGE_TYPE_2D,
		.format = vkformat,
		.extent = vkextent3d,
		.mipLevels = 1,
		.arrayLayers = 1,
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.tiling = VK_IMAGE_TILING_OPTIMAL,
		.usage = vkimageusageflags,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED
	};
	vkCreateImage(m_vkdevice_ptr[device], &vkimagecreateinfo, VK_NULL_HANDLE, vkimage_ptr);
}
