#ifndef NALI_LOADER_CLIENT_SHADER_H
#define NALI_LOADER_CLIENT_SHADER_H

#define NALI_LCS_D_SIZE 5

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

extern float lcs_float_p[16*2];

//VkDescriptorSet index
#define NALI_LCS_DSIT uint8_t

//c1j1
//c1j0
//t1j1u1v1
//t1j0u1v1
#define NALI_V_A_BL 2

extern uint8_t
	**lcs_a_p[NALI_V_A_BL],
	*lcs_a_bl1_p[NALI_V_A_BL];

extern NALI_LCS_DSIT
	lcs_a_bl0_p[NALI_V_A_BL];
// uint16_t
// 	v_a_bl;

extern VkDeviceSize *lcs_i_p;
extern uint32_t *lcs_ic_p;

extern VkDeviceSize 
	lcs_a_vkdevicesize_p[NALI_V_A_BL],
//jN
//default -> UBOB UBOA
	*lcs_b_vkdevicesize_p[NALI_V_A_BL];

extern VkDescriptorSetLayout lcs_vkdescriptorsetlayout;
extern VkDescriptorSet *lcs_vkdescriptorset_p[NALI_V_A_BL];

extern VkMappedMemoryRange *lcs_vkmappedmemoryrange_p;
extern uint16_t lcs_vkmappedmemoryrange_bl;

extern VkDescriptorPool lcs_vkdescriptorpool;

void lcs_setVkWriteDescriptorSet(VkDescriptorSet vkdescriptorset, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkWriteDescriptorSet *vkwritedescriptorset_p, VkDeviceSize *v_b_vkdevicesize_p, uint8_t mj);

void lcs_set();
void lcs_loop();

void lcs_vk();
void lcs_freeVk();
void lcs_free();

#endif