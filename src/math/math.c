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
	//auto \0
	char* char_p = malloc(strlen(str1) + strlen(str2) + 1);

	strcpy(char_p, str1);
	strcat(char_p, str2);

	return char_p;
}

//abs(number)
uint32_t math_length(uint32_t number)
{
	if (number == 0) return 1;
	return (uint32_t)log10(number) + 1;
}

char* math_get(uint32_t number)
{
	//auto \0
	char* c_p = malloc(sizeof(char) * math_length(number) + 1);
	sprintf(c_p, "%u", number);
	return c_p;
}
