static uint32_t thrd = 0;

int main_skin(void* d_name_ptr)
{
	// info("skin %s\n", (char*)name)

	char* n0_ptr = math_combine(C_IN, "/");
	char* n_in_ptr = math_combine(n0_ptr, d_name_ptr);
	free(n0_ptr);
	n0_ptr = math_combine(C_OUT, "/");

	FILE* file_ptr = fopen(n_in_ptr, "r");
	if (!file_ptr)
	{
		error("fopen");
	}

	char* dot_p = strchr(d_name_ptr, '.');

	if (dot_p)
	{
		*dot_p = '\0';
	}

	char* n_out_ptr = math_combine(n0_ptr, d_name_ptr);
	free(n0_ptr);

	collada_Source collada_source =
	{
		.max_bone = -2,
		.is_animated = file_reader_match(file_ptr, (const char*[]){"<library_visual_scenes>", "<library_controllers>"}, 2)
	};

	fseek(file_ptr, 0, SEEK_SET);

	if (collada_source.is_animated)
	{
		file_reader_match(file_ptr, (const char*[]){"<library_animations>"}, 1);

		while (file_reader_match(file_ptr, (const char*[]){"</library_animations>", C_ARMATURE_NAME}, 2))
		{
			++collada_source.max_bone;
		}

		fseek(file_ptr, 0, SEEK_SET);

		file_reader_match(file_ptr, (const char*[]){"<library_animations>"}, 1);
		file_reader_match(file_ptr, (const char*[]){C_ARMATURE_NAME}, 1);
		file_reader_match(file_ptr, (const char*[]){"count=\""}, 1);
		uint32_t temp_size = 0;
		int* int_ptr = malloc(0);
		int_ptr = file_reader_int(file_ptr, "\"", int_ptr, &temp_size);

		collada_source.max_frame = int_ptr[0];
		free(int_ptr);

		fseek(file_ptr, 0, SEEK_SET);

		file_reader_match(file_ptr, (const char*[]){"<library_visual_scenes>"}, 1);
		file_reader_match(file_ptr, (const char*[]){"</matrix>\n"}, 1);

		collada_source.collada_bone_ptr = malloc(0);
		temp_size = 0;
		while (temp_size < collada_source.max_bone)
		{
			collada_source.collada_bone_ptr = file_reader_node(file_ptr, collada_source.collada_bone_ptr, &temp_size);
		}

		collada_source.space_ptr = malloc(collada_source.max_bone * sizeof(uint32_t));
		for (int x = 0; x < collada_source.max_bone; ++x)
		{
			collada_Bone bonedata = collada_source.collada_bone_ptr[x];

			uint32_t value = graphic_reader_count(bonedata.name_ptr[1], ' ');
			collada_source.space_ptr[x] = value;

			graphic_reader_sanitize(bonedata.name_ptr[0]);
		}

		fseek(file_ptr, 0, SEEK_SET);
	}

	file_reader_match(file_ptr, (const char*[]){"<library_geometries>"}, 1);

	{
		collada_source.max_data = 0;
		collada_source.data_ptr = malloc(0);
		collada_source.vertex_size_ptr = malloc(0);
		collada_source.vertex_ptr = malloc(0);
		collada_source.normal_size_ptr = malloc(0);
		collada_source.normal_ptr = malloc(0);
		collada_source.texcoord_size_ptr = malloc(0);
		collada_source.texcoord_ptr = malloc(0);
		collada_source.p_size_ptr = malloc(0);
		collada_source.p_ptr = malloc(0);

		uint32_t v_index = 0;

		char state;
		while ((state = file_reader_match(file_ptr, (const char*[]){"</library_geometries>", "<geometry"}, 2)))
		{
			file_reader_match(file_ptr, (const char*[]){"\""}, 1);
			collada_source.data_ptr = file_reader_char_ptr(file_ptr, "\t", "-", collada_source.data_ptr, &collada_source.max_data);
			graphic_reader_sanitize(collada_source.data_ptr[v_index]);

			size_t fs_size = collada_source.max_data * sizeof(float*);
			size_t is_size = collada_source.max_data * sizeof(int*);
			size_t ui_size = collada_source.max_data * sizeof(uint32_t);

			file_reader_match(file_ptr, (const char*[]){"positions-array"}, 1);
			file_reader_match(file_ptr, (const char*[]){">"}, 1);
			collada_source.vertex_size_ptr = realloc(collada_source.vertex_size_ptr, ui_size);
			collada_source.vertex_size_ptr[v_index] = 0;
			collada_source.vertex_ptr = realloc(collada_source.vertex_ptr, fs_size);
			collada_source.vertex_ptr[v_index] = malloc(0);
			collada_source.vertex_ptr[v_index] = file_reader_float(file_ptr, "</float_array>", collada_source.vertex_ptr[v_index], &collada_source.vertex_size_ptr[v_index]);

			file_reader_match(file_ptr, (const char*[]){"normals-array"}, 1);
			file_reader_match(file_ptr, (const char*[]){">"}, 1);
			collada_source.normal_size_ptr = realloc(collada_source.normal_size_ptr, ui_size);
			collada_source.normal_size_ptr[v_index] = 0;
			collada_source.normal_ptr = realloc(collada_source.normal_ptr, fs_size);
			collada_source.normal_ptr[v_index] = malloc(0);
			collada_source.normal_ptr[v_index] = file_reader_float(file_ptr, "</float_array>", collada_source.normal_ptr[v_index], &collada_source.normal_size_ptr[v_index]);

			file_reader_match(file_ptr, (const char*[]){"map-0-array"}, 1);
			file_reader_match(file_ptr, (const char*[]){">"}, 1);
			collada_source.texcoord_size_ptr = realloc(collada_source.texcoord_size_ptr, ui_size);
			collada_source.texcoord_size_ptr[v_index] = 0;
			collada_source.texcoord_ptr = realloc(collada_source.texcoord_ptr, fs_size);
			collada_source.texcoord_ptr[v_index] = malloc(0);
			collada_source.texcoord_ptr[v_index] = file_reader_float(file_ptr, "</float_array>", collada_source.texcoord_ptr[v_index], &collada_source.texcoord_size_ptr[v_index]);

			file_reader_match(file_ptr, (const char*[]){"<p>"}, 1);
			collada_source.p_size_ptr = realloc(collada_source.p_size_ptr, ui_size);
			collada_source.p_size_ptr[v_index] = 0;
			collada_source.p_ptr = realloc(collada_source.p_ptr, is_size);
			collada_source.p_ptr[v_index] = malloc(0);
			collada_source.p_ptr[v_index] = file_reader_int(file_ptr, "</p>", collada_source.p_ptr[v_index], &collada_source.p_size_ptr[v_index]);
			++v_index;
		}
	}

	if (collada_source.is_animated)
	{
		file_reader_match(file_ptr, (const char*[]){"<library_controllers>"}, 1);

		collada_source.vcount_size_ptr = malloc(0);
		collada_source.vcount_ptr = malloc(0);
		collada_source.weight_size_ptr = malloc(0);
		collada_source.weight_ptr = malloc(0);
		collada_source.v_size_ptr = malloc(0);
		collada_source.v_ptr = malloc(0);

		uint32_t v_index = 0;

		char state;
		while ((state = file_reader_match(file_ptr, (const char*[]){"</library_controllers>", "<controller"}, 2)))
		{
			size_t cs2_size = collada_source.max_data * sizeof(char**);
			size_t fs_size = collada_source.max_data * sizeof(float*);
			size_t is_size = collada_source.max_data * sizeof(int*);
			size_t ui_size = collada_source.max_data * sizeof(uint32_t);

			file_reader_match(file_ptr, (const char*[]){"joints-array"}, 1);
			file_reader_match(file_ptr, (const char*[]){">"}, 1);

			if (v_index == 0)
			{
				uint32_t max_bone = 0;
				collada_source.joint_ptr = malloc(0);
				collada_source.joint_ptr = file_reader_char_ptr(file_ptr, " ", "</Name_array>", collada_source.joint_ptr, &max_bone);

				for (uint32_t j = 0; j < max_bone; ++j)
				{
					graphic_reader_sanitize(collada_source.joint_ptr[j]);
				}

				file_reader_match(file_ptr, (const char*[]){"bind_poses-array"}, 1);
				file_reader_match(file_ptr, (const char*[]){">"}, 1);
				max_bone = 0;
				collada_source.bind_pose_ptr = malloc(0);
				collada_source.bind_pose_ptr = file_reader_float(file_ptr, "</float_array>", collada_source.bind_pose_ptr, &max_bone);
			}

			file_reader_match(file_ptr, (const char*[]){"weights-array"}, 1);
			file_reader_match(file_ptr, (const char*[]){">"}, 1);
			collada_source.weight_size_ptr = realloc(collada_source.weight_size_ptr, ui_size);
			collada_source.weight_size_ptr[v_index] = 0;
			collada_source.weight_ptr = realloc(collada_source.weight_ptr, fs_size);
			collada_source.weight_ptr[v_index] = 0;
			collada_source.weight_ptr[v_index] = file_reader_float(file_ptr, "</float_array>", collada_source.weight_ptr[v_index], &collada_source.weight_size_ptr[v_index]);

			file_reader_match(file_ptr, (const char*[]){"<vcount>"}, 1);
			collada_source.vcount_size_ptr = realloc(collada_source.vcount_size_ptr, ui_size);
			collada_source.vcount_size_ptr[v_index] = 0;
			collada_source.vcount_ptr = realloc(collada_source.vcount_ptr, is_size);
			collada_source.vcount_ptr[v_index] = 0;
			collada_source.vcount_ptr[v_index] = file_reader_int(file_ptr, "</vcount>", collada_source.vcount_ptr[v_index], &collada_source.vcount_size_ptr[v_index]);

			file_reader_match(file_ptr, (const char*[]){"<v>"}, 1);
			collada_source.v_size_ptr = realloc(collada_source.v_size_ptr, ui_size);
			collada_source.v_size_ptr[v_index] = 0;
			collada_source.v_ptr = realloc(collada_source.v_ptr, is_size);
			collada_source.v_ptr[v_index] = 0;
			collada_source.v_ptr[v_index] = file_reader_int(file_ptr, "</v>", collada_source.v_ptr[v_index], &collada_source.v_size_ptr[v_index]);
			++v_index;
		}

		file_reader_match(file_ptr, (const char*[]){"name=\""}, 1);
		collada_source.armature_size = 0;
		collada_source.armature_ptr = malloc(0);
		collada_source.armature_ptr = file_reader_char_ptr(file_ptr, "\t", "\"", collada_source.armature_ptr, &collada_source.armature_size);

		file_reader_match(file_ptr, (const char*[]){"</animation>"}, 1);

		// collada_source.time_size_ptr = 0;
		// collada_source.time_ptr = malloc(0);
		collada_source.transform_size = 0;
		collada_source.transform_ptr = malloc(0);
		collada_source.v_bone_size = 0;
		collada_source.v_bone_ptr = malloc(0);

		for (int l = 0; l < collada_source.max_bone; ++l)
		{
			file_reader_match(file_ptr, (const char*[]){"<float_array"}, 1);
			// file_reader_match(file_ptr, (const char*[]){">"}, 1);
			// collada_source.time_ptr = file_reader_float(file_ptr, "</float_array>", collada_source.time_ptr, &collada_source.time_size_ptr);

			file_reader_match(file_ptr, (const char*[]){"<float_array"}, 1);
			file_reader_match(file_ptr, (const char*[]){">"}, 1);
			collada_source.transform_ptr = file_reader_float(file_ptr, "</float_array>", collada_source.transform_ptr, &collada_source.transform_size);

			file_reader_match(file_ptr, (const char*[]){"target=\""}, 1);
			file_reader_match(file_ptr, (const char*[]){collada_source.armature_ptr[0]}, 1);
			file_reader_match(file_ptr, (const char*[]){"_"}, 1);
			collada_source.v_bone_ptr = file_reader_char_ptr(file_ptr, "\t", "/", collada_source.v_bone_ptr, &collada_source.v_bone_size);
			graphic_reader_sanitize(collada_source.v_bone_ptr[collada_source.v_bone_size - 1]);
		}

		graphic_reader_makeBones(&collada_source);
	}

	if (collada_source.is_animated && C_FIX_ANIMATED)
	{
		graphic_reader_fixAnimation(&collada_source);
	}

	graphic_reader_mix(&collada_source);

	collada_source.max_joint_ptr = malloc(sizeof(uint8_t) * collada_source.max_data);
	if (collada_source.is_animated)
	{
		for (uint32_t m = 0; m < collada_source.max_data; ++m)
		{
			collada_source.max_joint_ptr[m] = 0;
			uint32_t collada_pack_size = collada_source.collada_pack_size_ptr[m];
			for (uint32_t p = 0; p < collada_pack_size; ++p)
			{
				collada_Pack collada_pack = collada_source.collada_pack_ptr[m][p];
				if (collada_source.max_joint_ptr[m] < collada_pack.max_bone)
				{
					collada_source.max_joint_ptr[m] = collada_pack.max_bone;
				}
			}
		}
	}

	file_writer_collada(&collada_source, n_out_ptr);

	fclose(file_ptr);
	free(n_in_ptr);
	free(n_out_ptr);
	free(d_name_ptr);

	//s0-free
	if (collada_source.is_animated)
	{
		for (uint32_t b = 0; b < collada_source.max_bone; ++b)
		{
			collada_Bone collada_bone = collada_source.collada_bone_ptr[b];
			for (uint32_t i = 0; i < collada_bone.name_size; ++i)
			{
				free(collada_bone.name_ptr[i]);
			}
			free(collada_bone.name_ptr);

			free(collada_bone.visual_ptr);

			free(collada_source.joint_ptr[b]);
		}
		free(collada_source.collada_bone_ptr);

		free(collada_source.joint_ptr);
		free(collada_source.bind_pose_ptr);

		free(collada_source.space_ptr);

		for (uint32_t b = 0; b < collada_source.max_bone; ++b)
		{
			free(collada_source.bone_ptr[b]);
		}
		free(collada_source.bone_ptr);
		free(collada_source.bone_size_ptr);

		for (uint32_t b = 0; b < collada_source.v_bone_size; ++b)
		{
			free(collada_source.v_bone_ptr[b]);
		}
		free(collada_source.v_bone_ptr);

		// free(collada_source.time_ptr);
		free(collada_source.transform_ptr);

		for (uint32_t a = 0; a < collada_source.armature_size; ++a)
		{
			free(collada_source.armature_ptr[a]);
		}
		free(collada_source.armature_ptr);
	}

	for (uint32_t m = 0; m < collada_source.max_data; ++m)
	{
		free(collada_source.data_ptr[m]);

		free(collada_source.vertex_ptr[m]);
		free(collada_source.normal_ptr[m]);
		free(collada_source.texcoord_ptr[m]);

		free(collada_source.p_ptr[m]);

		free(collada_source.index_ptr[m]);

		if (collada_source.is_animated)
		{
			free(collada_source.v_ptr[m]);
			free(collada_source.vcount_ptr[m]);
			free(collada_source.weight_ptr[m]);

			for (uint32_t p = 0; p < collada_source.collada_pack_size_ptr[m]; ++p)
			{
				collada_Pack collada_pack = collada_source.collada_pack_ptr[m][p];
				free(collada_pack.joint_ptr);
				free(collada_pack.weight_ptr);
			}
		}

		free(collada_source.collada_pack_ptr[m]);
	}
	free(collada_source.data_ptr);
	free(collada_source.max_joint_ptr);

	free(collada_source.vertex_ptr);
	free(collada_source.vertex_size_ptr);
	free(collada_source.normal_ptr);
	free(collada_source.normal_size_ptr);
	free(collada_source.texcoord_ptr);
	free(collada_source.texcoord_size_ptr);

	free(collada_source.p_ptr);
	free(collada_source.p_size_ptr);

	if (collada_source.is_animated)
	{
		free(collada_source.v_ptr);
		free(collada_source.v_size_ptr);

		free(collada_source.vcount_ptr);
		free(collada_source.vcount_size_ptr);

		free(collada_source.weight_ptr);
		free(collada_source.weight_size_ptr);
	}

	free(collada_source.index_ptr);
	free(collada_source.index_size_ptr);

	free(collada_source.collada_pack_ptr);
	free(collada_source.collada_pack_size_ptr);
	//e0-free

	--thrd;
	return 0;
}

// void gen(char *path)
// {
// 	// file_name = GraphicReader::repaste(file_name, "_", "/");
// 	size_t underscore_pos = file_name.find("_");

//	 if (underscore_pos != std::string::npos)
// 	{
//		 file_name = file_name.substr(0, underscore_pos);
//	 }
// 	FolderWriter::name("Results/" + file_name);

// 	std::vector<std::vector<int>> bones_int_2d_vector;
// 	std::vector<unsigned char> unsigned_char_vector;

// 	bones_int_2d_vector = file_reader_int(file, "\n");

// 	for (int i = 0; i < bones_int_2d_vector.size(); ++i)
// 	{
// 		if (bones_int_2d_vector[i][0] == 0)
// 		{
// 			unsigned_char_vector.push_back(0);
// 		}
// 		else
// 		{
// 			unsigned_char_vector.push_back(1);
// 		}
// 	}

// 	// for (int i = 0; i < bones_int_2d_vector.size(); ++i)
// 	// {
// 	// 	FileWriter::intPack(bones_int_2d_vector[i], "Results/" + file_name + "/" + std::to_string(i));
// 	// }

// 	FileWriter::bytePack(unsigned_char_vector, "Results/" + file_name + "/IdleBones");

// 	free(path);
// 	--thrd;
// }

// void collada_main()
int main()
{
	//(base-8) owner group others
	//4 read
	//2 write
	//1 execute
	mkdir(C_IN, 0700);
	mkdir(C_OUT, 0700);

	DIR* dir = opendir(C_IN);
	if (!dir)
	{
		error("opendir")
	}

	struct dirent* dirent_ptr;
	while ((dirent_ptr = readdir(dir)) != NULL)
	{
		char* d_name_ptr = strdup(dirent_ptr->d_name);
		// size_t size = strlen(d_name_ptr) + 1;
		// char* name_ptr = malloc(size);
		// memcpy(name_ptr, d_name_ptr, size);
		struct stat _stat;

		char* n0_ptr = math_combine(C_IN, "/");
		char* n_in_ptr = math_combine(n0_ptr, d_name_ptr);
		free(n0_ptr);

		if (stat(n_in_ptr, &_stat))
		{
			error("stat")
		}

		if (S_ISREG(_stat.st_mode))//S_ISDIR
		{
			thrd_t thread;
			// int result;

			// if (strstr(d_name, "$bone"))
			// {
			// 	result = thrd_create(&thread, gen, d_name);
			// }
			// else
			// {
			// 	result = thrd_create(&thread, main_skin, d_name);
			// }

			// if (result != thrd_success)
			if (thrd_create(&thread, main_skin, (void*)d_name_ptr) != thrd_success)
			{
				error("thrd_create")
			}

			++thrd;
		}

		free(n_in_ptr);
	}

	closedir(dir);

	while (thrd){}
}
