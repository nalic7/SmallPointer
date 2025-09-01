#ifndef _RB_H
	#define _RB_H

	//.i M2J

	//.c max connect
	#define _RB_UM 1
	//.c max connect type
	#define _RB_UT uint8_t
	//.i void user
	#define _RB_UN 255

	//.i package
	#define _RB_PT uint8_t
	#define _RB_NET_BL 255

	//.i animation
	#define _RB_AKIT uint8_t
	#define _RB_AKIN 0xFFu
	//.i animation key
	#define _RB_AKT uint8_t
	//.i animation keyframe/float /255
	#define _RB_AFT uint16_t

	//.i model
	#define _RB_MT uint8_t
	//.i model index
	#define _RB_MIT uint16_t
	#define _RB_M8BL 256/8
	#define _RB_MIM 0xFFFFu-1
	#define _RB_MIN 0xFFFFu

	//.i model attribute
	#define _RB_MAT uint8_t
	//.i model max
	#define _RB_MM 0xFFu-1
	#define _RB_MN 0xFFu

	//.i chunk
	#define _RB_CT uint8_t
	#define _RB_C_ST int8_t
	#define _RB_CIBL 16
	//.i xyz
	#define _RB_CMFL 1024.0F
	//.i chunk hash/3 key
	#define _RB_CHT uint16_t

	//s0-data
	//stage 1-2 data shader
	//joint first ...
	// 1 2 star0 land0

	// extern _RB_MT lb_ms_p[_RB_N_MAX];
	#define _RB_MA_BL 3
	// extern const uint8_t lb_ma_p[_RB_MA_BL];
	extern const uint8_t *lb_map_p[_RB_MA_BL];
	extern const uint8_t lb_mrb_p[_RB_MA_BL];
	extern const uint8_t lb_mab_p[_RB_MA_BL];
	#define _RB_MDP_BL 4
	extern const float lb_mdp_p[_RB_MDP_BL][3];
	//[_RB_AT]
	#define _RB_AK_BL 1
	extern const _RB_AKT lb_ak_p[_RB_AK_BL][3];
	// extern uint8_t lb_ms_abl_p[_RB_N_MAX];
	// extern VkDeviceSize lb_ms_vkdevicesize_p[_RB_N_MAX];
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
		_RB_MT m;
		_RB_MAT ma;
		_RB_AKIT aki;

		_RB_AFT af;
		// _RB_AKT ak;

		_RB_MIT mi;
		float rt_p[3 + 2];
	} LB_M;
	//s0-net

	//s1-key
	#define _RB_K_W 1
	#define _RB_K_A 2
	#define _RB_K_S 4
	#define _RB_K_D 8
	#define _RB_K_JUMP 16
	#define _RB_K_DIG 32
	#define _RB_K_REROTATE 64
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
