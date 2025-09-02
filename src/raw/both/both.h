#ifndef SMPTRB_H
	#define SMPTRB_H

	//.i M2J

	//.c max connect
	#define SMPTRB_UM 1
	//.c max connect type
	#define SMPTRB_UT uint8_t
	//.i void user
	#define SMPTRB_UN 255

	//.i package
	#define SMPTRB_PT uint8_t
	#define SMPTRB_NET_BL 255

	//.i animation
	#define SMPTRB_AKIT uint8_t
	#define SMPTRB_AKIN 0xFFu
	//.i animation key
	#define SMPTRB_AKT uint8_t
	//.i animation keyframe/float /255
	#define SMPTRB_AFT uint16_t

	//.i model
	#define SMPTRB_MT uint8_t
	//.i model index
	#define SMPTRB_MIT uint16_t
	#define SMPTRB_M8BL 256/8
	#define SMPTRB_MIM 0xFFFFu-1
	#define SMPTRB_MIN 0xFFFFu

	//.i model attribute
	#define SMPTRB_MAT uint8_t
	//.i model max
	#define SMPTRB_MM 0xFFu-1
	#define SMPTRB_MN 0xFFu

	//.i chunk
	#define SMPTRB_CT uint8_t
	#define SMPTRB_C_ST int8_t
	#define SMPTRB_CIBL 16
	//.i xyz
	#define SMPTRB_CMFL 1024.0F
	//.i chunk hash/3 key
	#define SMPTRB_CHT uint16_t

	//s0-data
	//stage 1-2 data shader
	//joint first ...
	// 1 2 star0 land0

	// extern SMPTRB_MT lb_ms_p[SMPTRB_N_MAX];
	#define SMPTRB_MA_BL 3
	// extern const uint8_t lb_ma_p[SMPTRB_MA_BL];
	extern const uint8_t *lb_map_p[SMPTRB_MA_BL];
	extern const uint8_t lb_mrb_p[SMPTRB_MA_BL];
	extern const uint8_t lb_mab_p[SMPTRB_MA_BL];
	#define SMPTRB_MDP_BL 4
	extern const float lb_mdp_p[SMPTRB_MDP_BL][3];
	//[SMPTRB_AT]
	#define SMPTRB_AK_BL 1
	extern const SMPTRB_AKT lb_ak_p[SMPTRB_AK_BL][3];
	// extern uint8_t lb_ms_abl_p[SMPTRB_N_MAX];
	// extern VkDeviceSize lb_ms_vkdevicesize_p[SMPTRB_N_MAX];
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
		SMPTRB_MT m;
		SMPTRB_MAT ma;
		SMPTRB_AKIT aki;

		SMPTRB_AFT af;
		// SMPTRB_AKT ak;

		SMPTRB_MIT mi;
		float rt_p[3 + 2];
	} LB_M;
	//s0-net

	//s1-key
	#define SMPTRB_K_W 1
	#define SMPTRB_K_A 2
	#define SMPTRB_K_S 4
	#define SMPTRB_K_D 8
	#define SMPTRB_K_JUMP 16
	#define SMPTRB_K_DIG 32
	#define SMPTRB_K_REROTATE 64
	//e1-key

	//e1-server
	//e0-net


	typedef struct
	{
		#ifdef SMPT_CM_CLIENT
			uint16_t
				**bs_p,
				**be_p;
			//server
		#endif
		#ifdef SMPT_CM_SERVER
		#endif
		uint8_t *d_p;
		uint32_t *d_bl_p;
	} LB_C;
	extern LB_C *lb_c;

	#if SMPT_CM_CLIENT && SMPT_CM_SERVER
		extern mtx_t *lb_mtx_t_p;
	#endif

	extern void *lb_cache_p;

	void lb_set();
	void lb_u_update(float w_p[16], float ry, float q_v4_array[4], float q0_m4x4_array[16], float q1_m4x4_array[16]);
	//void lb_loop();
	void lb_free0();
	void lb_free1();
#endif
