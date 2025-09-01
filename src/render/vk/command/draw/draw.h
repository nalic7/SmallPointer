#ifndef _RD_VK_CMD_H
	#define _RD_VK_CMD_H

	void _rd_vk_cmd_set();
	#ifdef _CM_WL
		void _rd_vk_cmd_loop();
	#else
		int _rd_vk_cmd_loop(void *p);
	#endif
#endif
