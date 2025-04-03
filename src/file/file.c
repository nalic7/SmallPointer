void *file_read(const char *name_char_p, long *size_p)
{
	FILE *file = fopen(name_char_p, "rb");
	nali_log("fopen %p", file)

	nali_info("fseek %d", fseek(file, 0, SEEK_END))

	nali_info("ftell %ld", *size_p = ftell(file))

	nali_info("fseek %d", fseek(file, 0, SEEK_SET))

	void *p = malloc(*size_p);

	nali_info("fread %ld", fread(p, *size_p, 1, file))

	nali_info("fclose %d", fclose(file))
	return p;
}