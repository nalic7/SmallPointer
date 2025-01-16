#ifndef NALI_COLLADA_PARSER_H
#define NALI_COLLADA_PARSER_H

#define C_IN "./C_I"
#define C_OUT "./C_O"

#define C_FIX_ANIMATED 1
// #define C_CURVE 1
#define C_OUT_NORMAL 0
#define C_ARMATURE_NAME "<animation id=\""
#define C_VERTEX_FILE "/vertex.bin"
#ifdef C_OUT_NORMAL
	#define C_NORMAL_FILE "/normal.bin"
#endif
#define C_TEXCOORD_FILE "/texcoord.bin"
#define C_JOINT_FILE "/joint.bin"
#define C_WEIGHT_FILE "/weight.bin"
#define C_BINDPOSE_FILE "/bindpose.bin"
#define C_INDEX_FILE "/index.bin"
#define C_TRANSFORM_FILE "/transform.bin"
// #define C_TIME_NAME "/time.bin"
// #define C_VISUALBONE_FILE "/visualbone.bin"

typedef struct
{
	float
		p_x, p_y, p_z,
		#ifdef C_OUT_NORMAL
			n_x, n_y, n_z,
		#endif
		t_x, t_y;
	uint8_t* joint_ptr;
	float* weight_ptr;
	uint8_t max_bone;
} collada_Pack;

typedef struct
{
	char** name_ptr;
  uint32_t name_size;
	float* visual_ptr;//M4x4
  uint32_t visual_size;
} collada_Bone;

typedef struct
{
	char is_animated;
	uint32_t max_frame;

	//s0-bone
	uint8_t max_bone;//-2

	collada_Bone* collada_bone_ptr;

	uint32_t* space_ptr;

	uint8_t** bone_ptr;
	uint32_t* bone_size_ptr;

	char** v_bone_ptr;
	uint32_t v_bone_size;
	// float* time_ptr;
	// uint32_t time_size_ptr;
	float* transform_ptr;
	uint32_t transform_size;
	char** armature_ptr;
	uint32_t armature_size;

	char** joint_ptr;
	float* bind_pose_ptr;//M4x4
	//e0-bone

	//s0-data
	uint8_t* max_joint_ptr;
	char** data_ptr;
	uint32_t max_data;

	float** vertex_ptr;//V3
	uint32_t* vertex_size_ptr;
	#ifdef C_OUT_NORMAL
		float** normal_ptr;//V3
		uint32_t* normal_size_ptr;
	#endif
	float** texcoord_ptr;//V2
	uint32_t* texcoord_size_ptr;

	int** p_ptr;//V[]
	uint32_t* p_size_ptr;

	float** weight_ptr;//V1-V4
	uint32_t* weight_size_ptr;

	int** v_ptr;//V[]
	uint32_t* v_size_ptr;//V[]
	int** vcount_ptr;//V[]
	uint32_t* vcount_size_ptr;//V[]

	uint32_t** index_ptr;
	uint32_t* index_size_ptr;

	collada_Pack** collada_pack_ptr;
	uint32_t* collada_pack_size_ptr;
	//e0-data
} collada_Source;

#endif
