float math_radian(float degree)
{
	return degree * M_PI / 180.0F;
}

float math_degree(float radian)
{
	return radian * 180.0F / M_PI;
}

char* math_combine(const char* str1, const char* str2)
{
	size_t len1 = strlen(str1);
	size_t len2 = strlen(str2);
	
	char *char_ptr = malloc(len1 + len2 + 1);

	strcpy(char_ptr, str1);
	strcat(char_ptr, str2);

	return char_ptr;
}

uint32_t math_n_c_size(int number)
{
	if (number == 0) return 1;
	return (uint32_t)log10(abs(number)) + 1;
}
