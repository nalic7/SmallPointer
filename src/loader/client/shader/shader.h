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

extern mtx_t *lcs_mtx_t_p;

extern float m_vp_float_array[16*2];

//c1j1
//c1j0
//t1j1u1v1
//t1j0u1v1
#define NALI_V_A_BL 2

extern uint8_t
	**v_a_p_array[NALI_V_A_BL],
	*v_a_bl1_p_array[NALI_V_A_BL];

extern uint16_t
	v_a_bl0_array[NALI_V_A_BL];
// uint16_t
// 	v_a_bl;

extern uint32_t *v_i_p;

extern VkDeviceSize 
	v_a_vkdevicesize_array[NALI_V_A_BL],
//jN
//default -> UBOB UBOA
	*v_b_vkdevicesize_p_array[NALI_V_A_BL];

extern float **v_s_p_array[NALI_V_A_BL];

extern VkDescriptorSetLayout lcs_vkdescriptorsetlayout;
extern VkDescriptorSet *lcs_vkdescriptorset_p[NALI_V_A_BL];

extern VkMappedMemoryRange *lcs_vkmappedmemoryrange_p;
extern uint16_t lcs_vkmappedmemoryrange_bl;

extern VkDeviceSize
	*lcs_add_vkdevicesize_p[NALI_V_A_BL];

void lcs_set();
void lcs_loop();

void lcs_vk();
void lcs_freeVk();
void lcs_free();

#endif