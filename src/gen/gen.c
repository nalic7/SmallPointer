#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

const char* file_array[] =
{
	NALI_FACTORY NALI_HOME_MODEL "/SuperCutePomi0.glb",
	// NALI_FACTORY "Font.glb"
};

#define NALI_FPS 24

#define NALI_MEMORY_RECOPY(w_p, r_p, size, byte) \
	w_p = realloc(w_p, size + byte); \
	memcpy(w_p + size, r_p, byte); \
	size += byte;

#define NALI_MEMORY_COPY(w_p, r_p, size, byte) \
	memcpy(w_p + size, r_p, byte); \
	size += byte;

// static uint8_t max_joint_bl = 0;

static uint32_t bone_bl = 0;

static uint8_t *joint_count_p;
static uint8_t joint_count_bl = 0;
static uint8_t *joint_srt_p;//float
static uint32_t joint_srt_bl = 0;
static uint32_t joint_srt_step = 0;
static uint8_t *joint_head_p;
static uint8_t *joint_p;
static uint32_t joint_bl = 0;

static uint8_t *animation_p;//float
static uint32_t animation_bl = 0;

static float *rgba_p = 0;
static char **material_p;
static uint8_t material_fl = 0;

static uint8_t *ia_p;//uint32_t
static uint32_t ia_bl = 0;

static uint8_t *attribute_p;
static uint32_t attribute_bl = 0;

static uint8_t *index_p;
static uint32_t index_bl = 0;

static void gen_model()
{
	joint_count_p = malloc(0);
	joint_srt_p = malloc(0);
	joint_p = malloc(1024);//fix size

	joint_head_p = malloc(1024);//fix size
	memset(joint_head_p, 0, 1024);

	animation_p = malloc(0);

	material_p = malloc(0);

	ia_p = malloc(0);
	attribute_p = malloc(0);
	index_p = malloc(0);

	cgltf_options *cgltf_options_p = &(cgltf_options){};
	cgltf_data *cgltf_data_p = NULL;
	for (uint32_t l_0 = 0; l_0 < sizeof(file_array) / sizeof(file_array[0]); ++l_0)
	{
		nali_info("cgltf_parse_file %d", cgltf_parse_file(cgltf_options_p, file_array[l_0], &cgltf_data_p))
		nali_info("cgltf_load_buffers %d", cgltf_load_buffers(cgltf_options_p, cgltf_data_p, file_array[l_0]))
		nali_info("cgltf_validate %d", cgltf_validate(cgltf_data_p))

		for (uint32_t l_1 = 0; l_1 < cgltf_data_p->animations_count; ++l_1)
		{
			cgltf_animation *cgltf_animation_p = &cgltf_data_p->animations[l_1];

			//input frame f 0 0.5 1.0
			//output s/r/t vec3/vec4 v v v
			// for (uint32_t s = 0; s < cgltf_animation_p->samplers_count; ++s)
			// {
			// 	cgltf_animation_p->samplers;
			// }

			for (uint32_t l_2 = 0; l_2 < cgltf_animation_p->channels_count; ++l_2)
			{
				cgltf_animation_sampler *cgltf_animation_sampler_p = &cgltf_animation_p->samplers[l_2];
				cgltf_animation_channel *cgltf_animation_channel_p = &cgltf_animation_p->channels[l_2];

				cgltf_accessor *cgltf_accessor_input_p = cgltf_animation_sampler_p->input;
				cgltf_accessor *cgltf_accessor_output_p = cgltf_animation_sampler_p->output;

				// /b\ 1
				animation_p = realloc(animation_p, animation_bl + sizeof(uint8_t) + cgltf_accessor_input_p->count);
				*(uint8_t *)(animation_p + animation_bl) = cgltf_accessor_input_p->count;
				animation_bl += sizeof(uint8_t);

				cgltf_buffer_view *cgltf_buffer_view_p = cgltf_accessor_input_p->buffer_view;
				uint8_t *p = cgltf_buffer_view_p->buffer->data + cgltf_buffer_view_p->offset;

				// /b\ 1
				for (uint32_t l_3 = 0; l_3 < cgltf_accessor_input_p->count; ++l_3)
				{
					*(uint8_t*)(animation_p + animation_bl + l_3) = ((float *)p)[l_3] * NALI_FPS;
				}
				animation_bl += cgltf_accessor_input_p->count;

				cgltf_buffer_view_p = cgltf_accessor_output_p->buffer_view;
				p = cgltf_buffer_view_p->buffer->data + cgltf_buffer_view_p->offset;

				switch (cgltf_animation_channel_p->target_path)
				{
					case cgltf_animation_path_type_scale:
						NALI_MEMORY_RECOPY(animation_p, p, animation_bl, cgltf_accessor_input_p->count * sizeof(float) * 3)
						break;
					case cgltf_animation_path_type_rotation:
						NALI_MEMORY_RECOPY(animation_p, p, animation_bl, cgltf_accessor_input_p->count * sizeof(float) * 4)
						break;
					case cgltf_animation_path_type_translation:
						NALI_MEMORY_RECOPY(animation_p, p, animation_bl, cgltf_accessor_input_p->count * sizeof(float) * 3)
						break;
					default:
						nali_info_t("cgltf_animation_channel_p->target_path %d", cgltf_animation_channel_p->target_path)
				}
			}
		}

		for (uint32_t l_1 = 0; l_1 < cgltf_data_p->skins_count; ++l_1)
		{
			cgltf_skin *cgltf_skin_p = &cgltf_data_p->skins[l_1];

			for (uint32_t l_2 = 0; l_2 < cgltf_skin_p->joints_count; ++l_2)
			{
				cgltf_node *cgltf_node_joints_p = cgltf_skin_p->joints[l_2];
				uint32_t j = (bone_bl + l_2) * 3;
				uint8_t j_step = j % 8;
				if (cgltf_node_joints_p->has_scale)
				{
					joint_head_p[j / 8] |= 1 << j_step;
					joint_srt_bl += sizeof(float) * 3;
				}

				if (cgltf_node_joints_p->has_rotation)
				{
					uint8_t j_next = j_step + 1;
					joint_head_p[j / 8 + j_next / 8] |= 1 << (j_next % 8);
					joint_srt_bl += sizeof(float) * 4;
				}

				if (cgltf_node_joints_p->has_translation)
				{
					uint8_t j_next = j_step + 2;
					joint_head_p[j / 8 + j_next / 8] |= 1 << (j_next % 8);
					joint_srt_bl += sizeof(float) * 3;
				}

				if (cgltf_node_joints_p->has_matrix)
				{
					nali_info_t("%s has_matrix", cgltf_node_joints_p->name);
					// cgltf_node_p->matrix;
				}
			}

			joint_srt_p = realloc(joint_srt_p, joint_srt_bl);

			for (uint32_t l_2 = 0; l_2 < cgltf_skin_p->joints_count; ++l_2)
			{
				cgltf_node *cgltf_node_joints_p = cgltf_skin_p->joints[l_2];
				if (cgltf_node_joints_p->has_scale)
				{
					NALI_MEMORY_COPY(joint_srt_p, cgltf_node_joints_p->scale, joint_srt_step, sizeof(float) * 3)
				}
				if (cgltf_node_joints_p->has_rotation)
				{
					NALI_MEMORY_COPY(joint_srt_p, cgltf_node_joints_p->rotation, joint_srt_step, sizeof(float) * 4)
				}
				if (cgltf_node_joints_p->has_translation)
				{
					NALI_MEMORY_COPY(joint_srt_p, cgltf_node_joints_p->translation, joint_srt_step, sizeof(float) * 3)
				}
			}

			joint_count_p = realloc(joint_count_p, joint_count_bl + sizeof(uint8_t));
			joint_count_p[joint_count_bl] = cgltf_skin_p->joints_count;
			joint_count_bl += sizeof(uint8_t);

			cgltf_node *parent_cgltf_node_p = cgltf_skin_p->joints[0]->parent;

			for (uint32_t l_2 = 0; l_2 < cgltf_skin_p->joints_count; ++l_2)
			{
				cgltf_node *cgltf_node_joints_p = cgltf_skin_p->joints[l_2];

				// joint_p = realloc(joint_p, joint_bl + sizeof(uint8_t) + sizeof(uint8_t) + cgltf_node_joints_p->children_count);

				// joint_p[joint_bl] = sizeof(uint8_t) + cgltf_node_joints_p->children_count;
				joint_p[joint_bl + 1] = l_2;
				joint_bl += 2;

				// for (uint32_t c_0 = 0; c_0 < cgltf_node_joints_p->children_count; ++c_0)
				uint32_t c_0 = 0;
				while ((cgltf_node_joints_p = cgltf_node_joints_p->parent) != parent_cgltf_node_p)
				{
					for (uint32_t j_1 = 0; j_1 < cgltf_skin_p->joints_count; ++j_1)
					{
						if (cgltf_node_joints_p == cgltf_skin_p->joints[j_1])
						{
							joint_p[joint_bl + c_0] = j_1;
							break;
						}
					}

					++c_0;
				}
				joint_p[joint_bl - 2] = sizeof(uint8_t) + c_0;
				joint_bl += c_0;

				// if (max_joint_bl < cgltf_node_joints_p->children_count)
				// {
				// 	max_joint_bl = cgltf_node_joints_p->children_count;
				// }
				// joint_bl += cgltf_node_joints_p->children_count;
			}

			bone_bl += cgltf_skin_p->joints_count;
		}

		//need reindex
		uint8_t mix_array[sizeof(float) * 3 + 2];
		uint32_t l_i = 0, l_a = 0;
		for (uint32_t l_1 = 0; l_1 < cgltf_data_p->meshes_count; ++l_1)
		// for (uint32_t l_1 = 0; l_1 < 1; ++l_1)
		{
			cgltf_mesh *cgltf_mesh_p = &cgltf_data_p->meshes[l_1];
			nali_log("cgltf_mesh %s", cgltf_mesh_p->name)

			for (uint32_t l_2 = 0; l_2 < cgltf_mesh_p->primitives_count; ++l_2)
			// for (uint32_t l_2 = 0; l_2 < 1; ++l_2)
			{
				cgltf_primitive *cgltf_primitive_p = &cgltf_mesh_p->primitives[l_2];

				// l_i += sizeof(uint32_t) * cgltf_primitive_p->indices->count;

				// cgltf_accessor *cgltf_accessor_p = cgltf_primitive_p->indices;
				// {
				// 	if (cgltf_accessor_p->component_type == cgltf_component_type_r_16u)
				// 	{
				// 		uint8_t type_bl = cgltf_component_size(cgltf_accessor_p->component_type);
				// 		uint32_t count = cgltf_accessor_p->count;

				// 		uint8_t a_bl = cgltf_accessor_p->stride / type_bl;
				// 		if (a_bl != 1)
				// 		{
				// 			nali_info_t("a_bl>1")
				// 		}

				// 		cgltf_buffer_view *cgltf_buffer_view_p = cgltf_accessor_p->buffer_view;
				// 		uint8_t *p = cgltf_buffer_view_p->buffer->data + cgltf_buffer_view_p->offset;

				// 		uint32_t c = sizeof(uint32_t) * count;
				// 		uint16_t *ui16_p = (uint16_t *)p;

				// 		// index_p = realloc(index_p, index_bl + c);

				// 		uint32_t i = index_bl / sizeof(uint32_t);

				// 		for (uint32_t c_0 = 0; c_0 < count; ++c_0)
				// 		{
				// 			// // ((uint32_t *)index_p)[i + c_0] = i + ui16_p[c_0];
				// 			// ((uint32_t *)index_p)[i + c_0] = ui16_p[c_0];

				// 			ui16_p[c_0];
				// 		}
				// 		// index_bl += c;
				// 		// l_i += c;
				// 	}
				// 	else
				// 	{
				// 		nali_info_t("cgltf_accessor_p->component_type %d", cgltf_accessor_p->component_type)
				// 	}
				// }

				//s0-m
				mix_array[sizeof(float) * 3 + 1] = 0;
				while (mix_array[sizeof(float) * 3 + 1] < material_fl)
				{
					if (!strcmp(material_p[mix_array[sizeof(float) * 3 + 1]], cgltf_primitive_p->material->name))
					{
						break;
					}
					++mix_array[sizeof(float) * 3 + 1];
				}
				if (mix_array[sizeof(float) * 3 + 1] == material_fl)
				{
					cgltf_material *cgltf_material_p = cgltf_primitive_p->material;
					cgltf_float *cgltf_float_array = cgltf_material_p->pbr_metallic_roughness.base_color_factor;
					cgltf_float *emissive_factor = cgltf_material_p->emissive_factor;
					if (strstr(cgltf_material_p->name, ".C0."))
					{
						nali_info_t(".C0.")
					}

					++material_fl;
					material_p = realloc(material_p, sizeof(char *) * material_fl);
					material_p[mix_array[sizeof(float) * 3 + 1]] = cgltf_material_p->name;
					rgba_p = realloc(rgba_p, sizeof(float) * 4 * material_fl);
					uint16_t i4 = mix_array[sizeof(float) * 3 + 1] * 4;
					rgba_p[i4] = emissive_factor[0];
					rgba_p[i4 + 1] = emissive_factor[1];
					rgba_p[i4 + 2] = emissive_factor[2];
					rgba_p[i4 + 3] = cgltf_float_array[3];
				}
				//e0-m

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
									// // /b\ 1
									mix_array[sizeof(float) * 3] = *(v_p + l_3_0 * cgltf_accessor_p->stride + l_5 * type_bl);
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
											nali_info_t("w2 %f", *p)
										}
									}
									else
									{
										nali_info_t("cgltf_accessor_p->component_type %d", cgltf_accessor_p->component_type)
									}

									// // // /b\ 1
									// mix_array[sizeof(float) * 3 + 1] = (uint8_t)*(float *)(v_p + l_3_0 * cgltf_accessor_p->stride + l_5 * type_bl);

									l_set = 1;
								}
								else if (l_5 == 1)
								{
									if (cgltf_accessor_p->component_type == cgltf_component_type_r_32f)
									{
										float *p = (float *)(v_p + l_3_0 * cgltf_accessor_p->stride + l_5 * type_bl);
										if (*p)
										{
											nali_info_t("w2 %f", *p)
										}
									}
									else
									{
										nali_info_t("cgltf_accessor_p->component_type %d", cgltf_accessor_p->component_type)
									}
								}
							}
							else if (cgltf_attribute_p->type == cgltf_attribute_type_position)
							{
								memcpy(mix_array + l_5 * type_bl, v_p + l_3_0 * cgltf_accessor_p->stride + l_5 * type_bl, type_bl);
							}
							else
							{
								nali_info_t("cgltf_attribute_p->type %d", cgltf_attribute_p->type)
							}
						}

						if (l_set == 1)
						{
							// // /b\ 1
							// attribute_p = realloc(attribute_p, attribute_bl + sizeof(uint8_t));
							// memset(attribute_p + attribute_bl, i, sizeof(uint8_t));
							// attribute_bl += sizeof(uint8_t);
							// l_a += sizeof(uint8_t);

							// jwcn |= i << 16;
							// ui_array[2] = i;

							for (uint32_t l_5 = 0; l_5 < attribute_bl; l_5 += sizeof(float) * 3 + 2)
							{
								if (!memcmp(attribute_p + l_5, mix_array, sizeof(float) * 3 + 2))
								{
									index_p = realloc(index_p, index_bl + sizeof(uint32_t));
									*(uint32_t *)(index_p + index_bl) = l_5 / (sizeof(float) * 3 + 2);
									index_bl += sizeof(uint32_t);
									l_i += sizeof(uint32_t);

									l_set = 0;
									break;
								}
							}
							if (l_set == 1)
							{
								attribute_p = realloc(attribute_p, attribute_bl + sizeof(float) * 3 + 2);
								memcpy(attribute_p + attribute_bl, mix_array, sizeof(float) * 3 + 2);

								index_p = realloc(index_p, index_bl + sizeof(uint32_t));
								*(uint32_t *)(index_p + index_bl) = attribute_bl / (sizeof(float) * 3 + 2);
								index_bl += sizeof(uint32_t);
								l_i += sizeof(uint32_t);

								attribute_bl += sizeof(float) * 3 + 2;
								l_a += sizeof(float) * 3 + 2;

								l_set = 0;
							}
							//add extra byte later
						}
					}
				}
			}
		}
		ia_p = realloc(ia_p, ia_bl + sizeof(uint32_t) * 2);
		*(uint32_t *)(ia_p + ia_bl) = l_i;
		*(uint32_t *)(ia_p + ia_bl + sizeof(uint32_t)) = l_a;
		ia_bl += sizeof(uint32_t) * 2;

		cgltf_free(cgltf_data_p);
	}

	nali_info("material_fl %d", material_fl)
	// nali_info("max_joint_bl %d", max_joint_bl)
	nali_info("bone_bl %d", bone_bl)

	// uint32_t l_step = 0;
	// for (uint8_t l_0 = 0; l_0 < joint_count_bl; ++l_0)
	// {
	// 	nali_info("start %d", l_step)

	// 	uint8_t l_joint_bl = joint_count_p[l_0];
	// 	nali_info("%d joint %d", l_0, l_joint_bl)

	// 	for (uint8_t l_1 = 0; l_1 < l_joint_bl; ++l_1)
	// 	{
	// 		uint8_t l_bl = joint_p[l_step];
	// 		l_step += sizeof(uint8_t) + l_bl;
	// 	}

	// 	nali_info("end %d", l_step)

	// 	if (l_joint_bl == max_joint_bl)
	// 	{
	// 		break;
	// 	}
	// }

	FILE *file = fopen(NALI_HOME "asset.bin", "ab");
	nali_log("fopen %p", file)

	fwrite(&joint_count_bl, sizeof(uint8_t), 1, file);
	fwrite(joint_count_p, sizeof(uint8_t), joint_count_bl, file);
	fwrite(joint_p, sizeof(uint8_t), joint_bl, file);
	fwrite(joint_head_p, sizeof(uint8_t), ceil(bone_bl * 3.0F / 8), file);
	fwrite(joint_srt_p, sizeof(uint8_t), joint_srt_bl, file);

	fwrite(&animation_bl, sizeof(uint32_t), 1, file);
	fwrite(animation_p, sizeof(uint8_t), animation_bl, file);

	fwrite(&ia_bl, sizeof(uint32_t), 1, file);
	fwrite(ia_p, sizeof(uint8_t), ia_bl, file);
	fwrite(index_p, sizeof(uint8_t), index_bl, file);
	fwrite(attribute_p, sizeof(uint8_t), attribute_bl, file);

	fwrite(rgba_p, sizeof(float), material_fl * 4, file);
	//color

	fclose(file);
}

// static const uint32_t pipeline[] =
// {
// 	//vert frag
// 	0, 0,
// 	1, 1
// };

// static const uint8_t image[] =
// {
// 	//mipmap line
// 	1 + 2 +
// 	4 + 8

// 	// 1 + 0 +
// 	// 4 + 0

// 	// 0 + 2 +
// 	// 0 + 8
// };

// static const uint32_t model[] =
// {
// 	0
// };

// static const void config[];

void gen_file()
{
	remove(NALI_HOME "asset.bin");
	gen_model();

	// FILE *file = fopen(NALI_HOME "pipeline.bin", "wb");
	// fwrite(pipeline, sizeof(char), sizeof(pipeline), file);
	// fclose(file);

	// file = fopen(NALI_HOME "model.bin", "wb");
	// fwrite(model, sizeof(char), sizeof(model), file);
	// fclose(file);

	// file = fopen(NALI_HOME "image.bin", "wb");
	// fwrite(image, sizeof(char), sizeof(image), file);
	// fclose(file);
}