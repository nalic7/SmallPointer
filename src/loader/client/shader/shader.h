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

extern VkDescriptorSetLayout lcs_vkdescriptorsetlayout;
extern VkDescriptorSet *lcs_vkdescriptorset_p_array[NALI_V_A_BL];

extern VkMappedMemoryRange *lcs_vkmappedmemoryrange_p;
extern uint16_t lcs_vkmappedmemoryrange_bl;

// extern void (**lcs_write_fp)(uint16_t);
// extern uint16_t lcs_write_fp_bl;

// extern uint16_t
// 	*lcs_free_vkdescriptorset_i_p;
extern uint8_t
	// *lcs_free_vkdescriptorset_a_p,
	// lcs_free_vkdescriptorset_i_bl,

	// *lcs_update_vkdescriptorset_b_p,
	// *lcs_update_vkdescriptorset_j_p,
	// lcs_update_vkdescriptorset_i_bl,

	// *lcs_edit_vkdescriptorset_b_p,
	// *lcs_edit_vkdescriptorset_j_p,
	// lcs_edit_vkdescriptorset_i_bl,

	**lcs_add_a_p_array[NALI_V_A_BL],
	*lcs_add_a_bl_p_array[NALI_V_A_BL],
	*lcs_add_ds_p_array[NALI_V_A_BL],
	*lcs_add_j_p_array[NALI_V_A_BL],
	lcs_add_i_bl_array[NALI_V_A_BL];

extern VkDeviceSize
	*lcs_add_vkdevicesize_p[NALI_V_A_BL];

void lcs_set();
void lcs_loop();

void lcs_vk();
void lcs_freeVk();

#endif