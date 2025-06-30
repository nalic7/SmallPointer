const int8_t m_i_p[3] =
{
	-1,
	0,
	1
};

// uint8_t m_ray(float a_p[3], float b_p[3], float c_p[3])
// {
// 	float b2a_x = a_p[0] - b_p[0];
// 	float b2a_y = a_p[1] - b_p[1];
// 	float b2a_z = a_p[2] - b_p[2];

// 	float b2a_l = sqrtf(NALI_M_SIZE(b2a_x, b2a_y, b2a_z));
// 	float c_l = sqrtf(NALI_M_SIZE(c_p[0], c_p[1], c_p[2]));

// 	float s = b2a_l - c_l;

// 	float x = a_p[0] - (b_p[0] + c_p[0] * s);
// 	float y = a_p[1] - (b_p[1] + c_p[1] * s);
// 	float z = a_p[2] - (b_p[2] + c_p[2] * s);

// 	return
// 		x >= -1 && x <= 1 &&
// 		y >= -1 && y <= 1 &&
// 		z >= -1 && z <= 1;
// }