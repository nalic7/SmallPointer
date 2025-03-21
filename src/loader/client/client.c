// uint16_t **m_nali_g_index_p;
VkDeviceSize **m_nali_g_index_vkdevicesize_p;
VkBuffer **m_nali_g_index_vkbuffer_p;
VkDeviceMemory **m_nali_g_index_vkdevicememory_p;

// float **m_nali_g_data_p;
VkDeviceSize **m_nali_g_data_vkdevicesize_p;
VkBuffer **m_nali_g_data_vkbuffer_p;
VkDeviceMemory **m_nali_g_data_vkdevicememory_p;

// uint32_t **m_nali_t_pixel_p;

// uint8_t vkvertexinputattributedescription_size = 2;

static const uint16_t nali_g_index_uint16_t_array[] =
{
	0, 1, 2
};

static const float nali_g_data_float_array[] =
{
	0.0, -0.5, 1.0, 0.0, 0.0,
	0.5, 0.5, 0.0, 1.0, 0.0,
	-0.5, 0.5, 0.0, 0.0, 1.0
};

void lc_init()
{
	//load file
	m_surface_state |= NALI_SURFACE_C_S_RENDER_ABLE;
}

void lc_initVK()
{
	while ((m_surface_state & NALI_SURFACE_C_S_RENDER_ABLE) == 0)
	{
		struct timespec ts = {1, 0};
		thrd_sleep(&ts, NULL);
	}

	//load shader

	// m_nali_g_index_p = malloc(sizeof(uint16_t *) * 1);
	m_nali_g_index_vkdevicesize_p = malloc(sizeof(VkDeviceSize *) * 1);
	m_nali_g_index_vkbuffer_p = malloc(sizeof(VkBuffer *) * 1);
	m_nali_g_index_vkdevicememory_p = malloc(sizeof(VkDeviceMemory *) * 1);

	m_nali_g_index_vkdevicesize_p[0] = malloc(sizeof(VkDeviceSize) * 1);
	m_nali_g_index_vkdevicesize_p[0][0] = sizeof(nali_g_index_uint16_t_array);
	m_nali_g_index_vkbuffer_p[0] = malloc(sizeof(VkBuffer) * 1);
	m_nali_g_index_vkdevicememory_p[0] = malloc(sizeof(VkDeviceMemory) * 1);

	// VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT -> VkMemoryPropertyFlagBits
	vk_makeBuffer(m_device, m_nali_g_index_vkdevicesize_p[0][0], 0, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_nali_g_index_vkbuffer_p[0], m_nali_g_index_vkdevicememory_p[0]);
	vk_mapBuffer(m_device, m_nali_g_index_vkdevicesize_p[0][0], 0, (void *)nali_g_index_uint16_t_array, m_nali_g_index_vkbuffer_p[0], m_nali_g_index_vkdevicememory_p[0]);

	// m_nali_g_data_p = malloc(sizeof(float *) * 1);
	m_nali_g_data_vkdevicesize_p = malloc(sizeof(VkDeviceSize *) * 1);
	m_nali_g_data_vkbuffer_p = malloc(sizeof(VkBuffer *) * 1);
	m_nali_g_data_vkdevicememory_p = malloc(sizeof(VkDeviceMemory *) * 1);

	m_nali_g_data_vkdevicesize_p[0] = malloc(sizeof(VkDeviceSize) * 1);
	m_nali_g_data_vkdevicesize_p[0][0] = sizeof(nali_g_data_float_array);
	m_nali_g_data_vkbuffer_p[0] = malloc(sizeof(VkBuffer) * 1);
	m_nali_g_data_vkdevicememory_p[0] = malloc(sizeof(VkDeviceMemory) * 1);

	vk_makeBuffer(m_device, m_nali_g_data_vkdevicesize_p[0][0], 0, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_nali_g_data_vkbuffer_p[0], m_nali_g_data_vkdevicememory_p[0]);
	vk_mapBuffer(m_device, m_nali_g_data_vkdevicesize_p[0][0], 0, (void *)nali_g_data_float_array, m_nali_g_data_vkbuffer_p[0], m_nali_g_data_vkdevicememory_p[0]);

	// VkVertexInputBindingDescription *vkvertexinputbindingdescription_p = malloc(sizeof(VkVertexInputBindingDescription) * 2);

	thrd_t thrd_t;
	if (thrd_create(&thrd_t, vk_loop, NULL) != thrd_success)
	{
		error("thrd_create")
	}
}

void lc_clearVK(uint32_t device)
{
	VkDevice vkdevice = m_vkdevice_p[device];
	vkDestroyBuffer(vkdevice, *m_nali_g_index_vkbuffer_p[0], VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, *m_nali_g_index_vkdevicememory_p[0], VK_NULL_HANDLE);

	vkDestroyBuffer(vkdevice, *m_nali_g_data_vkbuffer_p[0], VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, *m_nali_g_data_vkdevicememory_p[0], VK_NULL_HANDLE);

	for (uint32_t i = 0; i < 1; ++i)
	{
		free(m_nali_g_index_vkdevicesize_p[i]);
		free(m_nali_g_index_vkbuffer_p[i]);
		free(m_nali_g_index_vkdevicememory_p[i]);

		free(m_nali_g_data_vkdevicesize_p[i]);
		free(m_nali_g_data_vkbuffer_p[i]);
		free(m_nali_g_data_vkdevicememory_p[i]);
	}

	free(m_nali_g_index_vkdevicesize_p);
	free(m_nali_g_index_vkbuffer_p);
	free(m_nali_g_index_vkdevicememory_p);

	free(m_nali_g_data_vkdevicesize_p);
	free(m_nali_g_data_vkbuffer_p);
	free(m_nali_g_data_vkdevicememory_p);
}

void lc_setVkVertexInputBindingDescription(VkVertexInputBindingDescription *vkvertexinputbindingdescription_p)
{
	vkvertexinputbindingdescription_p[0] = (VkVertexInputBindingDescription)
	{
		.binding = 0,
		.stride = sizeof(float) * 2 + sizeof(float) * 3,
		.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
	};
}

void lc_setVkVertexInputAttributeDescription(VkVertexInputAttributeDescription *vkvertexinputattributedescription_p)
{
	vkvertexinputattributedescription_p[0] = (VkVertexInputAttributeDescription)
	{
		.binding = 0,
		.location = 0,
		.format = VK_FORMAT_R32G32_SFLOAT,
		.offset = 0
	};
	vkvertexinputattributedescription_p[1] = (VkVertexInputAttributeDescription)
	{
		.binding = 0,
		.location = 1,
		.format = VK_FORMAT_R32G32B32_SFLOAT,
		.offset = sizeof(float) * 2
	};
}