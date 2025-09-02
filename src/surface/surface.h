#ifndef _SF_H
	#define _SF_H

	extern uint32_t _sf_width;
	extern uint32_t _sf_height;

	#define _SF_S_EXIT 1
	#define _SF_S_RE 2
	#define _SF_S_RAW 4
	#define _SF_S_RENDER 8
	#define _SF_S_EXIT_RENDER 16
	extern uint8_t _sf_state;
#endif
