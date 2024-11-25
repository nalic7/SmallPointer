#ifndef NALI_COLLADA_PARSER_H
#define NALI_COLLADA_PARSER_H

#define C_IN "./C_I"
#define C_OUT "./C_O"

#define C_FIX_ANIMATED 1
#define C_ARMATURE_NAME "<animation id=\""
#define C_VERTEX_FILE "/vertex.bin"
#define C_NORMAL_FILE "/normal.bin"
#define C_TEXCOORD_FILE "/texcoord.bin"
#define C_JOINT_FILE "/joint.bin"
#define C_WEIGHT_FILE "/weight.bin"
#define C_BINDPOSE_FILE "/bindpose.bin"
#define C_BONE_FILE "/bone.dat"
#define C_INDEX_FILE "/index.bin"
// #define C_ANIMATION_NAME "/frame"
// #define C_BONE_NAME "/bone"
// #define C_BONES_M4X4_NAME "/BonesM4x4"
// #define C_SKINNING_BONES_NAME "/SkinningBones"
// #define C_ANIMATION_BONES_NAME "/AnimationBones"
// #define C_TIME_NAME "/time.bin"
#define C_TRANSFORM_FILE "/transform.bin"
// #define C_VISUALBONE_FILE "/visualbone.bin"

typedef struct
{
	float
		p_x, p_y, p_z,
		n_x, n_y, n_z,
		t_x, t_y;
	unsigned char* joint_ptr;
	float* weight_ptr;
	unsigned char max_bone;
} collada_Pack;

typedef struct
{
	//vector
  uint32_t bones_name_string_size;
	char **bones_name_string;
  uint32_t visual_bones_transform_float_vector_size;
	float *visual_bones_transform_float_vector; // M4x4
} BoneData;

typedef struct
{
	uint32_t animation_bone_name_vector_size;
	char **animation_bone_name_vector;



	float **un_pack_visual_bones;
	uint32_t **skinning_bones;
	uint32_t **animation_bones;

	uint32_t armature_string_vector_size;
	char **armature_string_vector;
	uint32_t armature_time_vector_size;
	float *armature_time_vector;
	uint32_t armature_transform_vector_size;
	float *armature_transform_vector; // V1 : M4x4 | DECOMPOSED : samples

	uint32_t max_bonedata;
	uint32_t *space_ptr;
	BoneData *bonedata_vector;

	// uint32_t **max_bones_string_vector_vector_vector;
	// char ****bones_string_vector_vector_vector;

	unsigned char** bone_ptr;
	uint32_t* bone_size_ptr;



	uint32_t max_bone;//-2
	uint32_t max_frame;
	char is_animated;

	uint32_t max_data;
	char **data_name_ptr;

	//s0-data
	uint32_t *vertex_size_ptr;
	float **vertex_ptr; // V3
	uint32_t *normal_size_ptr;
	float **normal_ptr; // V3
	uint32_t *texcoord_size_ptr;
	float **texcoord_ptr; // V2

	uint32_t *p_offset_size;
	int **p_offset; // V[]

	char** joint_ptr;
	float* weight_ptr; // V1-V4
	float* bind_pose_ptr; // M4x4

	uint32_t *v_offset_size; // V[]
	int **v_offset; // V[]
	uint32_t *vcount_offset_size; // V[]
	int **vcount_offset; // V[]
	//e0-data

	// // uint32_t max_bone_size;
	// uint32_t *max_bone_ptr;

	collada_Pack** collada_pack_ptr;
	uint32_t* collada_pack_size_ptr;

	uint32_t** index_ptr;
	uint32_t* index_size_ptr;
} collada_Source;

#endif
