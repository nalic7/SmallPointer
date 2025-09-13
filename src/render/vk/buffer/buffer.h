#ifndef SMPT_RD_VKhBF
	#define SMPT_RD_VKhBF

	uint32_t smpt_rd_vk_bfMtype(uint32_t device, uint32_t typefilter, VkMemoryPropertyFlags vkmemorypropertyflags);

	//VkMemoryRequirements vkmemoryrequirements
	#define SMPT_RD_VK_BFmMAKE(device, vkdevicesize, vkbufferusageflags, vkmemorypropertyflags, vkbuffer, vkdevicememory, vkmemoryrequirements) \
		SMPT_DBmR2L \
		( \
			"vkCreateBuffer %d", \
			vkCreateBuffer \
			( \
				smpt_rd_vkq_dvP[device], \
				&(VkBufferCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, \
					.size = vkdevicesize, \
					.sharingMode = VK_SHARING_MODE_EXCLUSIVE, \
					.usage = vkbufferusageflags, \
					.queueFamilyIndexCount = 0, \
					.pQueueFamilyIndices = VK_NULL_HANDLE, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				&vkbuffer \
			) \
		) \
		vkGetBufferMemoryRequirements(smpt_rd_vkq_dvP[device], vkbuffer, &vkmemoryrequirements); \
		SMPT_DBmR2L \
		( \
			"vkAllocateMemory %d", \
			vkAllocateMemory \
			( \
				smpt_rd_vkq_dvP[device], \
				&(VkMemoryAllocateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, \
					.memoryTypeIndex = smpt_rd_vk_bfMtype(device, vkmemoryrequirements.memoryTypeBits, vkmemorypropertyflags), \
					.allocationSize = vkmemoryrequirements.size, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				&vkdevicememory \
			) \
		) \
		SMPT_DBmR2L("vkBindBufferMemory %d", vkBindBufferMemory(smpt_rd_vkq_dvP[device], vkbuffer, vkdevicememory, 0))

	//void *Pdata
	#define SMPT_RD_VK_BFmMAP(device, vkdevicesize, Pbuffer_data, Pvkdevicememory, Pdata) \
		SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(smpt_rd_vkq_dvP[device], *Pvkdevicememory, 0, vkdevicesize, 0, &Pdata)) \
		memcpy(Pdata, Pbuffer_data, vkdevicesize); \
		vkUnmapMemory(smpt_rd_vkq_dvP[device], *Pvkdevicememory);
#endif
