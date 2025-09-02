#ifndef SMPT_RD_VKW_DSTSP_H
	#define SMPT_RD_VKW_DSTSP_H

	extern VkDescriptorPool smpt_rd_vkw_dstsp;

	void smpt_rd_vkw_dstsp_make(uint32_t device);
	void smpt_rd_vkw_dstsp_free(uint32_t device);
#endif
