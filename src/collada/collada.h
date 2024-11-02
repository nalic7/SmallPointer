#ifndef NALI_COLLADA_PARSER_H
#define NALI_COLLADA_PARSER_H

typedef struct
{
	//vector vector
	float **positions;
	float **normals;
	float **texcoord;
	float **color;
	uint32_t **joints;
	float **weights;
} IndexData;

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
	uint32_t max_animation_bones;//-2
	uint32_t max_frame;
	char create_animation;
	//vector
	uint32_t animation_bone_name_vector_size;
	char **animation_bone_name_vector;

	uint32_t max_joint_vector_size;
	uint32_t *max_joint_vector;

	uint32_t max_object;
	char **object_name_vector;

	uint32_t *positions_size;
	float **positions; // V3
	uint32_t *normals_size;
	float **normals; // V3
	uint32_t *texcoord_size;
	float **texcoord; // V2
	// float **color; // V4

	uint32_t *p_offset_size;
	int **p_offset; // V[]

	int **positions_offset;
	int **normals_offset;
	int **texcoord_offset;
	// uint32_t **color_offset;

	uint32_t *joints_size;
	char ***joints;
	uint32_t *weights_size;
	float **weights; // V1-V4
	uint32_t *bind_poses_size;
	float **bind_poses; // M4x4

	uint32_t *v_offset_size; // V[]
	int **v_offset; // V[]
	uint32_t *vcount_offset_size; // V[]
	int **vcount_offset; // V[]

	IndexData indexdata;

	uint32_t ***index; // V1
	uint32_t **unpack_index;
	float **pack_positions; // V3
	float **pack_normals; // V3
	float **pack_texcoord; // V2
	float **pack_color; // V4
	uint32_t *pack_joints_size;
	uint32_t **pack_joints; // V1-V4
	uint32_t *pack_weights_size;
	float **pack_weights; // V1-V4
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
	// BoneData **visual_bones_bonedata_vector_vector;

	uint32_t **max_bones_string_vector_vector_vector;
	char ****bones_string_vector_vector_vector;
} SourceDataType;

#endif
