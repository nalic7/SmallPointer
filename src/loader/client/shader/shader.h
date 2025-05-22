#ifndef NALI_LOADER_CLIENT_SHADER_H
#define NALI_LOADER_CLIENT_SHADER_H

#define LC_setVkVertexInputBindingDescription(name) \
	VkVertexInputBindingDescription name = \
	{ \
		.binding = 0, \
		.stride = sizeof(float) * 3 + sizeof(uint32_t), \
		.inputRate = VK_VERTEX_INPUT_RATE_VERTEX \
	};

#define LC_setVkVertexInputAttributeDescription(name) \
	VkVertexInputAttributeDescription name[] = \
	{ \
		(VkVertexInputAttributeDescription) \
		{ \
			.binding = 0, \
			.location = 0, \
			.format = VK_FORMAT_R32G32B32_SFLOAT, \
			.offset = 0 \
		}, \
		(VkVertexInputAttributeDescription) \
		{ \
			.binding = 0, \
			.location = 1, \
			.format = VK_FORMAT_R32_UINT, \
			.offset = sizeof(float) * 3 \
		} \
	};

extern VkDescriptorSetLayout lcs_vkdescriptorsetlayout;
extern VkDescriptorSet *lcs_vkdescriptorset_p;

void lcs_vk();
void lcs_freeVk();

#endif