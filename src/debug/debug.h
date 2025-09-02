#ifndef SMPT_DB_H
	#define SMPT_DB_H

	#ifdef SMPT_CM_DEBUG
		void smpt_db_set();
		void smpt_db_write(const char *format_p, ...);
		void smpt_db_free();

		#define SMPT_DB_R2L(format_p, ...) smpt_db_write(format_p, ##__VA_ARGS__);

		#define SMPT_DB_W2L(format_p, ...) smpt_db_write(format_p, ##__VA_ARGS__);

		#define SMPT_DB_N2L(format_p, ...) smpt_db_write(format_p, ##__VA_ARGS__);
	#else
		#define SMPT_DB_R2L(format_p, ...) __VA_ARGS__;

		#define SMPT_DB_W2L(format_p, ...) smpt_db_write(format_p, ##__VA_ARGS__);

		#define SMPT_DB_N2L(format_p, ...)
	#endif
#endif
