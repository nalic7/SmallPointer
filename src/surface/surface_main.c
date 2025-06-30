int main()
{
	// fp_read(NALI_F_HOME NALI_F_HOME_IMAGE "/0.png", &(long){});
	#ifdef NALI_D_FILE
		d_set();
	#endif

	// //s0-test
	// for (uint8_t l_1 = 0; l_1 < 3; ++l_1)
	// {
	// 	for (uint8_t l_2 = 0; l_2 < 3; ++l_2)
	// 	{
	// 		for (uint8_t l_3 = 0; l_3 < 3; ++l_3)
	// 		{
	// 			NALI_D_LOG("%d %d %d", l_1, l_2, l_3);
	// 			NALI_D_LOG("%d %d %d", m_i_p[l_1], m_i_p[l_2], m_i_p[l_3]);
	// 			NALI_D_LOG("%f %f", NALI_M_XZ2YAW(m_i_p[l_1], m_i_p[l_3]), NALI_M_XYZ2PITCH(m_i_p[l_1], m_i_p[l_2], m_i_p[l_3]));
	// 		}
	// 	}
	// }
	// d_free();
	// //e0-test

	#ifdef C_NALI_GEN
		g_write();
	#endif
	lb_set();
	#if C_NALI_SERVER
		ls_set();
	#endif
	#ifdef C_NALI_CLIENT
		lc_set();

		swlc_set();
		vk_set();
		al_set();
		lc_vk();
		lb_free0();

		swlcsp_pointer = 0;
	#endif

	lb_loop();
}