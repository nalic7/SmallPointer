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

	#define SMPT_RD_VK_BFmFREE_F \
		static VkBuffer *Pvkbuffer_free; \
		static VkDeviceMemory *Pvkdevicememory_free; \
		static uint8_t *Pfree; \
		static uint32_t Lfree = 0;
	#define SMPT_RD_VK_BFmFREE_SET \
		Pvkbuffer_free = malloc(0); \
		Pvkdevicememory_free = malloc(0); \
		Pfree = malloc(0);
	#define SMPT_RD_VK_BFmFREE_HELP \
		Pvkbuffer_free = realloc(Pvkbuffer_free, sizeof(VkBuffer) * (Lfree + Ue - Us) * smpt_rd_vk_swcUimage); \
		Pvkdevicememory_free = realloc(Pvkdevicememory_free, sizeof(VkDeviceMemory) * (Lfree + Ue - Us) * smpt_rd_vk_swcUimage); \
		Pfree = realloc(Pfree, sizeof(uint8_t) * (Lfree + Ue - Us)); \
		for (uint32_t l0 = Lfree; l0 < Lfree + Ue - Us; ++l0) \
		{ \
			Pfree[l0] = 1 << smpt_rd_vk_swcUimage; \
		} \
		memcpy(Pvkbuffer_free + Lfree * smpt_rd_vk_swcUimage, smptr_cemPvkbuffer + Us * smpt_rd_vk_swcUimage, sizeof(VkBuffer) * (Ue - Us) * smpt_rd_vk_swcUimage); \
		memcpy(Pvkdevicememory_free + Lfree * smpt_rd_vk_swcUimage, Pvkdevicememory + Us * smpt_rd_vk_swcUimage, sizeof(VkDeviceMemory) * (Ue - Us) * smpt_rd_vk_swcUimage); \
		Lfree += Ue - Us;
	#define SMPT_RD_VK_BFmFREE_ABLE(ls) !(Pfree[ls] = Pfree[ls] >> 1)
	#define SMPT_RD_VK_BFmFREE_DO(ls, ln) \
		for (uint8_t ln = 0; ln < smpt_rd_vk_swcUimage; ++ln) \
		{ \
			vkUnmapMemory(vkdevice, Pvkdevicememory_free[ls * smpt_rd_vk_swcUimage + ln]); \
			vkDestroyBuffer(vkdevice, Pvkbuffer_free[ls * smpt_rd_vk_swcUimage + ln], VK_NULL_HANDLE); \
			vkFreeMemory(vkdevice, Pvkdevicememory_free[ls * smpt_rd_vk_swcUimage + ln], VK_NULL_HANDLE); \
		}
	#define SMPT_RD_VK_BFmFREE_RE \
		Pvkbuffer_free = realloc(Pvkbuffer_free, sizeof(VkBuffer) * Lfree * smpt_rd_vk_swcUimage); \
		Pvkdevicememory_free = realloc(Pvkdevicememory_free, sizeof(VkDeviceMemory) * Lfree * smpt_rd_vk_swcUimage); \
		Pfree = realloc(Pfree, sizeof(uint8_t) * Lfree);
	#define SMPT_RD_VK_BFmFREE_CLEAN \
		free(Pfree); \
		free(Pvkdevicememory_free); \
		free(Pvkbuffer_free);
#endif
