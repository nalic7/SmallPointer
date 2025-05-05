#ifndef NALI_COLLADA_PARSER_H
#define NALI_COLLADA_PARSER_H

#define C_FIX_ANIMATED 1
// #define C_CURVE 1
// #define C_OUT_NORMAL 1
#define C_OUT_TEXCOORD 1
#define C_ARMATURE_NAME "<animation id=\""
#define C_VERTEX_FILE "/vertex.bin"
#ifdef C_OUT_NORMAL
	#define C_NORMAL_FILE "/normal.bin"
#endif
#ifdef C_OUT_TEXCOORD
	#define C_TEXCOORD_FILE "/texcoord.bin"
#endif
#define C_JOINT_FILE "/joint.bin"
#define C_WEIGHT_FILE "/weight.bin"
#define C_BINDPOSE_FILE "/bindpose.bin"
#define C_INDEX_FILE "/index.bin"
#define C_TRANSFORM_FILE "/transform.bin"

#define C_DOC_FILE "_Doc"
#define C_DOC_BONE_FILE "/bone.dat"
#define C_DOC_JOINT_FILE "/joint.dat"

#define C_BONE_FILE "/bone/"
#define C_BIN_FILE ".bin"
// #define C_TIME_NAME "/time.bin"
// #define C_VISUALBONE_FILE "/visualbone.bin"

typedef struct
{
	float
		#ifdef C_OUT_NORMAL
			n_x, n_y, n_z,
		#endif
		#ifdef C_OUT_TEXCOORD
			t_x, t_y,
		#endif
		p_x, p_y, p_z;
	uint8_t *joint_p;
	float *weight_p;
	uint8_t max_bone;
} collada_Pack;

typedef struct
{
	char **name_p;
  uint32_t name_size;
	float *visual_p;//M4x4
  uint32_t visual_size;
} collada_Bone;

typedef struct
{
	char is_animated;
	uint32_t max_frame;

	//s0-bone
	uint8_t max_bone;//-2

	collada_Bone *collada_bone_p;

	uint32_t *space_p;

	uint8_t **bone_p;
	uint32_t *bone_size_p;

	char **v_bone_p;
	uint32_t v_bone_size;
	// float *time_p;
	// uint32_t time_size_p;
	float *transform_p;
	uint32_t transform_size;
	char **armature_p;
	uint32_t armature_size;

	char **joint_p;
	float *bind_pose_p;//M4x4
	//e0-bone

	//s0-data
	uint8_t *max_joint_p;
	char **data_p;
	uint32_t max_data;

	float **vertex_p;//V3
	uint32_t *vertex_size_p;
	#ifdef C_OUT_NORMAL
		float **normal_p;//V3
		uint32_t *normal_size_p;
	#endif
	#ifdef C_OUT_TEXCOORD
		float **texcoord_p;//V2
		uint32_t *texcoord_size_p;
	#endif

	int **p_p;//V[]
	uint32_t *p_size_p;

	float **weight_p;//V1-V4
	uint32_t *weight_size_p;

	int **v_p;//V[]
	uint32_t *v_size_p;//V[]
	int **vcount_p;//V[]
	uint32_t *vcount_size_p;//V[]

	uint32_t **index_p;
	uint32_t *index_size_p;

	collada_Pack **collada_pack_p;
	uint32_t *collada_pack_size_p;
	//e0-data
} collada_Source;

#endif
