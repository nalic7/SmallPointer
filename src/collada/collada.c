static uint32_t thrd = 0;

int main_skin(void *name)
{
	info("skin %s\n", (char *)name)

	char *n0 = math_combine(CP_IN, "/");
	char *n_in = math_combine(n0, name);
	free(n0);
	n0 = math_combine(CP_OUT, "/");

	FILE *file = fopen(n_in, "r");
	if (!file)
	{
		error("fopen");
	}

	char *dot_ptr = strchr(name, '.');

	if (dot_ptr)
	{
		*dot_ptr = '\0';
	}

	SourceDataType sourcedatatype =
	{
		.max_animation_bones = -2,
		.create_animation = file_reader_match(file, (const char*[]){"<library_visual_scenes>", "<library_controllers>"}, 2)
	};

	fseek(file, 0, SEEK_SET);

	if (sourcedatatype.create_animation)
	{
		file_reader_match(file, (const char*[]){"<library_animations>"}, 1);

		while (file_reader_match(file, (const char*[]){"</library_animations>", CP_ARMATURE_NAME}, 2))
		{
			++sourcedatatype.max_animation_bones;
		}

		fseek(file, 0, SEEK_SET);

		file_reader_match(file, (const char*[]){"<library_animations>"}, 1);
		file_reader_match(file, (const char*[]){CP_ARMATURE_NAME}, 1);
		file_reader_match(file, (const char*[]){"count=\""}, 1);
		uint32_t int_size = 0;
		int *int_ptr = malloc(0);
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
		for (int l = 0; l < sourcedatatype.max_animation_bones; ++l)
		{
			sourcedatatype.bonedata_vector = file_reader_node(file, sourcedatatype.bonedata_vector, &sourcedatatype.max_bonedata);
		}

		sourcedatatype.space_ptr = malloc(sourcedatatype.max_animation_bones * sizeof(uint32_t));
		for (int x = 0; x < sourcedatatype.max_animation_bones; ++x)
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
		sourcedatatype.max_object = 0;
		sourcedatatype.object_name_vector = malloc(0);
		sourcedatatype.positions_size = malloc(0);
		sourcedatatype.positions = malloc(0);
		sourcedatatype.normals_size = malloc(0);
		sourcedatatype.normals = malloc(0);
		sourcedatatype.texcoord_size = malloc(0);
		sourcedatatype.texcoord = malloc(0);
		sourcedatatype.p_offset_size = malloc(0);
		sourcedatatype.p_offset = malloc(0);

		uint32_t v_index = 0;

		char state;
		while ((state = file_reader_match(file, (const char*[]){"</library_geometries>", "<geometry"}, 2)))
		{
			file_reader_match(file, (const char*[]){"\""}, 1);
			sourcedatatype.object_name_vector = file_reader_char_ptr(file, "\t", "-", sourcedatatype.object_name_vector, &sourcedatatype.max_object);
			graphic_reader_sanitize(sourcedatatype.object_name_vector[v_index]);

			size_t fs_size = sourcedatatype.max_object * sizeof(float *);
			size_t is_size = sourcedatatype.max_object * sizeof(int *);
			size_t ui_size = sourcedatatype.max_object * sizeof(uint32_t);

			file_reader_match(file, (const char *[]){"positions-array"}, 1);
			file_reader_match(file, (const char *[]){">"}, 1);
			sourcedatatype.positions_size = realloc(sourcedatatype.positions_size, ui_size);
			sourcedatatype.positions_size[v_index] = 0;
			sourcedatatype.positions = realloc(sourcedatatype.positions, fs_size);
			sourcedatatype.positions[v_index] = malloc(0);
			sourcedatatype.positions[v_index] = file_reader_float(file, "</float_array>", sourcedatatype.positions[v_index], &sourcedatatype.positions_size[v_index]);

			file_reader_match(file, (const char *[]){"normals-array"}, 1);
			file_reader_match(file, (const char *[]){">"}, 1);
			sourcedatatype.normals_size = realloc(sourcedatatype.normals_size, ui_size);
			sourcedatatype.normals_size[v_index] = 0;
			sourcedatatype.normals = realloc(sourcedatatype.normals, fs_size);
			sourcedatatype.normals[v_index] = malloc(0);
			sourcedatatype.normals[v_index] = file_reader_float(file, "</float_array>", sourcedatatype.normals[v_index], &sourcedatatype.normals_size[v_index]);

			file_reader_match(file, (const char *[]){"map-0-array"}, 1);
			file_reader_match(file, (const char *[]){">"}, 1);
			sourcedatatype.texcoord_size = realloc(sourcedatatype.texcoord_size, ui_size);
			sourcedatatype.texcoord_size[v_index] = 0;
			sourcedatatype.texcoord = realloc(sourcedatatype.texcoord, fs_size);
			sourcedatatype.texcoord[v_index] = malloc(0);
			sourcedatatype.texcoord[v_index] = file_reader_float(file, "</float_array>", sourcedatatype.texcoord[v_index], &sourcedatatype.texcoord_size[v_index]);

			// if (SourceDataType::CREATE_COLOR)
			// {
			// 	sourcedatatype.color.push_back({});

			// 	file_reader_match(char_pointer, "colors-Attribute-array");
			// 	file_reader_match(char_pointer, ">");
			// 	file_reader_float(char_pointer, "</float_array>", sourcedatatype.color[v_index]);
			// }

			file_reader_match(file, (const char *[]){"<p>"}, 1);
			sourcedatatype.p_offset_size = realloc(sourcedatatype.p_offset_size, ui_size);
			sourcedatatype.p_offset_size[v_index] = 0;
			sourcedatatype.p_offset = realloc(sourcedatatype.p_offset, is_size);
			sourcedatatype.p_offset[v_index] = malloc(0);
			sourcedatatype.p_offset[v_index] = file_reader_int(file, "</p>", sourcedatatype.p_offset[v_index], &sourcedatatype.p_offset_size[v_index]);
			++v_index;
		}

		uint32_t offset_size = sizeof(int *) * sourcedatatype.max_object;
		sourcedatatype.positions_offset = malloc(offset_size);
		sourcedatatype.normals_offset = malloc(offset_size);
		sourcedatatype.texcoord_offset = malloc(offset_size);
		// // GraphicReader::makeModelOffset(sourcedatatype);
		for (uint32_t x = 0; x < sourcedatatype.max_object; ++x)
		{
			uint32_t p_offset_size = sourcedatatype.p_offset_size[x];
			uint32_t offset2_size = sizeof(int) * p_offset_size;
			sourcedatatype.positions_offset[x] = malloc(offset2_size);
			sourcedatatype.normals_offset[x] = malloc(offset2_size);
			sourcedatatype.texcoord_offset[x] = malloc(offset2_size);
			char offset = 0;
			for (int y = 0; y < p_offset_size; ++y)
			{
				// if (CP_CREATE_COLOR)
				// {
				// 	sourcedatatype.color_offset.push_back({});

				// 	for (int i : sourcedatatype.p_offset[x])
				// 	{
				// 		if (i_offset == 0)
				// 		{
				// 			sourcedatatype.positions_offset[x].push_back(i);
				// 		}
				// 		else if (i_offset == 1)
				// 		{
				// 			sourcedatatype.normals_offset[x].push_back(i);
				// 		}
				// 		else if (i_offset == 2)
				// 		{
				// 			sourcedatatype.texcoord_offset[x].push_back(i);
				// 		}
				// 		else if (i_offset == 3)
				// 		{
				// 			sourcedatatype.color_offset[x].push_back(i);

				// 			i_offset = -1;
				// 		}
				// 	}
				// }
				// else
				// {
				int i = sourcedatatype.p_offset[x][y];
				switch (offset)
				{
					case 0:
						sourcedatatype.positions_offset[x][y] = i;
						++offset;
						break;
					case 1:
						sourcedatatype.normals_offset[x][y] = i;
						++offset;
						break;
					case 2:
						sourcedatatype.texcoord_offset[x][y] = i;
						offset = 0;
				}
				// }
			}
		}
	}

	// Skinning / Animation

	if (sourcedatatype.create_animation)
	{
		file_reader_match(file, (const char *[]){"<library_controllers>"}, 1);

		sourcedatatype.joints_size = malloc(0);
		sourcedatatype.joints = malloc(0);
		sourcedatatype.bind_poses_size = malloc(0);
		sourcedatatype.bind_poses = malloc(0);
		sourcedatatype.weights_size = malloc(0);
		sourcedatatype.weights = malloc(0);
		sourcedatatype.vcount_offset_size = malloc(0);
		sourcedatatype.vcount_offset = malloc(0);
		sourcedatatype.v_offset_size = malloc(0);
		sourcedatatype.v_offset = malloc(0);
		sourcedatatype.max_joint_vector_size = 0;
		sourcedatatype.max_joint_vector = malloc(0);

		uint32_t v_index = 0;

		char state;
		while ((state = file_reader_match(file, (const char *[]){"</library_controllers>", "<controller"}, 2)))
		{
			size_t cs2_size = sourcedatatype.max_object * sizeof(char **);
			size_t fs_size = sourcedatatype.max_object * sizeof(float *);
			size_t is_size = sourcedatatype.max_object * sizeof(int *);
			size_t ui_size = sourcedatatype.max_object * sizeof(uint32_t);

			file_reader_match(file, (const char *[]){"joints-array"}, 1);
			file_reader_match(file, (const char *[]){">"}, 1);
			sourcedatatype.joints_size = realloc(sourcedatatype.joints_size, ui_size);
			sourcedatatype.joints_size[v_index] = 0;
			sourcedatatype.joints = realloc(sourcedatatype.joints, cs2_size);
			sourcedatatype.joints[v_index] = malloc(0);
			sourcedatatype.joints[v_index] = file_reader_char_ptr(file, " ", "</Name_array>", sourcedatatype.joints[v_index], &sourcedatatype.joints_size[v_index]);

			for (uint32_t j = 0; j < sourcedatatype.joints_size[v_index]; ++j)
			{
				graphic_reader_sanitize(sourcedatatype.joints[v_index][j]);
			}

			file_reader_match(file, (const char *[]){"bind_poses-array"}, 1);
			file_reader_match(file, (const char *[]){">"}, 1);
			sourcedatatype.bind_poses_size = realloc(sourcedatatype.bind_poses_size, ui_size);
			sourcedatatype.bind_poses_size[v_index] = 0;
			sourcedatatype.bind_poses = realloc(sourcedatatype.bind_poses, fs_size);
			sourcedatatype.bind_poses[v_index] = malloc(0);
			sourcedatatype.bind_poses[v_index] = file_reader_float(file, "</float_array>", sourcedatatype.bind_poses[v_index], &sourcedatatype.bind_poses_size[v_index]);

			file_reader_match(file, (const char *[]){"weights-array"}, 1);
			file_reader_match(file, (const char *[]){">"}, 1);
			sourcedatatype.weights_size = realloc(sourcedatatype.weights_size, ui_size);
			sourcedatatype.weights_size[v_index] = 0;
			sourcedatatype.weights = realloc(sourcedatatype.weights, fs_size);
			sourcedatatype.weights[v_index] = 0;
			sourcedatatype.weights[v_index] = file_reader_float(file, "</float_array>", sourcedatatype.weights[v_index], &sourcedatatype.weights_size[v_index]);

			file_reader_match(file, (const char *[]){"<vcount>"}, 1);
			sourcedatatype.vcount_offset_size = realloc(sourcedatatype.vcount_offset_size, ui_size);
			sourcedatatype.vcount_offset_size[v_index] = 0;
			sourcedatatype.vcount_offset = realloc(sourcedatatype.vcount_offset, is_size);
			sourcedatatype.vcount_offset[v_index] = 0;
			sourcedatatype.vcount_offset[v_index] = file_reader_int(file, "</vcount>", sourcedatatype.vcount_offset[v_index], &sourcedatatype.vcount_offset_size[v_index]);

			sourcedatatype.max_joint_vector = realloc(sourcedatatype.max_joint_vector, ui_size);
			sourcedatatype.max_joint_vector[v_index] = 0;
			for (uint32_t j = 0; j < sourcedatatype.vcount_offset_size[v_index]; ++j)
			{
				if (sourcedatatype.max_joint_vector[v_index] < sourcedatatype.vcount_offset[v_index][j])
				{
					sourcedatatype.max_joint_vector[v_index] = sourcedatatype.vcount_offset[v_index][j];
				}
			}
			info("%s%s : %d\n", (char *)name, sourcedatatype.object_name_vector[v_index], sourcedatatype.max_joint_vector[v_index])

			file_reader_match(file, (const char *[]){"<v>"}, 1);
			sourcedatatype.v_offset_size = realloc(sourcedatatype.v_offset_size, ui_size);
			sourcedatatype.v_offset_size[v_index] = 0;
			sourcedatatype.v_offset = realloc(sourcedatatype.weights, is_size);
			sourcedatatype.v_offset[v_index] = 0;
			sourcedatatype.v_offset[v_index] = file_reader_int(file, "</v>", sourcedatatype.v_offset[v_index], &sourcedatatype.v_offset_size[v_index]);
			++v_index;
		}

		file_reader_match(file, (const char *[]){"name=\""}, 1);
		sourcedatatype.animation_bone_name_vector_size = 0;
		sourcedatatype.animation_bone_name_vector = malloc(0);
		sourcedatatype.animation_bone_name_vector = file_reader_char_ptr(file, "\t", "\"", sourcedatatype.animation_bone_name_vector, &sourcedatatype.animation_bone_name_vector_size);

		file_reader_match(file, (const char *[]){"</animation>"}, 1);

		sourcedatatype.armature_time_vector_size = 0;
		sourcedatatype.armature_time_vector = malloc(0);
		sourcedatatype.armature_transform_vector_size = 0;
		sourcedatatype.armature_transform_vector = malloc(0);
		sourcedatatype.armature_string_vector_size = 0;
		sourcedatatype.armature_string_vector = malloc(0);

		// for (int l = 0; l < sourcedatatype.max_animation_bones * (CP_DECOMPOSED ? 9 : 1); ++l)
		for (int l = 0; l < sourcedatatype.max_animation_bones; ++l)
		{
			file_reader_match(file, (const char *[]){"<float_array"}, 1);
			file_reader_match(file, (const char *[]){">"}, 1);
			sourcedatatype.armature_time_vector = file_reader_float(file, "</float_array>", sourcedatatype.armature_time_vector, &sourcedatatype.armature_time_vector_size);

			file_reader_match(file, (const char *[]){"<float_array"}, 1);
			file_reader_match(file, (const char *[]){">"}, 1);
			sourcedatatype.armature_transform_vector = file_reader_float(file, "</float_array>", sourcedatatype.armature_transform_vector, &sourcedatatype.armature_transform_vector_size);

			file_reader_match(file, (const char *[]){"target=\""}, 1);
			file_reader_match(file, (const char *[]){sourcedatatype.animation_bone_name_vector[0]}, 1);
			file_reader_match(file, (const char *[]){"_"}, 1);
			sourcedatatype.armature_string_vector = file_reader_char_ptr(file, "\t", "/", sourcedatatype.armature_string_vector, &sourcedatatype.armature_string_vector_size);
			graphic_reader_sanitize(sourcedatatype.armature_string_vector[sourcedatatype.armature_string_vector_size - 1]);
		}

		graphic_reader_makeBones(&sourcedatatype);
		// graphic_reader_switchBones(&sourcedatatype);
		// graphic_reader_switchAnimationBones(&sourcedatatype);
	}

	if (sourcedatatype.create_animation && CP_FIX_ANIMATION)
	{
		graphic_reader_fixAnimation(&sourcedatatype);
	}

	if (CP_COMPRESS)
	{
		graphic_reader_compressVertex(&sourcedatatype);
		// GraphicReader::unPackIndex(sourcedatatype);

		if (sourcedatatype.create_animation)
		{
			// GraphicReader::unPackVisualBones(sourcedatatype);
			// GraphicReader::updateBones(sourcedatatype);
		}
	}

	// modelFile(sourcedatatype, n_in);

	// file.close();

	free(n_in);
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

void collada_main()
{
	//(base-8) owner group others
	//4 read
	//2 write
	//1 execute
	mkdir(CP_IN, 0700);
	mkdir(CP_OUT, 0700);

	DIR *dir = opendir(CP_IN);
	if (!dir)
	{
		error("opendir")
	}

	struct dirent *dirent_ptr;
	while ((dirent_ptr = readdir(dir)) != NULL)
	{
		const char *d_name = dirent_ptr->d_name;
		size_t size = strlen(d_name) + 1;
		char *name = malloc(size);
		memcpy(name, d_name, size);
		struct stat _stat;

		char *n0 = math_combine(CP_IN, "/");
		char *n_in = math_combine(n0, name);
		free(n0);

		if (stat(n_in, &_stat))
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
			if (thrd_create(&thread, main_skin, (void *)d_name) != thrd_success)
			{
				error("thrd_create")
			}

			++thrd;
		}

		free(n_in);
	}

	while (thrd){}
}
