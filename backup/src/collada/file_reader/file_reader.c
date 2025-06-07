char file_reader_match(FILE *file_p, const char *mchar_p[], const uint32_t size)
{
	char *char_p[size];
	for (uint32_t i = 0; i < size; ++i)
	{
		char_p[i] = malloc(sizeof(char));
		char_p[i][0] = '\0';
	}
	uint32_t char_index[size];
	memset(char_index, 0, size * sizeof(uint32_t));

	char _char;
	while ((_char = fgetc(file_p)))
	{
		for (uint32_t i = 0; i < size; ++i)
		{
			if (_char == mchar_p[i][char_index[i]])
			{
				char_p[i] = realloc(char_p[i], char_index[i] + 1 + 1);
				char_p[i][char_index[i]] = _char;
				char_p[i][char_index[i]++ + 1] = '\0';
			}
			else
			{
				char_p[i] = realloc(char_p[i], sizeof(char));
				char_p[i][0] = '\0';
				char_index[i] = 0;
			}

			if (!strcmp(mchar_p[i], char_p[i]))
			{
				for (uint32_t l = 0; l < size; ++l)
				{
					free(char_p[l]);
				}
				return i;
			}
		}
	}

	NALI_D_LOG("file_reader_match -1")
	return -1;
}

char **file_reader_char_p(FILE *file_p, const char *f_char_p, const char *e_char_p, char **char_p, uint32_t *size)
{
	char *c_p = malloc(sizeof(char));
	c_p[0] = '\0';
	uint32_t c_index = 0;

	char *sf_char_p = malloc(sizeof(char));
	sf_char_p[0] = '\0';
	uint32_t sf_index = 0;

	char *se_char_p = malloc(sizeof(char));
	se_char_p[0] = '\0';
	uint32_t se_index = 0;

	char _char;
	while ((_char = fgetc(file_p)))
	{
		char write = 1;
		if (_char == f_char_p[sf_index])
		{
			sf_char_p = realloc(sf_char_p, sf_index + 1 + 1);
			sf_char_p[sf_index] = _char;
			sf_char_p[sf_index++ + 1] = '\0';
			write = 0;
		}

		if (_char == e_char_p[se_index])
		{
			se_char_p = realloc(se_char_p, se_index + 1 + 1);
			se_char_p[se_index] = _char;
			se_char_p[se_index++ + 1] = '\0';
			write = 0;
		}

		if (write)
		{
			sf_char_p = realloc(sf_char_p, sizeof(char));
			sf_char_p[0] = '\0';
			sf_index = 0;

			se_char_p = realloc(se_char_p, sizeof(char));
			se_char_p[0] = '\0';
			se_index = 0;

			c_p = realloc(c_p, c_index + 1 + 1);
			c_p[c_index] = _char;
			c_p[c_index++ + 1] = '\0';
		}

		if (!strcmp(f_char_p, sf_char_p))
		{
			char_p = realloc(char_p, (*size + 1) * sizeof(char*));
			size_t length = c_index + 1 + 1;
			char_p[*size] = malloc(length);
			memcpy(char_p[*size], c_p, length);
			++*size;

			c_p = realloc(c_p, sizeof(char));
			c_p[0] = '\0';
			c_index = 0;
		}

		if (!strcmp(e_char_p, se_char_p))
		{
			if (c_index != 0)
			{
				char_p = realloc(char_p, (*size + 1) * sizeof(char*));
				size_t length = c_index + 1 + 1;
				char_p[*size] = malloc(length);
				memcpy(char_p[*size], c_p, length);
				++*size;
			}

			free(sf_char_p);
			free(se_char_p);
			free(c_p);

			return char_p;
		}
	}

	NALI_D_LOG("file_reader_char_p -1")
	return char_p;
}

float *file_reader_float(FILE *file_p, const char *e_char_p, float *float_p, uint32_t *size)
{
	char *n_char_p = malloc(sizeof(char));//'\0'
	n_char_p[0] = '\0';
	uint32_t n_index = 0;

	char *se_char_p = malloc(sizeof(char));
	se_char_p[0] = '\0';
	uint32_t se_index = 0;

	char _char;
	while ((_char = fgetc(file_p)))
	{
		if (_char == e_char_p[se_index])
		{
			se_char_p = realloc(se_char_p, se_index + 1 + 1);
			se_char_p[se_index] = _char;
			se_char_p[se_index++ + 1] = '\0';
		}
		else
		{
			se_char_p = realloc(se_char_p, sizeof(char));
			se_char_p[0] = '\0';
			se_index = 0;

			if (_char == ' ')
			{
				float_p = realloc(float_p, (*size + 1) * sizeof(float));
				float_p[*size] = atof(n_char_p);
				++*size;

				n_char_p = realloc(n_char_p, sizeof(char));
				n_char_p[0] = '\0';
				n_index = 0;
			}
			else
			{
				n_char_p = realloc(n_char_p, n_index + 1 + 1);
				n_char_p[n_index] = _char;
				n_char_p[n_index++ + 1] = '\0';
			}
		}

		if (!strcmp(e_char_p, se_char_p))
		{
			if (n_index != 0)
			{
				float_p = realloc(float_p, (*size + 1) * sizeof(float));
				float_p[*size] = atof(n_char_p);
				++*size;
			}

			free(se_char_p);
			free(n_char_p);

			return float_p;
		}
	}

	NALI_D_LOG("file_reader_float -1")
	return float_p;
}

int32_t *file_reader_int(FILE *file_p, const char *e_char_p, int32_t *int_p, uint32_t *size)
{
	char *n_char_p = malloc(sizeof(char));
	n_char_p[0] = '\0';
	uint32_t n_index = 0;

	// char f_char[sizeof(int)];
	char *se_char_p = malloc(sizeof(char));
	se_char_p[0] = '\0';
	uint32_t se_index = 0;

	// // Hexadecimal (base 16)
	// num = strtol(str, &endptr, 16);
	// printf("Hexadecimal (base 16): %d\n", num);

	// while (fgets(&f_int, sizeof(int), file_p))
	// char c = 0;
	// while (fgets(&f_char[c], sizeof(char), file_p))
	char _char;
	while ((_char = fgetc(file_p)))
	{
		if (_char == e_char_p[se_index])
		{
			se_char_p = realloc(se_char_p, se_index + 1 + 1);
			se_char_p[se_index] = _char;
			se_char_p[se_index++ + 1] = '\0';
		}
		else
		{
			se_char_p = realloc(se_char_p, sizeof(char));
			se_char_p[0] = '\0';
			se_index = 0;

			if (_char == ' ')
			{
				int_p = realloc(int_p, (*size + 1) * sizeof(int32_t));
				int_p[*size] = atoi(n_char_p);
				++*size;

				n_char_p = realloc(n_char_p, sizeof(char));
				n_char_p[0] = '\0';
				n_index = 0;
			}
			else
			{
				n_char_p = realloc(n_char_p, n_index + 1 + 1);
				n_char_p[n_index] = _char;
				n_char_p[n_index++ + 1] = '\0';
			}
		}

		// ++c;
		// c %= sizeof(int);
		// fseek(file, 1, SEEK_CUR);
		if (!strcmp(e_char_p, se_char_p))
		{
			if (n_index != 0)
			{
				int_p = realloc(int_p, (*size + 1) * sizeof(int32_t));
				int_p[*size] = atoi(n_char_p);
				++*size;
			}

			free(se_char_p);
			free(n_char_p);

			return int_p;
		}
	}

	NALI_D_LOG("file_reader_int -1")
	return int_p;
}

collada_Bone *file_reader_node(FILE *file_p, collada_Bone *collada_bone_p, uint32_t *size)
{
	collada_bone_p = realloc(collada_bone_p, (*size + 1) * sizeof(collada_Bone));
	collada_bone_p[*size].name_size = 0;
	collada_bone_p[*size].name_p = malloc(0);
	file_reader_match(file_p, (const char*[]){"name=\""}, 1);
	collada_bone_p[*size].name_p = file_reader_char_p(file_p, "\t", "\"", collada_bone_p[*size].name_p, &collada_bone_p[*size].name_size);
	file_reader_match(file_p, (const char*[]){"type=\"JOINT\">\n"}, 1);
	collada_bone_p[*size].name_p = file_reader_char_p(file_p, "\t", "<matrix sid=\"transform\">", collada_bone_p[*size].name_p, &collada_bone_p[*size].name_size);
	collada_bone_p[*size].visual_size = 0;
	collada_bone_p[*size].visual_p = malloc(0);
	collada_bone_p[*size].visual_p = file_reader_float(file_p, "</matrix>", collada_bone_p[*size].visual_p, &collada_bone_p[*size].visual_size);
	++*size;
	return collada_bone_p;
}
