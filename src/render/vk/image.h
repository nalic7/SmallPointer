#ifndef SMPT_RD_VKhIM
	#define SMPT_RD_VKhIM

	/*mipmap 1
	vksamplecountflagbits VK_SAMPLE_COUNT_1_BIT
	vkimagetiling VK_IMAGE_TILING_OPTIMAL
	vkimagelayout VK_IMAGE_LAYOUT_UNDEFINED*/
	#define SMPT_RD_VK_IMmMAKE(device, vkformat, vkextent3d, mipmap, vkimagetiling, vkimageusageflags, vkimagelayout, vksamplecountflagbits, vkimage_p) \
		SMPT_DBmR2L \
		( \
			"vkCreateImage %d", \
			vkCreateImage \
			( \
				smpt_rd_vkq_dvP[device], \
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
	#define SMPT_RD_VK_IMmGEN(device, vkimage, vkmemorypropertyflags, vkdevicememory_p, vkmemoryrequirements) \
		vkGetImageMemoryRequirements(smpt_rd_vkq_dvP[device], vkimage, &vkmemoryrequirements); \
		SMPT_DBmR2L \
		( \
			"vkAllocateMemory %d", \
			vkAllocateMemory \
			( \
				smpt_rd_vkq_dvP[device], \
				&(VkMemoryAllocateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, \
					.allocationSize = vkmemoryrequirements.size, \
					.memoryTypeIndex = smpt_rd_vk_bfMtype(device, vkmemoryrequirements.memoryTypeBits, vkmemorypropertyflags), \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				vkdevicememory_p \
			) \
		) \
		SMPT_DBmR2L("vkBindImageMemory %d", vkBindImageMemory(smpt_rd_vkq_dvP[device], vkimage, *vkdevicememory_p, 0))
#endif
