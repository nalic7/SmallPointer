#ifndef SMPThM
	#define SMPThM

	#define NALI_M_MIN(a, b) ((a) < (b) ? (a) : (b))
	#define NALI_M_MAX(a, b) ((a) > (b) ? (a) : (b))
	#define NALI_M_LENGTH(number) ((number) == 0 ? 1 : log10(number) + 1)

	#define NALI_M_NORMALN_F(v, m) fmodf(fmodf((v) + m / 2, m) + m, m) - m / 2
	#define NALI_M_NORMALN_I(v, m) ((((v) + m / 2) % m + m) % m - m / 2)

	#define NALI_M_NORMALP_F(v, m) fmodf(fmodf(v, m) + m, m)
	#define NALI_M_NORMALP_I(v, m) (((v) % m + m) % m)

	#define NALI_M_WRAP_F(v, min, max) fmodf(v - min, max - min) + min
	#define NALI_M_WRAP_I(v, min, max) ((v - min) % (max - min)) + min

	#define NALI_M_SIZE(x, y, z) (x) * (x) + (y) * (y) + (z) * (z)

	//image
	#define NALI_M_MIPMAP(width, height) (uint32_t)(log2(((width) > (height)) ? (width) : (height))) + 1

	//rotate
	#define NALI_M_D2R(v) ((v) * M_PI / 180.0)
	#define NALI_M_R2D(v) ((v) * 180.0 / M_PI)

	//animation
	//! clean this
	#define NALI_M_LERP(a, b, t) (a) = (a) + ((b) - (a)) * (t)

	//hash
	#define NALI_M_H3(x, y, z, m) x * m * m + y * m + z
	#define NALI_M_H3X(hi, m) hi / (m * m)
	#define NALI_M_H3Y(hi, m) (hi / m) % m
	#define NALI_M_H3Z(hi, m) hi % m

	//view

	//908 ~ 3422
	//-x
	#define NALI_M_XZ2YAW(x, z) atan2f(x, z)
	//-y
	#define NALI_M_XYZ2PITCH(x, y, z) atan2f(y, sqrtf(x * x + z * z))
	// #define M_EPSILON = 45.0F
	// #define M_IN_C(a, b) abs(a - b) <= M_EPSILON

	//4679 ~ 8940
	#define NALI_M_HV2X(yaw, pitch) cosf(pitch) * cosf(yaw)
	#define NALI_M_V2Y(pitch) sinf(pitch)
	#define NALI_M_HV2Z(yaw, pitch) cosf(pitch) * sinf(yaw)

	extern const int8_t m_i_p[3];
	// uint8_t m_ray(float a_p[3], float b_p[3], float c_p[3]);

	// a * b
	// float dot(float a_p[3], float b_p[3]) 
	// {
	// 	return a_p[0] * b_p[0] + a_p[1] * b_p[1] + a_p[2] * b_p[2];
	// }
#endif
