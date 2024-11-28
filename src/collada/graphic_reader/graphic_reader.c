uint32_t graphic_reader_count(char* char_ptr, char c_char)
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

void graphic_reader_makeBones(collada_Source* collada_source_ptr)
{
	uint32_t max_data = collada_source_ptr->max_data;
	uint32_t max_bone = collada_source_ptr->max_bone;

	uint8_t** bone_ptr = malloc(sizeof(uint8_t*) * max_bone);
	uint32_t* bone_size_ptr = malloc(sizeof(uint32_t) * max_bone);

	collada_Bone* bonedata_vector = collada_source_ptr->collada_bone_ptr;

	for (int16_t w = 0; w < max_bone; ++w)
	{
		for (int16_t y = 0; y < max_bone; ++y)
		{
			if (strcmp(collada_source_ptr->joint_ptr[w], bonedata_vector[y].name_ptr[0]) == 0)
			{
				uint32_t max_z = collada_source_ptr->space_ptr[w];
				uint32_t index = 1;

				bone_ptr[w] = malloc(sizeof(uint8_t));
				bone_ptr[w][0] = w;

				for (int16_t z = y - 1; z != -1; --z)
				{
					uint32_t new_max_z = collada_source_ptr->space_ptr[z];
					if (max_z > new_max_z)
					{
						max_z = new_max_z;

						for (int16_t h = 0; h < max_bone; ++h)
						{
							if (strcmp(collada_source_ptr->joint_ptr[h], bonedata_vector[z].name_ptr[0]) == 0)
							{
								++index;
								bone_ptr[w] = realloc(bone_ptr[w], sizeof(uint8_t) * index);
								bone_ptr[w][index - 1] = h;
								break;
							}
						}
					}
				}

				bone_size_ptr[w] = index;
				break;
			}
		}
	}

	collada_source_ptr->bone_ptr = bone_ptr;
	collada_source_ptr->bone_size_ptr = bone_size_ptr;
}

void graphic_reader_mix(collada_Source* collada_source_ptr)
{
	uint32_t max_data = collada_source_ptr->max_data;

	collada_Pack** collada_pack_ptr = malloc(sizeof(collada_Pack*) * max_data);
	uint32_t* collada_pack_size_ptr = malloc(sizeof(uint32_t) * max_data);

	uint32_t** index_ptr = malloc(sizeof(uint32_t*) * max_data);
	uint32_t* index_size_ptr = malloc(sizeof(uint32_t) * max_data);

	for (uint32_t m = 0; m < max_data; ++m)
	{
		// uint32_t max_joint = collada_source_ptr->max_bone_ptr[m];
		uint32_t p_size = collada_source_ptr->p_size_ptr[m];

		collada_pack_ptr[m] = malloc(0);
		collada_pack_size_ptr[m] = 0;

		index_ptr[m] = malloc(0);
		index_size_ptr[m] = 0;

		float
			p_x = 0, p_y = 0, p_z = 0,
			n_x = 0, n_y = 0, n_z = 0,
			t_x = 0, t_y = 0;
		uint8_t* joint_ptr;
		float* weight_ptr;
		uint8_t max_bone = 0;

		for (uint32_t p = 0; p < p_size; ++p)
		{
			uint32_t p0 = collada_source_ptr->p_ptr[m][p];
			uint8_t id = p % 3;

			switch (id)
			{
				case 0:
					uint32_t v = p0 * 3;
					p_x = collada_source_ptr->vertex_ptr[m][v];
					p_y = collada_source_ptr->vertex_ptr[m][v + 1];
					p_z = collada_source_ptr->vertex_ptr[m][v + 2];

					if (collada_source_ptr->is_animated)
					{
						joint_ptr = malloc(sizeof(uint8_t) * 4);
						weight_ptr = malloc(sizeof(float) * 4);
						for (uint8_t i = 0; i < 4; ++i)
						{
							joint_ptr[i] = 0;
							weight_ptr[i] = 0;
						}

						uint32_t v_by_p0 = 0;

						for (uint32_t i = 0; i < p0; ++i)
						{
							v_by_p0 += collada_source_ptr->vcount_ptr[m][i];
						}

						v_by_p0 *= 2;

						int vc = collada_source_ptr->vcount_ptr[m][p0];

						max_bone = 0;

						uint8_t limit = 0;
						while (max_bone < vc)
						{
							uint32_t step = v_by_p0 + max_bone * 2;
							joint_ptr[max_bone] = collada_source_ptr->v_ptr[m][step];
							weight_ptr[max_bone] = collada_source_ptr->weight_ptr[m][collada_source_ptr->v_ptr[m][step + 1]];

							if (weight_ptr[max_bone] == 0)
							{
								joint_ptr[max_bone] = 0;
								if (max_bone == vc - 1)
								{
									limit = 1;
								}
							}

							++max_bone;
						}
						//need test
						if (limit == 1 && max_bone != 0)
						{
							--max_bone;
						}
					}
					break;
				case 1:
					uint32_t n = p0 * 3;
					n_x = collada_source_ptr->normal_ptr[m][n];
					n_y = collada_source_ptr->normal_ptr[m][n + 1];
					n_z = collada_source_ptr->normal_ptr[m][n + 2];
					break;
				case 2:
					uint32_t t = p0 * 2;
					t_x = collada_source_ptr->texcoord_ptr[m][t];
					t_y = collada_source_ptr->texcoord_ptr[m][t + 1];
			}

			if (id == 2)
			{
				uint8_t pass = 0;
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

						if (collada_source_ptr->is_animated)
						{
							for (uint8_t j = 0; j < 4; ++j)
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
						.p_x = p_x, .p_y = p_y, .p_z = p_z,
						.n_x = n_x, .n_y = n_y, .n_z = n_z,
						.t_x = t_x, .t_y = t_y,
					};

					if (collada_source_ptr->is_animated)
					{
						new_collada_pack.joint_ptr = joint_ptr;
						new_collada_pack.weight_ptr = weight_ptr;
						new_collada_pack.max_bone = max_bone;
					}

					collada_pack_ptr[m] = realloc(collada_pack_ptr[m], sizeof(collada_Pack) * collada_pack_size_ptr[m]);
					collada_pack_ptr[m][new_index] = new_collada_pack;

					index_ptr[m][index_size_ptr[m] - 1] = new_index;
				}
				else
				{
					if (collada_source_ptr->is_animated)
					{
						free(joint_ptr);
						free(weight_ptr);
					}
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

void graphic_reader_fixAnimation(collada_Source* collada_source_ptr)
{
	uint32_t max_bone = collada_source_ptr->max_bone;

	for (uint32_t y = 0; y < collada_source_ptr->v_bone_size; ++y)
	{
		for (uint32_t x = 0; x < max_bone; ++x)
		{
			if (strcmp(collada_source_ptr->v_bone_ptr[y], collada_source_ptr->collada_bone_ptr[x].name_ptr[0]) == 0)
			{
				uint32_t y_index = y * collada_source_ptr->max_frame * 16;

				for (uint32_t z = 0; z < collada_source_ptr->max_frame; ++z)
				{
					uint32_t z_index = z * 16;

					collada_source_ptr->transform_ptr[y_index + 3 + z_index] -= collada_source_ptr->collada_bone_ptr[x].visual_ptr[3];
					collada_source_ptr->transform_ptr[y_index + 7 + z_index] -= collada_source_ptr->collada_bone_ptr[x].visual_ptr[7];
					collada_source_ptr->transform_ptr[y_index + 11 + z_index] -= collada_source_ptr->collada_bone_ptr[x].visual_ptr[11];
					m4x4_inverse(collada_source_ptr->transform_ptr, y_index + z_index);
				}
			}
		}
	}
}
