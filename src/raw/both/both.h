#ifndef RB_H
	#define RB_H

	//.c max connect
	#define NALI_LB_UM 1
	//.c max connect type
	#define NALI_LB_UT uint8_t
	//.i void user
	#define NALI_LB_UN 255

	//.i package
	#define NALI_LB_PT uint8_t
	#define NALI_LB_NET_BL 255

	//.i animation
	#define NALI_LB_AKIT uint8_t
	#define NALI_LB_AKIN 0xFFu
	//.i animation key
	#define NALI_LB_AKT uint8_t
	//.i animation keyframe/float /255
	#define NALI_LB_AFT uint16_t

	//.i model
	#define NALI_LB_MT uint8_t
	//.i model index
	#define NALI_LB_MIT uint16_t
	#define NALI_LB_M8BL 256/8
	#define NALI_LB_MIM 0xFFFFu-1
	#define NALI_LB_MIN 0xFFFFu

	//.i model attribute
	#define NALI_LB_MAT uint8_t
	//.i model max
	#define NALI_LB_MM 0xFFu-1
	#define NALI_LB_MN 0xFFu

	//.i chunk
	#define NALI_LB_CT uint8_t
	#define NALI_LB_C_ST int8_t
	#define NALI_LB_CIBL 16
	//.i xyz
	#define NALI_LB_CMFL 1024.0F
	//.i chunk hash/3 key
	#define NALI_LB_CHT uint16_t

	//s0-data
	//stage 1-2 data shader
	//joint first ...
	// 1 2 star0 land0

	// extern NALI_LB_MT lb_ms_p[NALI_LB_N_MAX];
	#define NALI_LB_MA_BL 3
	// extern const uint8_t lb_ma_p[NALI_LB_MA_BL];
	extern const uint8_t *lb_map_p[NALI_LB_MA_BL];
	extern const uint8_t lb_mrb_p[NALI_LB_MA_BL];
	extern const uint8_t lb_mab_p[NALI_LB_MA_BL];
	#define NALI_LB_MDP_BL 4
	extern const float lb_mdp_p[NALI_LB_MDP_BL][3];
	//[NALI_LB_AT]
	#define NALI_LB_AK_BL 1
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

		NALI_LB_MIT mi;
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


	typedef struct
	{
		#ifdef _CM_CLIENT
			uint16_t
				**bs_p,
				**be_p;
			//server
		#endif
		#ifdef _CM_SERVER
		#endif
		uint8_t *d_p;
		uint32_t *d_bl_p;
	} LB_C;
	extern LB_C *lb_c;

	extern mtx_t *lb_mtx_t_p;

	extern void *lb_cache_p;

	void lb_set();
	void lb_u_update(float w_p[16], float ry, float q_v4_array[4], float q0_m4x4_array[16], float q1_m4x4_array[16]);
	//void lb_loop();
	void lb_free0();
	void lb_free1();
#endif
