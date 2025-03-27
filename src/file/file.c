void *file_read(const char *name_char_p, long *size_p)
{
	FILE *file = fopen(name_char_p, "rb");
	
	if (file == NULL)
	{
		error("fopen");
	}

	fseek(file, 0, SEEK_END);

	*size_p = ftell(file);
	if (*size_p == -1)
	{
		error("ftell");
	}

	fseek(file, 0, SEEK_SET);

	void *p = malloc(*size_p);
	if (p == NULL)
	{
		error("malloc");
	}

	size_t read = fread(p, *size_p, 1, file);
	// if (read != *size_p)
	// {
	// 	error("fread");
	// }

	fclose(file);
	return p;
}