#ifndef NALI_LOADER_CLIENT_SHADER_H
#define NALI_LOADER_CLIENT_SHADER_H

#define NALI_LCS_D_SIZE 5

#define LCS_setVkVertexInputBindingDescription(name) \
	VkVertexInputBindingDescription name = \
	{ \
		.binding = 0, \
		.stride = sizeof(float) * 3 + sizeof(uint32_t), \
		.inputRate = VK_VERTEX_INPUT_RATE_VERTEX \
	};

#define LCS_setVkVertexInputAttributeDescription(name) \
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

//c1j1
//c1j0
//t1j1u1v1
//t1j0u1v1
#define NALI_LCS_A_BL 2

extern VkDeviceSize *lcs_ib_p;
extern uint32_t *lcs_ic_p;

extern VkDeviceSize lcs_a_vkdevicesize_p[NALI_LCS_A_BL];

extern VkDescriptorSetLayout lcs_vkdescriptorsetlayout;
extern VkDescriptorPool lcs_vkdescriptorpool;

#define NALI_LCM__UPDATE_S_AD 1
typedef struct
{
	NALI_LB_MT m;
	NALI_LB_MAT ma;
	NALI_LB_AKIT aki;

	NALI_LB_CHT ch;
	NALI_LB_MIT mi;
	uint8_t state;

	uint8_t rt_frame;
	float _rt_p[3 + 2];
	float rt_p[3 + 2];
	uint8_t a_f_frame;
	float _a_f;
	float a_f;
	// NALI_LB_AKT ak;
} lcs__m;
#define NALI_LCS_AIT uint8_t
typedef struct
{
	lcs__m m;

	VkDescriptorSet vkdescriptorset;
	const NALI_LCS_AIT *a_p;
	uint8_t mab;
	// VkDeviceSize *vkdevicesize_p;
	NALI_LB_MIT ds;
} lcs__;
extern lcs__ lcs___p[NALI_LB_MIM];

extern uint32_t lcs_s_bl;
typedef struct
{
	NALI_LB_MIT _;
	// NALI_LB_MAT ib;
	// NALI_LB_MAT ic;
	NALI_LB_MAT i;
	float d;
} lcs_s;
extern lcs_s *lcs_s_p;

void lcs_setVkWriteDescriptorSet(VkDescriptorSet vkdescriptorset, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkWriteDescriptorSet *vkwritedescriptorset_p, NALI_LB_MIT ds, uint8_t j, uint8_t mj);

void lcs_set();
// void lcs_loop();

void lcs_vk();
void lcs_freeVk();
void lcs_free();

#endif
