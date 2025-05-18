#ifndef NALI_DEBUG_H
#define NALI_DEBUG_H

#ifdef NALI_DEBUG
	#ifdef NALI_S_ANDROID
		#define nali_info(format, ...) \
			__android_log_print(ANDROID_LOG_DEBUG, "nali_info", format, ##__VA_ARGS__);
	#else
		#define nali_info(format, ...) \
			printf("nali_info: " format "\n", ##__VA_ARGS__);
	#endif
	// fflush(stdout);
	// exit(EXIT_FAILURE);

	#define nali_info_t(format, ...) nali_info(format, ##__VA_ARGS__)

	#define nali_log(format, ...) nali_info(format, ##__VA_ARGS__)
#else
	#define nali_info(format, ...) \
		__VA_ARGS__;

	#define nali_info_t(format, ...) \
		printf("nali_info: " format "\n", ##__VA_ARGS__);

	#define nali_log(format, ...)
#endif

#endif