static uint32_t thrd = 0;

int main_skin(void* name)
{
	info("skin %s\n", (char*)name)

	char* n0_ptr = math_combine(C_IN, "/");
	char* n_in_ptr = math_combine(n0_ptr, name);
	free(n0_ptr);
	n0_ptr = math_combine(C_OUT, "/");

	FILE* file = fopen(n_in_ptr, "r");
	if (!file)
	{
		error("fopen");
	}

	char* dot_ptr = strchr(name, '.');

	if (dot_ptr)
	{
		*dot_ptr = '\0';
	}

	char* n_out = math_combine(n0_ptr, name);
	free(n0_ptr);

	collada_Source sourcedatatype =
	{
		.max_bone = -2,
		.is_animated = file_reader_match(file, (const char*[]){"<library_visual_scenes>", "<library_controllers>"}, 2)
	};

	fseek(file, 0, SEEK_SET);

	if (sourcedatatype.is_animated)
	{
		file_reader_match(file, (const char*[]){"<library_animations>"}, 1);

		while (file_reader_match(file, (const char*[]){"</library_animations>", C_ARMATURE_NAME}, 2))
		{
			++sourcedatatype.max_bone;
		}

		fseek(file, 0, SEEK_SET);

		file_reader_match(file, (const char*[]){"<library_animations>"}, 1);
		file_reader_match(file, (const char*[]){C_ARMATURE_NAME}, 1);
		file_reader_match(file, (const char*[]){"count=\""}, 1);
		uint32_t int_size = 0;
		int* int_ptr = malloc(0);
		int_ptr = file_reader_int(file, "\"", int_ptr, &int_size);

		sourcedatatype.max_frame = int_ptr[0];

		fseek(file, 0, SEEK_SET);

		// VisualBones

		file_reader_match(file, (const char*[]){"<library_visual_scenes>"}, 1);

		// if (CP_DECOMPOSED)
		// {
		// 	file_reader_match(file, "</translate>", 1);
		// }
		// else
		// {
		file_reader_match(file, (const char*[]){"</matrix>\n"}, 1);
		// }

		sourcedatatype.max_bonedata = 0;
		sourcedatatype.bonedata_vector = malloc(0);
		for (int l = 0; l < sourcedatatype.max_bone; ++l)
		{
			sourcedatatype.bonedata_vector = file_reader_node(file, sourcedatatype.bonedata_vector, &sourcedatatype.max_bonedata);
		}

		sourcedatatype.space_ptr = malloc(sourcedatatype.max_bone * sizeof(uint32_t));
		for (int x = 0; x < sourcedatatype.max_bone; ++x)
		{
			BoneData bonedata = sourcedatatype.bonedata_vector[x];

			// for (int y = 0; y < bonedata.bones_name_string_size; y += 2)
			// {
			// uint32_t value = graphic_reader_count(bonedata.bones_name_string[y + 1], ' ');
			uint32_t value = graphic_reader_count(bonedata.bones_name_string[1], ' ');
			// sourcedatatype.space_ptr[y / 2] = value;
			sourcedatatype.space_ptr[x] = value;

			graphic_reader_sanitize(bonedata.bones_name_string[0]);
			// }
		}

		fseek(file, 0, SEEK_SET);
	}

	file_reader_match(file, (const char*[]){"<library_geometries>"}, 1);

	{
		sourcedatatype.max_data = 0;
		sourcedatatype.data_name_ptr = malloc(0);
		sourcedatatype.vertex_size_ptr = malloc(0);
		sourcedatatype.vertex_ptr = malloc(0);
		sourcedatatype.normal_size_ptr = malloc(0);
		sourcedatatype.normal_ptr = malloc(0);
		sourcedatatype.texcoord_size_ptr = malloc(0);
		sourcedatatype.texcoord_ptr = malloc(0);
		sourcedatatype.p_offset_size = malloc(0);
		sourcedatatype.p_offset = malloc(0);

		uint32_t v_index = 0;

		char state;
		while ((state = file_reader_match(file, (const char*[]){"</library_geometries>", "<geometry"}, 2)))
		{
			file_reader_match(file, (const char*[]){"\""}, 1);
			sourcedatatype.data_name_ptr = file_reader_char_ptr(file, "\t", "-", sourcedatatype.data_name_ptr, &sourcedatatype.max_data);
			graphic_reader_sanitize(sourcedatatype.data_name_ptr[v_index]);

			size_t fs_size = sourcedatatype.max_data * sizeof(float*);
			size_t is_size = sourcedatatype.max_data * sizeof(int*);
			size_t ui_size = sourcedatatype.max_data * sizeof(uint32_t);

			file_reader_match(file, (const char*[]){"positions-array"}, 1);
			file_reader_match(file, (const char*[]){">"}, 1);
			sourcedatatype.vertex_size_ptr = realloc(sourcedatatype.vertex_size_ptr, ui_size);
			sourcedatatype.vertex_size_ptr[v_index] = 0;
			sourcedatatype.vertex_ptr = realloc(sourcedatatype.vertex_ptr, fs_size);
			sourcedatatype.vertex_ptr[v_index] = malloc(0);
			sourcedatatype.vertex_ptr[v_index] = file_reader_float(file, "</float_array>", sourcedatatype.vertex_ptr[v_index], &sourcedatatype.vertex_size_ptr[v_index]);

			file_reader_match(file, (const char*[]){"normals-array"}, 1);
			file_reader_match(file, (const char*[]){">"}, 1);
			sourcedatatype.normal_size_ptr = realloc(sourcedatatype.normal_size_ptr, ui_size);
			sourcedatatype.normal_size_ptr[v_index] = 0;
			sourcedatatype.normal_ptr = realloc(sourcedatatype.normal_ptr, fs_size);
			sourcedatatype.normal_ptr[v_index] = malloc(0);
			sourcedatatype.normal_ptr[v_index] = file_reader_float(file, "</float_array>", sourcedatatype.normal_ptr[v_index], &sourcedatatype.normal_size_ptr[v_index]);

			file_reader_match(file, (const char*[]){"map-0-array"}, 1);
			file_reader_match(file, (const char*[]){">"}, 1);
			sourcedatatype.texcoord_size_ptr = realloc(sourcedatatype.texcoord_size_ptr, ui_size);
			sourcedatatype.texcoord_size_ptr[v_index] = 0;
			sourcedatatype.texcoord_ptr = realloc(sourcedatatype.texcoord_ptr, fs_size);
			sourcedatatype.texcoord_ptr[v_index] = malloc(0);
			sourcedatatype.texcoord_ptr[v_index] = file_reader_float(file, "</float_array>", sourcedatatype.texcoord_ptr[v_index], &sourcedatatype.texcoord_size_ptr[v_index]);

			// if (SourceDataType::CREATE_COLOR)
			// {
			// 	sourcedatatype.color.push_back({});

			// 	file_reader_match(char_pointer, "colors-Attribute-array");
			// 	file_reader_match(char_pointer, ">");
			// 	file_reader_float(char_pointer, "</float_array>", sourcedatatype.color[v_index]);
			// }

			file_reader_match(file, (const char*[]){"<p>"}, 1);
			sourcedatatype.p_offset_size = realloc(sourcedatatype.p_offset_size, ui_size);
			sourcedatatype.p_offset_size[v_index] = 0;
			sourcedatatype.p_offset = realloc(sourcedatatype.p_offset, is_size);
			sourcedatatype.p_offset[v_index] = malloc(0);
			sourcedatatype.p_offset[v_index] = file_reader_int(file, "</p>", sourcedatatype.p_offset[v_index], &sourcedatatype.p_offset_size[v_index]);
			++v_index;
		}

		// uint32_t offset_size = sizeof(int *) * sourcedatatype.max_object;
		// sourcedatatype.positions_offset = malloc(offset_size);
		// sourcedatatype.normals_offset = malloc(offset_size);
		// sourcedatatype.texcoord_offset = malloc(offset_size);
		// // // GraphicReader::makeModelOffset(sourcedatatype);
		// for (uint32_t x = 0; x < sourcedatatype.max_object; ++x)
		// {
		// 	uint32_t p_offset_size = sourcedatatype.p_offset_size[x];
		// 	uint32_t offset2_size = sizeof(int) * p_offset_size;
		// 	sourcedatatype.positions_offset[x] = malloc(offset2_size);
		// 	sourcedatatype.normals_offset[x] = malloc(offset2_size);
		// 	sourcedatatype.texcoord_offset[x] = malloc(offset2_size);
		// 	char offset = 0;
		// 	for (int y = 0; y < p_offset_size; ++y)
		// 	{
		// 		// if (CP_CREATE_COLOR)
		// 		// {
		// 		// 	sourcedatatype.color_offset.push_back({});
		//
		// 		// 	for (int i : sourcedatatype.p_offset[x])
		// 		// 	{
		// 		// 		if (i_offset == 0)
		// 		// 		{
		// 		// 			sourcedatatype.positions_offset[x].push_back(i);
		// 		// 		}
		// 		// 		else if (i_offset == 1)
		// 		// 		{
		// 		// 			sourcedatatype.normals_offset[x].push_back(i);
		// 		// 		}
		// 		// 		else if (i_offset == 2)
		// 		// 		{
		// 		// 			sourcedatatype.texcoord_offset[x].push_back(i);
		// 		// 		}
		// 		// 		else if (i_offset == 3)
		// 		// 		{
		// 		// 			sourcedatatype.color_offset[x].push_back(i);
		//
		// 		// 			i_offset = -1;
		// 		// 		}
		// 		// 	}
		// 		// }
		// 		// else
		// 		// {
		// 		int i = sourcedatatype.p_offset[x][y];
		// 		switch (offset)
		// 		{
		// 			case 0:
		// 				sourcedatatype.positions_offset[x][y] = i;
		// 				++offset;
		// 				break;
		// 			case 1:
		// 				sourcedatatype.normals_offset[x][y] = i;
		// 				++offset;
		// 				break;
		// 			case 2:
		// 				sourcedatatype.texcoord_offset[x][y] = i;
		// 				offset = 0;
		// 		}
		// 		// }
		// 	}
		// }
	}

	// Skinning / Animation

	if (sourcedatatype.is_animated)
	{
		file_reader_match(file, (const char*[]){"<library_controllers>"}, 1);

		// sourcedatatype.joints_size = malloc(0);
		// sourcedatatype.joints = malloc(0);
		// sourcedatatype.bind_poses_size = malloc(0);
		// sourcedatatype.bind_pose_ptr = malloc(0);
		// sourcedatatype.weights_size = malloc(0);
		// sourcedatatype.weight_ptr = malloc(0);
		sourcedatatype.vcount_offset_size = malloc(0);
		sourcedatatype.vcount_offset = malloc(0);
		sourcedatatype.v_offset_size = malloc(0);
		sourcedatatype.v_offset = malloc(0);
		// sourcedatatype.max_bone_size = 0;
		// sourcedatatype.max_bone_ptr = malloc(0);

		uint32_t v_index = 0;

		char state;
		while ((state = file_reader_match(file, (const char*[]){"</library_controllers>", "<controller"}, 2)))
		{
			size_t cs2_size = sourcedatatype.max_data * sizeof(char**);
			size_t fs_size = sourcedatatype.max_data * sizeof(float*);
			size_t is_size = sourcedatatype.max_data * sizeof(int*);
			size_t ui_size = sourcedatatype.max_data * sizeof(uint32_t);

			file_reader_match(file, (const char*[]){"joints-array"}, 1);
			file_reader_match(file, (const char*[]){">"}, 1);
			// sourcedatatype.joints_size = realloc(sourcedatatype.joints_size, ui_size);
			// sourcedatatype.joints_size[v_index] = 0;

			if (v_index == 0)
			{
				uint32_t max_bone = 0;
				// sourcedatatype.joints = realloc(sourcedatatype.joints, cs2_size);
				sourcedatatype.joint_ptr = malloc(0);
				sourcedatatype.joint_ptr = file_reader_char_ptr(file, " ", "</Name_array>", sourcedatatype.joint_ptr, &max_bone);

				for (uint32_t j = 0; j < max_bone; ++j)
				{
					graphic_reader_sanitize(sourcedatatype.joint_ptr[j]);
				}

				file_reader_match(file, (const char*[]){"bind_poses-array"}, 1);
				file_reader_match(file, (const char*[]){">"}, 1);
				// sourcedatatype.bind_poses_size = realloc(sourcedatatype.bind_poses_size, ui_size);
				// sourcedatatype.bind_poses_size[v_index] = 0;
				// sourcedatatype.bind_pose_ptr = realloc(sourcedatatype.bind_pose_ptr, fs_size);
				max_bone = 0;
				sourcedatatype.bind_pose_ptr = malloc(0);
				sourcedatatype.bind_pose_ptr = file_reader_float(file, "</float_array>", sourcedatatype.bind_pose_ptr, &max_bone);

				file_reader_match(file, (const char*[]){"weights-array"}, 1);
				file_reader_match(file, (const char*[]){">"}, 1);
				// sourcedatatype.weights_size = realloc(sourcedatatype.weights_size, ui_size);
				// sourcedatatype.weights_size[v_index] = 0;
				// sourcedatatype.weight_ptr = realloc(sourcedatatype.weight_ptr, fs_size);
				max_bone = 0;
				sourcedatatype.weight_ptr = malloc(0);
				sourcedatatype.weight_ptr = file_reader_float(file, "</float_array>", sourcedatatype.weight_ptr, &max_bone);
			}

			file_reader_match(file, (const char*[]){"<vcount>"}, 1);
			sourcedatatype.vcount_offset_size = realloc(sourcedatatype.vcount_offset_size, ui_size);
			sourcedatatype.vcount_offset_size[v_index] = 0;
			sourcedatatype.vcount_offset = realloc(sourcedatatype.vcount_offset, is_size);
			sourcedatatype.vcount_offset[v_index] = 0;
			sourcedatatype.vcount_offset[v_index] = file_reader_int(file, "</vcount>", sourcedatatype.vcount_offset[v_index], &sourcedatatype.vcount_offset_size[v_index]);

			// sourcedatatype.max_bone_ptr = realloc(sourcedatatype.max_bone_ptr, ui_size);
			// sourcedatatype.max_bone_ptr[v_index] = 0;
			// for (uint32_t j = 0; j < sourcedatatype.vcount_offset_size[v_index]; ++j)
			// {
			// 	if (sourcedatatype.max_bone_ptr[v_index] < sourcedatatype.vcount_offset[v_index][j])
			// 	{
			// 		sourcedatatype.max_bone_ptr[v_index] = sourcedatatype.vcount_offset[v_index][j];
			// 	}
			// }
			// info("%s%s : %d\n", (char *)name, sourcedatatype.data_name_ptr[v_index], sourcedatatype.max_bone_ptr[v_index])
			unsigned char max_bone = 0;
			for (uint32_t j = 0; j < sourcedatatype.vcount_offset_size[v_index]; ++j)
			{
				if (max_bone < sourcedatatype.vcount_offset[v_index][j])
				{
					max_bone = sourcedatatype.vcount_offset[v_index][j];
				}
			}
			info("%s%s %d\n", (char *)name, sourcedatatype.data_name_ptr[v_index], max_bone)

			file_reader_match(file, (const char*[]){"<v>"}, 1);
			sourcedatatype.v_offset_size = realloc(sourcedatatype.v_offset_size, ui_size);
			sourcedatatype.v_offset_size[v_index] = 0;
			sourcedatatype.v_offset = realloc(sourcedatatype.weight_ptr, is_size);
			sourcedatatype.v_offset[v_index] = 0;
			sourcedatatype.v_offset[v_index] = file_reader_int(file, "</v>", sourcedatatype.v_offset[v_index], &sourcedatatype.v_offset_size[v_index]);
			++v_index;
		}

		file_reader_match(file, (const char*[]){"name=\""}, 1);
		sourcedatatype.animation_bone_name_vector_size = 0;
		sourcedatatype.animation_bone_name_vector = malloc(0);
		sourcedatatype.animation_bone_name_vector = file_reader_char_ptr(file, "\t", "\"", sourcedatatype.animation_bone_name_vector, &sourcedatatype.animation_bone_name_vector_size);

		file_reader_match(file, (const char*[]){"</animation>"}, 1);

		sourcedatatype.armature_time_vector_size = 0;
		sourcedatatype.armature_time_vector = malloc(0);
		sourcedatatype.armature_transform_vector_size = 0;
		sourcedatatype.armature_transform_vector = malloc(0);
		sourcedatatype.armature_string_vector_size = 0;
		sourcedatatype.armature_string_vector = malloc(0);

		// for (int l = 0; l < sourcedatatype.max_animation_bones * (CP_DECOMPOSED ? 9 : 1); ++l)
		for (int l = 0; l < sourcedatatype.max_bone; ++l)
		{
			file_reader_match(file, (const char*[]){"<float_array"}, 1);
			file_reader_match(file, (const char*[]){">"}, 1);
			sourcedatatype.armature_time_vector = file_reader_float(file, "</float_array>", sourcedatatype.armature_time_vector, &sourcedatatype.armature_time_vector_size);

			file_reader_match(file, (const char*[]){"<float_array"}, 1);
			file_reader_match(file, (const char*[]){">"}, 1);
			sourcedatatype.armature_transform_vector = file_reader_float(file, "</float_array>", sourcedatatype.armature_transform_vector, &sourcedatatype.armature_transform_vector_size);

			file_reader_match(file, (const char*[]){"target=\""}, 1);
			file_reader_match(file, (const char*[]){sourcedatatype.animation_bone_name_vector[0]}, 1);
			file_reader_match(file, (const char*[]){"_"}, 1);
			sourcedatatype.armature_string_vector = file_reader_char_ptr(file, "\t", "/", sourcedatatype.armature_string_vector, &sourcedatatype.armature_string_vector_size);
			graphic_reader_sanitize(sourcedatatype.armature_string_vector[sourcedatatype.armature_string_vector_size - 1]);
		}

		graphic_reader_makeBones(&sourcedatatype);
		// graphic_reader_switchBones(&sourcedatatype);
		// graphic_reader_switchAnimationBones(&sourcedatatype);
	}

	if (sourcedatatype.is_animated && C_FIX_ANIMATED)
	{
		graphic_reader_fixAnimation(&sourcedatatype);
	}

	graphic_reader_mix(&sourcedatatype);
	// if (CP_COMPRESS)
	// {
	// 	graphic_reader_compressVertex(&sourcedatatype);
	// 	// GraphicReader::unPackIndex(sourcedatatype);
	//
	// 	if (sourcedatatype.create_animation)
	// 	{
	// 		// GraphicReader::unPackVisualBones(sourcedatatype);
	// 		// GraphicReader::updateBones(sourcedatatype);
	// 	}
	// }

	// modelFile(sourcedatatype, n_in);
	file_writer_collada(&sourcedatatype, n_out);

	// file.close();
	fclose(file);
	free(n_in_ptr);
	free(n_out);
	free(name);
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
		const char* d_name = strdup(dirent_ptr->d_name);
		size_t size = strlen(d_name) + 1;
		char* name = malloc(size);
		memcpy(name, d_name, size);
		struct stat _stat;

		char* n0_ptr = math_combine(C_IN, "/");
		char* n_in_ptr = math_combine(n0_ptr, name);
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
			if (thrd_create(&thread, main_skin, (void*)d_name) != thrd_success)
			{
				error("thrd_create")
			}

			++thrd;
		}

		free(n_in_ptr);
	}

	while (thrd){}
}
