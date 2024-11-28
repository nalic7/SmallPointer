char file_reader_match(FILE* file_ptr, const char* mchar_ptr[], const uint32_t size)
{
	char* char_ptr[size];
	for (uint32_t i = 0; i < size; ++i)
	{
		char_ptr[i] = malloc(sizeof(char));
		char_ptr[i][sizeof(char) - 1] = '\0';
	}
	uint32_t char_index[size];
	memset(char_index, 0, size * sizeof(uint32_t));

	char _char;
	while ((_char = fgetc(file_ptr)))
	{
		for (uint32_t i = 0; i < size; ++i)
		{
			if (_char == mchar_ptr[i][char_index[i]])
			{
				char_ptr[i] = realloc(char_ptr[i], (char_index[i] + sizeof(char) + 1) * sizeof(char));
				char_ptr[i][char_index[i]] = _char;
				char_ptr[i][char_index[i]++ + 1] = '\0';
			}
			else
			{
				char_ptr[i] = realloc(char_ptr[i], sizeof(char));
				char_ptr[i][sizeof(char) - 1] = '\0';
				char_index[i] = 0;
			}

			if (strcmp(mchar_ptr[i], char_ptr[i]) == 0)
			{
				for (uint32_t l = 0; l < size; ++l)
				{
					free(char_ptr[l]);
				}
				return i;
			}
		}
	}

	error("file_reader_match")
	return -1;
}

char** file_reader_char_ptr(FILE* file_ptr, const char* f_char_ptr, const char* e_char_ptr, char** char_ptr, uint32_t* size)
{
	char* c_ptr = malloc(sizeof(char));
	c_ptr[sizeof(char) - 1] = '\0';
	uint32_t c_index = 0;

	char* sf_char_ptr = malloc(sizeof(char));
	sf_char_ptr[sizeof(char) - 1] = '\0';
	uint32_t sf_index = 0;

	char* se_char_ptr = malloc(sizeof(char));
	se_char_ptr[sizeof(char) - 1] = '\0';
	uint32_t se_index = 0;

	char _char;
	while ((_char = fgetc(file_ptr)))
	{
		char write = 1;
		if (_char == f_char_ptr[sf_index])
		{
			sf_char_ptr = realloc(sf_char_ptr, (sf_index + sizeof(char) + 1) * sizeof(char));
			sf_char_ptr[sf_index] = _char;
			sf_char_ptr[sf_index++ + 1] = '\0';
			write = 0;
		}

		if (_char == e_char_ptr[se_index])
		{
			se_char_ptr = realloc(se_char_ptr, (se_index + sizeof(char) + 1) * sizeof(char));
			se_char_ptr[se_index] = _char;
			se_char_ptr[se_index++ + 1] = '\0';
			write = 0;
		}

		if (write)
		{
			sf_char_ptr = realloc(sf_char_ptr, sizeof(char));
			sf_char_ptr[sizeof(char) - 1] = '\0';
			sf_index = 0;

			se_char_ptr = realloc(se_char_ptr, sizeof(char));
			se_char_ptr[sizeof(char) - 1] = '\0';
			se_index = 0;

			c_ptr = realloc(c_ptr, (c_index + sizeof(char) + 1) * sizeof(char));
			c_ptr[c_index] = _char;
			c_ptr[c_index++ + 1] = '\0';
		}

		if (strcmp(f_char_ptr, sf_char_ptr) == 0)
		{
			char_ptr = realloc(char_ptr, (*size + 1) * sizeof(char*));
			size_t length = (c_index + sizeof(char) + 1) * sizeof(char);
			char_ptr[*size] = malloc(length);
			memcpy(char_ptr[*size], c_ptr, length);
			++*size;

			c_ptr = realloc(c_ptr, sizeof(char));
			c_ptr[sizeof(char) - 1] = '\0';
			c_index = 0;
		}

		if (strcmp(e_char_ptr, se_char_ptr) == 0)
		{
			if (c_index != 0)
			{
				char_ptr = realloc(char_ptr, (*size + 1) * sizeof(char*));
				size_t length = (c_index + sizeof(char) + 1) * sizeof(char);
				char_ptr[*size] = malloc(length);
				memcpy(char_ptr[*size], c_ptr, length);
				++*size;
			}

			free(sf_char_ptr);
			free(se_char_ptr);
			free(c_ptr);

			return char_ptr;
		}
	}

	error("file_reader_char_ptr")
	return char_ptr;
}

float* file_reader_float(FILE* file_ptr, const char* e_char_ptr, float* float_ptr, uint32_t* size)
{
	char* n_char_ptr = malloc(sizeof(char));//'\0'
	n_char_ptr[sizeof(char) - 1] = '\0';
	uint32_t n_index = 0;

	char* se_char_ptr = malloc(sizeof(char));
	se_char_ptr[sizeof(char) - 1] = '\0';
	uint32_t se_index = 0;

	char _char;
	while ((_char = fgetc(file_ptr)))
	{
		if (_char == e_char_ptr[se_index])
		{
			se_char_ptr = realloc(se_char_ptr, (se_index + sizeof(char) + 1) * sizeof(char));
			se_char_ptr[se_index] = _char;
			se_char_ptr[se_index++ + 1] = '\0';
		}
		else
		{
			se_char_ptr = realloc(se_char_ptr, sizeof(char));
			se_char_ptr[sizeof(char) - 1] = '\0';
			se_index = 0;

			if (_char == ' ')
			{
				float_ptr = realloc(float_ptr, (*size + 1) * sizeof(float));
				float_ptr[*size] = atof(n_char_ptr);
				++*size;

				n_char_ptr = realloc(n_char_ptr, sizeof(char));
				n_char_ptr[sizeof(char) - 1] = '\0';
				n_index = 0;
			}
			else
			{
				n_char_ptr = realloc(n_char_ptr, (n_index + sizeof(char) + 1) * sizeof(char));
				n_char_ptr[n_index] = _char;
				n_char_ptr[n_index++ + 1] = '\0';
			}
		}

		if (strcmp(e_char_ptr, se_char_ptr) == 0)
		{
			if (n_index != 0)
			{
				float_ptr = realloc(float_ptr, (*size + 1) * sizeof(float));
				float_ptr[*size] = atof(n_char_ptr);
				++*size;
			}

			free(se_char_ptr);
			free(n_char_ptr);

			return float_ptr;
		}
	}

	error("file_reader_float")
	return float_ptr;
}

int32_t* file_reader_int(FILE* file_ptr, const char* e_char_ptr, int32_t* int_ptr, uint32_t* size)
{
	char* n_char_ptr = malloc(sizeof(char));
	n_char_ptr[sizeof(char) - 1] = '\0';
	uint32_t n_index = 0;

	// char f_char[sizeof(int)];
	char* se_char_ptr = malloc(sizeof(char));
	se_char_ptr[sizeof(char) - 1] = '\0';
	uint32_t se_index = 0;

	// // Hexadecimal (base 16)
	// num = strtol(str, &endptr, 16);
	// printf("Hexadecimal (base 16): %d\n", num);

	// while (fgets(&f_int, sizeof(int), file_ptr))
	// char c = 0;
	// while (fgets(&f_char[c], sizeof(char), file_ptr))
	char _char;
	while ((_char = fgetc(file_ptr)))
	{
		if (_char == e_char_ptr[se_index])
		{
			se_char_ptr = realloc(se_char_ptr, (se_index + sizeof(char) + 1) * sizeof(char));
			se_char_ptr[se_index] = _char;
			se_char_ptr[se_index++ + 1] = '\0';
		}
		else
		{
			se_char_ptr = realloc(se_char_ptr, sizeof(char));
			se_char_ptr[sizeof(char) - 1] = '\0';
			se_index = 0;

			if (_char == ' ')
			{
				int_ptr = realloc(int_ptr, (*size + 1) * sizeof(int32_t));
				int_ptr[*size] = atoi(n_char_ptr);
				++*size;

				n_char_ptr = realloc(n_char_ptr, sizeof(char));
				n_char_ptr[sizeof(char) - 1] = '\0';
				n_index = 0;
			}
			else
			{
				n_char_ptr = realloc(n_char_ptr, (n_index + sizeof(char) + 1) * sizeof(char));
				n_char_ptr[n_index] = _char;
				n_char_ptr[n_index++ + 1] = '\0';
			}
		}

		// ++c;
		// c %= sizeof(int);
		// fseek(file, 1, SEEK_CUR);
		if (strcmp(e_char_ptr, se_char_ptr) == 0)
		{
			if (n_index != 0)
			{
				int_ptr = realloc(int_ptr, (*size + 1) * sizeof(int32_t));
				int_ptr[*size] = atoi(n_char_ptr);
				++*size;
			}

			free(se_char_ptr);
			free(n_char_ptr);

			return int_ptr;
		}
	}

	error("file_reader_int")
	return int_ptr;
}

collada_Bone* file_reader_node(FILE* file_ptr, collada_Bone* collada_bone_ptr, uint32_t* size)
{
	collada_bone_ptr = realloc(collada_bone_ptr, (*size + 1) * sizeof(collada_Bone));
	collada_bone_ptr[*size].name_size = 0;
	collada_bone_ptr[*size].name_ptr = malloc(0);
	file_reader_match(file_ptr, (const char*[]){"name=\""}, 1);
	collada_bone_ptr[*size].name_ptr = file_reader_char_ptr(file_ptr, "\t", "\"", collada_bone_ptr[*size].name_ptr, &collada_bone_ptr[*size].name_size);
	file_reader_match(file_ptr, (const char*[]){"type=\"JOINT\">\n"}, 1);
	collada_bone_ptr[*size].name_ptr = file_reader_char_ptr(file_ptr, "\t", "<matrix sid=\"transform\">", collada_bone_ptr[*size].name_ptr, &collada_bone_ptr[*size].name_size);
	collada_bone_ptr[*size].visual_size = 0;
	collada_bone_ptr[*size].visual_ptr = malloc(0);
	collada_bone_ptr[*size].visual_ptr = file_reader_float(file_ptr, "</matrix>", collada_bone_ptr[*size].visual_ptr, &collada_bone_ptr[*size].visual_size);
	++*size;
	return collada_bone_ptr;
}
