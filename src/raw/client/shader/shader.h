#ifndef _RC_SD_H
#define _RC_SD_H

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

//c1j1
//c1j0
//t1j1u1v1
//t1j0u1v1
#define NALI_LCS_A_BL 2

#define NALI_LCM__UPDATE_S_AD 1
typedef struct
{
	_RB_MT m;
	_RB_MAT ma;
	_RB_AKIT aki;

	_RB_CHT ch;
	_RB_MIT mi;
	uint8_t state;

	uint8_t rt_frame;
	float _rt_p[3 + 2];
	float rt_p[3 + 2];
	uint8_t a_f_frame;
	float _a_f;
	float a_f;
	// _RB_AKT ak;
} lcs__m;
#define NALI_LCS_AIT uint8_t
typedef struct
{
	lcs__m m;

	VkDescriptorSet *vkdescriptorset_p;
	const NALI_LCS_AIT *a_p;
	uint8_t mab;
	// VkDeviceSize *vkdevicesize_p;
	_RB_MIT ds;
} lcs__;
extern lcs__ lcs___p[_RB_MIM];

extern uint32_t lcs_s_bl;
typedef struct
{
	_RB_MIT _;
	// _RB_MAT ib;
	// _RB_MAT ic;
	_RB_MAT i;
	float d;
} lcs_s;
extern lcs_s *lcs_s_p;

void lcs_set();
// void lcs_loop();

void lcs_free();

#endif
