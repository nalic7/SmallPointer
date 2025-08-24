#ifndef _VK_BF_H
#define _VK_BF_H
	uint32_t _vk_bf_type(uint32_t device, uint32_t typefilter, VkMemoryPropertyFlags vkmemorypropertyflags);

	//VkMemoryRequirements vkmemoryrequirements
	#define _VK_BF_MAKE(device, vkdevicesize, vkbufferusageflags, vkmemorypropertyflags, vkbuffer, vkdevicememory, vkmemoryrequirements) \
		NALI_D_INFO \
		( \
			"vkCreateBuffer %d", \
			vkCreateBuffer \
			( \
				_vkq_dv_p[device], \
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
		vkGetBufferMemoryRequirements(_vkq_dv_p[device], vkbuffer, &vkmemoryrequirements); \
		NALI_D_INFO \
		( \
			"vkAllocateMemory %d", \
			vkAllocateMemory \
			( \
				_vkq_dv_p[device], \
				&(VkMemoryAllocateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, \
					.memoryTypeIndex = _vk_bf_type(device, vkmemoryrequirements.memoryTypeBits, vkmemorypropertyflags), \
					.allocationSize = vkmemoryrequirements.size, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				&vkdevicememory \
			) \
		) \
		NALI_D_INFO("vkBindBufferMemory %d", vkBindBufferMemory(_vkq_dv_p[device], vkbuffer, vkdevicememory, 0))

	//void *data_p
	#define _VK_BF_MAP(device, vkdevicesize, buffer_data_p, vkdevicememory_p, data_p) \
		NALI_D_INFO("vkMapMemory %d", vkMapMemory(_vkq_dv_p[device], *vkdevicememory_p, 0, vkdevicesize, 0, &data_p)) \
		memcpy(data_p, buffer_data_p, vkdevicesize); \
		vkUnmapMemory(_vkq_dv_p[device], *vkdevicememory_p);
#endif
