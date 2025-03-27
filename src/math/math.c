// char *math_combine(const char *str1, const char *str2)
// {
// 	//auto \0
// 	char *char_p = malloc(strlen(str1) + strlen(str2) + 1);

// 	strcpy(char_p, str1);
// 	strcat(char_p, str2);

// 	return char_p;
// }

//abs(number)
uint32_t math_length(uint32_t number)
{
	if (number == 0) return 1;
	return (uint32_t)log10(number) + 1;
}

uint32_t math_mipmap(uint32_t width, uint32_t height)
{
	uint32_t max_dimension = (width > height) ? width : height;
	return (uint32_t)(log2(max_dimension)) + 1;
}

// char *math_get(uint32_t number)
// {
// 	//auto \0
// 	char *c_p = malloc(sizeof(char) * math_length(number) + 1);
// 	sprintf(c_p, "%u", number);
// 	return c_p;
// }

// void math_set(uint32_t number, char *c_p)
// {
// 	sprintf(c_p, "%u", number);
// }