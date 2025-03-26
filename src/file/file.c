uint32_t *file_uint32_t(const char *filename, uint32_t *file_size)
{
	FILE *file = fopen(filename, "rb");
	
	if (file == NULL)
	{
		error("fopen");
	}

	fseek(file, 0, SEEK_END);

	*file_size = ftell(file);
	if (*file_size == -1)
	{
		error("ftell");
	}

	fseek(file, 0, SEEK_SET);

	size_t size = *file_size / sizeof(uint32_t);
	if (*file_size % sizeof(uint32_t) != 0)
	{
		error("uint32_t");
	}

	uint32_t *uint32_t_p = (uint32_t*)malloc(*file_size);
	if (uint32_t_p == NULL)
	{
		error("malloc");
	}

	size_t bytesRead = fread(uint32_t_p, sizeof(uint32_t), size, file);
	if (bytesRead != size)
	{
		error("fread");
	}

	fclose(file);
	return uint32_t_p;
}