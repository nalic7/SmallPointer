void vk_makeImage(uint32_t device, VkFormat vkformat, VkExtent3D vkextent3d, VkImageUsageFlags vkimageusageflags, VkImageLayout vkimagelayout, VkImageCreateFlags vkimagecreateflags, VkImage *vkimage_p)
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
		.initialLayout = vkimagelayout,//VK_IMAGE_LAYOUT_UNDEFINED

		.flags = vkimagecreateflags,

		.pNext = VK_NULL_HANDLE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = VK_NULL_HANDLE
	};
	vkCreateImage(m_vkdevice_p[device], &vkimagecreateinfo, VK_NULL_HANDLE, vkimage_p);
}

void vk_genImage(uint32_t device, VkImage vkimage, VkMemoryPropertyFlags vkmemorypropertyflags, VkDeviceMemory *vkdevicememory_p)
{
	VkDevice vkdevice = m_vkdevice_p[device];
	VkMemoryRequirements vkmemoryrequirements;
	vkGetImageMemoryRequirements(vkdevice, vkimage, &vkmemoryrequirements);

	VkMemoryAllocateInfo vkmemoryallocateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.allocationSize = vkmemoryrequirements.size,
		.memoryTypeIndex = vk_findMemoryType(device, vkmemoryrequirements.memoryTypeBits, vkmemorypropertyflags),
		.pNext = VK_NULL_HANDLE
	};

	vkAllocateMemory(vkdevice, &vkmemoryallocateinfo, VK_NULL_HANDLE, vkdevicememory_p);
	vkBindImageMemory(vkdevice, vkimage, *vkdevicememory_p, 0);
}
//vkCmdBlitImage vkCmdCopyImage VK_QUEUE_TRANSFER_BIT