#ifndef _VK_CMP_H
#define _VK_CMP_H
	extern VkCommandPool **_vk_cmp_p;

	void _vk_cmp_set();
	void _vk_cmp_make(uint32_t device);
	void _vk_cmp_free();
#endif
