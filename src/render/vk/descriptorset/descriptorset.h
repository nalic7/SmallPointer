#ifndef _VK_DSPS_H
	#define _VK_DSPS_H

	void _vk_dsps_make(uint32_t device, VkDescriptorPool vkdescriptorpool, VkDescriptorSetLayout *vkdescriptorsetlayout_p, uint32_t vkdescriptorsetlayout_size, VkDescriptorSet *vkdescriptorset_p);
	void _vk_dsps_write(uint32_t device, uint32_t bind, VkDescriptorImageInfo *vkdescriptorimageinfo_p, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkDescriptorType vkdescriptortype, VkDescriptorSet vkdescriptorset, VkWriteDescriptorSet *vkwritedescriptorset_p);
#endif
