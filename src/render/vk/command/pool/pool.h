#ifndef _RD_VK_CMP_H
	#define _RD_VK_CMP_H

	extern VkCommandPool **_rd_vk_cmp_p;

	void _rd_vk_cmp_set();
	void _rd_vk_cmp_make(uint32_t device);
	void _rd_vk_cmp_free();
#endif
