#ifndef SMPThDB
	#define SMPThDB

	#ifdef SMPT_CM_DEBUG
		void smpt_dbMset();
		void smpt_dbMwrite(const char *format_p, ...);
		void smpt_dbMfree();

		#define SMPT_DBmR2L(format_p, ...) smpt_dbMwrite(format_p, ##__VA_ARGS__);

		#define SMPT_DBmW2L(format_p, ...) smpt_dbMwrite(format_p, ##__VA_ARGS__);

		#define SMPT_DBmN2L(format_p, ...) smpt_dbMwrite(format_p, ##__VA_ARGS__);
	#else
		#define SMPT_DBmR2L(format_p, ...) __VA_ARGS__;

		#define SMPT_DBmW2L(format_p, ...) smpt_dbMwrite(format_p, ##__VA_ARGS__);

		#define SMPT_DBmN2L(format_p, ...)
	#endif
#endif
