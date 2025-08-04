#ifndef NALI_LOADER_BOTH_H
#define NALI_LOADER_BOTH_H

//max connect
#define NALI_LB_UM 1
//max connect type
#define NALI_LB_UT uint8_t
//void user
#define NALI_LB_UN 255

//package
#define NALI_LB_PT uint8_t
#define NALI_LB_NET_BL 255

//animation
#define NALI_LB_AKIT uint8_t
// #define NALI_LB_AT uint8_t
//animation key
#define NALI_LB_AKT uint8_t
//animation keyframe/float /255
#define NALI_LB_AFT uint16_t
#define NALI_LB_AN 0xFFu

//model
#define NALI_LB_MT uint8_t
//model index
#define NALI_LB_MIT uint16_t
#define NALI_LB_M8BL 256/8
#define NALI_LB_MIM 0xFFFFu-1
#define NALI_LB_MIN 0xFFFFu

//model attribute
#define NALI_LB_MAT uint8_t
//model max
#define NALI_LB_MM 0xFFu-1
#define NALI_LB_MN 0xFFu

//chunk
#define NALI_LB_CT uint8_t
#define NALI_LB_C_ST int8_t
#define NALI_LB_CIBL 16
//xyz
#define NALI_LB_CMFL 1024.0F
//chunk hash
//3 key
#define NALI_LB_CHT uint16_t

//s0-data
//stage 1-2 data shader
//joint first ...
// 1 2 star0 land0

// extern NALI_LB_MT lb_ms_p[NALI_LB_N_MAX];
#define NALI_LB_MA_BL 1
extern const uint8_t lb_ma_p[NALI_LB_MA_BL];
extern const uint8_t *lb_map_p[NALI_LB_MA_BL];
extern const uint8_t lb_mrb_p[NALI_LB_MA_BL];
extern const uint8_t lb_mab_p[NALI_LB_MA_BL];
#define NALI_LB_MDP_BL 4
extern const float lb_mdp_p[NALI_LB_MDP_BL][3];
//[NALI_LB_AT]
#define NALI_LB_AK_BL 3
extern const NALI_LB_AKT lb_ak_p[NALI_LB_AK_BL][3];
// extern uint8_t lb_ms_abl_p[NALI_LB_N_MAX];
// extern VkDeviceSize lb_ms_vkdevicesize_p[NALI_LB_N_MAX];
//e0-data

//s0-net
typedef struct
{
	//t3
	//r2
	float rt_p[3 + 2];
} LB_U;

typedef struct
{
	//m -> j
	NALI_LB_MT m;
	NALI_LB_MAT ma;
	NALI_LB_AKIT aki;

	NALI_LB_AFT af;
	// NALI_LB_AKT ak;

	NALI_LB_MIT update;
	float rt_p[3 + 2];
} LB_M;
//s0-net

//s1-key
#define NALI_LB_K_W 1
#define NALI_LB_K_A 2
#define NALI_LB_K_S 4
#define NALI_LB_K_D 8
#define NALI_LB_K_JUMP 16
#define NALI_LB_K_DIG 32
#define NALI_LB_K_REROTATE 64
//e1-key

//e1-server
//e0-net


#define NALI_LB_CACHE_P_BL sizeof(void *) * 4
//client
#define NALI_LB_CACHE_P_BS_P (((uint8_t ***)lb_cache_p)[0])
#define NALI_LB_CACHE_P_BE_P (((uint8_t ***)lb_cache_p)[1])

//both
#define NALI_LB_CACHE_P_D_P (((uint8_t **)lb_cache_p)[2])
#define NALI_LB_CACHE_P_D_BL_P (((uint32_t **)lb_cache_p)[3])

extern mtx_t *lb_mtx_t_p;

extern void *lb_cache_p;

void lb_set();
void lb_u_update(float w_p[16], float ry, float q_v4_array[4], float q0_m4x4_array[16], float q1_m4x4_array[16]);
void lb_loop();
void lb_free0();
void lb_free1();

#endif