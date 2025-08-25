#ifndef _DB_H
	#define _DB_H

	#ifdef _CM_DEBUG
		extern mtx_t *_db_mtx_t_p;
		void _db_set();
		void _db_write(const char *format_p, ...);
		void _db_free();

		#define _DB_R2L(format_p, ...) _db_write(format_p, ##__VA_ARGS__);

		#define _DB_W2L(format_p, ...) _db_write(format_p, ##__VA_ARGS__);

		#define _DB_N2L(format_p, ...) _db_write(format_p, ##__VA_ARGS__);
	#else
		#define _DB_R2L(format_p, ...) __VA_ARGS__;

		#define _DB_W2L(format_p, ...) _db_write(format_p, ##__VA_ARGS__);

		#define _DB_N2L(format_p, ...)
	#endif
#endif
