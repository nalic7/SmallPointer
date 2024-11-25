// void graphic_reader_repaste(char *char_ptr, char c_char, char r_char)
// {
// 	while (*char_ptr)
// 	{
// 		if (*char_ptr == c_char)
// 		{
// 			*char_ptr = r_char;
// 		}
// 		++char_ptr;
// 	}
// }

uint32_t graphic_reader_count(char *char_ptr, char c_char)
{
	uint32_t v = 0;

	while (*char_ptr)
	{
		if (*char_ptr == c_char)
		{
			++v;
		}
		++char_ptr;
	}

	return v;
}

void graphic_reader_sanitize(char* char_ptr)
{
	while (*char_ptr)
	{
		if (!isalnum(*char_ptr))
		{
			*char_ptr = '_';
		}
		++char_ptr;
	}
}

void graphic_reader_makeBones(collada_Source *sourcedatatype_ptr)
{
	uint32_t max_data = sourcedatatype_ptr->max_data;
	uint32_t max_bone = sourcedatatype_ptr->max_bone;

	unsigned char** bone_ptr = malloc(sizeof(unsigned char*) * max_bone);
	uint32_t* bone_size_ptr = malloc(sizeof(uint32_t) * max_bone);

	BoneData *bonedata_vector = sourcedatatype_ptr->bonedata_vector;

	for (int w = 0; w < max_bone; ++w)
	{
		for (int y = 0; y < sourcedatatype_ptr->max_bonedata; ++y)
		{
			if (strcmp(sourcedatatype_ptr->joint_ptr[w], bonedata_vector[y].bones_name_string[0]) == 0)
			{
				bone_ptr[w] = malloc(0);

				uint32_t max_z = sourcedatatype_ptr->space_ptr[w];
				uint32_t index = 1;

				for (int z = y - 1; z - 1 > -2; --z)
				{
					uint32_t new_max_z = sourcedatatype_ptr->space_ptr[z];
					if (max_z > new_max_z)
					{
						max_z = new_max_z;
						bone_ptr[w] = realloc(bone_ptr[w], sizeof(unsigned char) * index);
						bone_ptr[w][index - 1] = z;
						++index;
					}
				}

				bone_size_ptr[w] = index;
				break;
			}
		}
	}

	sourcedatatype_ptr->bone_ptr = bone_ptr;
	sourcedatatype_ptr->bone_size_ptr = bone_size_ptr;
}

void graphic_reader_mix(collada_Source* collada_source_ptr)
{
	uint32_t max_object = collada_source_ptr->max_data;

	collada_Pack** collada_pack_ptr = malloc(sizeof(collada_Pack*) * max_object);
	uint32_t* collada_pack_size_ptr = malloc(sizeof(uint32_t) * max_object);

	uint32_t** index_ptr = malloc(sizeof(uint32_t*) * max_object);
	uint32_t* index_size_ptr = malloc(sizeof(uint32_t) * max_object);

	for (uint32_t m = 0; m < max_object; ++m)
	{
		// uint32_t max_joint = collada_source_ptr->max_bone_ptr[m];
		uint32_t p_offset_size = collada_source_ptr->p_offset_size[m];

		collada_pack_ptr[m] = malloc(0);
		collada_pack_size_ptr[m] = 0;

		index_ptr[m] = malloc(0);
		index_size_ptr[m] = 0;

		float
			p_x = 0, p_y = 0, p_z = 0,
			n_x = 0, n_y = 0, n_z = 0,
			t_x = 0, t_y = 0;
		unsigned char* joint_ptr;
		float* weight_ptr;
		unsigned char max_bone = 0;

		for (uint32_t p = 0; p < p_offset_size; ++p)
		{
			uint32_t po = collada_source_ptr->p_offset[m][p];
			unsigned char id = p % 3;

			switch (id)
			{
				case 0:
					uint32_t v = po * 3;
					p_x = collada_source_ptr->vertex_ptr[m][v];
					p_y = collada_source_ptr->vertex_ptr[m][v + 1];
					p_z = collada_source_ptr->vertex_ptr[m][v + 2];

					if (collada_source_ptr->is_animated)
					{
						// joint_ptr = malloc(sizeof(uint32_t) * max_joint);
						// weight_ptr = malloc(sizeof(float) * max_joint);
						joint_ptr = malloc(sizeof(unsigned char) * 4);
						weight_ptr = malloc(sizeof(float) * 4);
						for (unsigned char i = 0; i < 4; ++i)
						{
							joint_ptr[i] = 0;
							weight_ptr[i] = 0;
						}

						uint32_t v_offset_by_p = 0;

						for (uint32_t i = 0; i < po; ++i)
						{
							v_offset_by_p += collada_source_ptr->vcount_offset[m][i];
						}

						v_offset_by_p *= 2;

						int vc = collada_source_ptr->vcount_offset[m][po];

						max_bone = 0;

						while (max_bone < vc)
						{
							uint32_t step = v_offset_by_p + max_bone * 2;
							joint_ptr[max_bone] = collada_source_ptr->v_offset[m][step];
							weight_ptr[max_bone] = collada_source_ptr->weight_ptr[collada_source_ptr->v_offset[m][step + 1]];
							if (weight_ptr[max_bone] == 0)
							{
								info("m%d p%d %s", m, p, collada_source_ptr->data_name_ptr[m]);
							}
							++max_bone;
						}
					}
					break;
				case 1:
					uint32_t n = po * 3;
					n_x = collada_source_ptr->normal_ptr[m][n];
					n_y = collada_source_ptr->normal_ptr[m][n + 1];
					n_z = collada_source_ptr->normal_ptr[m][n + 2];
					break;
				case 2:
					uint32_t t = po * 2;
					t_x = collada_source_ptr->texcoord_ptr[m][t];
					t_y = collada_source_ptr->texcoord_ptr[m][t + 1];
			}

			if (id == 2)
			{
				unsigned char pass = 0;
				uint32_t i = 0;

				while (i < collada_pack_size_ptr[m])
				{
					if
					(
						p_x == collada_pack_ptr[m][i].p_x &&
						p_y == collada_pack_ptr[m][i].p_y &&
						p_z == collada_pack_ptr[m][i].p_z &&

						n_x == collada_pack_ptr[m][i].n_x &&
						n_y == collada_pack_ptr[m][i].n_y &&
						n_z == collada_pack_ptr[m][i].n_z &&

						t_x == collada_pack_ptr[m][i].t_x &&
						t_y == collada_pack_ptr[m][i].t_y
					)
					{
						pass = 1;

						////memory leak
						//for (int j = 0; j < max_joint; ++j)
						for (unsigned char j = 0; j < 4; ++j)
						{
							if
							(
								joint_ptr[j] != collada_pack_ptr[m][i].joint_ptr[j] ||
								weight_ptr[j] != collada_pack_ptr[m][i].weight_ptr[j]
							)
							{
								pass = 0;
								break;
							}
						}

						if (pass == 1)
						{
							break;
						}
					}
					else
					{
						pass = 0;
					}
					++i;
				}

				++index_size_ptr[m];
				index_ptr[m] = realloc(index_ptr[m], sizeof(uint32_t) * index_size_ptr[m]);
				if (pass == 0)
				{
					uint32_t new_index = collada_pack_size_ptr[m];
					++collada_pack_size_ptr[m];

					collada_Pack new_collada_pack =
					{
						p_x, p_y, p_z,
						n_x, n_y, n_z,
						t_x, t_y,
						joint_ptr,
						weight_ptr,
						max_bone
					};

					collada_pack_ptr[m] = realloc(collada_pack_ptr[m], sizeof(collada_Pack) * collada_pack_size_ptr[m]);
					collada_pack_ptr[m][new_index] = new_collada_pack;

					index_ptr[m][index_size_ptr[m] - 1] = new_index;
				}
				else
				{
					free(joint_ptr);
					free(weight_ptr);
					index_ptr[m][index_size_ptr[m] - 1] = i;
				}
			}
		}
	}

	collada_source_ptr->collada_pack_ptr = collada_pack_ptr;
	collada_source_ptr->collada_pack_size_ptr = collada_pack_size_ptr;
	collada_source_ptr->index_ptr = index_ptr;
	collada_source_ptr->index_size_ptr = index_size_ptr;
}

void graphic_reader_fixAnimation(collada_Source *sourcedatatype_ptr)
{
	for (int y = 0; y < sourcedatatype_ptr->armature_string_vector_size; ++y)
	{
		for (int x = 0; x < sourcedatatype_ptr->max_bonedata; ++x)
		{
			if (strcmp(sourcedatatype_ptr->armature_string_vector[y], sourcedatatype_ptr->bonedata_vector[x].bones_name_string[0]) == 0)
			{
				int y_index = y * sourcedatatype_ptr->max_frame * 16;

				for (int z = 0; z < sourcedatatype_ptr->max_frame; ++z)
				{
					int z_index = z * 16;

					// M4x4::inverse(sourcedatatype_ptr->armature_transform_vector, y_index + z_index);
					// M4x4::inverse(sourcedatatype_ptr->armature_transform_vector, y_index + z_index);
					sourcedatatype_ptr->armature_transform_vector[y_index + 3 + z_index] -= sourcedatatype_ptr->bonedata_vector[x].visual_bones_transform_float_vector[3];
					sourcedatatype_ptr->armature_transform_vector[y_index + 7 + z_index] -= sourcedatatype_ptr->bonedata_vector[x].visual_bones_transform_float_vector[7];
					sourcedatatype_ptr->armature_transform_vector[y_index + 11 + z_index] -= sourcedatatype_ptr->bonedata_vector[x].visual_bones_transform_float_vector[11];
					m4x4_inverse(sourcedatatype_ptr->armature_transform_vector, y_index + z_index);
				}
			}
		}
	}
}
