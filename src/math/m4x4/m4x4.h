#ifndef SMPTMhM4X4
	#define SMPTMhM4X4

	extern const float smptmPm4x4[16];

	void smptm_m4x4Mi(float m[16]);
	void smptm_m4x4Mm(const float a[16], const float b[16], float w[16]);

	#define SMPTM_M4X4mP(fov, aspect, z_near, z_far, m4x4_p) \
		(m4x4_p)[0] = -1.0F / (fov * aspect); \
		(m4x4_p)[5] = 1.0F / fov; \
		(m4x4_p)[10] = -(z_far + z_near) / (z_far - z_near); \
		(m4x4_p)[11] = -1.0F; \
		(m4x4_p)[14] = -(2.0F * z_far * z_near) / (z_far - z_near);
#endif
