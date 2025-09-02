#ifndef SMPT_RD_VK_IM_H
	#define SMPT_RD_VK_IM_H

	/*mipmap 1
	vksamplecountflagbits VK_SAMPLE_COUNT_1_BIT
	vkimagetiling VK_IMAGE_TILING_OPTIMAL
	vkimagelayout VK_IMAGE_LAYOUT_UNDEFINED*/
	#define SMPT_RD_VK_IM_MAKE(device, vkformat, vkextent3d, mipmap, vkimagetiling, vkimageusageflags, vkimagelayout, vksamplecountflagbits, vkimage_p) \
		SMPT_DB_R2L \
		( \
			"vkCreateImage %d", \
			vkCreateImage \
			( \
				smpt_rd_vkq_dv_p[device], \
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
	#define SMPT_RD_VK_IM_GEN(device, vkimage, vkmemorypropertyflags, vkdevicememory_p, vkmemoryrequirements) \
		vkGetImageMemoryRequirements(smpt_rd_vkq_dv_p[device], vkimage, &vkmemoryrequirements); \
		SMPT_DB_R2L \
		( \
			"vkAllocateMemory %d", \
			vkAllocateMemory \
			( \
				smpt_rd_vkq_dv_p[device], \
				&(VkMemoryAllocateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, \
					.allocationSize = vkmemoryrequirements.size, \
					.memoryTypeIndex = smpt_rd_vk_bf_type(device, vkmemoryrequirements.memoryTypeBits, vkmemorypropertyflags), \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				vkdevicememory_p \
			) \
		) \
		SMPT_DB_R2L("vkBindImageMemory %d", vkBindImageMemory(smpt_rd_vkq_dv_p[device], vkimage, *vkdevicememory_p, 0))
#endif
