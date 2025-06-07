void fp_read(const char *name_char_p, long *size_p)
{
	FILE *file_p = fopen(name_char_p, "rb");
	NALI_D_LOG("fopen %p", file_p)

	NALI_D_INFO("fseek %d", fseek(file_p, 0, SEEK_END))
	NALI_D_INFO("ftell %ld", *size_p = ftell(file_p))
	NALI_D_INFO("fseek %d", fseek(file_p, 0, SEEK_SET))

	uint8_t *head_p = malloc(sizeof(uint8_t) * 8 + 1);
	head_p[sizeof(uint8_t) * 8] = '\0';
	NALI_D_INFO("fread %ld", fread(head_p, sizeof(uint8_t), 8, file_p))
	NALI_D_LOG("head %s", head_p)//�PNG
	free(head_p);

	uint32_t chunk_size;
	NALI_D_INFO("fread %ld", fread(head_p, sizeof(uint32_t), 1, file_p))
	// MATH_4E2S(chunk_size, (uint8_t *)&chunk_size, 0)
	NALI_D_LOG("chunk_size %d", chunk_size)

	uint8_t *chunk_type_p = malloc(sizeof(uint8_t) * 4 + 1);
	chunk_type_p[sizeof(uint8_t) * 4] = '\0';
	NALI_D_INFO("fread %ld", fread(chunk_type_p, sizeof(uint8_t), 4, file_p))
	NALI_D_LOG("chunk_type %s", chunk_type_p)

	if (!strcmp(chunk_type_p, "IHDR"))
	{
		uint32_t width;
		NALI_D_INFO("fread %ld", fread(&width, sizeof(uint32_t), 1, file_p))
		MATH_4E2S(width, (uint8_t *)&width, 0)
		NALI_D_LOG("width %d", width)

		uint32_t height;
		NALI_D_INFO("fread %ld", fread(&height, sizeof(uint32_t), 1, file_p))
		MATH_4E2S(height, (uint8_t *)&height, 0)
		NALI_D_LOG("height %d", height)

		//bit_depth
		uint8_t color_size;
		NALI_D_INFO("fread %ld", fread(&color_size, sizeof(uint8_t), 1, file_p))
		NALI_D_LOG("color_size %d", color_size)

		//6 RGBA
		uint8_t color_type;
		NALI_D_INFO("fread %ld", fread(&color_type, sizeof(uint8_t), 1, file_p))
		NALI_D_LOG("color_type %d", color_type)

		uint8_t compress_type;
		NALI_D_INFO("fread %ld", fread(&compress_type, sizeof(uint8_t), 1, file_p))
		NALI_D_LOG("compress_type %d", compress_type)

		uint8_t filter;
		NALI_D_INFO("fread %ld", fread(&filter, sizeof(uint8_t), 1, file_p))
		NALI_D_LOG("filter %d", filter)

		//interlace
		uint8_t enlacement;
		NALI_D_INFO("fread %ld", fread(&enlacement, sizeof(uint8_t), 1, file_p))
		NALI_D_LOG("enlacement %d", enlacement)
	}

	uint32_t data_size;
	NALI_D_INFO("fread %ld", fread(head_p, sizeof(uint32_t), 1, file_p))
	MATH_4E2S(data_size, (uint8_t *)&data_size, 0)
	NALI_D_LOG("data_size %d", data_size)

	uint8_t *test = malloc(40 + 1);
	test[40] = '\0';
	NALI_D_INFO("fread %ld", fread(test, sizeof(uint8_t), 40, file_p))
	NALI_D_LOG("test %s", test)
	free(test);

	free(chunk_type_p);
	NALI_D_INFO("fclose %d", fclose(file_p))
}