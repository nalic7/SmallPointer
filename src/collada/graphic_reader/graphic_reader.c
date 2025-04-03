uint32_t graphic_reader_count(const char *char_p, const char c_char)
{
	uint32_t v = 0;

	while (*char_p)
	{
		if (*char_p == c_char)
		{
			++v;
		}
		++char_p;
	}

	return v;
}

void graphic_reader_sanitize(char *char_p)
{
	while (*char_p)
	{
		if (!isalnum(*char_p))
		{
			*char_p = '_';
		}
		++char_p;
	}
}

void graphic_reader_makeBones(collada_Source *collada_source_p)
{
	const uint32_t max_data = collada_source_p->max_data;
	const uint8_t max_bone = collada_source_p->max_bone;

	uint8_t **bone_p = malloc(sizeof(uint8_t*) * max_bone);
	uint32_t *bone_size_p = malloc(sizeof(uint32_t) * max_bone);

	const collada_Bone *collada_bone_p = collada_source_p->collada_bone_p;

	for (uint8_t mb0 = 0; mb0 < max_bone; ++mb0)
	{
		for (int16_t mb1 = 0; mb1 < max_bone; ++mb1)
		{
			if (!strcmp(collada_source_p->joint_p[mb0], collada_bone_p[mb1].name_p[0]))
			{
				uint32_t max_space = collada_source_p->space_p[mb0];
				uint8_t bone_index = 1;

				bone_p[mb0] = malloc(sizeof(uint8_t));
				bone_p[mb0][0] = mb0;

				for (int16_t sb = mb1 - 1; sb != -1; --sb)
				{
					const uint32_t space = collada_source_p->space_p[sb];
					if (max_space > space)
					{
						max_space = space;

						for (uint8_t mb2 = 0; mb2 < max_bone; ++mb2)
						{
							if (!strcmp(collada_source_p->joint_p[mb2], collada_bone_p[sb].name_p[0]))
							{
								++bone_index;
								bone_p[mb0] = realloc(bone_p[mb0], sizeof(uint8_t) * bone_index);
								bone_p[mb0][bone_index - 1] = mb2;
								break;
							}
						}
					}
				}

				bone_size_p[mb0] = bone_index;
				break;
			}
		}
	}

	collada_source_p->bone_p = bone_p;
	collada_source_p->bone_size_p = bone_size_p;
}

void graphic_reader_mix(collada_Source *collada_source_p)
{
	const uint32_t max_data = collada_source_p->max_data;

	collada_Pack **collada_pack_p = malloc(sizeof(collada_Pack*) * max_data);
	uint32_t *collada_pack_size_p = malloc(sizeof(uint32_t) * max_data);

	uint32_t **index_p = malloc(sizeof(uint32_t*) * max_data);
	uint32_t *index_size_p = malloc(sizeof(uint32_t) * max_data);

	for (uint32_t md = 0; md < max_data; ++md)
	{
		const uint32_t p_size = collada_source_p->p_size_p[md];

		collada_pack_p[md] = malloc(0);
		collada_pack_size_p[md] = 0;

		index_p[md] = malloc(0);
		index_size_p[md] = 0;

		float
			#ifdef C_OUT_NORMAL
				n_x = 0, n_y = 0, n_z = 0,
			#endif
			#ifdef C_OUT_TEXCOORD
				t_x = 0, t_y = 0,
			#endif
			p_x = 0, p_y = 0, p_z = 0;
		uint8_t *joint_p;
		float *weight_p;
		uint8_t max_bone = 0;

		for (uint32_t p = 0; p < p_size; ++p)
		{
			const uint32_t p0 = collada_source_p->p_p[md][p];
			const uint8_t id = p % 3;

			uint32_t sd;
			switch (id)
			{
				case 0:
					sd = p0 * 3;
					p_x = collada_source_p->vertex_p[md][sd];
					p_y = collada_source_p->vertex_p[md][sd + 1];
					p_z = collada_source_p->vertex_p[md][sd + 2];

					if (collada_source_p->is_animated)
					{
						joint_p = malloc(sizeof(uint8_t) * 4);
						weight_p = malloc(sizeof(float) * 4);
						for (uint8_t i = 0; i < 4; ++i)
						{
							joint_p[i] = 0;
							weight_p[i] = 0;
						}

						uint32_t p0_vcount = 0;

						for (uint32_t i = 0; i < p0; ++i)
						{
							p0_vcount += collada_source_p->vcount_p[md][i];
						}

						p0_vcount *= 2;

						const int vcount = collada_source_p->vcount_p[md][p0];

						max_bone = 0;

						uint8_t limit = 0;
						while (max_bone < vcount)
						{
							const uint32_t step = p0_vcount + max_bone * 2;
							joint_p[max_bone] = collada_source_p->v_p[md][step];
							weight_p[max_bone] = collada_source_p->weight_p[md][collada_source_p->v_p[md][step + 1]];

							if (weight_p[max_bone] == 0)
							{
								joint_p[max_bone] = 0;
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
						n_x = collada_source_p->normal_p[md][sd];
						n_y = collada_source_p->normal_p[md][sd + 1];
						n_z = collada_source_p->normal_p[md][sd + 2];
					#endif
					break;
				case 2:
					#ifdef C_OUT_TEXCOORD
						sd = p0 * 2;
						t_x = collada_source_p->texcoord_p[md][sd];
						t_y = collada_source_p->texcoord_p[md][sd + 1];
					#endif
			}

			if (id == 2)
			{
				uint8_t pass = 0;
				uint32_t i = 0;

				while (i < collada_pack_size_p[md])
				{
					if
					(
						#ifdef C_OUT_NORMAL
							n_x == collada_pack_p[md][i].n_x &&
							n_y == collada_pack_p[md][i].n_y &&
							n_z == collada_pack_p[md][i].n_z &&
						#endif

						#ifdef C_OUT_TEXCOORD
							t_x == collada_pack_p[md][i].t_x &&
							t_y == collada_pack_p[md][i].t_y &&
						#endif

						p_x == collada_pack_p[md][i].p_x &&
						p_y == collada_pack_p[md][i].p_y &&
						p_z == collada_pack_p[md][i].p_z
					)
					{
						pass = 1;

						if (collada_source_p->is_animated)
						{
							for (uint8_t j = 0; j < 4; ++j)
							{
								if
								(
									joint_p[j] != collada_pack_p[md][i].joint_p[j] ||
									weight_p[j] != collada_pack_p[md][i].weight_p[j]
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

				++index_size_p[md];
				index_p[md] = realloc(index_p[md], sizeof(uint32_t) * index_size_p[md]);
				if (pass == 0)
				{
					const uint32_t new_index = collada_pack_size_p[md];
					++collada_pack_size_p[md];

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

					if (collada_source_p->is_animated)
					{
						new_collada_pack.joint_p = joint_p;
						new_collada_pack.weight_p = weight_p;
						new_collada_pack.max_bone = max_bone;
					}

					collada_pack_p[md] = realloc(collada_pack_p[md], sizeof(collada_Pack) * collada_pack_size_p[md]);
					collada_pack_p[md][new_index] = new_collada_pack;

					index_p[md][index_size_p[md] - 1] = new_index;
				}
				else
				{
					if (collada_source_p->is_animated)
					{
						free(joint_p);
						free(weight_p);
					}
					index_p[md][index_size_p[md] - 1] = i;
				}
			}
		}
	}

	collada_source_p->collada_pack_p = collada_pack_p;
	collada_source_p->collada_pack_size_p = collada_pack_size_p;
	collada_source_p->index_p = index_p;
	collada_source_p->index_size_p = index_size_p;
}

void graphic_reader_fixAnimation(collada_Source *collada_source_p)
{
	for (uint32_t v = 0; v < collada_source_p->v_bone_size; ++v)
	{
		for (uint8_t mb = 0; mb < collada_source_p->max_bone; ++mb)
		{
			if (!strcmp(collada_source_p->v_bone_p[v], collada_source_p->collada_bone_p[mb].name_p[0]))
			{
				const uint32_t v_mf_16 = v * collada_source_p->max_frame * 16;

				for (uint32_t mf = 0; mf < collada_source_p->max_frame; ++mf)
				{
					const uint32_t mf_16 = mf * 16;

					collada_source_p->transform_p[v_mf_16 + 3 + mf_16] -= collada_source_p->collada_bone_p[mb].visual_p[3];
					collada_source_p->transform_p[v_mf_16 + 7 + mf_16] -= collada_source_p->collada_bone_p[mb].visual_p[7];
					collada_source_p->transform_p[v_mf_16 + 11 + mf_16] -= collada_source_p->collada_bone_p[mb].visual_p[11];
					m4x4_inverse(collada_source_p->transform_p + v_mf_16 + mf_16);
				}
			}
		}
	}
}
