int main()
{
	#ifdef NALI_CLIENT
		lc_init();
		wlc_init();
		vk_init();
		al_init();
		// nwc_init();
		lc_initVK();
		m_pointer_id = 0;
	#else
		nws_init();
	#endif
	while (1)
	{

	}
}