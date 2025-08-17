#ifndef NALI_TEST_H
#define NALI_TEST_H
	#ifdef C_NALI_TEST
		#define NALI_T_P(d_bl, l_bl) \
			if ((d_bl) >= (l_bl)) \
			{ \
				exit(EXIT_FAILURE); \
			}
	#else
		#define NALI_T_P(d_bl, l_bl)
	#endif
#endif
