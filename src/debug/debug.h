#ifndef NALI_DEBUG_H
#define NALI_DEBUG_H
	#ifdef _CM_DEBUG
		extern mtx_t *d_mtx_t_p;
		void d_set();
		void d_write(const char *format_p, ...);
		void d_free();

		#define NALI_D_INFO(format_p, ...) d_write(format_p, ##__VA_ARGS__);

		#define NALI_D_INFO_A(format_p, ...) d_write(format_p, ##__VA_ARGS__);

		#define NALI_D_LOG(format_p, ...) d_write(format_p, ##__VA_ARGS__);
	#else
		#define NALI_D_INFO(format_p, ...) __VA_ARGS__;

		#define NALI_D_INFO_A(format_p, ...) d_write(format_p, ##__VA_ARGS__);

		#define NALI_D_LOG(format_p, ...)
	#endif
#endif
