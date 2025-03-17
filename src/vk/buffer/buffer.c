
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

void vk_makeBuffer(uint32_t device, VkDeviceSize vkdevicesize, VkBufferCreateFlagBits vkbuffercreateflagbits, VkBufferUsageFlags vkbufferusageflags, VkMemoryPropertyFlags vkmemorypropertyflags, VkBuffer* vkbuffer_p, VkDeviceMemory* vkdevicememory_p)
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

	vkCreateBuffer(vkdevice, &vkbuffercreateinfo, NULL, vkbuffer_p);

	VkMemoryRequirements vkmemoryrequirements;
	vkGetBufferMemoryRequirements(vkdevice, *vkbuffer_p, &vkmemoryrequirements);

	VkMemoryAllocateInfo vkmemoryallocateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.memoryTypeIndex = vk_findMemoryType(device, vkmemoryrequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
		.allocationSize = vkmemoryrequirements.size,
		.pNext = VK_NULL_HANDLE
	};

	vkAllocateMemory(vkdevice, &vkmemoryallocateinfo, NULL, vkdevicememory_p);

	vkBindBufferMemory(vkdevice, *vkbuffer_p, *vkdevicememory_p, 0);
}

static const uint16_t model_index_uint16_t_array[] =
{
	0, 1, 2
};

static const float model_data_float_array[] =
{
	0.0, -0.5, 1.0, 0.0, 0.0,
	0.5, 0.5, 0.0, 1.0, 0.0,
	-0.5, 0.5, 0.0, 0.0, 1.0
};

//VK_BUFFER_USAGE_VERTEX_BUFFER_BIT -> vkbufferusageflags
//sizeof(model_data_float_array) -> vkdevicesize
//model_data_float_array -> buffer_data_p

//VK_BUFFER_USAGE_INDEX_BUFFER_BIT -> vkbufferusageflags
//sizeof(model_index_uint16_t_array) -> vkdevicesize
//model_index_uint16_t_array -> buffer_data_p

//0 -> vkmemorymapflags
void mapBuffer(uint32_t device, VkDeviceSize vkdevicesize, VkMemoryMapFlags vkmemorymapflags, VkBufferUsageFlags vkbufferusageflags, void* buffer_data_p, VkBuffer* vkbuffer_p, VkDeviceMemory* vkdevicememory_p)
{
	VkDevice vkdevice = m_vkdevice_p[device];

	vk_makeBuffer(device, vkdevicesize, 0, vkbufferusageflags, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vkbuffer_p, vkdevicememory_p);
	void* data_p;
	vkMapMemory(vkdevice, *vkdevicememory_p, 0, vkdevicesize, vkmemorymapflags, &data_p);
	memcpy(data_p, buffer_data_p, vkdevicesize);
	vkUnmapMemory(vkdevice, *vkdevicememory_p);
}
//vkDestroyBuffer