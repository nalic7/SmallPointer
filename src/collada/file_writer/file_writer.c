void file_writer_collada(const collada_Source* collada_source_p, const char* path)
{
	const uint32_t max_data = collada_source_p->max_data;

	uint32_t path_name_size = strlen(path) + 1;
	char* n0_p = malloc(path_name_size);
	strcpy(n0_p, path);

	for (uint32_t md = 0; md < max_data; ++md)
	{
		const uint32_t collada_pack_size = collada_source_p->collada_pack_size_p[md];
		const char* data_p = collada_source_p->data_p[md];

		uint32_t file_name_size = path_name_size + strlen(data_p);
		n0_p = realloc(n0_p, file_name_size);
		n0_p[path_name_size - 1] = '\0';
		strcat(n0_p, data_p);

		mkdir(n0_p, 0700);
		n0_p = realloc(n0_p, file_name_size + sizeof(C_INDEX_FILE)-1);
		n0_p[file_name_size - 1] = '\0';
		strcat(n0_p, C_INDEX_FILE);

		FILE* index_file = fopen(n0_p, "wb");
		fwrite(collada_source_p->index_p[md], sizeof(float), collada_source_p->index_size_p[md], index_file);
		fclose(index_file);

		n0_p = realloc(n0_p, file_name_size + sizeof(C_VERTEX_FILE)-1);
		n0_p[file_name_size - 1] = '\0';
		strcat(n0_p, C_VERTEX_FILE);
		remove(n0_p);
		FILE* vertex_file = fopen(n0_p, "ab");

		#ifdef C_OUT_NORMAL
			n0_p = realloc(n0_p, file_name_size + sizeof(C_NORMAL_FILE)-1);
			n0_p[file_name_size - 1] = '\0';
			strcat(n0_p, C_NORMAL_FILE);
			remove(n0_p);
			FILE* normal_file = fopen(n0_p, "ab");
		#endif

		#ifdef C_OUT_TEXCOORD
			n0_p = realloc(n0_p, file_name_size + sizeof(C_TEXCOORD_FILE)-1);
			n0_p[file_name_size - 1] = '\0';
			strcat(n0_p, C_TEXCOORD_FILE);
			remove(n0_p);
			FILE* texcoord_file = fopen(n0_p, "ab");
		#endif

		FILE* joint_file;
		FILE* weight_file;
		if (collada_source_p->is_animated)
		{
			n0_p = realloc(n0_p, file_name_size + sizeof(C_JOINT_FILE)-1);
			n0_p[file_name_size - 1] = '\0';
			strcat(n0_p, C_JOINT_FILE);
			remove(n0_p);
			joint_file = fopen(n0_p, "ab");

			n0_p = realloc(n0_p, file_name_size + sizeof(C_WEIGHT_FILE)-1);
			n0_p[file_name_size - 1] = '\0';
			strcat(n0_p, C_WEIGHT_FILE);
			remove(n0_p);
			weight_file = fopen(n0_p, "ab");
		}

		const uint8_t max_joint = collada_source_p->max_joint_p[md];
		for (uint32_t p = 0; p < collada_pack_size; ++p)
		{
			const collada_Pack collada_pack = collada_source_p->collada_pack_p[md][p];
			fwrite(&collada_pack.p_x, sizeof(float), 1, vertex_file);
			fwrite(&collada_pack.p_y, sizeof(float), 1, vertex_file);
			fwrite(&collada_pack.p_z, sizeof(float), 1, vertex_file);

			#ifdef C_OUT_NORMAL
				fwrite(&collada_pack.n_x, sizeof(float), 1, normal_file);
				fwrite(&collada_pack.n_y, sizeof(float), 1, normal_file);
				fwrite(&collada_pack.n_z, sizeof(float), 1, normal_file);
			#endif

			#ifdef C_OUT_TEXCOORD
				fwrite(&collada_pack.t_x, sizeof(float), 1, texcoord_file);
				fwrite(&collada_pack.t_y, sizeof(float), 1, texcoord_file);
			#endif

			if (collada_source_p->is_animated)
			{
				fwrite(collada_pack.joint_p, sizeof(uint8_t), max_joint, joint_file);
				fwrite(collada_pack.weight_p, sizeof(float), max_joint, weight_file);
				// for (uint8_t i = 0; i < 4; ++i)
				// {
				// 	// if (collada_pack.weight_p[i] != 0 && collada_pack.weight_p[i] != 1)
				// 	if (collada_pack.weight_p[i] > 0.4 && collada_pack.weight_p[i] < 0.6)
				// 	{
				// 		float aa = collada_pack.weight_p[i];
				// 	}
				// }
			}
		}

		fclose(vertex_file);
		#ifdef C_OUT_NORMAL
			fclose(normal_file);
		#endif
		#ifdef C_OUT_TEXCOORD
			fclose(texcoord_file);
		#endif

		if (collada_source_p->is_animated)
		{
			fclose(joint_file);
			fclose(weight_file);
		}
	}

	if (collada_source_p->is_animated)
	{
		const uint8_t max_bone = collada_source_p->max_bone;

		mkdir(path, 0700);

		n0_p = realloc(n0_p, path_name_size + sizeof(C_BINDPOSE_FILE)-1);
		n0_p[path_name_size - 1] = '\0';
		strcat(n0_p, C_BINDPOSE_FILE);
		FILE* file = fopen(n0_p, "wb");
		fwrite(collada_source_p->bind_pose_p, sizeof(float), max_bone * 16, file);
		// float* bind_pose_p = collada_source_p->bind_pose_p;
		// for (uint8_t mb = 0; mb < max_bone; ++mb)
		// {
		// 	fwrite(bind_pose_p, sizeof(float), (16 - 4), file);
		// 	bind_pose_p += 16 - 4;
		// 	if (*bind_pose_p != 0)
		// 	{
		// 		info("bp0 !0");
		// 	}
		// 	++bind_pose_p;
		// 	if (*bind_pose_p != 0)
		// 	{
		// 		info("bp1 !0");
		// 	}
		// 	++bind_pose_p;
		// 	if (*bind_pose_p != 0)
		// 	{
		// 		info("bp2 !0");
		// 	}
		// 	++bind_pose_p;
		// 	if (*bind_pose_p != 1)
		// 	{
		// 		info("bp3 !1");
		// 	}
		// 	++bind_pose_p;
		// }

		fclose(file);

		n0_p = realloc(n0_p, path_name_size + sizeof(C_TRANSFORM_FILE)-1);
		n0_p[path_name_size - 1] = '\0';
		strcat(n0_p, C_TRANSFORM_FILE);
		file = fopen(n0_p, "wb");
		fwrite(collada_source_p->transform_p, sizeof(float), max_bone * collada_source_p->max_frame * 16, file);
		// float* transform_p = collada_source_p->transform_p;
		// for (uint32_t mb = 0; mb < max_bone * collada_source_p->max_frame; ++mb)
		// {
		// 	fwrite(transform_p, sizeof(float), (16 - 4), file);
		// 	transform_p += 16 - 4;
		// 	if (*transform_p != 0)
		// 	{
		// 		info("a0 !0");
		// 	}
		// 	++transform_p;
		// 	if (*transform_p != 0)
		// 	{
		// 		info("a1 !0");
		// 	}
		// 	++transform_p;
		// 	if (*transform_p != 0)
		// 	{
		// 		info("a2 !0");
		// 	}
		// 	++transform_p;
		// 	if (*transform_p != 1)
		// 	{
		// 		info("a3 !1");
		// 	}
		// 	++transform_p;
		// }

		fclose(file);

		uint32_t doc_name_size = path_name_size + sizeof(C_DOC_FILE)-1;
		n0_p = realloc(n0_p, doc_name_size);
		n0_p[path_name_size - 1] = '\0';
		strcat(n0_p, C_DOC_FILE);
		mkdir(n0_p, 0700);

		n0_p = realloc(n0_p, doc_name_size + sizeof(C_DOC_BONE_FILE)-1);
		n0_p[doc_name_size - 1] = '\0';
		strcat(n0_p, C_DOC_BONE_FILE);
		file = fopen(n0_p, "w");
		for (uint8_t mb = 0; mb < max_bone; ++mb)
		{
			const collada_Bone collada_bone = collada_source_p->collada_bone_p[mb];
			fwrite(collada_bone.name_p[0], sizeof(char), strlen(collada_bone.name_p[0]), file);
			if (mb != max_bone - 1)
			{
				char n = '\n';
				fwrite(&n, sizeof(char), 1, file);
			}
		}
		fclose(file);

		n0_p = realloc(n0_p, doc_name_size + sizeof(C_DOC_JOINT_FILE)-1);
		n0_p[doc_name_size - 1] = '\0';
		strcat(n0_p, C_DOC_JOINT_FILE);
		file = fopen(n0_p, "w");
		char n[2];
		for (uint32_t md = 0; md < max_data; ++md)
		{
			// uint8_t max_joint = 0;
			// for (uint32_t j = 0; j < collada_source_p->vcount_size_p[m]; ++j)
			// {
			// 	if (max_joint < collada_source_p->vcount_p[m][j])
			// 	{
			// 		max_joint = collada_source_p->vcount_p[m][j];
			// 	}
			// }
			fwrite(path, sizeof(char), strlen(path), file);
			fwrite(collada_source_p->data_p[md], sizeof(char), strlen(collada_source_p->data_p[md]), file);
			fwrite(&(char){' '}, sizeof(char), 1, file);
			sprintf(n, "%hhu", collada_source_p->max_joint_p[md]);
			fwrite(&n, sizeof(char), 1, file);
			if (md != max_data - 1)
			{
				fwrite(&(char){'\n'}, sizeof(char), 1, file);
				// info("%s%s %d\n", path, collada_source_p->data_p[m], max_joint)
			}
		}
		fclose(file);

		uint32_t bone_name_size = path_name_size + sizeof(C_BONE_FILE)-1;
		n0_p = realloc(n0_p, bone_name_size);
		n0_p[path_name_size - 1] = '\0';
		strcat(n0_p, C_BONE_FILE);
		mkdir(n0_p, 0700);

		uint32_t bone_name_number_size;
		for (uint8_t mb = 0; mb < max_bone; ++mb)
		{
			bone_name_number_size = bone_name_size + math_length(mb);
			n0_p = realloc(n0_p, bone_name_number_size + sizeof(C_BIN_FILE)-1);
			sprintf(n0_p + bone_name_size - 1, "%u", mb);
			n0_p[bone_name_number_size - 1] = '\0';
			strcat(n0_p, C_BIN_FILE);
			file = fopen(n0_p, "wb");
			fwrite(collada_source_p->bone_p[mb], sizeof(uint8_t), collada_source_p->bone_size_p[mb], file);
			fclose(file);
		}

		free(n0_p);
	}
}
