#ifndef _RD_VKW_DSTSP_H
	#define _RD_VKW_DSTSP_H

	extern VkDescriptorPool _rd_vkw_dstsp;

	void _rd_vkw_dstsp_make(uint32_t device);
	void _rd_vkw_dstsp_free(uint32_t device);
#endif
