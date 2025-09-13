#ifndef SMPT_RD_VK_CMhP
	#define SMPT_RD_VK_CMhP

	extern VkCommandPool **smpt_rd_vk_cmpP;

	void smpt_rd_vk_cmpMset();
	void smpt_rd_vk_cmpMmake(uint32_t device);
	void smpt_rd_vk_cmpMfree();
#endif
