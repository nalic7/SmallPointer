#ifndef NALI_DEBUG_H
#define NALI_DEBUG_H

#ifdef NALI_DEBUG
	extern mtx_t *m_mtx_t_print_p;
	void debug_init();
	void debug_free();

	#define nali_info(format, ...) \
		mtx_lock(m_mtx_t_print_p); \
		printf("nali_info: " format "\n", ##__VA_ARGS__); \
		fflush(stdout); \
		mtx_unlock(m_mtx_t_print_p);

	#define nali_log(format, ...) nali_info(format, ##__VA_ARGS__)

	// #define nali_error(format, ...) \
	// 	mtx_lock(m_mtx_t_print_p); \
	// 	printf("nali_error: " format "\n", ##__VA_ARGS__); \
	// 	fflush(stdout); \
	// 	exit(EXIT_FAILURE);
#else
	#define nali_info(format, ...) \
		__VA_ARGS__;

	#define nali_log(format, ...)

	// #define nali_error(format, ...)
#endif

#endif