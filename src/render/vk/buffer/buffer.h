#ifndef SMPT_RD_VK_BF_H
	#define SMPT_RD_VK_BF_H

	uint32_t smpt_rd_vk_bf_type(uint32_t device, uint32_t typefilter, VkMemoryPropertyFlags vkmemorypropertyflags);

	//VkMemoryRequirements vkmemoryrequirements
	#define SMPT_RD_VK_BF_MAKE(device, vkdevicesize, vkbufferusageflags, vkmemorypropertyflags, vkbuffer, vkdevicememory, vkmemoryrequirements) \
		SMPT_DB_R2L \
		( \
			"vkCreateBuffer %d", \
			vkCreateBuffer \
			( \
				smpt_rd_vkq_dv_p[device], \
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
		vkGetBufferMemoryRequirements(smpt_rd_vkq_dv_p[device], vkbuffer, &vkmemoryrequirements); \
		SMPT_DB_R2L \
		( \
			"vkAllocateMemory %d", \
			vkAllocateMemory \
			( \
				smpt_rd_vkq_dv_p[device], \
				&(VkMemoryAllocateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, \
					.memoryTypeIndex = smpt_rd_vk_bf_type(device, vkmemoryrequirements.memoryTypeBits, vkmemorypropertyflags), \
					.allocationSize = vkmemoryrequirements.size, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				&vkdevicememory \
			) \
		) \
		SMPT_DB_R2L("vkBindBufferMemory %d", vkBindBufferMemory(smpt_rd_vkq_dv_p[device], vkbuffer, vkdevicememory, 0))

	//void *data_p
	#define SMPT_RD_VK_BF_MAP(device, vkdevicesize, buffer_data_p, vkdevicememory_p, data_p) \
		SMPT_DB_R2L("vkMapMemory %d", vkMapMemory(smpt_rd_vkq_dv_p[device], *vkdevicememory_p, 0, vkdevicesize, 0, &data_p)) \
		memcpy(data_p, buffer_data_p, vkdevicesize); \
		vkUnmapMemory(smpt_rd_vkq_dv_p[device], *vkdevicememory_p);
#endif
