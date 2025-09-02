#ifndef SMPT_RD_VK_CMP_H
	#define SMPT_RD_VK_CMP_H

	extern VkCommandPool **smpt_rd_vk_cmp_p;

	void smpt_rd_vk_cmp_set();
	void smpt_rd_vk_cmp_make(uint32_t device);
	void smpt_rd_vk_cmp_free();
#endif
