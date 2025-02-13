void file_writer_collada(const collada_Source* collada_source_ptr, const char* path)
{
	const uint32_t max_data = collada_source_ptr->max_data;
	for (uint32_t md = 0; md < max_data; ++md)
	{
		const uint32_t collada_pack_size = collada_source_ptr->collada_pack_size_ptr[md];
		const char* data_ptr = collada_source_ptr->data_ptr[md];

		char* n0_ptr = math_combine(path, data_ptr);
		mkdir(n0_ptr, 0700);

		char* n1_ptr = math_combine(n0_ptr, C_INDEX_FILE);
		FILE* index_file = fopen(n1_ptr, "wb");
		fwrite(collada_source_ptr->index_ptr[md], sizeof(float), collada_source_ptr->index_size_ptr[md], index_file);
		free(n1_ptr);
		fclose(index_file);

		n1_ptr = math_combine(n0_ptr, C_VERTEX_FILE);
		remove(n1_ptr);
		FILE* vertex_file = fopen(n1_ptr, "ab");
		free(n1_ptr);

		#ifdef C_OUT_NORMAL
			n1_ptr = math_combine(n0_ptr, C_NORMAL_FILE);
			remove(n1_ptr);
			FILE* normal_file = fopen(n1_ptr, "ab");
			free(n1_ptr);
		#endif

		#ifdef C_OUT_TEXCOORD
			n1_ptr = math_combine(n0_ptr, C_TEXCOORD_FILE);
			remove(n1_ptr);
			FILE* texcoord_file = fopen(n1_ptr, "ab");
			free(n1_ptr);
		#endif

		FILE* joint_file;
		FILE* weight_file;
		if (collada_source_ptr->is_animated)
		{
			n1_ptr = math_combine(n0_ptr, C_JOINT_FILE);
			remove(n1_ptr);
			joint_file = fopen(n1_ptr, "ab");
			free(n1_ptr);

			n1_ptr = math_combine(n0_ptr, C_WEIGHT_FILE);
			remove(n1_ptr);
			weight_file = fopen(n1_ptr, "ab");
			free(n1_ptr);
		}

		const uint8_t max_joint = collada_source_ptr->max_joint_ptr[md];
		for (uint32_t p = 0; p < collada_pack_size; ++p)
		{
			const collada_Pack collada_pack = collada_source_ptr->collada_pack_ptr[md][p];
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

			if (collada_source_ptr->is_animated)
			{
				fwrite(collada_pack.joint_ptr, sizeof(uint8_t), max_joint, joint_file);
				fwrite(collada_pack.weight_ptr, sizeof(float), max_joint, weight_file);
				// for (uint8_t i = 0; i < 4; ++i)
				// {
				// 	// if (collada_pack.weight_ptr[i] != 0 && collada_pack.weight_ptr[i] != 1)
				// 	if (collada_pack.weight_ptr[i] > 0.4 && collada_pack.weight_ptr[i] < 0.6)
				// 	{
				// 		float aa = collada_pack.weight_ptr[i];
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

		if (collada_source_ptr->is_animated)
		{
			fclose(joint_file);
			fclose(weight_file);
		}

		free(n0_ptr);
	}

	if (collada_source_ptr->is_animated)
	{
		const uint8_t max_bone = collada_source_ptr->max_bone;

		mkdir(path, 0700);
		char* n1_ptr = math_combine(path, C_BINDPOSE_FILE);
		FILE* file = fopen(n1_ptr, "wb");
		fwrite(collada_source_ptr->bind_pose_ptr, sizeof(float), max_bone * 16, file);
		// float* bind_pose_ptr = collada_source_ptr->bind_pose_ptr;
		// for (uint8_t mb = 0; mb < max_bone; ++mb)
		// {
		// 	fwrite(bind_pose_ptr, sizeof(float), (16 - 4), file);
		// 	bind_pose_ptr += 16 - 4;
		// 	if (*bind_pose_ptr != 0)
		// 	{
		// 		info("bp0 !0");
		// 	}
		// 	++bind_pose_ptr;
		// 	if (*bind_pose_ptr != 0)
		// 	{
		// 		info("bp1 !0");
		// 	}
		// 	++bind_pose_ptr;
		// 	if (*bind_pose_ptr != 0)
		// 	{
		// 		info("bp2 !0");
		// 	}
		// 	++bind_pose_ptr;
		// 	if (*bind_pose_ptr != 1)
		// 	{
		// 		info("bp3 !1");
		// 	}
		// 	++bind_pose_ptr;
		// }

		free(n1_ptr);
		fclose(file);

		n1_ptr = math_combine(path, C_TRANSFORM_FILE);
		file = fopen(n1_ptr, "wb");
		fwrite(collada_source_ptr->transform_ptr, sizeof(float), max_bone * collada_source_ptr->max_frame * 16, file);
		// float* transform_ptr = collada_source_ptr->transform_ptr;
		// for (uint32_t mb = 0; mb < max_bone * collada_source_ptr->max_frame; ++mb)
		// {
		// 	fwrite(transform_ptr, sizeof(float), (16 - 4), file);
		// 	transform_ptr += 16 - 4;
		// 	if (*transform_ptr != 0)
		// 	{
		// 		info("a0 !0");
		// 	}
		// 	++transform_ptr;
		// 	if (*transform_ptr != 0)
		// 	{
		// 		info("a1 !0");
		// 	}
		// 	++transform_ptr;
		// 	if (*transform_ptr != 0)
		// 	{
		// 		info("a2 !0");
		// 	}
		// 	++transform_ptr;
		// 	if (*transform_ptr != 1)
		// 	{
		// 		info("a3 !1");
		// 	}
		// 	++transform_ptr;
		// }

		free(n1_ptr);
		fclose(file);

		n1_ptr = math_combine(path, "_Doc");
		mkdir(n1_ptr, 0700);

		char* n2_ptr = math_combine(n1_ptr, "/bone.dat");
		file = fopen(n2_ptr, "w");
		for (uint8_t mb = 0; mb < max_bone; ++mb)
		{
			const collada_Bone collada_bone = collada_source_ptr->collada_bone_ptr[mb];
			fwrite(collada_bone.name_ptr[0], sizeof(char), strlen(collada_bone.name_ptr[0]), file);
			if (mb != max_bone - 1)
			{
				char n = '\n';
				fwrite(&n, sizeof(char), 1, file);
			}
		}
		free(n2_ptr);
		fclose(file);

		n2_ptr = math_combine(n1_ptr, "/joint.dat");
		file = fopen(n2_ptr, "w");
		for (uint32_t md = 0; md < max_data; ++md)
		{
			// uint8_t max_joint = 0;
			// for (uint32_t j = 0; j < collada_source_ptr->vcount_size_ptr[m]; ++j)
			// {
			// 	if (max_joint < collada_source_ptr->vcount_ptr[m][j])
			// 	{
			// 		max_joint = collada_source_ptr->vcount_ptr[m][j];
			// 	}
			// }
			fwrite(path, sizeof(char), strlen(path), file);
			fwrite(collada_source_ptr->data_ptr[md], sizeof(char), strlen(collada_source_ptr->data_ptr[md]), file);
			char n = ' ';
			fwrite(&n, sizeof(char), 1, file);
			char* n_ptr = math_get(collada_source_ptr->max_joint_ptr[md]);
			fwrite(n_ptr, sizeof(uint8_t), 1, file);
			free(n_ptr);
			if (md != max_data - 1)
			{
				n = '\n';
				fwrite(&n, sizeof(char), 1, file);
				// info("%s%s %d\n", path, collada_source_ptr->data_ptr[m], max_joint)
			}
		}
		free(n2_ptr);
		fclose(file);

		free(n1_ptr);

		n1_ptr = math_combine(path, "/bone/");
		mkdir(n1_ptr, 0700);

		for (uint8_t mb = 0; mb < max_bone; ++mb)
		{
			char* n_ptr = math_get(mb);
			n2_ptr = math_combine(n1_ptr, n_ptr);
			free(n_ptr);
			n_ptr = math_combine(n2_ptr, ".bin");
			free(n2_ptr);
			file = fopen(n_ptr, "wb");
			fwrite(collada_source_ptr->bone_ptr[mb], sizeof(uint8_t), collada_source_ptr->bone_size_ptr[mb], file);
			free(n_ptr);
			fclose(file);
		}

		free(n1_ptr);
	}
}
