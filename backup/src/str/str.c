void m_str_p(char **data_p, const char *e_p[], uint8_t bl)
{
	while (1)
	{
		for (uint32_t i = 0; i < bl; ++i)
			if (strstr(*data_p, e_p[i]))
				return;
		++*data_p;
	}
}

void m_str_c2c(char **data_p, char **c_p, uint32_t *bl_p, const char *s_p, const char *e_p)
{
	uint32_t s = 0, e = 0;

	while (1)
	{
		if (strstr(*data_p + e, e_p))
		{
			*c_p = realloc(*c_p, *bl_p * sizeof(float) + sizeof(float));
			memcpy(*c_p, data_p + s, e);
			*bl_p += e;
			return;
		}

		if (strstr(*data_p + e, s_p))
		{
			*c_p = realloc(*c_p, *bl_p * sizeof(float) + sizeof(float));
			memcpy(*c_p, data_p + s, e);
			*bl_p += e;

			s += e;
			e = 0;
		}
		else
			++e;

		++*data_p;
	}
}

void m_str_c2f(char **data_p, float **w_p, uint32_t *bl_p, const char *s_p, const char *e_p)
{
	uint32_t s = 0, e = 0;

	while (1)
	{
		if (strstr(*data_p + e, e_p))
		{
			*w_p = realloc(*w_p, *bl_p * sizeof(float) + sizeof(float));
			(*w_p)[*bl_p++] = atof(*data_p + s);
			return;
		}

		if (strstr(*data_p + e, s_p))
		{
			*w_p = realloc(*w_p, *bl_p * sizeof(float) + sizeof(float));
			(*w_p)[*bl_p++] = atof(*data_p + s);

			s += e;
			e = 0;
		}
		else
			++e;

		++*data_p;
	}
}

void m_str_c2i(char **data_p, int32_t **w_p, uint32_t *bl_p, const char *s_p, const char *e_p)
{
	uint32_t s = 0, e = 0;

	while (1)
	{
		if (strstr(*data_p + e, e_p))
		{
			*w_p = realloc(*w_p, *bl_p * sizeof(float) + sizeof(float));
			(*w_p)[*bl_p++] = atoi(*data_p + s);
			return;
		}

		if (strstr(*data_p + e, s_p))
		{
			*w_p = realloc(*w_p, *bl_p * sizeof(float) + sizeof(float));
			(*w_p)[*bl_p++] = atoi(*data_p + s);

			s += e;
			e = 0;
		}
		else
			++e;

		++*data_p;
	}
}