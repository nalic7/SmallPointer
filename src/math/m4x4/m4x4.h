#ifndef SMPTMhM4X4
	#define SMPTMhM4X4

	extern const float smptmPm4x4[16];

	void smptm_m4x4Mi(float m[16]);
	void smptm_m4x4Mm(const float a[16], const float b[16], float w[16]);

	//.c fov / project
//	#define SMPTM_M4X4fFOV 90.0F * 0.5F
	#define SMPTM_M4X4fFOV (90.0F * (M_PI / 180.0F) / 2.0F)
	#define SMPTM_M4X4fFOV_P tanf(SMPTM_M4X4fFOV)
	#define SMPTM_M4X4fZ_NEAR 0.1F
	#define SMPTM_M4X4fZ_FAR 100.0F
//	#define SMPTM_M4X4fASPECT (smpt_sfUwidth / smpt_sfUheight)
	#define SMPTM_M4X4fASPECT smpt_sfUwidth / smpt_sfUheight

//	#define SMPTM_M4X4mP(m4x4_p) \
//		(m4x4_p)[0] = 1.0F / (SMPTM_M4X4fFOV_P * SMPTM_M4X4fASPECT); \
//		(m4x4_p)[5] = 1.0F / SMPTM_M4X4fFOV_P; \
//		(m4x4_p)[10] = SMPTM_M4X4fZ_FAR / (SMPTM_M4X4fZ_FAR - SMPTM_M4X4fZ_NEAR); \
//		(m4x4_p)[11] = 1.0F; \
//		(m4x4_p)[14] = -(SMPTM_M4X4fZ_FAR * SMPTM_M4X4fZ_NEAR) / (SMPTM_M4X4fZ_FAR - SMPTM_M4X4fZ_NEAR);
	#define SMPTM_M4X4mP(m4x4_p) \
		(m4x4_p)[0] = -1.0F / (SMPTM_M4X4fFOV_P * SMPTM_M4X4fASPECT); \
		(m4x4_p)[5] = 1.0F / SMPTM_M4X4fFOV_P; \
		(m4x4_p)[10] = -(SMPTM_M4X4fZ_FAR + SMPTM_M4X4fZ_NEAR) / (SMPTM_M4X4fZ_FAR - SMPTM_M4X4fZ_NEAR); \
		(m4x4_p)[11] = -1.0F; \
		(m4x4_p)[14] = -(2.0F * SMPTM_M4X4fZ_FAR * SMPTM_M4X4fZ_NEAR) / (SMPTM_M4X4fZ_FAR - SMPTM_M4X4fZ_NEAR);
#endif
