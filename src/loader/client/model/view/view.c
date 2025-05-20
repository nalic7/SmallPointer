float m_mvp_float_array[] =
{
	// // //m4x4 mvp
	// // 1, 0, 0, 0,
	// // 0, 1, 0, 0,
	// // 0, 0, 1, 0,
	// // 0, 0, 0, 1,
	// // //m4x4 m
	// // 1, 0, 0, 0,
	// // 0, 1, 0, 0,
	// // 0, 0, 1, 0,
	// // 0, 0, 0, 1,
	// //m4x4 v
	// 1, 0, 0, 0,
	// 0, 1, 0, 0,
	// 0, 0, 1, 0,
	// 0, 1, -2, 1,
	// //m4x4 p
	// 1, 0, 0, 0,
	// 0, 1, 0, 0,
	// 0, 0, 1, 0,
	// 0, 0, 0, 1,
	// //m4x4 vp
	// 1, 0, 0, 0,
	// 0, 1, 0, 0,
	// 0, 0, 1, 0,
	// 0, 0, 0, 1

	//m4x4 m
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1,
	//m4x4 v
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 1.5, -2, 1,
	// //m4x4 p
	// 1, 0, 0, 0,
	// 0, 1, 0, 0,
	// 0, 0, 1, 0,
	// 0, 0, 0, 1,
};

void lcmv_init()
{
	float q[4];
	m_v4_q(0, 0, s_rz, q);
	m_v4_q2m(q, m_mvp_float_array + 16);

	// float qv4_float_p[4], m[16], m1[16];
	// v4_q(0, 0, MATH_D2R(180.0F), qv4_float_p);
	// v4_q2m(qv4_float_p, m);
	// memcpy(m1, m_mvp_float_array + 16, sizeof(float) * 16);
	// v4_m4(m, m1, m_mvp_float_array + 16);
	// // M_M4X4_P(tanf(90.0F * (M_PI / 180.0F) / 2.0F), 16.0F / 9.0F, 0.1F, 100.0F, m_mvp_float_array + 16 * 2)

	// // memcpy(vp_float_array + 16 * 2, vp_float_array + 16, 16 * sizeof(float));
	// // m4x4_m(vp_float_array, vp_float_array + 16 * 2);
}

void lcmv_vk()
{
	memcpy(m_vkbuffer_p, m_mvp_float_array, NALI_LC_MVP_BL);
}