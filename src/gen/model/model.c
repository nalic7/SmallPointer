#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

//! apply macro
static const uint8_t Pg[] =
{
	1
//	#define X(v, n, b, r) 1,
//		SMPTRnM
//	#undef X
//	#define X(v, n) 0,
//		SMPTRnM1
//	#undef X
};

//! apply macro
static const char *Pc[] =
{
	SMPTFcFACTORY_MODEL "/SuperCutePomi2.glb",
//	#define X(v, n, b, r) SMPTFcFACTORY_MODEL "/" n ".glb",
//		SMPTRnM
//	#undef X
//	#define X(v, n) SMPTFcFACTORY_MODEL "/" n ".glb",
//		SMPTRnM1
//	#undef X
};

static const char *Pm[] =
{
	#define X(v, n, b) n,
		SMPTRnMA
	#undef X
};

static uint8_t mesh_id_array[sizeof(Pm) / sizeof(Pm[0])];
static uint8_t mesh_index = 0;

static uint32_t bone_bl = 0;

static uint8_t *joint_count_p;
static uint8_t joint_count_bl = 0;
static uint8_t joint_array[1024];
static uint32_t joint_bl = 0;

static float *rgba_p = 0;
static char **material_p;
static uint8_t material_fl = 0;

static uint8_t *ai_p;
static uint32_t ai_bl = 0;

static uint8_t *attribute_j1c1_p;
static uint32_t attribute_j1c1_bl = 0;
static uint8_t *attribute_c1_p;
static uint32_t attribute_c1_bl = 0;

static uint8_t *i_p;
static uint32_t i_bl = 0;
static uint8_t *cut_i_p;
static uint32_t cut_i_bl = 0;

static float *i_bindpose_p;
static uint32_t i_bindpose_bl = 0;

void smptg_mdMsend()
{
	joint_count_p = malloc(0);

	i_bindpose_p = malloc(0);

	material_p = malloc(0);

	ai_p = malloc(0);
	attribute_j1c1_p = malloc(0);
	i_p = malloc(0);
	cut_i_p = malloc(0);

	cgltf_options *cgltf_options_p = &(cgltf_options){};
	cgltf_data *cgltf_data_p = NULL;
	for (uint32_t l_0 = 0; l_0 < sizeof(Pc) / sizeof(Pc[0]); ++l_0)
	{
		SMPT_DBmR2L("cgltf_parse_file %d", cgltf_parse_file(cgltf_options_p, Pc[l_0], &cgltf_data_p))
		SMPT_DBmR2L("cgltf_load_buffers %d", cgltf_load_buffers(cgltf_options_p, cgltf_data_p, Pc[l_0]))
		SMPT_DBmR2L("cgltf_validate %d", cgltf_validate(cgltf_data_p))

		if (Pg[l_0] & 1)
		{
			cgltf_skin *cgltf_skin_p = &cgltf_data_p->skins[0];

			//.i bindpose
			i_bindpose_p = realloc(i_bindpose_p, (cgltf_skin_p->joints_count - 1) * sizeof(float) * 16);
			memcpy(i_bindpose_p + i_bindpose_bl * 16, cgltf_skin_p->inverse_bind_matrices->buffer_view->buffer->data + cgltf_skin_p->inverse_bind_matrices->buffer_view->offset + sizeof(float) * 16, sizeof(float) * 16 * (cgltf_skin_p->joints_count - 1));
			i_bindpose_bl += cgltf_skin_p->joints_count - 1;

			joint_count_p = realloc(joint_count_p, joint_count_bl + sizeof(uint8_t));
			joint_count_p[joint_count_bl] = cgltf_skin_p->joints_count;
			joint_count_bl += sizeof(uint8_t);

			//.i use first bone as main with default m4x4
			cgltf_node *base_cgltf_node_p = cgltf_skin_p->joints[0];

			for (uint32_t l_2 = 0; l_2 < cgltf_skin_p->joints_count; ++l_2)
			{
				cgltf_node *cgltf_node_joints_p = cgltf_skin_p->joints[l_2];

				if (l_2 == 0)
				{
					joint_array[joint_bl] = 0;
					joint_bl += sizeof(uint8_t);
				}
				else
				{
					uint32_t c_0 = 0;
					while ((cgltf_node_joints_p = cgltf_node_joints_p->parent) != base_cgltf_node_p)
					{
						for (uint32_t j_1 = 0; j_1 < cgltf_skin_p->joints_count; ++j_1)
							if (cgltf_node_joints_p == cgltf_skin_p->joints[j_1])
							{
								joint_array[joint_bl + c_0 + 1] = j_1;
								break;
							}

						++c_0;
					}
					joint_array[joint_bl] = c_0;
					joint_bl += sizeof(uint8_t) + c_0;
				}
			}

			bone_bl += cgltf_skin_p->joints_count;
		}

		uint8_t mix_array[sizeof(float) * 3 + 2];
		uint32_t l_index = 0;
		uint32_t l_own_index = 0;
		uint32_t *l_index_p;
		for (uint32_t l_1 = 0; l_1 < cgltf_data_p->meshes_count; ++l_1)
		{
			cgltf_mesh *cgltf_mesh_p = &cgltf_data_p->meshes[l_1];
			SMPT_DBmN2L("cgltf_mesh %s", cgltf_mesh_p->name)

			l_index_p = &l_index;

			for (uint8_t l_2 = 0; l_2 < sizeof(Pm) / sizeof(Pm[0]); ++l_2)
				if (!strcmp(Pm[l_2], cgltf_mesh_p->name))
				{
					mesh_id_array[l_2] = mesh_index++;
					l_own_index = 0;
					l_index_p = &l_own_index;
					break;
				}

			for (uint32_t l_2 = 0; l_2 < cgltf_mesh_p->primitives_count; ++l_2)
			{
				cgltf_primitive *cgltf_primitive_p = &cgltf_mesh_p->primitives[l_2];

				mix_array[sizeof(float) * 3] = 0;
				//.i material/color
				while (mix_array[sizeof(float) * 3] < material_fl)
				{
					if (!strcmp(material_p[mix_array[sizeof(float) * 3]], cgltf_primitive_p->material->name))
						break;
					//.i j1c1
					++mix_array[sizeof(float) * 3];
				}
				if (mix_array[sizeof(float) * 3] == material_fl)
				{
					cgltf_material *cgltf_material_p = cgltf_primitive_p->material;
					cgltf_float *cgltf_float_array = cgltf_material_p->pbr_metallic_roughness.base_color_factor;
					cgltf_float *emissive_factor = cgltf_material_p->emissive_factor;
					if (strstr(cgltf_material_p->name, ".C0."))
						SMPT_DBmW2L("SMPTG %s", cgltf_material_p->name)

					++material_fl;
					material_p = realloc(material_p, sizeof(char *) * material_fl);
					material_p[mix_array[sizeof(float) * 3]] = cgltf_material_p->name;
					rgba_p = realloc(rgba_p, sizeof(float) * 4 * material_fl);
					uint16_t i4 = mix_array[sizeof(float) * 3] * 4;
					rgba_p[i4] = emissive_factor[0];
					rgba_p[i4 + 1] = emissive_factor[1];
					rgba_p[i4 + 2] = emissive_factor[2];
					rgba_p[i4 + 3] = cgltf_float_array[3];
				}

				uint8_t l_set = 0;
				for (uint32_t l_3 = 0; l_3 < cgltf_primitive_p->indices->count; ++l_3)
				{
					uint16_t l_3_0 = *(uint16_t *)(cgltf_primitive_p->indices->buffer_view->buffer->data + cgltf_primitive_p->indices->buffer_view->offset + l_3 * sizeof(uint16_t));

					for (uint32_t l_4 = 0; l_4 < cgltf_primitive_p->attributes_count; ++l_4)
					{
						cgltf_attribute *cgltf_attribute_p = &cgltf_primitive_p->attributes[l_4];
						cgltf_accessor *cgltf_accessor_p = cgltf_attribute_p->data;

						cgltf_buffer_view *cgltf_buffer_view_p = cgltf_accessor_p->buffer_view;
						uint8_t type_bl = cgltf_component_size(cgltf_accessor_p->component_type);
						uint8_t *v_p = cgltf_buffer_view_p->buffer->data + cgltf_buffer_view_p->offset;

						uint8_t a_bl = cgltf_accessor_p->stride / type_bl;
						for (uint32_t l_5 = 0; l_5 < a_bl; ++l_5)
						{
							if (cgltf_attribute_p->type == cgltf_attribute_type_joints)
							{
								if (l_5 == 0)
								{
									uint8_t a_j = *(v_p + l_3_0 * cgltf_accessor_p->stride + l_5 * type_bl);
									if (a_j == 0)
									{
										SMPT_DBmW2L("SMPTG a_j0")
									}
									//.c b1
									mix_array[sizeof(float) * 3 + 1] = a_j;
								}
							}
							else if (cgltf_attribute_p->type == cgltf_attribute_type_weights)
							{
								if (l_5 == 0)
								{
									if (cgltf_accessor_p->component_type == cgltf_component_type_r_32f)
									{
										float *p = (float *)(v_p + l_3_0 * cgltf_accessor_p->stride + l_5 * type_bl);
										if (!*p)
										{
											SMPT_DBmW2L("SMPTG w2 %f", *p)
										}
									}
									else
									{
										SMPT_DBmW2L("SMPTG cgltf_accessor_p->component_type %d", cgltf_accessor_p->component_type)
									}

									l_set = 1;
								}
								else if (l_5 == 1)
								{
									if (cgltf_accessor_p->component_type == cgltf_component_type_r_32f)
									{
										float *p = (float *)(v_p + l_3_0 * cgltf_accessor_p->stride + l_5 * type_bl);
										if (*p)
										{
											SMPT_DBmW2L("SMPTG w2 %f", *p)
										}
									}
									else
									{
										SMPT_DBmW2L("SMPTG cgltf_accessor_p->component_type %d", cgltf_accessor_p->component_type)
									}
								}
							}
							else if (cgltf_attribute_p->type == cgltf_attribute_type_position)
							{
								memcpy(mix_array + l_5 * type_bl, v_p + l_3_0 * cgltf_accessor_p->stride + l_5 * type_bl, type_bl);
							}
							else
							{
								SMPT_DBmW2L("SMPTG cgltf_attribute_p->type %d", cgltf_attribute_p->type)
							}
						}

						//.i c1
						if (cgltf_primitive_p->attributes_count == 1)
						{
							for (uint32_t l_5 = 0; l_5 < attribute_c1_bl; l_5 += sizeof(float) * 3 + 1)
							{
								if (!memcmp(attribute_c1_p + l_5, mix_array, sizeof(float) * 3 + 1))
								{
									if (l_index_p == &l_own_index)
									{
										cut_i_p = realloc(cut_i_p, cut_i_bl + sizeof(uint32_t));
										*(uint32_t *)(cut_i_p + cut_i_bl) = l_5 / (sizeof(float) * 3 + 1);
										cut_i_bl += sizeof(uint32_t);
									}
									else
									{
										i_p = realloc(i_p, i_bl + sizeof(uint32_t));
										*(uint32_t *)(i_p + i_bl) = l_5 / (sizeof(float) * 3 + 1);
										i_bl += sizeof(uint32_t);
									}
									*l_index_p += sizeof(uint32_t);

									l_set = 0;
									break;
								}
							}
							if (l_set == 1)
							{
								attribute_c1_p = realloc(attribute_c1_p, attribute_c1_bl + sizeof(float) * 3 + 1);
								memcpy(attribute_c1_p + attribute_c1_bl, mix_array, sizeof(float) * 3 + 1);

								if (l_index_p == &l_own_index)
								{
									cut_i_p = realloc(cut_i_p, cut_i_bl + sizeof(uint32_t));
									*(uint32_t *)(cut_i_p + cut_i_bl) = attribute_c1_bl / (sizeof(float) * 3 + 1);
									cut_i_bl += sizeof(uint32_t);
								}
								else
								{
									i_p = realloc(i_p, i_bl + sizeof(uint32_t));
									*(uint32_t *)(i_p + i_bl) = attribute_c1_bl / (sizeof(float) * 3 + 1);
									i_bl += sizeof(uint32_t);
								}
								*l_index_p += sizeof(uint32_t);

								attribute_c1_bl += sizeof(float) * 3 + 1;

								l_set = 0;
							}
						}
						//.i j1u1v1t1
						//else if (cgltf_primitive_p->attributes_count == 4 && l_4 == 3)
						//{
						//}
						//.i j1c1
						else if (l_set == 1)
						{
							for (uint32_t l_5 = 0; l_5 < attribute_j1c1_bl; l_5 += sizeof(float) * 3 + 2)
							{
								if (!memcmp(attribute_j1c1_p + l_5, mix_array, sizeof(float) * 3 + 2))
								{
									if (l_index_p == &l_own_index)
									{
										cut_i_p = realloc(cut_i_p, cut_i_bl + sizeof(uint32_t));
										*(uint32_t *)(cut_i_p + cut_i_bl) = l_5 / (sizeof(float) * 3 + 2);
										cut_i_bl += sizeof(uint32_t);
									}
									else
									{
										i_p = realloc(i_p, i_bl + sizeof(uint32_t));
										*(uint32_t *)(i_p + i_bl) = l_5 / (sizeof(float) * 3 + 2);
										i_bl += sizeof(uint32_t);
									}
									*l_index_p += sizeof(uint32_t);

									l_set = 0;
									break;
								}
							}
							if (l_set == 1)
							{
								attribute_j1c1_p = realloc(attribute_j1c1_p, attribute_j1c1_bl + sizeof(float) * 3 + 2);
								memcpy(attribute_j1c1_p + attribute_j1c1_bl, mix_array, sizeof(float) * 3 + 2);

								if (l_index_p == &l_own_index)
								{
									cut_i_p = realloc(cut_i_p, cut_i_bl + sizeof(uint32_t));
									*(uint32_t *)(cut_i_p + cut_i_bl) = attribute_j1c1_bl / (sizeof(float) * 3 + 2);
									cut_i_bl += sizeof(uint32_t);
								}
								else
								{
									i_p = realloc(i_p, i_bl + sizeof(uint32_t));
									*(uint32_t *)(i_p + i_bl) = attribute_j1c1_bl / (sizeof(float) * 3 + 2);
									i_bl += sizeof(uint32_t);
								}
								*l_index_p += sizeof(uint32_t);

								attribute_j1c1_bl += sizeof(float) * 3 + 2;

								l_set = 0;
							}
						}
					}
				}
			}

			if (l_index_p == &l_own_index)
			{
				ai_p = realloc(ai_p, ai_bl + sizeof(uint32_t));
				*(uint32_t *)(ai_p + ai_bl) = l_own_index;
				ai_bl += sizeof(uint32_t);
			}
		}
		ai_p = realloc(ai_p, ai_bl + sizeof(uint32_t));
		*(uint32_t *)(ai_p + ai_bl) = l_index;
		ai_bl += sizeof(uint32_t);

		cgltf_free(cgltf_data_p);
	}

	SMPT_DBmR2L("material_fl %d", material_fl)
	SMPT_DBmR2L("bone_bl %d", bone_bl)

	FILE *file = fopen(SMPTFcHOME_ASSET, "ab");
	SMPT_DBmN2L("fopen %p", file)

	fwrite(&joint_count_bl, sizeof(uint8_t), 1, file);
	fwrite(joint_count_p, sizeof(uint8_t), joint_count_bl, file);
	fwrite(joint_array, sizeof(uint8_t), joint_bl, file);
	fwrite(i_bindpose_p, sizeof(float), i_bindpose_bl * 16, file);

	fwrite(&ai_bl, sizeof(uint32_t), 1, file);
	for (uint8_t l_0 = 0; l_0 < sizeof(Pm) / sizeof(Pm[0]); ++l_0)
	{
		uint8_t l_0_0 = mesh_id_array[l_0];
		fwrite(ai_p + l_0_0 * sizeof(uint32_t), sizeof(uint32_t), 1, file);
	}
	fwrite(ai_p + sizeof(Pm) / sizeof(Pm[0]) * sizeof(uint32_t), sizeof(uint32_t), 1, file);

	for (uint8_t l_0 = 0; l_0 < sizeof(Pm) / sizeof(Pm[0]); ++l_0)
	{
		uint8_t l_0_0 = mesh_id_array[l_0];

		uint32_t size = *(uint32_t *)(ai_p + l_0_0 * sizeof(uint32_t));
		uint32_t index = 0;

		for (uint8_t l_1 = 0; l_1 < l_0_0; ++l_1)
		{
			index += *(uint32_t *)(ai_p + l_1 * sizeof(uint32_t));
		}

		fwrite(cut_i_p + index, sizeof(uint8_t), size, file);
	}
	fwrite(i_p, sizeof(uint8_t), i_bl, file);

	fwrite(&material_fl, sizeof(uint8_t), 1, file);
	fwrite(rgba_p, sizeof(float), material_fl * 4, file);

	//.i uv

	//.i a c1
	fwrite((uint32_t[]){attribute_c1_bl / (sizeof(float)*3+1)}, sizeof(uint32_t), 1, file);
	fwrite(attribute_c1_p, sizeof(uint8_t), attribute_c1_bl, file);

	//.i a j1c1
	fwrite(attribute_j1c1_p, sizeof(uint8_t), attribute_j1c1_bl, file);

	//.i a j1t1u1v1

	//.i a t1u1v1

	fclose(file);
}
