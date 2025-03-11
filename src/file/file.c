uint32_t* file_uint32_t(const char* filename, uint32_t* size)
{
	FILE *file = fopen(filename, "rb");
	
	if (file == NULL)
	{
		error("fopen");
	}

	fseek(file, 0, SEEK_END);

	long file_size = ftell(file);
	if (file_size == -1)
	{
		error("ftell");
	}

	fseek(file, 0, SEEK_SET);

	*size = file_size / sizeof(uint32_t);
	if (file_size % sizeof(uint32_t) != 0)
	{
		error("uint32_t");
	}

	uint32_t* uint32_t_ptr = (uint32_t*)malloc(*size * sizeof(uint32_t));
	if (uint32_t_ptr == NULL)
	{
		error("malloc");
	}

	size_t bytesRead = fread(uint32_t_ptr, sizeof(uint32_t), *size, file);
	if (bytesRead != *size)
	{
		error("fread");
	}

	fclose(file);
	return uint32_t_ptr;
}