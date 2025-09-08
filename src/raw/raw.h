#ifndef SMPTRh
	#define SMPTRh

	#define SMPTRtM uint16_t

	#ifdef SMPT_CM_RAW
		#if defined(SMPT_CM_CLIENT) && defined(SMPT_CM_SERVER)
		#else
			#ifdef SMPT_CM_CLIENT
			#endif
			#ifdef SMPT_CM_SERVER
			#endif
		#endif
	#elif defined(SMPT_CM_UDP)
		#if defined(SMPT_CM_CLIENT) && defined(SMPT_CM_SERVER)
		#else
			#ifdef SMPT_CM_CLIENT
			#endif
			#ifdef SMPT_CM_SERVER
			#endif
		#endif
	#endif

	//.i model
	#define SMPTRtM uint8_t
	#define SMPTRvM 0xFFFFu
	#define SMPTRtMA uint8_t
	#define SMPTRtMB uint8_t
	#define SMPTRtMI uint16_t
	#define SMPTRmMI (0xFFFFu - 1)
	#define SMPTRtMK uint8_t
	#define SMPTRtMT uint16_t
	#define SMPTRtMD float
	#define SMPTRnMA \
		X(FE0000_000, "FE0000.000", 1) \
		X(FE0000_001, "FE0000.001", 1) \
		X(FE0001_000, "FE0001.000", 1) \
		X(FE0001_001, "FE0001.001", 1) \
		X(FE00_000, "FE00.000", 1) \
		X(FE00_001, "FE00.001", 1) \
		X(FE01_000, "FE01.000", 1) \
		X(FE01_001, "FE01.001", 1) \
		X(FE01_002, "FE01.002", 1) \
		X(FE01_003, "FE01.003", 1) \
		X(FE0_000, "FE0.000", 1) \
		X(FE0_001, "FE0.001", 1) \
		X(FE1, "FE1", 1) \
		X(M1_000, "M1.000", 1) \
		X(M1_001, "M1.001", 1) \
		X(M0, "M0", 1) \
		X(IShovel, "IShovel", 1)

	#define SMPTRnM \
		X(POMI_PAPI, "SuperCutePomi2.glb", 1) \
		X(POMI_TEA, "SuperCutePomi1.glb", 1) \
		X(POMI_CAFE, "SuperCutePomi0.glb", 1)

	enum SMPTReMA
	{
		#define X(v, n, b) SMPTReMA_##v,
			SMPTRnMA
		#undef X
		SMPTReMAc
	};

	enum SMPTReM
	{
		#define X(v, n, b) SMPTReM_##v,
			SMPTRnM
		#undef X
		SMPTReMc
	};

	extern const SMPTRtMB smptrPmb[SMPTReMAc + SMPTReMc];

	struct SMPTRsM
	{
		//.i client always get same size as server
		//.i server can return norender to client
		//.i i
		SMPTRtM m;
		//.i a
		SMPTRtMK k;
		SMPTRtMT t;
		//.i r
		uint8_t l;
		SMPTRtMA *Pa;
	};
	extern struct SMPTRsM *smptrPm;
	extern SMPTRtM smptrLm;

	//.c server read/write
	#define SMPTRBuRW 20

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

	struct LB_C
	{
		#ifdef SMPT_CM_CLIENT
			uint16_t
				**bs_p,
				**be_p;
		#endif
		#ifdef SMPT_CM_SERVER
		#endif
		uint8_t *d_p;
		uint32_t *d_bl_p;
	};
	extern struct LB_C *lb_c;

	#if SMPT_CM_CLIENT && SMPT_CM_SERVER
		extern mtx_t *lb_mtx_t_p;
	#endif

	void lb_set();
	void lb_u_update(float w_p[16], float ry, float q_v4_array[4], float q0_m4x4_array[16], float q1_m4x4_array[16]);
	void lb_free0();
	void lb_free1();
#endif
