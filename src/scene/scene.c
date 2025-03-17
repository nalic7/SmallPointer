int main()
{
	#ifdef NALI_CLIENT
		wlc_init();
		vk_init();
		al_init();
		// nwc_init();
	#else
		// nws_init();
	#endif
	m_pointer_id = 0;
	while (1)
	{

	}
}