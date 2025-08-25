#ifndef _VK_CMD_H
	#define _VK_CMD_H

	void _vk_cmd_set();
	#ifdef _CM_ST_ANDROID
		int _vk_cmd_loop(void *p);
	#else
		void _vk_cmd_loop();
	#endif
#endif
