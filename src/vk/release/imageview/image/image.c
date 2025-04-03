void vk_makeImage(uint32_t device, VkFormat vkformat, VkExtent3D vkextent3d, uint32_t mipmap, VkImageTiling vkimagetiling, VkImageUsageFlags vkimageusageflags, VkImageLayout vkimagelayout, VkSampleCountFlagBits vksamplecountflagbits, VkImage *vkimage_p)
{
	nali_info
	(
		"vkCreateImage %d",
		vkCreateImage
		(
			m_vkdevice_p[device],
			&(VkImageCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
				.imageType = VK_IMAGE_TYPE_2D,
				.format = vkformat,
				.extent = vkextent3d,
				.mipLevels = mipmap,//1
				.arrayLayers = 1,
				.samples = vksamplecountflagbits,//VK_SAMPLE_COUNT_1_BIT,
				.tiling = vkimagetiling,//VK_IMAGE_TILING_OPTIMAL
				.usage = vkimageusageflags,
				.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
				.initialLayout = vkimagelayout,//VK_IMAGE_LAYOUT_UNDEFINED
		
				.queueFamilyIndexCount = 0,
				.pQueueFamilyIndices = VK_NULL_HANDLE,
		
				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkimage_p
		)
	)
}

void vk_genImage(uint32_t device, VkImage vkimage, VkMemoryPropertyFlags vkmemorypropertyflags, VkDeviceMemory *vkdevicememory_p)
{
	VkDevice vkdevice = m_vkdevice_p[device];
	VkMemoryRequirements vkmemoryrequirements;
	vkGetImageMemoryRequirements(vkdevice, vkimage, &vkmemoryrequirements);

	nali_info
	(
		"vkAllocateMemory %d",
		vkAllocateMemory
		(
			vkdevice,
			&(VkMemoryAllocateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
				.allocationSize = vkmemoryrequirements.size,
				.memoryTypeIndex = vk_findMemoryType(device, vkmemoryrequirements.memoryTypeBits, vkmemorypropertyflags),
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkdevicememory_p
		)
	)
	nali_info("vkBindImageMemory %d", vkBindImageMemory(vkdevice, vkimage, *vkdevicememory_p, 0))
}