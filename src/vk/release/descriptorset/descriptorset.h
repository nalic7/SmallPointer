#ifndef NALI_VK_DESCRIPTORSET_H
#define NALI_VK_DESCRIPTORSET_H

void vk_makeDescriptorSet(uint32_t device, VkDescriptorPool *vkdescriptorpool_p, VkDescriptorSetLayout *vkdescriptorsetlayout_p, uint32_t vkdescriptorsetlayout_size, VkDescriptorSet *vkdescriptorset_p);
void vk_setVkWriteDescriptorSet(uint32_t device, uint32_t bind, VkDescriptorImageInfo *vkdescriptorimageinfo_p, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkDescriptorType vkdescriptortype, VkDescriptorSet *vkdescriptorset_p, VkWriteDescriptorSet *vkwritedescriptorset_p, uint16_t vkwritedescriptorset_index);

#endif