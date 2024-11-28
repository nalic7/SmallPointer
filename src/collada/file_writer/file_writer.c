#include <stdint.h>
void file_writer_collada(collada_Source* collada_source_ptr, const char* path)
{
	uint32_t max_data = collada_source_ptr->max_data;
	for (uint32_t m = 0; m < max_data; ++m)
	{
		uint32_t collada_pack_size = collada_source_ptr->collada_pack_size_ptr[m];
		char* name_ptr = collada_source_ptr->data_ptr[m];

		char* n0_ptr = math_combine(path, name_ptr);
		mkdir(n0_ptr, 0700);

		char* n1_ptr = math_combine(n0_ptr, C_INDEX_FILE);
		FILE* index_file = fopen(n1_ptr, "wb");
		fwrite(collada_source_ptr->index_ptr[m], sizeof(float), collada_source_ptr->index_size_ptr[m], index_file);
		free(n1_ptr);
		fclose(index_file);

		n1_ptr = math_combine(n0_ptr, C_VERTEX_FILE);
		remove(n1_ptr);
		FILE* vertex_file = fopen(n1_ptr, "ab");
		free(n1_ptr);

		n1_ptr = math_combine(n0_ptr, C_NORMAL_FILE);
		remove(n1_ptr);
		FILE* normal_file = fopen(n1_ptr, "ab");
		free(n1_ptr);

		n1_ptr = math_combine(n0_ptr, C_TEXCOORD_FILE);
		remove(n1_ptr);
		FILE* texcoord_file = fopen(n1_ptr, "ab");
		free(n1_ptr);

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

		uint8_t max_joint = collada_source_ptr->max_joint_ptr[m];
		for (uint32_t p = 0; p < collada_pack_size; ++p)
		{
			collada_Pack collada_pack = collada_source_ptr->collada_pack_ptr[m][p];
			fwrite(&collada_pack.p_x, sizeof(float), 1, vertex_file);
			fwrite(&collada_pack.p_y, sizeof(float), 1, vertex_file);
			fwrite(&collada_pack.p_z, sizeof(float), 1, vertex_file);

			fwrite(&collada_pack.n_x, sizeof(float), 1, normal_file);
			fwrite(&collada_pack.n_y, sizeof(float), 1, normal_file);
			fwrite(&collada_pack.n_z, sizeof(float), 1, normal_file);

			fwrite(&collada_pack.t_x, sizeof(float), 1, texcoord_file);
			fwrite(&collada_pack.t_y, sizeof(float), 1, texcoord_file);

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
		fclose(normal_file);
		fclose(texcoord_file);

		if (collada_source_ptr->is_animated)
		{
			fclose(joint_file);
			fclose(weight_file);
		}

		free(n0_ptr);
	}

	if (collada_source_ptr->is_animated)
	{
		uint32_t max_bone = collada_source_ptr->max_bone;

		mkdir(path, 0700);
		char* n1_ptr = math_combine(path, C_BINDPOSE_FILE);
		FILE* file = fopen(n1_ptr, "wb");
		fwrite(collada_source_ptr->bind_pose_ptr, sizeof(float), max_bone * 16, file);
		free(n1_ptr);
		fclose(file);

		n1_ptr = math_combine(path, C_TRANSFORM_FILE);
		file = fopen(n1_ptr, "wb");
		fwrite(collada_source_ptr->transform_ptr, sizeof(float), max_bone * collada_source_ptr->max_frame * 16, file);
		free(n1_ptr);
		fclose(file);

		n1_ptr = math_combine(path, "_Doc");
		mkdir(n1_ptr, 0700);

		char* n2_ptr = math_combine(n1_ptr, "/bone.dat");
		file = fopen(n2_ptr, "w");
		for (uint32_t m = 0; m < max_bone; ++m)
		{
			collada_Bone bonedata = collada_source_ptr->collada_bone_ptr[m];
			fwrite(bonedata.name_ptr[0], sizeof(char), strlen(bonedata.name_ptr[0]), file);
			if (m != max_bone - 1)
			{
				char n = '\n';
				fwrite(&n, sizeof(char), 1, file);
			}
		}
		free(n2_ptr);
		fclose(file);

		n2_ptr = math_combine(n1_ptr, "/joint.dat");
		file = fopen(n2_ptr, "w");
		for (uint32_t m = 0; m < max_data; ++m)
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
			fwrite(collada_source_ptr->data_ptr[m], sizeof(char), strlen(collada_source_ptr->data_ptr[m]), file);
			char n = ' ';
			fwrite(&n, sizeof(char), 1, file);
			char* n_ptr = math_get(collada_source_ptr->max_joint_ptr[m]);
			fwrite(n_ptr, sizeof(uint8_t), 1, file);
			free(n_ptr);
			if (m != max_data - 1)
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

		for (uint32_t m = 0; m < max_bone; ++m)
		{
			char* n_ptr = math_get(m);
			n2_ptr = math_combine(n1_ptr, n_ptr);
			free(n_ptr);
			n_ptr = math_combine(n2_ptr, ".bin");
			free(n2_ptr);
			file = fopen(n_ptr, "wb");
			fwrite(collada_source_ptr->bone_ptr[m], sizeof(uint8_t), collada_source_ptr->bone_size_ptr[m], file);
			free(n_ptr);
			fclose(file);
		}

		free(n1_ptr);
	}
}
