uint32_t vk_findMemoryType(uint32_t device, uint32_t typefilter, VkMemoryPropertyFlags vkmemorypropertyflags)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[device];
	VkPhysicalDeviceMemoryProperties vkphysicaldevicememoryproperties;
	vkGetPhysicalDeviceMemoryProperties(vkphysicaldevice, &vkphysicaldevicememoryproperties);

	for (uint32_t t = 0; t < vkphysicaldevicememoryproperties.memoryTypeCount; ++t)
	{
		if ((typefilter & (1 << t)) && (vkphysicaldevicememoryproperties.memoryTypes[t].propertyFlags & vkmemorypropertyflags) == vkmemorypropertyflags)
		{
			return t;
		}
	}

	error("findMemoryType")

	return 0;
}

void vk_makeBuffer(uint32_t device, VkDeviceSize vkdevicesize, VkBufferCreateFlagBits vkbuffercreateflagbits, VkBufferUsageFlags vkbufferusageflags, VkMemoryPropertyFlags vkmemorypropertyflags, VkBuffer *vkbuffer_p, VkDeviceMemory *vkdevicememory_p)
{
	VkDevice vkdevice = m_vkdevice_p[device];

	VkBufferCreateInfo vkbuffercreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.size = vkdevicesize,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,

		.usage = vkbufferusageflags,
		.flags = vkbuffercreateflagbits,

		//VK_SHARING_MODE_CONCURRENT
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = VK_NULL_HANDLE,

		.pNext = VK_NULL_HANDLE
	};

	vkCreateBuffer(vkdevice, &vkbuffercreateinfo, VK_NULL_HANDLE, vkbuffer_p);

	VkMemoryRequirements vkmemoryrequirements;
	vkGetBufferMemoryRequirements(vkdevice, *vkbuffer_p, &vkmemoryrequirements);

	VkMemoryAllocateInfo vkmemoryallocateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.memoryTypeIndex = vk_findMemoryType(device, vkmemoryrequirements.memoryTypeBits, vkmemorypropertyflags),
		.allocationSize = vkmemoryrequirements.size,
		.pNext = VK_NULL_HANDLE
	};

	vkAllocateMemory(vkdevice, &vkmemoryallocateinfo, VK_NULL_HANDLE, vkdevicememory_p);
	vkBindBufferMemory(vkdevice, *vkbuffer_p, *vkdevicememory_p, 0);
}

void vk_mapBuffer(uint32_t device, VkDeviceSize vkdevicesize, VkMemoryMapFlags vkmemorymapflags, void *buffer_data_p, VkDeviceMemory *vkdevicememory_p)
{
	VkDevice vkdevice = m_vkdevice_p[device];

	void *data_p;
	vkMapMemory(vkdevice, *vkdevicememory_p, 0, vkdevicesize, vkmemorymapflags, &data_p);
	memcpy(data_p, buffer_data_p, vkdevicesize);
	vkUnmapMemory(vkdevice, *vkdevicememory_p);
}