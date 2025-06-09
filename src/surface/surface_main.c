int main()
{
	// fp_read(NALI_F_HOME NALI_F_HOME_IMAGE "/0.png", &(long){});
	#ifdef NALI_D_FILE
		d_set();
	#endif

	#ifdef C_NALI_GEN
		g_write();
	#endif
	#if C_NALI_SERVER
		nls_set();
	#endif
	#ifdef C_NALI_CLIENT
		nlc_set();
		//need test network
		// lb_set();
		// lc_set();
		// wlc_set();
		// vk_set();
		// al_set();
		// lc_vk();
		// lb_free0();
		// s_pointer_id = 0;
	#endif

	lb_loop();
}