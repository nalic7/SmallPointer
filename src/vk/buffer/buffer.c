
uint32_t vk_findMemoryType(uint32_t device, uint32_t typefilter, VkMemoryPropertyFlags vkmemorypropertyflags)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_ptr[device];
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

void vk_makeBuffer(uint32_t device, VkDeviceSize vkdevicesize, VkBufferCreateFlagBits vkbuffercreateflagbits, VkBufferUsageFlags vkbufferusageflags, VkMemoryPropertyFlags vkmemorypropertyflags, VkBuffer* vkbuffer_ptr, VkDeviceMemory* vkdevicememory_ptr)
{
	VkDevice vkdevice = m_vkdevice_ptr[device];

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

	vkCreateBuffer(vkdevice, &vkbuffercreateinfo, NULL, vkbuffer_ptr);

	VkMemoryRequirements vkmemoryrequirements;
	vkGetBufferMemoryRequirements(vkdevice, *vkbuffer_ptr, &vkmemoryrequirements);

	VkMemoryAllocateInfo vkmemoryallocateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.memoryTypeIndex = vk_findMemoryType(device, vkmemoryrequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
		.allocationSize = vkmemoryrequirements.size,
		.pNext = VK_NULL_HANDLE
	};

	vkAllocateMemory(vkdevice, &vkmemoryallocateinfo, NULL, vkdevicememory_ptr);

	vkBindBufferMemory(vkdevice, *vkbuffer_ptr, *vkdevicememory_ptr, 0);
}

// const float quadVertices[] =
// {
// 	-1.0f, -1.0f, 0.0f, 0.0f, // Bottom-left  (UV 0,0)
// 	1.0f, -1.0f, 1.0f, 0.0f, // Bottom-right (UV 1,0)
// 	-1.0f,  1.0f, 0.0f, 1.0f, // Top-left     (UV 0,1)
// 	1.0f,  1.0f, 1.0f, 1.0f  // Top-right    (UV 1,1)
// };

// const uint16_t quadIndices[] =
// {
// 	0, 1, 2, 2, 1, 3 // Two triangles forming a quad
// };

// void createVertexBuffer(uint32_t device)
// {
// 	VkDevice vkdevice = m_vkdevice_ptr[device];

// 	VkDeviceSize bufferSize = sizeof(quadVertices);
// 	vk_makeBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &vertexBuffer, &vertexBufferMemory);
// 	void* data;
// 	vkMapMemory(vkdevice, vertexBufferMemory, 0, bufferSize, 0, &data);
// 	memcpy(data, quadVertices, (size_t)bufferSize);
// 	vkUnmapMemory(vkdevice, vertexBufferMemory);
// }

// void createIndexBuffer(uint32_t device)
// {
// 	VkDevice vkdevice = m_vkdevice_ptr[device];

// 	VkDeviceSize bufferSize = sizeof(quadIndices);
// 	vk_makeBuffer(bufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &indexBuffer, &indexBufferMemory);
// 	void* data;
// 	vkMapMemory(vkdevice, indexBufferMemory, 0, bufferSize, 0, &data);
// 	memcpy(data, quadIndices, (size_t)bufferSize);
// 	vkUnmapMemory(vkdevice, indexBufferMemory);
// }
