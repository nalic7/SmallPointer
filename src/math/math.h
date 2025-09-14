#ifndef SMPThM
	#define SMPThM

//	#define SMPTMmMIN(a, b) ((a) < (b) ? (a) : (b))
//	#define SMPTMmMAX(a, b) ((a) > (b) ? (a) : (b))
//	#define SMPTMmLENGTH(number) ((number) == 0 ? 1 : log10(number) + 1)

	#define SMPTMmNORM_NF(v, m) fmodf(fmodf((v) + m / 2, m) + m, m) - m / 2
//	#define SMPTMmNORM_NI(v, m) ((((v) + m / 2) % m + m) % m - m / 2)
//	#define SMPTMmNORM_PF(v, m) fmodf(fmodf(v, m) + m, m)
//	#define SMPTMmNORM_PI(v, m) (((v) % m + m) % m)

//	#define SMPTMmFIX_F(v, min, max) fmodf(v - min, max - min) + min
//	#define SMPTMmFIX_I(v, min, max) ((v - min) % (max - min)) + min
	#define SMPTMmWRAP_I(v, min, max) min + (((v - min) % (max - min)) + (max - min)) % (max - min)
	#define SMPTMmWRAP_F(v, min, max) min + fmodf((fmodf((v - min), (max - min)) + (max - min)), (max - min))

	#define SMPTMmLERP(a, b, t) (a) = (a) + ((b) - (a)) * (t)

	#define SMPTMmD2R(v) ((v) * M_PI / 180.0)
	#define SMPTMmR2D(v) ((v) * 180.0 / M_PI)

	//! clean
//	//hash
//	#define SMPTMmH3(x, y, z, m) x * m * m + y * m + z
//	#define SMPTMmH3X(hi, m) hi / (m * m)
//	#define SMPTMmH3Y(hi, m) (hi / m) % m
//	#define SMPTMmH3Z(hi, m) hi % m

//	//908 ~ 3422
//	//-x
//	#define SMPTMmXZ2YAW(x, z) atan2f(x, z)
//	//-y
//	#define SMPTMmXYZ2PITCH(x, y, z) atan2f(y, sqrtf(x * x + z * z))
//	// #define M_EPSILON = 45.0F
//	// #define M_IN_C(a, b) abs(a - b) <= M_EPSILON

//	//4679 ~ 8940
//	#define SMPTMmHV2X(yaw, pitch) cosf(pitch) * cosf(yaw)
//	#define SMPTMmV2Y(pitch) sinf(pitch)
//	#define SMPTMmHV2Z(yaw, pitch) cosf(pitch) * sinf(yaw)
#endif
