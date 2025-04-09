// uint16_t m_nali_g_max_data;

// uint16_t **m_nali_g_index_p;
// VkDeviceSize **m_nali_g_index_vkdevicesize_p;
VkBuffer **m_nali_g_index_vkbuffer_p;
VkDeviceMemory **m_nali_g_index_vkdevicememory_p;

// float **m_nali_g_data_p;
// VkDeviceSize **m_nali_g_data_vkdevicesize_p;
VkBuffer **m_nali_g_data_vkbuffer_p;
VkDeviceMemory **m_nali_g_data_vkdevicememory_p;

// VkDeviceSize *m_nali_g_ubo_vkdevicesize_p;
VkBuffer *m_nali_g_ubo_vkbuffer_p;
VkDeviceMemory *m_nali_g_ubo_vkdevicememory_p;

uint16_t m_nali_g_max_image;
long m_nali_g_max_image_state;
uint8_t *m_nali_g_image_state_uint8_t_p;
uint8_t **m_nali_g_image_uint8_t_p;
uint32_t *m_nali_g_image_wh_uint32_t_p;
VkImage *m_nali_g_image_vkimage_p;
VkImageView *m_nali_g_image_vkimageview_p;
VkSampler *m_nali_g_image_vksampler_p;
VkDeviceMemory *m_nali_g_image_vkimage_vkdevicememory_p;

VkBuffer *m_nali_g_image_vkbuffer_p;
VkDeviceMemory *m_nali_g_image_vkbuffer_vkdevicememory_p;

// uint32_t **m_nali_t_pixel_p;

// uint8_t vkvertexinputattributedescription_size = 2;

static const uint16_t nali_g_index_uint16_t_array[] =
{
	// 0, 1, 2
	0, 1, 2,
	2, 3, 0
};

//float + uint16_t
// void *nali_g_data_void_p;

static const float nali_g_data_float_array[] =
{
	// 0.0, -0.5, 1.0, 0.0, 0.0,
	// 0.5, 0.5, 0.0, 1.0, 0.0,
	// -0.5, 0.5, 0.0, 0.0, 1.0

	-1.0F, -1.0F, 0.0F, 0.0F,//bottom left
	1.0F, -1.0F, 1.0F, 0.0F,//bottom right
	1.0F,  1.0F, 1.0F, 1.0F,//top right
	-1.0F,  1.0F, 0.0F, 1.0F//top left
};

// static const float nali_g_v_float_array[] =
// {
// 	// 0.0, -0.5, 1.0, 0.0, 0.0,
// 	// 0.5, 0.5, 0.0, 1.0, 0.0,
// 	// -0.5, 0.5, 0.0, 0.0, 1.0

// 	-1.0F, -1.0F,//bottom left
// 	1.0F, -1.0F,//bottom right
// 	1.0F,  1.0F,//top right
// 	-1.0F,  1.0F//top left
// };

// static const int16_t nali_g_t_int16_t_array[] =
// {
// 	0, 0,
// 	512, 0,
// 	512, 512,
// 	0, 512
// };

static float nali_v_uniform_float_array[] =
{
	//m4x4 m
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1,
	//m4x4 v
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, -1, 1,
	//m4x4 p
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

// static const float nali_f_uniform_float_array[] =
// {
// 	//width height
// 	512, 512
// };

void lc_init()
{
	#ifdef NALI_GEN
		gen_file();
	#endif

	//load file

	//s0-image

	m_nali_g_image_state_uint8_t_p = f_read(NALI_HOME "image.bin", &m_nali_g_max_image_state);
	m_nali_g_image_uint8_t_p = malloc(0);
	m_nali_g_image_wh_uint32_t_p = malloc(0);

	struct dirent *dirent_p;

	const char image_type[] = ".png";
	const char image_path[] = NALI_HOME NALI_HOME_IMAGE;
	DIR *dir_p = opendir(image_path);
	nali_log("opendir %p", dir_p)

	size_t name_index = sizeof(image_path)-1 + 1 + 1;
	char *image_file = malloc(name_index);
	strcpy(image_file, image_path);
	strcat(image_file, "/");

	// png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	// png_infop info = png_create_info_struct(png);

	int16_t index;
	int16_t size = -1;
	uint32_t wh_index;
	uint8_t name_index_size;
	while ((dirent_p = readdir(dir_p)) != NULL)
	{
		if (dirent_p->d_type == DT_REG)
		{
			sscanf(dirent_p->d_name, "%hd", &index);
			if (size < index)
			{
				size = index;

				m_nali_g_max_image = size + 1;
				m_nali_g_image_uint8_t_p = realloc(m_nali_g_image_uint8_t_p, sizeof(uint8_t *) * m_nali_g_max_image);
				m_nali_g_image_wh_uint32_t_p = realloc(m_nali_g_image_wh_uint32_t_p, sizeof(uint32_t) * m_nali_g_max_image * 2);
			}
			name_index_size = name_index + MATH_LENGTH(index);
			image_file = realloc(image_file, name_index_size + sizeof(image_type)-1);
			sprintf(image_file + name_index - 1, "%u", index);
			image_file[name_index_size - 1] = '\0';
			strcat(image_file, image_type);

			wh_index = index * 2;

			// FILE *file_p = fopen(image_file, "rb");
			// nali_log("file_p %p", file_p)
			// png_init_io(png, file_p);
			// png_read_info(png, info);

			// m_nali_g_image_wh_uint32_t_p[wh_index] = png_get_image_width(png, info);
			// png_uint_32 height = m_nali_g_image_wh_uint32_t_p[wh_index + 1] = png_get_image_height(png, info);
			// // png_byte color_type = png_get_color_type(png, info);
			// // png_byte bit_depth = png_get_bit_depth(png, info);

			// png_read_update_info(png, info);
			// png_bytep *row_pointers = malloc(sizeof(png_bytep) * height);
			// for (int y = 0; y < height; y++)
			// {
			// 	row_pointers[y] = malloc(png_get_rowbytes(png, info));
			// }

			// png_read_image(png, row_pointers);

			ffmpeg_read(image_file);
			m_nali_g_image_uint8_t_p[index] = ffmpeg_png(&m_nali_g_image_wh_uint32_t_p[wh_index], &m_nali_g_image_wh_uint32_t_p[wh_index + 1]);
			ffmpeg_clean();
		}
	}
	free(image_file);
	//e0-image

	float qv4_float_p[4];
	v4_q(0, MATH_D2R(35.0F), 0, qv4_float_p);
	v4_qm(qv4_float_p, nali_v_uniform_float_array + 16);
	M4X4_P(tanf(90.0F * (M_PI / 180.0F) / 2.0F), 16.0F / 9.0F, 0.1F, 100.0F, nali_v_uniform_float_array + 16 + 16)
	m_surface_state |= NALI_SURFACE_C_S_RENDER_ABLE;
}

void lc_initVK()
{
	while (!(m_surface_state & NALI_SURFACE_C_S_RENDER_ABLE))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	//load shader

	//s0-index
	// m_nali_g_index_p = malloc(sizeof(uint16_t *) * 1);
	// m_nali_g_index_vkdevicesize_p = malloc(sizeof(VkDeviceSize *) * 1);
	m_nali_g_index_vkbuffer_p = malloc(sizeof(VkBuffer *) * 1);
	m_nali_g_index_vkdevicememory_p = malloc(sizeof(VkDeviceMemory *) * 1);

	// m_nali_g_index_vkdevicesize_p[0] = malloc(sizeof(VkDeviceSize) * 1);
	// m_nali_g_index_vkdevicesize_p[0][0] = sizeof(nali_g_index_uint16_t_array);
	m_nali_g_index_vkbuffer_p[0] = malloc(sizeof(VkBuffer) * 1);
	m_nali_g_index_vkdevicememory_p[0] = malloc(sizeof(VkDeviceMemory) * 1);

	// VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT -> VkMemoryPropertyFlagBits
	VkDeviceSize vkdevicesize = sizeof(nali_g_index_uint16_t_array);
	// vk_makeBuffer(m_device, m_nali_g_index_vkdevicesize_p[0][0], 0, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_nali_g_index_vkbuffer_p[0], m_nali_g_index_vkdevicememory_p[0]);
	// vk_mapBuffer(m_device, m_nali_g_index_vkdevicesize_p[0][0], 0, (void *)nali_g_index_uint16_t_array, m_nali_g_index_vkbuffer_p[0], m_nali_g_index_vkdevicememory_p[0]);
	vk_makeBuffer(m_device, vkdevicesize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_nali_g_index_vkbuffer_p[0], m_nali_g_index_vkdevicememory_p[0]);
	vk_mapBuffer(m_device, vkdevicesize, (void *)nali_g_index_uint16_t_array, m_nali_g_index_vkdevicememory_p[0]);
	//e0-index

	//s0-data
	// m_nali_g_data_p = malloc(sizeof(float *) * 1);
	// m_nali_g_data_vkdevicesize_p = malloc(sizeof(VkDeviceSize *) * 1);
	m_nali_g_data_vkbuffer_p = malloc(sizeof(VkBuffer *) * 1);
	m_nali_g_data_vkdevicememory_p = malloc(sizeof(VkDeviceMemory *) * 1);

	// m_nali_g_data_vkdevicesize_p[0] = malloc(sizeof(VkDeviceSize) * 1);
	// m_nali_g_data_vkdevicesize_p[0][0] = sizeof(nali_g_data_float_array);
	m_nali_g_data_vkbuffer_p[0] = malloc(sizeof(VkBuffer) * 1);
	m_nali_g_data_vkdevicememory_p[0] = malloc(sizeof(VkDeviceMemory) * 1);

	vkdevicesize = sizeof(nali_g_data_float_array);
	// vkdevicesize = sizeof(nali_g_v_float_array) + sizeof(nali_g_t_int16_t_array);
	// nali_g_data_void_p = malloc(vkdevicesize);
	// void *temp_nali_g_data_void_p = nali_g_data_void_p;
	// for (uint8_t u = 0; u < 4; ++u)
	// {
	// 	// info("f %d %f", u, *(nali_g_v_float_array + u))
	// 	// info("d %d %d", u, *(nali_g_t_int16_t_array + u))
	// 	memcpy(temp_nali_g_data_void_p, nali_g_v_float_array + u * 2, sizeof(float));
	// 	info("x0 %d %f", u, *(float *)temp_nali_g_data_void_p)
	// 	// temp_nali_g_data_void_p = (float *)temp_nali_g_data_void_p + 1;
	// 	temp_nali_g_data_void_p += sizeof(float);

	// 	memcpy(temp_nali_g_data_void_p, nali_g_v_float_array + u * 2 + 1, sizeof(float));
	// 	info("x1 %d %f", u, *(float *)temp_nali_g_data_void_p)
	// 	// temp_nali_g_data_void_p = (float *)temp_nali_g_data_void_p + 1;
	// 	temp_nali_g_data_void_p += sizeof(float);

	// 	memcpy(temp_nali_g_data_void_p, nali_g_t_int16_t_array + u * 2, sizeof(int16_t));
	// 	info("y0 %d %d", u, *(int16_t *)temp_nali_g_data_void_p)
	// 	// temp_nali_g_data_void_p = (int16_t *)temp_nali_g_data_void_p + 1;
	// 	temp_nali_g_data_void_p += sizeof(int16_t);

	// 	memcpy(temp_nali_g_data_void_p, nali_g_t_int16_t_array + u * 2 + 1, sizeof(int16_t));
	// 	info("y1 %d %d", u, *(int16_t *)temp_nali_g_data_void_p)
	// 	// temp_nali_g_data_void_p = (int16_t *)temp_nali_g_data_void_p + 1;
	// 	temp_nali_g_data_void_p += sizeof(int16_t);
	// }
	// // vk_makeBuffer(m_device, m_nali_g_data_vkdevicesize_p[0][0], 0, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_nali_g_data_vkbuffer_p[0], m_nali_g_data_vkdevicememory_p[0]);
	// // vk_mapBuffer(m_device, m_nali_g_data_vkdevicesize_p[0][0], 0, (void *)nali_g_data_float_array, m_nali_g_data_vkbuffer_p[0], m_nali_g_data_vkdevicememory_p[0]);
	vk_makeBuffer(m_device, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, m_nali_g_data_vkbuffer_p[0], m_nali_g_data_vkdevicememory_p[0]);
	// vk_mapBuffer(m_device, vkdevicesize, 0, (void *)nali_g_data_void_p, m_nali_g_data_vkdevicememory_p[0]);
	vk_mapBuffer(m_device, vkdevicesize, (void *)nali_g_data_float_array, m_nali_g_data_vkdevicememory_p[0]);
	//e0-data

	//s0-image
	m_nali_g_image_vkimage_p = malloc(sizeof(VkImage) * m_nali_g_max_image);
	m_nali_g_image_vkimageview_p = malloc(sizeof(VkImageView) * m_nali_g_max_image);
	m_nali_g_image_vksampler_p = malloc(sizeof(VkSampler) * m_nali_g_max_image);
	m_nali_g_image_vkimage_vkdevicememory_p = malloc(sizeof(VkDeviceMemory) * m_nali_g_max_image);

	m_nali_g_image_vkbuffer_p = malloc(sizeof(VkBuffer) * m_nali_g_max_image);
	m_nali_g_image_vkbuffer_vkdevicememory_p = malloc(sizeof(VkDeviceMemory) * m_nali_g_max_image);

	uint32_t u2;
	uint32_t u2_1;
	uint8_t line;
	int vkimageusageflagbits = 0;
	for (uint16_t u = 0; u < m_nali_g_max_image; ++u)
	{
		u2 = u * 2;
		u2_1 = u2 + 1;

		uint8_t mipmap = 1;
		if (m_nali_g_image_state_uint8_t_p[u / (8/2)] & 1 << (u % (8/2)) * 2)
		{
			mipmap = MATH_MIPMAP(m_nali_g_image_wh_uint32_t_p[u2], m_nali_g_image_wh_uint32_t_p[u2_1]);
			vkimageusageflagbits = VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
		}
		line = m_nali_g_image_state_uint8_t_p[u / (8/2)] & 2 << (u % (8/2)) * 2;

		vk_makeImage
		(
			m_device,
			NALI_VK_COLOR_FORMAT,
			(VkExtent3D)
			{
				.width = m_nali_g_image_wh_uint32_t_p[u2],
				.height = m_nali_g_image_wh_uint32_t_p[u2_1],
				.depth = 1
			},
			mipmap,
			line ? VK_IMAGE_TILING_LINEAR : VK_IMAGE_TILING_OPTIMAL,
			//sampler
			vkimageusageflagbits | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
			//image2d
			// VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_STORAGE_BIT,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_SAMPLE_COUNT_1_BIT,
			&m_nali_g_image_vkimage_p[u]
		);
		vk_genImage(m_device, m_nali_g_image_vkimage_p[u], VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &m_nali_g_image_vkimage_vkdevicememory_p[u]);
		vkdevicesize = m_nali_g_image_wh_uint32_t_p[u2] * m_nali_g_image_wh_uint32_t_p[u2_1] * NALI_VK_COLOR_FORMAT_BYTE;
		// vk_mapBuffer(m_device, vkdevicesize, 0, m_nali_g_image_uint8_t_p[0], &m_nali_g_image_vkimage_vkdevicememory_p[0]);

		vk_makeBuffer(m_device, vkdevicesize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &m_nali_g_image_vkbuffer_p[u], &m_nali_g_image_vkbuffer_vkdevicememory_p[u]);
		vk_mapBuffer(m_device, vkdevicesize, m_nali_g_image_uint8_t_p[u], &m_nali_g_image_vkbuffer_vkdevicememory_p[u]);

		vk_makeImageView(m_device, m_nali_g_image_vkimage_p[u], NALI_VK_COLOR_FORMAT, VK_IMAGE_ASPECT_COLOR_BIT, mipmap, &m_nali_g_image_vkimageview_p[u]);
		vk_makeSampler(m_device, mipmap, line, &m_nali_g_image_vksampler_p[u]);

		// info("&m_nali_g_image_vkbuffer_p[0] %p", &m_nali_g_image_vkbuffer_p[0]);
		// info("&m_nali_g_image_vkbuffer_vkdevicememory_p[0] %p", &m_nali_g_image_vkbuffer_vkdevicememory_p[0]);
	}
	//e0-image

	//s0-ubo
	m_nali_g_ubo_vkbuffer_p = malloc(sizeof(VkBuffer) * 1);
	m_nali_g_ubo_vkdevicememory_p = malloc(sizeof(VkDeviceMemory) * 1);

	vkdevicesize = sizeof(nali_v_uniform_float_array);
	vk_makeBuffer(m_device, vkdevicesize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &m_nali_g_ubo_vkbuffer_p[0], &m_nali_g_ubo_vkdevicememory_p[0]);
	vk_mapBuffer(m_device, vkdevicesize, (void *)nali_v_uniform_float_array, &m_nali_g_ubo_vkdevicememory_p[0]);
	//e0-ubo

	vk_initCmdDraw();
	//thrd_success
	nali_info("thrd_create %d", thrd_create(&(thrd_t){}, vk_cmdDraw, NULL))
}

void lc_clearVK(uint32_t device)
{
	VkDevice vkdevice = m_vkdevice_p[device];

	//s0-index
	//s1-data
	for (uint32_t i = 0; i < 1; ++i)
	{
		vkDestroyBuffer(vkdevice, *m_nali_g_index_vkbuffer_p[i], VK_NULL_HANDLE);
		vkFreeMemory(vkdevice, *m_nali_g_index_vkdevicememory_p[i], VK_NULL_HANDLE);
	
		vkDestroyBuffer(vkdevice, *m_nali_g_data_vkbuffer_p[i], VK_NULL_HANDLE);
		vkFreeMemory(vkdevice, *m_nali_g_data_vkdevicememory_p[i], VK_NULL_HANDLE);

		// free(m_nali_g_index_vkdevicesize_p[i]);
		free(m_nali_g_index_vkbuffer_p[i]);
		free(m_nali_g_index_vkdevicememory_p[i]);

		// free(m_nali_g_data_vkdevicesize_p[i]);
		free(m_nali_g_data_vkbuffer_p[i]);
		free(m_nali_g_data_vkdevicememory_p[i]);
	}
	// free(m_nali_g_index_vkdevicesize_p);
	free(m_nali_g_index_vkbuffer_p);
	free(m_nali_g_index_vkdevicememory_p);

	// free(m_nali_g_data_vkdevicesize_p);
	free(m_nali_g_data_vkbuffer_p);
	free(m_nali_g_data_vkdevicememory_p);
	//e1-data
	//e0-index

	//s0-image
	for (uint32_t i = 0; i < m_nali_g_max_image; ++i)
	{
		vkDestroySampler(vkdevice, m_nali_g_image_vksampler_p[i], VK_NULL_HANDLE);
		vkDestroyImageView(vkdevice, m_nali_g_image_vkimageview_p[i], VK_NULL_HANDLE);
		vkDestroyImage(vkdevice, m_nali_g_image_vkimage_p[i], VK_NULL_HANDLE);
		vkFreeMemory(vkdevice, m_nali_g_image_vkimage_vkdevicememory_p[i], VK_NULL_HANDLE);

		// vkDestroyBuffer(vkdevice, m_nali_g_image_vkbuffer_p[i], VK_NULL_HANDLE);
		// vkFreeMemory(vkdevice, m_nali_g_image_vkbuffer_vkdevicememory_p[i], VK_NULL_HANDLE);

		// free(m_nali_g_image_uint8_t_p[i]);
	}
	free(m_nali_g_image_state_uint8_t_p);
	// free(m_nali_g_image_uint8_t_p);
	free(m_nali_g_image_wh_uint32_t_p);
	free(m_nali_g_image_vkimage_p);
	free(m_nali_g_image_vkimageview_p);
	free(m_nali_g_image_vksampler_p);
	free(m_nali_g_image_vkimage_vkdevicememory_p);

	// free(m_nali_g_image_vkbuffer_p);
	// free(m_nali_g_image_vkbuffer_vkdevicememory_p);
	//e0-image

	//s0-ubo
	vkDestroyBuffer(vkdevice, m_nali_g_ubo_vkbuffer_p[0], VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, m_nali_g_ubo_vkdevicememory_p[0], VK_NULL_HANDLE);
	free(m_nali_g_ubo_vkbuffer_p);
	free(m_nali_g_ubo_vkdevicememory_p);
	//e0-ubo

	// free(nali_g_data_void_p);
}

//from file
void lc_setVkVertexInputBindingDescription(VkVertexInputBindingDescription *vkvertexinputbindingdescription_p)
{
	vkvertexinputbindingdescription_p[0] = (VkVertexInputBindingDescription)
	{
		.binding = 0,
		// .stride = sizeof(float) * 2 + sizeof(float) * 3,
		.stride = sizeof(float) * 2 + sizeof(float) * 2,
		// .stride = sizeof(float) * 2 + sizeof(int16_t) * 2,
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
		// .format = VK_FORMAT_R32G32B32_SFLOAT,
		.format = VK_FORMAT_R32G32_SFLOAT,
		// .format = VK_FORMAT_R16G16_SINT,
		.offset = sizeof(float) * 2
	};
}

void lc_setVkDescriptorSetLayout(VkDescriptorSetLayout *vkdescriptorsetlayout_p)
{
	vk_makeDescriptorSetLayout
	(
		m_device,
		(VkDescriptorSetLayoutBinding[])
		{
			{
				.binding = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,//VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC
				.pImmutableSamplers = VK_NULL_HANDLE,
				.stageFlags = VK_SHADER_STAGE_VERTEX_BIT//VK_SHADER_STAGE_VERTEX_BIT VK_SHADER_STAGE_FRAGMENT_BIT
			},
			{
				.binding = 1,
				.descriptorCount = 1,
				//sampler VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
				//image2d VK_DESCRIPTOR_TYPE_STORAGE_IMAGE
				.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
				.pImmutableSamplers = VK_NULL_HANDLE,
				.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
			}
		},
		2,
		vkdescriptorsetlayout_p
	);
}

void lc_setVkDescriptorPoolSize(VkDescriptorPoolSize *vkdescriptorpoolsize_p)
{
	vkdescriptorpoolsize_p[0] = (VkDescriptorPoolSize)
	{
		.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		.descriptorCount = 1
	};
	vkdescriptorpoolsize_p[1] = (VkDescriptorPoolSize)
	{
		//image2d
		// .type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
		//sampler
		.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		.descriptorCount = 1
	};
}

void lc_setVkWriteDescriptorSet(VkDescriptorSet vkdescriptorset, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkDescriptorImageInfo *vkdescriptorimageinfo_p, VkWriteDescriptorSet *vkwritedescriptorset_p)
{
	*vkdescriptorbufferinfo_p = (VkDescriptorBufferInfo)
	{
		.buffer = m_nali_g_ubo_vkbuffer_p[0],
		.offset = 0,
		// .range = m_nali_g_ubo_vkdevicesize_p[0]
		.range = sizeof(nali_v_uniform_float_array)
	};
	vk_setVkWriteDescriptorSet(m_device, 0, VK_NULL_HANDLE, vkdescriptorbufferinfo_p, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p);
	*vkdescriptorimageinfo_p = (VkDescriptorImageInfo)
	{
		//sampler VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
		//image2d VK_IMAGE_LAYOUT_GENERAL
		.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		.imageView = m_nali_g_image_vkimageview_p[0],
		.sampler = m_nali_g_image_vksampler_p[0]
		// .sampler = VK_NULL_HANDLE
	};
	vk_setVkWriteDescriptorSet(m_device, 1, vkdescriptorimageinfo_p, VK_NULL_HANDLE, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, vkdescriptorset, vkwritedescriptorset_p + 1);
	// *vkdescriptorbufferinfo_p = (VkDescriptorBufferInfo)
	// {
	// 	.buffer = ,
	// 	.offset = 0,
	// 	.range = 
	// };
	// vk_setVkWriteDescriptorSet(m_device, 2, VK_NULL_HANDLE, vkdescriptorbufferinfo_p, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset, vkwritedescriptorset_p + 2);
}