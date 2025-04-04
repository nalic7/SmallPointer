static uint32_t thrd = 0;

static const char C_IN[] = "./C_I";
static const char C_OUT[] = "./C_O";

static int skin(void *arg)
{
	// info("skin %s\n", (char*)name)

	char *d_name_char_p = ((void **)arg)[0];
	char *dot_p = strchr(d_name_char_p, '.');
	if (dot_p)
	{
		*dot_p = '\0';
	}

	char *file_char_p = ((void **)arg)[1];
	free(arg);

	char *out_char_p = malloc(sizeof(C_OUT)-1 + 1 + strlen(d_name_char_p) + 1);
	strcpy(out_char_p, C_OUT);
	strcat(out_char_p, "/");
	strcat(out_char_p, d_name_char_p);

	FILE *file_p = fopen(file_char_p, "r");
	nali_log("fopen %p", file_p);
	free(file_char_p);

	collada_Source collada_source =
	{
		.max_bone = -2,
		.is_animated = file_reader_match(file_p, (const char*[]){"<library_visual_scenes>", "<library_controllers>"}, 2)
	};

	fseek(file_p, 0, SEEK_SET);

	if (collada_source.is_animated)
	{
		file_reader_match(file_p, (const char*[]){"<library_animations>"}, 1);

		while (file_reader_match(file_p, (const char*[]){"</library_animations>", C_ARMATURE_NAME}, 2))
		{
			++collada_source.max_bone;
		}

		fseek(file_p, 0, SEEK_SET);

		file_reader_match(file_p, (const char*[]){"<library_animations>"}, 1);
		file_reader_match(file_p, (const char*[]){C_ARMATURE_NAME}, 1);
		file_reader_match(file_p, (const char*[]){"count=\""}, 1);
		uint32_t temp_size = 0;
		int *int_p = malloc(0);
		int_p = file_reader_int(file_p, "\"", int_p, &temp_size);

		collada_source.max_frame = int_p[0];
		free(int_p);

		fseek(file_p, 0, SEEK_SET);

		file_reader_match(file_p, (const char*[]){"<library_visual_scenes>"}, 1);
		file_reader_match(file_p, (const char*[]){"</matrix>\n"}, 1);

		collada_source.collada_bone_p = malloc(0);
		temp_size = 0;
		while (temp_size < collada_source.max_bone)
		{
			collada_source.collada_bone_p = file_reader_node(file_p, collada_source.collada_bone_p, &temp_size);
		}

		collada_source.space_p = malloc(collada_source.max_bone * sizeof(uint32_t));
		for (int x = 0; x < collada_source.max_bone; ++x)
		{
			collada_Bone bonedata = collada_source.collada_bone_p[x];

			uint32_t value = graphic_reader_count(bonedata.name_p[1], ' ');
			collada_source.space_p[x] = value;

			graphic_reader_sanitize(bonedata.name_p[0]);
		}

		fseek(file_p, 0, SEEK_SET);
	}

	file_reader_match(file_p, (const char*[]){"<library_geometries>"}, 1);

	{
		collada_source.max_data = 0;
		collada_source.data_p = malloc(0);
		collada_source.vertex_size_p = malloc(0);
		collada_source.vertex_p = malloc(0);
		#ifdef C_OUT_NORMAL
			collada_source.normal_size_p = malloc(0);
			collada_source.normal_p = malloc(0);
		#endif
		#ifdef C_OUT_TEXCOORD
			collada_source.texcoord_size_p = malloc(0);
			collada_source.texcoord_p = malloc(0);
		#endif
		collada_source.p_size_p = malloc(0);
		collada_source.p_p = malloc(0);

		uint32_t v_index = 0;

		char state;
		while ((state = file_reader_match(file_p, (const char*[]){"</library_geometries>", "<geometry"}, 2)))
		{
			file_reader_match(file_p, (const char*[]){"\""}, 1);
			collada_source.data_p = file_reader_char_p(file_p, "\t", "-", collada_source.data_p, &collada_source.max_data);
			graphic_reader_sanitize(collada_source.data_p[v_index]);

			size_t fs_size = collada_source.max_data * sizeof(float*);
			size_t is_size = collada_source.max_data * sizeof(int*);
			size_t ui_size = collada_source.max_data * sizeof(uint32_t);

			file_reader_match(file_p, (const char*[]){"positions-array"}, 1);
			file_reader_match(file_p, (const char*[]){">"}, 1);
			collada_source.vertex_size_p = realloc(collada_source.vertex_size_p, ui_size);
			collada_source.vertex_size_p[v_index] = 0;
			collada_source.vertex_p = realloc(collada_source.vertex_p, fs_size);
			collada_source.vertex_p[v_index] = malloc(0);
			collada_source.vertex_p[v_index] = file_reader_float(file_p, "</float_array>", collada_source.vertex_p[v_index], &collada_source.vertex_size_p[v_index]);

			#ifdef C_OUT_NORMAL
				file_reader_match(file_p, (const char*[]){"normals-array"}, 1);
				file_reader_match(file_p, (const char*[]){">"}, 1);
				collada_source.normal_size_p = realloc(collada_source.normal_size_p, ui_size);
				collada_source.normal_size_p[v_index] = 0;
				collada_source.normal_p = realloc(collada_source.normal_p, fs_size);
				collada_source.normal_p[v_index] = malloc(0);
				collada_source.normal_p[v_index] = file_reader_float(file_p, "</float_array>", collada_source.normal_p[v_index], &collada_source.normal_size_p[v_index]);
			#endif

			#ifdef C_OUT_TEXCOORD
				file_reader_match(file_p, (const char*[]){"map-0-array"}, 1);
				file_reader_match(file_p, (const char*[]){">"}, 1);
				collada_source.texcoord_size_p = realloc(collada_source.texcoord_size_p, ui_size);
				collada_source.texcoord_size_p[v_index] = 0;
				collada_source.texcoord_p = realloc(collada_source.texcoord_p, fs_size);
				collada_source.texcoord_p[v_index] = malloc(0);
				collada_source.texcoord_p[v_index] = file_reader_float(file_p, "</float_array>", collada_source.texcoord_p[v_index], &collada_source.texcoord_size_p[v_index]);
			#endif

			file_reader_match(file_p, (const char*[]){"<p>"}, 1);
			collada_source.p_size_p = realloc(collada_source.p_size_p, ui_size);
			collada_source.p_size_p[v_index] = 0;
			collada_source.p_p = realloc(collada_source.p_p, is_size);
			collada_source.p_p[v_index] = malloc(0);
			collada_source.p_p[v_index] = file_reader_int(file_p, "</p>", collada_source.p_p[v_index], &collada_source.p_size_p[v_index]);
			++v_index;
		}
	}

	if (collada_source.is_animated)
	{
		file_reader_match(file_p, (const char*[]){"<library_controllers>"}, 1);

		collada_source.vcount_size_p = malloc(0);
		collada_source.vcount_p = malloc(0);
		collada_source.weight_size_p = malloc(0);
		collada_source.weight_p = malloc(0);
		collada_source.v_size_p = malloc(0);
		collada_source.v_p = malloc(0);

		uint32_t v_index = 0;

		char state;
		while ((state = file_reader_match(file_p, (const char*[]){"</library_controllers>", "<controller"}, 2)))
		{
			size_t cs2_size = collada_source.max_data * sizeof(char**);
			size_t fs_size = collada_source.max_data * sizeof(float*);
			size_t is_size = collada_source.max_data * sizeof(int*);
			size_t ui_size = collada_source.max_data * sizeof(uint32_t);

			file_reader_match(file_p, (const char*[]){"joints-array"}, 1);
			file_reader_match(file_p, (const char*[]){">"}, 1);

			if (v_index == 0)
			{
				uint32_t max_bone = 0;
				collada_source.joint_p = malloc(0);
				collada_source.joint_p = file_reader_char_p(file_p, " ", "</Name_array>", collada_source.joint_p, &max_bone);

				for (uint32_t j = 0; j < max_bone; ++j)
				{
					graphic_reader_sanitize(collada_source.joint_p[j]);
				}

				file_reader_match(file_p, (const char*[]){"bind_poses-array"}, 1);
				file_reader_match(file_p, (const char*[]){">"}, 1);
				max_bone = 0;
				collada_source.bind_pose_p = malloc(0);
				collada_source.bind_pose_p = file_reader_float(file_p, "</float_array>", collada_source.bind_pose_p, &max_bone);
			}

			file_reader_match(file_p, (const char*[]){"weights-array"}, 1);
			file_reader_match(file_p, (const char*[]){">"}, 1);
			collada_source.weight_size_p = realloc(collada_source.weight_size_p, ui_size);
			collada_source.weight_size_p[v_index] = 0;
			collada_source.weight_p = realloc(collada_source.weight_p, fs_size);
			collada_source.weight_p[v_index] = 0;
			collada_source.weight_p[v_index] = file_reader_float(file_p, "</float_array>", collada_source.weight_p[v_index], &collada_source.weight_size_p[v_index]);

			file_reader_match(file_p, (const char*[]){"<vcount>"}, 1);
			collada_source.vcount_size_p = realloc(collada_source.vcount_size_p, ui_size);
			collada_source.vcount_size_p[v_index] = 0;
			collada_source.vcount_p = realloc(collada_source.vcount_p, is_size);
			collada_source.vcount_p[v_index] = 0;
			collada_source.vcount_p[v_index] = file_reader_int(file_p, "</vcount>", collada_source.vcount_p[v_index], &collada_source.vcount_size_p[v_index]);

			file_reader_match(file_p, (const char*[]){"<v>"}, 1);
			collada_source.v_size_p = realloc(collada_source.v_size_p, ui_size);
			collada_source.v_size_p[v_index] = 0;
			collada_source.v_p = realloc(collada_source.v_p, is_size);
			collada_source.v_p[v_index] = 0;
			collada_source.v_p[v_index] = file_reader_int(file_p, "</v>", collada_source.v_p[v_index], &collada_source.v_size_p[v_index]);
			++v_index;
		}

		file_reader_match(file_p, (const char*[]){"name=\""}, 1);
		collada_source.armature_size = 0;
		collada_source.armature_p = malloc(0);
		collada_source.armature_p = file_reader_char_p(file_p, "\t", "\"", collada_source.armature_p, &collada_source.armature_size);

		file_reader_match(file_p, (const char*[]){"</animation>"}, 1);

		// collada_source.time_size_p = 0;
		// collada_source.time_p = malloc(0);
		collada_source.transform_size = 0;
		collada_source.transform_p = malloc(0);
		collada_source.v_bone_size = 0;
		collada_source.v_bone_p = malloc(0);

		for (int l = 0; l < collada_source.max_bone; ++l)
		{
			file_reader_match(file_p, (const char*[]){"<float_array"}, 1);
			// file_reader_match(file_p, (const char*[]){">"}, 1);
			// collada_source.time_p = file_reader_float(file_p, "</float_array>", collada_source.time_p, &collada_source.time_size_p);

			file_reader_match(file_p, (const char*[]){"<float_array"}, 1);
			file_reader_match(file_p, (const char*[]){">"}, 1);
			collada_source.transform_p = file_reader_float(file_p, "</float_array>", collada_source.transform_p, &collada_source.transform_size);

			file_reader_match(file_p, (const char*[]){"target=\""}, 1);
			file_reader_match(file_p, (const char*[]){collada_source.armature_p[0]}, 1);
			file_reader_match(file_p, (const char*[]){"_"}, 1);
			collada_source.v_bone_p = file_reader_char_p(file_p, "\t", "/", collada_source.v_bone_p, &collada_source.v_bone_size);
			graphic_reader_sanitize(collada_source.v_bone_p[collada_source.v_bone_size - 1]);
		}

		graphic_reader_makeBones(&collada_source);
	}

	if (collada_source.is_animated && C_FIX_ANIMATED)
	{
		graphic_reader_fixAnimation(&collada_source);
	}

	graphic_reader_mix(&collada_source);

	collada_source.max_joint_p = malloc(sizeof(uint8_t) * collada_source.max_data);
	if (collada_source.is_animated)
	{
		for (uint32_t m = 0; m < collada_source.max_data; ++m)
		{
			collada_source.max_joint_p[m] = 0;
			uint32_t collada_pack_size = collada_source.collada_pack_size_p[m];
			for (uint32_t p = 0; p < collada_pack_size; ++p)
			{
				collada_Pack collada_pack = collada_source.collada_pack_p[m][p];
				if (collada_source.max_joint_p[m] < collada_pack.max_bone)
				{
					collada_source.max_joint_p[m] = collada_pack.max_bone;
				}
			}
		}
	}

	file_writer_collada(&collada_source, out_char_p);
	free(out_char_p);

	fclose(file_p);
	free(d_name_char_p);

	//s0-free
	if (collada_source.is_animated)
	{
		for (uint32_t b = 0; b < collada_source.max_bone; ++b)
		{
			collada_Bone collada_bone = collada_source.collada_bone_p[b];
			for (uint32_t i = 0; i < collada_bone.name_size; ++i)
			{
				free(collada_bone.name_p[i]);
			}
			free(collada_bone.name_p);

			free(collada_bone.visual_p);

			free(collada_source.joint_p[b]);
		}
		free(collada_source.collada_bone_p);

		free(collada_source.joint_p);
		free(collada_source.bind_pose_p);

		free(collada_source.space_p);

		for (uint32_t b = 0; b < collada_source.max_bone; ++b)
		{
			free(collada_source.bone_p[b]);
		}
		free(collada_source.bone_p);
		free(collada_source.bone_size_p);

		for (uint32_t b = 0; b < collada_source.v_bone_size; ++b)
		{
			free(collada_source.v_bone_p[b]);
		}
		free(collada_source.v_bone_p);

		// free(collada_source.time_p);
		free(collada_source.transform_p);

		for (uint32_t a = 0; a < collada_source.armature_size; ++a)
		{
			free(collada_source.armature_p[a]);
		}
		free(collada_source.armature_p);
	}

	for (uint32_t m = 0; m < collada_source.max_data; ++m)
	{
		free(collada_source.data_p[m]);

		free(collada_source.vertex_p[m]);
		#ifdef C_OUT_NORMAL
			free(collada_source.normal_p[m]);
		#endif
		#ifdef C_OUT_TEXCOORD
			free(collada_source.texcoord_p[m]);
		#endif

		free(collada_source.p_p[m]);

		free(collada_source.index_p[m]);

		if (collada_source.is_animated)
		{
			free(collada_source.v_p[m]);
			free(collada_source.vcount_p[m]);
			free(collada_source.weight_p[m]);

			for (uint32_t p = 0; p < collada_source.collada_pack_size_p[m]; ++p)
			{
				collada_Pack collada_pack = collada_source.collada_pack_p[m][p];
				free(collada_pack.joint_p);
				free(collada_pack.weight_p);
			}
		}

		free(collada_source.collada_pack_p[m]);
	}
	free(collada_source.data_p);
	free(collada_source.max_joint_p);

	free(collada_source.vertex_p);
	free(collada_source.vertex_size_p);
	#ifdef C_OUT_NORMAL
		free(collada_source.normal_p);
		free(collada_source.normal_size_p);
	#endif
	#ifdef C_OUT_TEXCOORD
		free(collada_source.texcoord_p);
		free(collada_source.texcoord_size_p);
	#endif

	free(collada_source.p_p);
	free(collada_source.p_size_p);

	if (collada_source.is_animated)
	{
		free(collada_source.v_p);
		free(collada_source.v_size_p);

		free(collada_source.vcount_p);
		free(collada_source.vcount_size_p);

		free(collada_source.weight_p);
		free(collada_source.weight_size_p);
	}

	free(collada_source.index_p);
	free(collada_source.index_size_p);

	free(collada_source.collada_pack_p);
	free(collada_source.collada_pack_size_p);
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

	DIR *dir_p = opendir(C_IN);
	nali_log("opendir %p", dir_p);

	struct dirent *dirent_p;
	while ((dirent_p = readdir(dir_p)) != NULL)
	{
		char *d_name_char_p = strdup(dirent_p->d_name);
		// // size_t size = strlen(d_name_p) + 1;
		// // char *name_p = malloc(size);
		// // memcpy(name_p, d_name_p, size);
		// struct stat _stat;

		char *file_char_p = malloc(sizeof(C_IN)-1 + 1 + strlen(d_name_char_p) + 1);
		strcpy(file_char_p, C_IN);
		strcat(file_char_p, "/");
		strcat(file_char_p, d_name_char_p);

		// if (stat(file_char_p, &_stat))
		// {
		// 	error("stat")
		// }

		// if (S_ISREG(_stat.st_mode))//S_ISDIR
		if (dirent_p->d_type == DT_REG)
		{
			void **arg = malloc(sizeof(void *) * 2);
			arg[0] = d_name_char_p;
			arg[1] = file_char_p;
			nali_info("thrd_create %d", thrd_create(&(thrd_t){}, skin, arg))

			++thrd;
		}
		else
		{
			free(file_char_p);
		}
	}

	closedir(dir_p);

	while (thrd){}
}
