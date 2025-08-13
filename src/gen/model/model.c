#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

#define NALI_GEN_READ_SKIN 1
static const uint8_t setting_array[] =
{
	//read_skin+read_anim
	NALI_GEN_READ_SKIN,
	// 0
};

static const char *file_array[] =
{
	//NALI_F_FACTORY_MODEL "/SuperCutePomi0.glb"//main
	//NALI_F_FACTORY_MODEL "/SuperCutePomi1.glb"
	NALI_F_FACTORY_MODEL "/SuperCutePomi2.glb",//main for now
	// NALI_FACTORY "Font.glb"
};

static const char *mesh_out[] =
{
	//s0-0
	"FE0000.000",//0
	"FE0000.001",//1

	"FE0001.000",//2
	"FE0001.001",//3

	"FE00.000",//4
	"FE00.001",//5

	"FE01.000",//6
	"FE01.001",//7
	"FE01.002",//8
	"FE01.003",//9

	"FE0.000",//10
	"FE0.001",//11

	"FE1",//12

	"M1.000",//13
	"M1.001",//14

	"M0",//15

	"IShovel"//16
	//e0-0
};

static uint8_t mesh_id_array[sizeof(mesh_out) / sizeof(mesh_out[0])];
static uint8_t mesh_index = 0;

// static uint8_t max_joint_bl = 0;

static uint32_t bone_bl = 0;

static uint8_t *joint_count_p;
static uint8_t joint_count_bl = 0;
// static uint8_t *joint_srt_p;//float
// static uint32_t joint_srt_bl = 0;
// static uint32_t joint_srt_step = 0;
// static uint8_t joint_head_array[1024];
static uint8_t joint_array[1024];
static uint32_t joint_bl = 0;

// typedef struct
// {
// 	uint8_t
// 		*time_s_p,
// 		time_s_bl,
// 		*time_r_p,
// 		time_r_bl,
// 		*time_t_p,
// 		time_t_bl;
// 	float
// 		*animation_s_p,
// 		*animation_r_p,
// 		*animation_t_p;
// } anim_bone;

// static anim_bone *anim_bone_p;

// static uint8_t *animation_array[1024 * sizeof(float)];//float
// static uint32_t animation_bl = 0;

static float *rgba_p = 0;
static char **material_p;
static uint8_t material_fl = 0;

static uint8_t *ai_p;//uint32_t
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

// static float i_bindpose_array[1024*2];
// static float global_bindpose_array[1024*2];

void gm_write()
{
	// // float a[16] =
	// // {
	// // 	1,	4,	6,	3,
	// // 	4,	1,	2,	3,
	// // 	9,	7,	1,	3,
	// // 	8,	4,	1,	1
	// // },
	// // b[16] =
	// // {
	// // 	1,	5,	7,	5,
	// // 	2,	1,	1,	4,
	// // 	4,	1,	1,	3,
	// // 	4,	1,	8,	1
	// // }, c[16];
	// // m4x4_m(a, b, c);
	// // m4x4_m(b, a, c);
	// // m4x4_i(c);
	// float q[4];
	// v4_q(0.229, -0.927, 0.458, q);
	// float r[16];
	// v4_qm(q, r);
	joint_count_p = malloc(0);
	// // joint_srt_p = malloc(0);

	// memset(joint_head_array, 0, 1024);

	// // memset(animation_array, 0, 1024 * sizeof(float));
	// // animation_p = malloc(0);
	// anim_bone_p = malloc(0);

	i_bindpose_p = malloc(0);

	material_p = malloc(0);

	ai_p = malloc(0);
	attribute_j1c1_p = malloc(0);
	i_p = malloc(0);
	cut_i_p = malloc(0);

	cgltf_options *cgltf_options_p = &(cgltf_options){};
	cgltf_data *cgltf_data_p = NULL;
	for (uint32_t l_0 = 0; l_0 < sizeof(file_array) / sizeof(file_array[0]); ++l_0)
	{
		NALI_D_INFO("cgltf_parse_file %d", cgltf_parse_file(cgltf_options_p, file_array[l_0], &cgltf_data_p))
		NALI_D_INFO("cgltf_load_buffers %d", cgltf_load_buffers(cgltf_options_p, cgltf_data_p, file_array[l_0]))
		NALI_D_INFO("cgltf_validate %d", cgltf_validate(cgltf_data_p))

		// for (uint32_t l_1 = 0; l_1 < cgltf_data_p->animations_count; ++l_1)
		cgltf_node *parent_cgltf_node_p = cgltf_data_p->skins[0].joints[0]->parent;

		// if (setting_array[l_0] & NALI_GEN_READ_SKIN)
		// {
		// 	// cgltf_animation *cgltf_animation_p = &cgltf_data_p->animations[l_1];
		// 	cgltf_animation *cgltf_animation_p = &cgltf_data_p->animations[0];

		// 	//input frame f 0 0.5 1.0
		// 	//output s/r/t vec3/vec4 v v v
		// 	// for (uint32_t s = 0; s < cgltf_animation_p->samplers_count; ++s)
		// 	// {
		// 	// 	cgltf_animation_p->samplers;
		// 	// }

		// 	anim_bone_p = realloc(anim_bone_p, (bone_bl + cgltf_data_p->skins[0].joints_count) * sizeof(anim_bone));
		// 	memset(anim_bone_p + bone_bl, 0, cgltf_data_p->skins[0].joints_count * sizeof(anim_bone));

		// 	for (uint32_t l_2 = 0; l_2 < cgltf_animation_p->channels_count; ++l_2)
		// 	{
		// 		// cgltf_animation_sampler *cgltf_animation_sampler_p = &cgltf_animation_p->samplers[l_2];
		// 		cgltf_animation_channel *cgltf_animation_channel_p = &cgltf_animation_p->channels[l_2];
		// 		cgltf_animation_sampler *cgltf_animation_sampler_p = cgltf_animation_channel_p->sampler;

		// 		cgltf_accessor *cgltf_accessor_input_p = cgltf_animation_sampler_p->input;
		// 		cgltf_accessor *cgltf_accessor_output_p = cgltf_animation_sampler_p->output;

		// 		uint8_t bone_index;
		// 		// for (uint32_t l_3 = 0; l_3 < cgltf_data_p->skins_count; ++l_3)
		// 			// for (uint32_t l_4 = 0; l_4 < cgltf_data_p->skins[l_3].joints_count; ++l_4)
		// 		for (uint32_t l_3 = 0; l_3 < cgltf_data_p->skins[0].joints_count; ++l_3)
		// 				// if (cgltf_animation_channel_p->target_node == cgltf_data_p->skins[l_3].joints[l_4])
		// 			if (cgltf_animation_channel_p->target_node == cgltf_data_p->skins[0].joints[l_3])
		// 			{
		// 				bone_index = l_3;
		// 				break;
		// 			}

		// 		// /b\ 1
		// 		// animation_p = realloc(animation_p, animation_bl + sizeof(uint8_t) + cgltf_accessor_input_p->count);
		// 		// *(uint8_t *)(animation_p + animation_bl) = cgltf_accessor_input_p->count;
		// 		// animation_bl += sizeof(uint8_t);

		// 		cgltf_buffer_view *cgltf_buffer_view_p = cgltf_accessor_input_p->buffer_view;
		// 		float *tp = cgltf_buffer_view_p->buffer->data + cgltf_buffer_view_p->offset;

		// 		// /b\ 1
		// 		// for (uint32_t l_3 = 0; l_3 < cgltf_accessor_input_p->count; ++l_3)
		// 		// 	*(uint8_t*)(animation_p + animation_bl + l_3) = p[l_3] * NALI_FPS;
		// 		// animation_bl += cgltf_accessor_input_p->count;

		// 		cgltf_buffer_view_p = cgltf_accessor_output_p->buffer_view;
		// 		float *p = cgltf_buffer_view_p->buffer->data + cgltf_buffer_view_p->offset;

		// 		uint32_t j = (bone_bl + bone_index) * 3;
		// 		uint8_t
		// 			j_step = j % 8,
		// 			j_next,

		// 			time_bl = 0;

		// 		float l_q[4];
		// 		// /b\ keyframe
		// 		float q[4*255];
		// 		switch (cgltf_animation_channel_p->target_path)
		// 		{
		// 			case cgltf_animation_path_type_scale:
		// 				joint_head_array[j / 8] |= 1 << j_step;

		// 				// for (uint32_t l_4 = 0; l_4 < cgltf_accessor_input_p->count; ++l_4)
		// 				// {
		// 				// 	q[l_4 * 3] = p[l_4 * 3] - cgltf_animation_channel_p->target_node->scale[0];
		// 				// 	q[l_4 * 3 + 1] = p[l_4 * 3 + 1] - cgltf_animation_channel_p->target_node->scale[1];
		// 				// 	q[l_4 * 3 + 2] = p[l_4 * 3 + 2] - cgltf_animation_channel_p->target_node->scale[2];

		// 				// 	q[l_4 * 3] = 0;
		// 				// 	q[l_4 * 3 + 1] = 0;
		// 				// 	q[l_4 * 3 + 2] = 0;
		// 				// }

		// 				anim_bone_p[bone_bl + bone_index].time_s_bl = cgltf_accessor_input_p->count;
		// 				anim_bone_p[bone_bl + bone_index].time_s_p = malloc(cgltf_accessor_input_p->count);
		// 				for (uint32_t l_3 = 0; l_3 < cgltf_accessor_input_p->count; ++l_3)
		// 					anim_bone_p[bone_bl + bone_index].time_s_p[l_3] = tp[l_3] * NALI_FPS;
		// 				anim_bone_p[bone_bl + bone_index].animation_s_p = malloc(cgltf_accessor_input_p->count * sizeof(float) * 3);
		// 				memcpy(anim_bone_p[bone_bl + bone_index].animation_s_p, p, cgltf_accessor_input_p->count * sizeof(float) * 3);

		// 				// anim_bone_p[bone_bl + bone_index].time_s_p = malloc(0);
		// 				// anim_bone_p[bone_bl + bone_index].animation_s_p = malloc(0);
		// 				// for (uint32_t l_3 = 0; l_3 < cgltf_accessor_input_p->count; ++l_3)
		// 				// {
		// 				// 	uint8_t time = tp[l_3] * NALI_FPS;
		// 				// 	for (uint32_t l_4 = 0; l_4 < keyframe_bl_array[l_0]; ++l_4)
		// 				// 		if (keyframe_p_array[l_0][l_4] == time)
		// 				// 		{
		// 				// 			++time_bl;
		// 				// 			break;
		// 				// 		}
		// 				// 	if (time_bl > 0)
		// 				// 	{
		// 				// 		anim_bone_p[bone_bl + bone_index].time_s_p = realloc(anim_bone_p[bone_bl + bone_index].time_s_p, time_bl);
		// 				// 		anim_bone_p[bone_bl + bone_index].time_s_p[time_bl - 1] = time;
		// 				// 		anim_bone_p[bone_bl + bone_index].animation_s_p = realloc(anim_bone_p[bone_bl + bone_index].animation_s_p, time_bl * 3 * sizeof(float));
		// 				// 		memcpy(anim_bone_p[bone_bl + bone_index].animation_s_p + (time_bl - 1) * 3, p + l_3 * 3, sizeof(float) * 3);
		// 				// 	}
		// 				// }
		// 				// anim_bone_p[bone_bl + bone_index].time_s_bl = time_bl;

		// 				// NALI_MEMORY_RECOPY(animation_p, p, animation_bl, cgltf_accessor_input_p->count * sizeof(float) * 3)
		// 				break;
		// 			case cgltf_animation_path_type_rotation:
		// 				// if (bone_index != 1)
		// 				// 	continue;
		// 				j_next = j_step + 1;
		// 				joint_head_array[j / 8 + j_next / 8] |= 1 << (j_next % 8);

		// 				memcpy(l_q, cgltf_animation_channel_p->target_node->rotation, sizeof(float) * 4);
		// 				MV4_qi(l_q, 0)
		// 				for (uint32_t l_4 = 0; l_4 < cgltf_accessor_input_p->count; ++l_4)
		// 				{
		// 					// MV4_qi(p, l_4 * 4)
		// 					m_v4_m(l_q, p + l_4 * 4, q + l_4 * 4);
		// 					MV4_qi(q, l_4 * 4)
		// 				}
		// 				// for (uint32_t l_4 = 0; l_4 < cgltf_accessor_input_p->count; ++l_4)
		// 				// {
		// 				// 	if (q[3+l_4*4] == 0)
		// 				// 	{
		// 				// 		q[3+l_4*4] = 1;
		// 				// 	}
		// 				// }

		// 				anim_bone_p[bone_bl + bone_index].time_r_bl = cgltf_accessor_input_p->count;
		// 				anim_bone_p[bone_bl + bone_index].time_r_p = malloc(cgltf_accessor_input_p->count);
		// 				for (uint32_t l_3 = 0; l_3 < cgltf_accessor_input_p->count; ++l_3)
		// 					anim_bone_p[bone_bl + bone_index].time_r_p[l_3] = tp[l_3] * NALI_FPS;
		// 				anim_bone_p[bone_bl + bone_index].animation_r_p = malloc(cgltf_accessor_input_p->count * sizeof(float) * 4);
		// 				memcpy(anim_bone_p[bone_bl + bone_index].animation_r_p, q, cgltf_accessor_input_p->count * sizeof(float) * 4);

		// 				// anim_bone_p[bone_bl + bone_index].time_r_p = malloc(0);
		// 				// anim_bone_p[bone_bl + bone_index].animation_r_p = malloc(0);
		// 				// for (uint32_t l_3 = 0; l_3 < cgltf_accessor_input_p->count; ++l_3)
		// 				// {
		// 				// 	uint8_t time = tp[l_3] * NALI_FPS;
		// 				// 	for (uint32_t l_4 = 0; l_4 < keyframe_bl_array[l_0]; ++l_4)
		// 				// 		if (keyframe_p_array[l_0][l_4] == time)
		// 				// 		{
		// 				// 			++time_bl;
		// 				// 			break;
		// 				// 		}
		// 				// 	if (time_bl > 0)
		// 				// 	{
		// 				// 		anim_bone_p[bone_bl + bone_index].time_r_p = realloc(anim_bone_p[bone_bl + bone_index].time_r_p, time_bl);
		// 				// 		anim_bone_p[bone_bl + bone_index].time_r_p[time_bl - 1] = time;
		// 				// 		anim_bone_p[bone_bl + bone_index].animation_r_p = realloc(anim_bone_p[bone_bl + bone_index].animation_r_p, time_bl * 4 * sizeof(float));
		// 				// 		memcpy(anim_bone_p[bone_bl + bone_index].animation_r_p + (time_bl - 1) * 4, q + l_3 * 4, sizeof(float) * 4);
		// 				// 	}
		// 				// }
		// 				// anim_bone_p[bone_bl + bone_index].time_r_bl = time_bl;

		// 				// NALI_MEMORY_RECOPY(animation_p, q, animation_bl, cgltf_accessor_input_p->count * sizeof(float) * 4)
		// 				break;
		// 			case cgltf_animation_path_type_translation:
		// 				if (bone_index != 12)
		// 					continue;
		// 				j_next = j_step + 2;
		// 				joint_head_array[j / 8 + j_next / 8] |= 1 << (j_next % 8);

		// 				for (uint32_t l_4 = 0; l_4 < cgltf_accessor_input_p->count; ++l_4)
		// 				{
		// 					if (l_4 != 75)
		// 						continue;

		// 					q[l_4 * 3] = p[l_4 * 3];
		// 					q[l_4 * 3 + 1] = p[l_4 * 3 + 1];
		// 					q[l_4 * 3 + 2] = p[l_4 * 3 + 2];

		// 					cgltf_node *own_parent_cgltf_node_p = cgltf_animation_channel_p->target_node;
		// 					do
		// 					{
		// 						q[l_4 * 3] -= own_parent_cgltf_node_p->translation[0];
		// 						q[l_4 * 3 + 1] -= own_parent_cgltf_node_p->translation[1];
		// 						q[l_4 * 3 + 2] -= own_parent_cgltf_node_p->translation[2];
		// 					} while ((own_parent_cgltf_node_p = own_parent_cgltf_node_p->parent) != parent_cgltf_node_p);

		// 					q[l_4 * 3] = -q[l_4 * 3];
		// 					q[l_4 * 3 + 1] = -q[l_4 * 3 + 1];
		// 					q[l_4 * 3 + 2] = -q[l_4 * 3 + 2];
		// 				}

		// 				// 	// 	// q[l_4 * 3] = 0;
		// 				// 	// 	// q[l_4 * 3 + 1] = 0;
		// 				// 	// 	// q[l_4 * 3 + 2] = 0;
		// 				// 	// }

		// 				// 	q[l_4 * 3] = cgltf_animation_channel_p->target_node->translation[0] - p[l_4 * 3];
		// 				// 	q[l_4 * 3 + 1] = cgltf_animation_channel_p->target_node->translation[1] - p[l_4 * 3 + 1];
		// 				// 	q[l_4 * 3 + 2] = cgltf_animation_channel_p->target_node->translation[2] - p[l_4 * 3 + 2];
		// 				// }

		// 				anim_bone_p[bone_bl + bone_index].time_t_bl = cgltf_accessor_input_p->count;
		// 				anim_bone_p[bone_bl + bone_index].time_t_p = malloc(cgltf_accessor_input_p->count);
		// 				for (uint32_t l_3 = 0; l_3 < cgltf_accessor_input_p->count; ++l_3)
		// 					anim_bone_p[bone_bl + bone_index].time_t_p[l_3] = tp[l_3] * NALI_FPS;
		// 				anim_bone_p[bone_bl + bone_index].animation_t_p = malloc(cgltf_accessor_input_p->count * sizeof(float) * 3);
		// 				memcpy(anim_bone_p[bone_bl + bone_index].animation_t_p, q, cgltf_accessor_input_p->count * sizeof(float) * 3);

		// 				// anim_bone_p[bone_bl + bone_index].time_t_p = malloc(0);
		// 				// anim_bone_p[bone_bl + bone_index].animation_t_p = malloc(0);
		// 				// for (uint32_t l_3 = 0; l_3 < cgltf_accessor_input_p->count; ++l_3)
		// 				// {
		// 				// 	uint8_t time = tp[l_3] * NALI_FPS;
		// 				// 	for (uint32_t l_4 = 0; l_4 < keyframe_bl_array[l_0]; ++l_4)
		// 				// 		if (keyframe_p_array[l_0][l_4] == time)
		// 				// 		{
		// 				// 			++time_bl;
		// 				// 			break;
		// 				// 		}
		// 				// 	if (time_bl > 0)
		// 				// 	{
		// 				// 		anim_bone_p[bone_bl + bone_index].time_t_p = realloc(anim_bone_p[bone_bl + bone_index].time_t_p, time_bl);
		// 				// 		anim_bone_p[bone_bl + bone_index].time_t_p[time_bl - 1] = time;
		// 				// 		anim_bone_p[bone_bl + bone_index].animation_t_p = realloc(anim_bone_p[bone_bl + bone_index].animation_t_p, time_bl * 3 * sizeof(float));
		// 				// 		memcpy(anim_bone_p[bone_bl + bone_index].animation_t_p + (time_bl - 1) * 3, q + l_3 * 3, sizeof(float) * 3);
		// 				// 	}
		// 				// }
		// 				// anim_bone_p[bone_bl + bone_index].time_t_bl = time_bl;

		// 				// NALI_MEMORY_RECOPY(animation_p, p, animation_bl, cgltf_accessor_input_p->count * sizeof(float) * 3)
		// 				break;
		// 			default:
		// 				NALI_D_INFO_A("cgltf_animation_channel_p->target_path %d", cgltf_animation_channel_p->target_path)
		// 		}
		// 	}
		// }

		// for (uint32_t l_1 = 0; l_1 < cgltf_data_p->skins_count; ++l_1)
		if (setting_array[l_0] & NALI_GEN_READ_SKIN)
		{
			// cgltf_skin *cgltf_skin_p = &cgltf_data_p->skins[l_1];
			cgltf_skin *cgltf_skin_p = &cgltf_data_p->skins[0];

			// for (uint32_t l_2 = 0; l_2 < cgltf_skin_p->joints_count; ++l_2)
			// {
			// 	cgltf_node *cgltf_node_joints_p = cgltf_skin_p->joints[l_2];
			// 	uint32_t j = (bone_bl + l_2) * 3;
			// 	uint8_t j_step = j % 8;
			// 	if (cgltf_node_joints_p->has_scale)
			// 	{
			// 		joint_head_array[j / 8] |= 1 << j_step;
			// 		joint_srt_bl += sizeof(float) * 3;
			// 	}

			// 	if (cgltf_node_joints_p->has_rotation)
			// 	{
			// 		uint8_t j_next = j_step + 1;
			// 		joint_head_array[j / 8 + j_next / 8] |= 1 << (j_next % 8);
			// 		joint_srt_bl += sizeof(float) * 4;
			// 	}

			// 	if (cgltf_node_joints_p->has_translation)
			// 	{
			// 		uint8_t j_next = j_step + 2;
			// 		joint_head_array[j / 8 + j_next / 8] |= 1 << (j_next % 8);
			// 		joint_srt_bl += sizeof(float) * 3;
			// 	}

			// 	if (cgltf_node_joints_p->has_matrix)
			// 	{
			// 		NALI_D_INFO_A("%s has_matrix", cgltf_node_joints_p->name);
			// 		// cgltf_node_p->matrix;
			// 	}
			// }

			// joint_srt_p = realloc(joint_srt_p, joint_srt_bl);

			//s0-test
			i_bindpose_p = realloc(i_bindpose_p, (bone_bl + cgltf_skin_p->joints_count) * sizeof(float) * 16);
			// memcpy(i_bindpose_array + bone_bl * 16, cgltf_skin_p->inverse_bind_matrices->buffer_view->buffer->data + cgltf_skin_p->inverse_bind_matrices->buffer_view->offset, sizeof(float) * 16 * cgltf_skin_p->joints_count);
			memcpy(i_bindpose_p + bone_bl * 16, cgltf_skin_p->inverse_bind_matrices->buffer_view->buffer->data + cgltf_skin_p->inverse_bind_matrices->buffer_view->offset, sizeof(float) * 16 * cgltf_skin_p->joints_count);

			// for (uint32_t l_2 = 0; l_2 < cgltf_skin_p->joints_count; ++l_2)
			// {
			// 	cgltf_node *cgltf_node_joints_p = cgltf_skin_p->joints[l_2];

			// 	memcpy(global_bindpose_array + (bone_bl + l_2) * 16, m_m4x4_mat, sizeof(float) * 16);
			// 	do
			// 	{
			// 		//trs
			// 		if (cgltf_node_joints_p->has_scale)
			// 		{
			// 			float s_array[16] =
			// 			{
			// 				cgltf_node_joints_p->scale[0], 0, 0, 0,
			// 				0, cgltf_node_joints_p->scale[1], 0, 0,
			// 				0, 0, cgltf_node_joints_p->scale[2], 0,
			// 				0, 0, 0, 1,
			// 			};
			// 			m4x4_m(s_array, global_bindpose_array + (bone_bl + l_2) * 16, global_bindpose_array + (bone_bl + l_2) * 16);
			// 		}
			// 		if (cgltf_node_joints_p->has_rotation)
			// 		{
			// 			float r_array[16];
			// 			memcpy(r_array, m_m4x4_mat, sizeof(float) * 16);
			// 			v4_q2m(cgltf_node_joints_p->rotation, r_array);
			// 			m4x4_m(r_array, global_bindpose_array + (bone_bl + l_2) * 16, global_bindpose_array + (bone_bl + l_2) * 16);
			// 		}
			// 		if (cgltf_node_joints_p->has_translation)
			// 		{
			// 			float t_array[16] =
			// 			{
			// 				1, 0, 0, 0,
			// 				0, 1, 0, 0,
			// 				0, 0, 1, 0,
			// 				cgltf_node_joints_p->translation[0], cgltf_node_joints_p->translation[1], cgltf_node_joints_p->translation[2], 1,
			// 			};
			// 			m4x4_m(t_array, global_bindpose_array + (bone_bl + l_2) * 16, global_bindpose_array + (bone_bl + l_2) * 16);
			// 		}
			// 		if (cgltf_node_joints_p->has_matrix)
			// 		{
			// 			NALI_D_INFO_A("cgltf_node_joints_p->has_matrix");
			// 		}
			// 	}
			// 	while ((cgltf_node_joints_p = cgltf_node_joints_p->parent) != parent_cgltf_node_p);

			// // 	m4x4_i(global_bindpose_array + (bone_bl + l_2) * 16);
			// // 	m4x4_m(i_bindpose_array + (bone_bl + l_2) * 16, global_bindpose_array + (bone_bl + l_2) * 16, i_bindpose_array + (bone_bl + l_2) * 16);
			// // // 	// for (uint8_t l_3 = 0; l_3 < 16; ++l_3)
			// // // 	// {
			// // // 	// 	NALI_D_LOG("%d [%d] %f", bone_bl + l_2, l_3, fabsf((local_bindpose_array + (bone_bl + l_2) * 16)[l_3] - (global_bindpose_array + (bone_bl + l_2) * 16)[l_3]));
			// // // 	// }

			// // // 	// NALI_D_LOG("---");
			// }
			// memcpy(i_bindpose_array + bone_bl * 16, global_bindpose_array + bone_bl * 16, sizeof(float) * 16 * cgltf_skin_p->joints_count);

			// // // for (uint32_t l_2 = 0; l_2 < cgltf_skin_p->joints_count; ++l_2)
			// // // {
			// // // 	cgltf_node *cgltf_node_joints_p = cgltf_skin_p->joints[l_2];

			// // // 	int8_t l_2_0 = 0;
			// // // 	float bindpose[22][16];
			// // // 	do
			// // // 	{
			// // // 		memcpy(bindpose[l_2_0], m_m4x4_mat, sizeof(float) * 16);
			// // // 		for (uint32_t l_3 = 0; l_3 < cgltf_skin_p->joints_count; ++l_3)
			// // // 		{
			// // // 			if (cgltf_skin_p->joints[l_3] == cgltf_node_joints_p)
			// // // 			{
			// // // 				m4x4_m(global_bindpose_array + (bone_bl + l_3) * 16, bindpose[l_2_0]);
			// // // 				break;
			// // // 			}
			// // // 		}
			// // // 		++l_2_0;
			// // // 	}
			// // // 	while ((cgltf_node_joints_p = cgltf_node_joints_p->parent) != parent_cgltf_node_p);

			// // // 	memcpy(bindpose[l_2_0 + 1], m_m4x4_mat, sizeof(float) * 16);
			// // // 	for (int8_t l_3 = l_2_0 - 1; l_3 > -1; --l_3)
			// // // 	{
			// // // 		m4x4_m(bindpose[l_3], bindpose[l_2_0 + 1]);
			// // // 	}

			// // // 	m4x4_i(bindpose[l_2_0 + 1]);
			// // // 	for (uint8_t l_3 = 0; l_3 < 16; ++l_3)
			// // // 	{
			// // // 		NALI_D_LOG("%d [%d] %f", bone_bl + l_2, l_3, fabsf((local_bindpose_array + (bone_bl + l_2) * 16)[l_3] - bindpose[l_2_0 + 1][l_3]));
			// // // 	}

			// // // 	NALI_D_LOG("---");
			// // // }
			// //e0-test

			// for (uint32_t l_2 = 0; l_2 < cgltf_skin_p->joints_count; ++l_2)
			// {
			// 	cgltf_node *cgltf_node_joints_p = cgltf_skin_p->joints[l_2];
			// 	if (cgltf_node_joints_p->has_scale)
			// 	{
			// 		NALI_MEMORY_COPY(joint_srt_p, cgltf_node_joints_p->scale, joint_srt_step, sizeof(float) * 3)
			// 	}
			// 	if (cgltf_node_joints_p->has_rotation)
			// 	{
			// 		NALI_MEMORY_COPY(joint_srt_p, cgltf_node_joints_p->rotation, joint_srt_step, sizeof(float) * 4)
			// 	}
			// 	if (cgltf_node_joints_p->has_translation)
			// 	{
			// 		NALI_MEMORY_COPY(joint_srt_p, cgltf_node_joints_p->translation, joint_srt_step, sizeof(float) * 3)
			// 	}
			// }

			joint_count_p = realloc(joint_count_p, joint_count_bl + sizeof(uint8_t));
			joint_count_p[joint_count_bl] = cgltf_skin_p->joints_count;
			joint_count_bl += sizeof(uint8_t);

			// cgltf_node *parent_cgltf_node_p = cgltf_skin_p->joints[0]->parent;

			for (uint32_t l_2 = 0; l_2 < cgltf_skin_p->joints_count; ++l_2)
			{
				cgltf_node *cgltf_node_joints_p = cgltf_skin_p->joints[l_2];

				// joint_p = realloc(joint_p, joint_bl + sizeof(uint8_t) + sizeof(uint8_t) + cgltf_node_joints_p->children_count);

				// joint_p[joint_bl] = sizeof(uint8_t) + cgltf_node_joints_p->children_count;
				joint_array[joint_bl + 1] = l_2;
				joint_bl += 2;

				// for (uint32_t c_0 = 0; c_0 < cgltf_node_joints_p->children_count; ++c_0)
				uint32_t c_0 = 0;
				while ((cgltf_node_joints_p = cgltf_node_joints_p->parent) != parent_cgltf_node_p)
				{
					for (uint32_t j_1 = 0; j_1 < cgltf_skin_p->joints_count; ++j_1)
						if (cgltf_node_joints_p == cgltf_skin_p->joints[j_1])
						{
							joint_array[joint_bl + c_0] = j_1;
							break;
						}

					++c_0;
				}
				joint_array[joint_bl - 2] = sizeof(uint8_t) + c_0;
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
		uint32_t l_index = 0;
		uint32_t l_own_index = 0;
		uint32_t *l_index_p;
		for (uint32_t l_1 = 0; l_1 < cgltf_data_p->meshes_count; ++l_1)
		// for (uint32_t l_1 = 0; l_1 < 3; ++l_1)
		{
			cgltf_mesh *cgltf_mesh_p = &cgltf_data_p->meshes[l_1];
			NALI_D_LOG("cgltf_mesh %s", cgltf_mesh_p->name)

			l_index_p = &l_index;

			for (uint8_t l_2 = 0; l_2 < sizeof(mesh_out) / sizeof(mesh_out[0]); ++l_2)
				if (!strcmp(mesh_out[l_2], cgltf_mesh_p->name))
				{
					mesh_id_array[l_2] = mesh_index++;
					l_own_index = 0;
					l_index_p = &l_own_index;
					break;
				}

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
				// 			NALI_D_INFO_A("a_bl>1")
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
				// 		NALI_D_INFO_A("cgltf_accessor_p->component_type %d", cgltf_accessor_p->component_type)
				// 	}
				// }

				//s0-m
				mix_array[sizeof(float) * 3] = 0;
				while (mix_array[sizeof(float) * 3] < material_fl)
				{
					if (!strcmp(material_p[mix_array[sizeof(float) * 3]], cgltf_primitive_p->material->name))
						break;
					//j1c1
					++mix_array[sizeof(float) * 3];
				}
				if (mix_array[sizeof(float) * 3] == material_fl)
				{
					cgltf_material *cgltf_material_p = cgltf_primitive_p->material;
					cgltf_float *cgltf_float_array = cgltf_material_p->pbr_metallic_roughness.base_color_factor;
					cgltf_float *emissive_factor = cgltf_material_p->emissive_factor;
					if (strstr(cgltf_material_p->name, ".C0."))
						NALI_D_INFO_A("nali_format .C0.")

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
									mix_array[sizeof(float) * 3 + 1] = *(v_p + l_3_0 * cgltf_accessor_p->stride + l_5 * type_bl);
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
											NALI_D_INFO_A("nali_format w2 %f", *p)
										}
									}
									else
									{
										NALI_D_INFO_A("nali_format cgltf_accessor_p->component_type %d", cgltf_accessor_p->component_type)
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
											NALI_D_INFO_A("nali_format w2 %f", *p)
										}
									}
									else
									{
										NALI_D_INFO_A("nali_format cgltf_accessor_p->component_type %d", cgltf_accessor_p->component_type)
									}
								}
							}
							else if (cgltf_attribute_p->type == cgltf_attribute_type_position)
							{
								memcpy(mix_array + l_5 * type_bl, v_p + l_3_0 * cgltf_accessor_p->stride + l_5 * type_bl, type_bl);
							}
							else
							{
								NALI_D_INFO_A("nali_format cgltf_attribute_p->type %d", cgltf_attribute_p->type)
							}
						}

						//c1
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
						//j1u1v1t1
						// if (cgltf_primitive_p->attributes_count == 4 && l_4 == 3)
						// {

						// }
						//j1c1
						else if (l_set == 1)
						{
							// // /b\ 1
							// attribute_p = realloc(attribute_p, attribute_bl + sizeof(uint8_t));
							// memset(attribute_p + attribute_bl, i, sizeof(uint8_t));
							// attribute_bl += sizeof(uint8_t);
							// l_a += sizeof(uint8_t);

							// jwcn |= i << 16;
							// ui_array[2] = i;

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
							//add extra byte later
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

	NALI_D_INFO("material_fl %d", material_fl)
	// NALI_D_INFO("max_joint_bl %d", max_joint_bl)
	NALI_D_INFO("bone_bl %d", bone_bl)

	// uint32_t l_step = 0;
	// for (uint8_t l_0 = 0; l_0 < joint_count_bl; ++l_0)
	// {
	// 	NALI_D_INFO("start %d", l_step)

	// 	uint8_t l_joint_bl = joint_count_p[l_0];
	// 	NALI_D_INFO("%d joint %d", l_0, l_joint_bl)

	// 	for (uint8_t l_1 = 0; l_1 < l_joint_bl; ++l_1)
	// 	{
	// 		uint8_t l_bl = joint_p[l_step];
	// 		l_step += sizeof(uint8_t) + l_bl;
	// 	}

	// 	NALI_D_INFO("end %d", l_step)

	// 	if (l_joint_bl == max_joint_bl)
	// 	{
	// 		break;
	// 	}
	// }

	FILE *file = fopen(NALI_F_HOME_ASSET, "ab");
	NALI_D_LOG("fopen %p", file)

	fwrite(&joint_count_bl, sizeof(uint8_t), 1, file);
	fwrite(joint_count_p, sizeof(uint8_t), joint_count_bl, file);
	fwrite(joint_array, sizeof(uint8_t), joint_bl, file);
	// fwrite(i_bindpose_array, sizeof(float), bone_bl * 16, file);
	fwrite(i_bindpose_p, sizeof(float), bone_bl * 16, file);
	// fwrite(global_bindpose_array, sizeof(float), bone_bl * 16, file);

	// //anim
	// fwrite(joint_head_array, sizeof(uint8_t), ceil(bone_bl * 3.0F / 8), file);
	// // fwrite(joint_srt_p, sizeof(uint8_t), joint_srt_bl, file);

	// // fwrite(&animation_bl, sizeof(uint32_t), 1, file);
	// // fwrite(animation_array, sizeof(uint8_t), animation_bl, file);
	// for (uint32_t l_0 = 0; l_0 < bone_bl; ++l_0)
	// {
	// 	if (anim_bone_p[l_0].time_s_bl)
	// 	{
	// 		fwrite(&anim_bone_p[l_0].time_s_bl, sizeof(uint8_t), 1, file);
	// 		fwrite(anim_bone_p[l_0].time_s_p, sizeof(uint8_t), anim_bone_p[l_0].time_s_bl, file);

	// 		fwrite(anim_bone_p[l_0].animation_s_p, sizeof(float), anim_bone_p[l_0].time_s_bl * 3, file);
	// 	}

	// 	if (anim_bone_p[l_0].time_r_bl)
	// 	{
	// 		fwrite(&anim_bone_p[l_0].time_r_bl, sizeof(uint8_t), 1, file);
	// 		fwrite(anim_bone_p[l_0].time_r_p, sizeof(uint8_t), anim_bone_p[l_0].time_r_bl, file);

	// 		fwrite(anim_bone_p[l_0].animation_r_p, sizeof(float), anim_bone_p[l_0].time_r_bl * 4, file);
	// 	}

	// 	if (anim_bone_p[l_0].time_t_bl)
	// 	{
	// 		fwrite(&anim_bone_p[l_0].time_t_bl, sizeof(uint8_t), 1, file);
	// 		fwrite(anim_bone_p[l_0].time_t_p, sizeof(uint8_t), anim_bone_p[l_0].time_t_bl, file);

	// 		fwrite(anim_bone_p[l_0].animation_t_p, sizeof(float), anim_bone_p[l_0].time_t_bl * 3, file);
	// 	}
	// }

	fwrite(&ai_bl, sizeof(uint32_t), 1, file);
	// fwrite(ai_p, sizeof(uint8_t), ai_bl, file);
	for (uint8_t l_0 = 0; l_0 < sizeof(mesh_out) / sizeof(mesh_out[0]); ++l_0)
	{
		uint8_t l_0_0 = mesh_id_array[l_0];
		fwrite(ai_p + l_0_0 * sizeof(uint32_t), sizeof(uint32_t), 1, file);
	}
	fwrite(ai_p + sizeof(mesh_out) / sizeof(mesh_out[0]) * sizeof(uint32_t), sizeof(uint32_t), 1, file);

	for (uint8_t l_0 = 0; l_0 < sizeof(mesh_out) / sizeof(mesh_out[0]); ++l_0)
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
	// fwrite(cut_i_p, sizeof(uint8_t), cut_i_bl, file);
	fwrite(i_p, sizeof(uint8_t), i_bl, file);

	fwrite(&material_fl, sizeof(uint8_t), 1, file);
	fwrite(rgba_p, sizeof(float), material_fl * 4, file);

	//uv

	//a c1
	fwrite((uint32_t[]){attribute_c1_bl / (sizeof(float)*3+1)}, sizeof(uint32_t), 1, file);
	fwrite(attribute_c1_p, sizeof(uint8_t), attribute_c1_bl, file);

	//a j1c1
	// fwrite((uint32_t[]){attribute_j1c1_bl / (sizeof(float)*3+2)}, sizeof(uint32_t), 1, file);
	fwrite(attribute_j1c1_p, sizeof(uint8_t), attribute_j1c1_bl, file);

	//a j1t1u1v1

	//a t1u1v1

	fclose(file);
}
