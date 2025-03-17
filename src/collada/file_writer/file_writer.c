void file_writer_collada(const collada_Source* collada_source_p, const char* path)
{
	const uint32_t max_data = collada_source_p->max_data;
	for (uint32_t md = 0; md < max_data; ++md)
	{
		const uint32_t collada_pack_size = collada_source_p->collada_pack_size_p[md];
		const char* data_p = collada_source_p->data_p[md];

		char* n0_p = math_combine(path, data_p);
		mkdir(n0_p, 0700);

		char* n1_p = math_combine(n0_p, C_INDEX_FILE);
		FILE* index_file = fopen(n1_p, "wb");
		fwrite(collada_source_p->index_p[md], sizeof(float), collada_source_p->index_size_p[md], index_file);
		free(n1_p);
		fclose(index_file);

		n1_p = math_combine(n0_p, C_VERTEX_FILE);
		remove(n1_p);
		FILE* vertex_file = fopen(n1_p, "ab");
		free(n1_p);

		#ifdef C_OUT_NORMAL
			n1_p = math_combine(n0_p, C_NORMAL_FILE);
			remove(n1_p);
			FILE* normal_file = fopen(n1_p, "ab");
			free(n1_p);
		#endif

		#ifdef C_OUT_TEXCOORD
			n1_p = math_combine(n0_p, C_TEXCOORD_FILE);
			remove(n1_p);
			FILE* texcoord_file = fopen(n1_p, "ab");
			free(n1_p);
		#endif

		FILE* joint_file;
		FILE* weight_file;
		if (collada_source_p->is_animated)
		{
			n1_p = math_combine(n0_p, C_JOINT_FILE);
			remove(n1_p);
			joint_file = fopen(n1_p, "ab");
			free(n1_p);

			n1_p = math_combine(n0_p, C_WEIGHT_FILE);
			remove(n1_p);
			weight_file = fopen(n1_p, "ab");
			free(n1_p);
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

		free(n0_p);
	}

	if (collada_source_p->is_animated)
	{
		const uint8_t max_bone = collada_source_p->max_bone;

		mkdir(path, 0700);
		char* n1_p = math_combine(path, C_BINDPOSE_FILE);
		FILE* file = fopen(n1_p, "wb");
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

		free(n1_p);
		fclose(file);

		n1_p = math_combine(path, C_TRANSFORM_FILE);
		file = fopen(n1_p, "wb");
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

		free(n1_p);
		fclose(file);

		n1_p = math_combine(path, "_Doc");
		mkdir(n1_p, 0700);

		char* n2_p = math_combine(n1_p, "/bone.dat");
		file = fopen(n2_p, "w");
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
		free(n2_p);
		fclose(file);

		n2_p = math_combine(n1_p, "/joint.dat");
		file = fopen(n2_p, "w");
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
			char n = ' ';
			fwrite(&n, sizeof(char), 1, file);
			char* n_p = math_get(collada_source_p->max_joint_p[md]);
			fwrite(n_p, sizeof(uint8_t), 1, file);
			free(n_p);
			if (md != max_data - 1)
			{
				n = '\n';
				fwrite(&n, sizeof(char), 1, file);
				// info("%s%s %d\n", path, collada_source_p->data_p[m], max_joint)
			}
		}
		free(n2_p);
		fclose(file);

		free(n1_p);

		n1_p = math_combine(path, "/bone/");
		mkdir(n1_p, 0700);

		for (uint8_t mb = 0; mb < max_bone; ++mb)
		{
			char* n_p = math_get(mb);
			n2_p = math_combine(n1_p, n_p);
			free(n_p);
			n_p = math_combine(n2_p, ".bin");
			free(n2_p);
			file = fopen(n_p, "wb");
			fwrite(collada_source_p->bone_p[mb], sizeof(uint8_t), collada_source_p->bone_size_p[mb], file);
			free(n_p);
			fclose(file);
		}

		free(n1_p);
	}
}
