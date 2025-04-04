#ifndef NALI_DEBUG_H
#define NALI_DEBUG_H

#ifdef NALI_DEBUG
	// extern mtx_t *m_mtx_t_print_p;
	// void debug_init();
	// void debug_free();

	// mtx_lock(m_mtx_t_print_p);
	// mtx_unlock(m_mtx_t_print_p);
	#ifdef NALI_OS_ANDROID
		#define nali_info(format, ...) \
			__android_log_print(ANDROID_LOG_DEBUG, "nali_info", format, ##__VA_ARGS__);
	#else
		#define nali_info(format, ...) \
			printf("nali_info: " format "\n", ##__VA_ARGS__);
	#endif
	// fflush(stdout);

	#define nali_info_t(format, ...) nali_info(format, ##__VA_ARGS__)

	#define nali_log(format, ...) nali_info(format, ##__VA_ARGS__)

	// #define nali_error(format, ...) \
	// 	mtx_lock(m_mtx_t_print_p); \
	// 	printf("nali_error: " format "\n", ##__VA_ARGS__); \
	// 	fflush(stdout); \
	// 	exit(EXIT_FAILURE);
#else
	#define nali_info(format, ...) \
		__VA_ARGS__;

	#define nali_info_t(format, ...) \
		printf("nali_info: " format "\n", ##__VA_ARGS__);

	#define nali_log(format, ...)

	// #define nali_error(format, ...)
#endif

#endif