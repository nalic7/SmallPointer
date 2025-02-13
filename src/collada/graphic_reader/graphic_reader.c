uint32_t graphic_reader_count(const char* char_ptr, const char c_char)
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
	const uint32_t max_data = collada_source_ptr->max_data;
	const uint8_t max_bone = collada_source_ptr->max_bone;

	uint8_t** bone_ptr = malloc(sizeof(uint8_t*) * max_bone);
	uint32_t* bone_size_ptr = malloc(sizeof(uint32_t) * max_bone);

	const collada_Bone* collada_bone_ptr = collada_source_ptr->collada_bone_ptr;

	for (uint8_t mb0 = 0; mb0 < max_bone; ++mb0)
	{
		for (int16_t mb1 = 0; mb1 < max_bone; ++mb1)
		{
			if (strcmp(collada_source_ptr->joint_ptr[mb0], collada_bone_ptr[mb1].name_ptr[0]) == 0)
			{
				uint32_t max_space = collada_source_ptr->space_ptr[mb0];
				uint8_t bone_index = 1;

				bone_ptr[mb0] = malloc(sizeof(uint8_t));
				bone_ptr[mb0][0] = mb0;

				for (int16_t sb = mb1 - 1; sb != -1; --sb)
				{
					const uint32_t space = collada_source_ptr->space_ptr[sb];
					if (max_space > space)
					{
						max_space = space;

						for (uint8_t mb2 = 0; mb2 < max_bone; ++mb2)
						{
							if (strcmp(collada_source_ptr->joint_ptr[mb2], collada_bone_ptr[sb].name_ptr[0]) == 0)
							{
								++bone_index;
								bone_ptr[mb0] = realloc(bone_ptr[mb0], sizeof(uint8_t) * bone_index);
								bone_ptr[mb0][bone_index - 1] = mb2;
								break;
							}
						}
					}
				}

				bone_size_ptr[mb0] = bone_index;
				break;
			}
		}
	}

	collada_source_ptr->bone_ptr = bone_ptr;
	collada_source_ptr->bone_size_ptr = bone_size_ptr;
}

void graphic_reader_mix(collada_Source* collada_source_ptr)
{
	const uint32_t max_data = collada_source_ptr->max_data;

	collada_Pack** collada_pack_ptr = malloc(sizeof(collada_Pack*) * max_data);
	uint32_t* collada_pack_size_ptr = malloc(sizeof(uint32_t) * max_data);

	uint32_t** index_ptr = malloc(sizeof(uint32_t*) * max_data);
	uint32_t* index_size_ptr = malloc(sizeof(uint32_t) * max_data);

	for (uint32_t md = 0; md < max_data; ++md)
	{
		const uint32_t p_size = collada_source_ptr->p_size_ptr[md];

		collada_pack_ptr[md] = malloc(0);
		collada_pack_size_ptr[md] = 0;

		index_ptr[md] = malloc(0);
		index_size_ptr[md] = 0;

		float
			#ifdef C_OUT_NORMAL
				n_x = 0, n_y = 0, n_z = 0,
			#endif
			#ifdef C_OUT_TEXCOORD
				t_x = 0, t_y = 0,
			#endif
			p_x = 0, p_y = 0, p_z = 0;
		uint8_t* joint_ptr;
		float* weight_ptr;
		uint8_t max_bone = 0;

		for (uint32_t p = 0; p < p_size; ++p)
		{
			const uint32_t p0 = collada_source_ptr->p_ptr[md][p];
			const uint8_t id = p % 3;

			uint32_t sd;
			switch (id)
			{
				case 0:
					sd = p0 * 3;
					p_x = collada_source_ptr->vertex_ptr[md][sd];
					p_y = collada_source_ptr->vertex_ptr[md][sd + 1];
					p_z = collada_source_ptr->vertex_ptr[md][sd + 2];

					if (collada_source_ptr->is_animated)
					{
						joint_ptr = malloc(sizeof(uint8_t) * 4);
						weight_ptr = malloc(sizeof(float) * 4);
						for (uint8_t i = 0; i < 4; ++i)
						{
							joint_ptr[i] = 0;
							weight_ptr[i] = 0;
						}

						uint32_t p0_vcount = 0;

						for (uint32_t i = 0; i < p0; ++i)
						{
							p0_vcount += collada_source_ptr->vcount_ptr[md][i];
						}

						p0_vcount *= 2;

						const int vcount = collada_source_ptr->vcount_ptr[md][p0];

						max_bone = 0;

						uint8_t limit = 0;
						while (max_bone < vcount)
						{
							const uint32_t step = p0_vcount + max_bone * 2;
							joint_ptr[max_bone] = collada_source_ptr->v_ptr[md][step];
							weight_ptr[max_bone] = collada_source_ptr->weight_ptr[md][collada_source_ptr->v_ptr[md][step + 1]];

							if (weight_ptr[max_bone] == 0)
							{
								joint_ptr[max_bone] = 0;
								if (max_bone == vcount - 1)
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
					#ifdef C_OUT_NORMAL
						sd = p0 * 3;
						n_x = collada_source_ptr->normal_ptr[md][sd];
						n_y = collada_source_ptr->normal_ptr[md][sd + 1];
						n_z = collada_source_ptr->normal_ptr[md][sd + 2];
					#endif
					break;
				case 2:
					#ifdef C_OUT_TEXCOORD
						sd = p0 * 2;
						t_x = collada_source_ptr->texcoord_ptr[md][sd];
						t_y = collada_source_ptr->texcoord_ptr[md][sd + 1];
					#endif
			}

			if (id == 2)
			{
				uint8_t pass = 0;
				uint32_t i = 0;

				while (i < collada_pack_size_ptr[md])
				{
					if
					(
						#ifdef C_OUT_NORMAL
							n_x == collada_pack_ptr[md][i].n_x &&
							n_y == collada_pack_ptr[md][i].n_y &&
							n_z == collada_pack_ptr[md][i].n_z &&
						#endif

						#ifdef C_OUT_TEXCOORD
							t_x == collada_pack_ptr[md][i].t_x &&
							t_y == collada_pack_ptr[md][i].t_y &&
						#endif

						p_x == collada_pack_ptr[md][i].p_x &&
						p_y == collada_pack_ptr[md][i].p_y &&
						p_z == collada_pack_ptr[md][i].p_z
					)
					{
						pass = 1;

						if (collada_source_ptr->is_animated)
						{
							for (uint8_t j = 0; j < 4; ++j)
							{
								if
								(
									joint_ptr[j] != collada_pack_ptr[md][i].joint_ptr[j] ||
									weight_ptr[j] != collada_pack_ptr[md][i].weight_ptr[j]
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

				++index_size_ptr[md];
				index_ptr[md] = realloc(index_ptr[md], sizeof(uint32_t) * index_size_ptr[md]);
				if (pass == 0)
				{
					const uint32_t new_index = collada_pack_size_ptr[md];
					++collada_pack_size_ptr[md];

					collada_Pack new_collada_pack =
					{
						.p_x = p_x, .p_y = p_y, .p_z = p_z,
						#ifdef C_OUT_NORMAL
							.n_x = n_x, .n_y = n_y, .n_z = n_z,
						#endif
						#ifdef C_OUT_TEXCOORD
							.t_x = t_x, .t_y = t_y,
						#endif
					};

					if (collada_source_ptr->is_animated)
					{
						new_collada_pack.joint_ptr = joint_ptr;
						new_collada_pack.weight_ptr = weight_ptr;
						new_collada_pack.max_bone = max_bone;
					}

					collada_pack_ptr[md] = realloc(collada_pack_ptr[md], sizeof(collada_Pack) * collada_pack_size_ptr[md]);
					collada_pack_ptr[md][new_index] = new_collada_pack;

					index_ptr[md][index_size_ptr[md] - 1] = new_index;
				}
				else
				{
					if (collada_source_ptr->is_animated)
					{
						free(joint_ptr);
						free(weight_ptr);
					}
					index_ptr[md][index_size_ptr[md] - 1] = i;
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
	for (uint32_t v = 0; v < collada_source_ptr->v_bone_size; ++v)
	{
		for (uint8_t mb = 0; mb < collada_source_ptr->max_bone; ++mb)
		{
			if (strcmp(collada_source_ptr->v_bone_ptr[v], collada_source_ptr->collada_bone_ptr[mb].name_ptr[0]) == 0)
			{
				const uint32_t v_mf_16 = v * collada_source_ptr->max_frame * 16;

				for (uint32_t mf = 0; mf < collada_source_ptr->max_frame; ++mf)
				{
					const uint32_t mf_16 = mf * 16;

					collada_source_ptr->transform_ptr[v_mf_16 + 3 + mf_16] -= collada_source_ptr->collada_bone_ptr[mb].visual_ptr[3];
					collada_source_ptr->transform_ptr[v_mf_16 + 7 + mf_16] -= collada_source_ptr->collada_bone_ptr[mb].visual_ptr[7];
					collada_source_ptr->transform_ptr[v_mf_16 + 11 + mf_16] -= collada_source_ptr->collada_bone_ptr[mb].visual_ptr[11];
					m4x4_inverse(collada_source_ptr->transform_ptr, v_mf_16 + mf_16);
				}
			}
		}
	}
}
