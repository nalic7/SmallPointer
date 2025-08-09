#ifndef NALI_DEBUG_H
#define NALI_DEBUG_H

#define NALI_D_FILE
#ifdef NALI_D_FILE
	extern mtx_t *d_mtx_t_p;
	void d_set();
	void d_write(const char *format_p, ...);
	void d_free();
#endif

#ifdef C_NALI_DEBUG
//	#ifdef C_NALI_S_ANDROID
//		#define NALI_D_INFO(format_p, ...) \
//			__android_log_print(ANDROID_LOG_DEBUG, "NALI_D_INFO", format_p, ##__VA_ARGS__);
//	#else
	#ifdef NALI_D_FILE
		#define NALI_D_INFO(format_p, ...) \
			d_write(format_p, ##__VA_ARGS__);
	#else
		#define NALI_D_INFO(format_p, ...) \
			printf("NALI_D_INFO: " format_p "\n", ##__VA_ARGS__);
	#endif
//	#endif
	// fflush(stdout);
	// exit(EXIT_FAILURE);

	#define NALI_D_INFO_A(format_p, ...) NALI_D_INFO(format_p, ##__VA_ARGS__)

	#define NALI_D_LOG(format_p, ...) NALI_D_INFO(format_p, ##__VA_ARGS__)
#else
	#define NALI_D_INFO(format_p, ...) \
		__VA_ARGS__;

	#ifdef NALI_D_FILE
		#define NALI_D_INFO_A(format_p, ...) \
			d_write(format_p, ##__VA_ARGS__);
	#else
		#define NALI_D_INFO_A(format_p, ...) \
			printf("NALI_D_INFO: " format_p "\n", ##__VA_ARGS__);
	#endif

	#define NALI_D_LOG(format_p, ...)
#endif

#endif
