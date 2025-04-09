void fp_read(const char *name_char_p, long *size_p)
{
	FILE *file_p = fopen(name_char_p, "rb");
	nali_log("fopen %p", file_p)

	nali_info("fseek %d", fseek(file_p, 0, SEEK_END))
	nali_info("ftell %ld", *size_p = ftell(file_p))
	nali_info("fseek %d", fseek(file_p, 0, SEEK_SET))

	uint8_t *head_p = malloc(sizeof(uint8_t) * 8 + 1);
	head_p[sizeof(uint8_t) * 8] = '\0';
	nali_info("fread %ld", fread(head_p, sizeof(uint8_t), 8, file_p))
	nali_log("head %s", head_p)//�PNG
	free(head_p);

	uint32_t chunk_size;
	nali_info("fread %ld", fread(head_p, sizeof(uint32_t), 1, file_p))
	// MATH_4E2S(chunk_size, (uint8_t *)&chunk_size, 0)
	nali_log("chunk_size %d", chunk_size)

	uint8_t *chunk_type_p = malloc(sizeof(uint8_t) * 4 + 1);
	chunk_type_p[sizeof(uint8_t) * 4] = '\0';
	nali_info("fread %ld", fread(chunk_type_p, sizeof(uint8_t), 4, file_p))
	nali_log("chunk_type %s", chunk_type_p)

	if (!strcmp(chunk_type_p, "IHDR"))
	{
		uint32_t width;
		nali_info("fread %ld", fread(&width, sizeof(uint32_t), 1, file_p))
		MATH_4E2S(width, (uint8_t *)&width, 0)
		nali_log("width %d", width)

		uint32_t height;
		nali_info("fread %ld", fread(&height, sizeof(uint32_t), 1, file_p))
		MATH_4E2S(height, (uint8_t *)&height, 0)
		nali_log("height %d", height)

		//bit_depth
		uint8_t color_size;
		nali_info("fread %ld", fread(&color_size, sizeof(uint8_t), 1, file_p))
		nali_log("color_size %d", color_size)

		//6 RGBA
		uint8_t color_type;
		nali_info("fread %ld", fread(&color_type, sizeof(uint8_t), 1, file_p))
		nali_log("color_type %d", color_type)

		uint8_t compress_type;
		nali_info("fread %ld", fread(&compress_type, sizeof(uint8_t), 1, file_p))
		nali_log("compress_type %d", compress_type)

		uint8_t filter;
		nali_info("fread %ld", fread(&filter, sizeof(uint8_t), 1, file_p))
		nali_log("filter %d", filter)

		//interlace
		uint8_t enlacement;
		nali_info("fread %ld", fread(&enlacement, sizeof(uint8_t), 1, file_p))
		nali_log("enlacement %d", enlacement)
	}

	uint32_t data_size;
	nali_info("fread %ld", fread(head_p, sizeof(uint32_t), 1, file_p))
	MATH_4E2S(data_size, (uint8_t *)&data_size, 0)
	nali_log("data_size %d", data_size)

	uint8_t *test = malloc(40 + 1);
	test[40] = '\0';
	nali_info("fread %ld", fread(test, sizeof(uint8_t), 40, file_p))
	nali_log("test %s", test)
	free(test);

	free(chunk_type_p);
	nali_info("fclose %d", fclose(file_p))
}