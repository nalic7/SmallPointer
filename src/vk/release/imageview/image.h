#ifndef NALI_VK_IMAGE_H
#define NALI_VK_IMAGE_H

/*mipmap 1
vksamplecountflagbits VK_SAMPLE_COUNT_1_BIT
vkimagetiling VK_IMAGE_TILING_OPTIMAL
vkimagelayout VK_IMAGE_LAYOUT_UNDEFINED*/
#define VK_makeImage(device, vkformat, vkextent3d, mipmap, vkimagetiling, vkimageusageflags, vkimagelayout, vksamplecountflagbits, vkimage_p) \
	NALI_D_INFO \
	( \
		"vkCreateImage %d", \
		vkCreateImage \
		( \
			vkqd_vkdevice_p[device], \
			&(VkImageCreateInfo) \
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
			}, \
			VK_NULL_HANDLE, \
			vkimage_p \
		) \
	)

//vkmemoryrequirements f
#define VK_genImage(device, vkimage, vkmemorypropertyflags, vkdevicememory_p, vkmemoryrequirements) \
	vkGetImageMemoryRequirements(vkqd_vkdevice_p[device], vkimage, &vkmemoryrequirements); \
	NALI_D_INFO \
	( \
		"vkAllocateMemory %d", \
		vkAllocateMemory \
		( \
			vkqd_vkdevice_p[device], \
			&(VkMemoryAllocateInfo) \
			{ \
				.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, \
				.allocationSize = vkmemoryrequirements.size, \
				.memoryTypeIndex = vkb_findMemoryType(device, vkmemoryrequirements.memoryTypeBits, vkmemorypropertyflags), \
				.pNext = VK_NULL_HANDLE \
			}, \
			VK_NULL_HANDLE, \
			vkdevicememory_p \
		) \
	) \
	NALI_D_INFO("vkBindImageMemory %d", vkBindImageMemory(vkqd_vkdevice_p[device], vkimage, *vkdevicememory_p, 0))

#endif