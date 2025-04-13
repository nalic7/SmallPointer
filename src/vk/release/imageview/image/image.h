#ifndef NALI_VK_IMAGE_H
#define NALI_VK_IMAGE_H

/*mipmap 1
vksamplecountflagbits VK_SAMPLE_COUNT_1_BIT
vkimagetiling VK_IMAGE_TILING_OPTIMAL
vkimagelayout VK_IMAGE_LAYOUT_UNDEFINED*/
#define VK_makeImage(device, vkformat, vkextent3d, mipmap, vkimagetiling, vkimageusageflags, vkimagelayout, vksamplecountflagbits, vkimage_p) \
	nali_info \
	( \
		"vkCreateImage %d", \
		vkCreateImage \
		( \
			m_vkdevice_p[device], \
			(&(VkImageCreateInfo) \
			{ \
				.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO, \
				.imageType = VK_IMAGE_TYPE_2D, \
				.format = vkformat, \
				.extent = vkextent3d, \
				.mipLevels = mipmap, \
				.arrayLayers = 1, \
				.samples = vksamplecountflagbits, \
				.tiling = vkimagetiling, \
				.usage = vkimageusageflags, \
				.sharingMode = VK_SHARING_MODE_EXCLUSIVE, \
				.initialLayout = vkimagelayout, \
				.queueFamilyIndexCount = 0, \
				.pQueueFamilyIndices = VK_NULL_HANDLE, \
				.flags = 0, \
				.pNext = VK_NULL_HANDLE \
			}), \
			VK_NULL_HANDLE, \
			vkimage_p \
		) \
	)

//vkmemoryrequirements f
#define VK_genImage(device, vkimage, vkmemorypropertyflags, vkdevicememory_p, vkmemoryrequirements) \
	vkGetImageMemoryRequirements(m_vkdevice_p[device], vkimage, &vkmemoryrequirements); \
	nali_info \
	( \
		"vkAllocateMemory %d", \
		vkAllocateMemory \
		( \
			m_vkdevice_p[device], \
			(&(VkMemoryAllocateInfo) \
			{ \
				.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, \
				.allocationSize = vkmemoryrequirements.size, \
				.memoryTypeIndex = vk_findMemoryType(device, vkmemoryrequirements.memoryTypeBits, vkmemorypropertyflags), \
				.pNext = VK_NULL_HANDLE \
			}), \
			VK_NULL_HANDLE, \
			vkdevicememory_p \
		) \
	) \
	nali_info("vkBindImageMemory %d", vkBindImageMemory(m_vkdevice_p[device], vkimage, *vkdevicememory_p, 0))

#endif