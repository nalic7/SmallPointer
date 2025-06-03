#define NALI_LCS_U_RGBA 1
#define NALI_LCS_U_A 2
// /8
static uint8_t *state_p_array[NALI_V_A_BL];
//offset size
static VkDeviceSize *vkdevicesize_p_array[NALI_V_A_BL];
// static float *rgba_p_array[NALI_V_A_BL];
static void update(uint8_t a, uint16_t lcs_write_fp_bl)
{
	// //write flush

	// uint32_t l0;
	// uint32_t l_offset;
	// uint32_t l_size;

	// //rgba b
	// if (state_p_array[a][lcs_write_fp_bl] & NALI_LCS_U_RGBA)
	// {
	// 	l0 = lcm_vkdevicesize_p[lcm_joint_count_bl - 1] + NALI_LCM_BONE_BL * sizeof(float) * 4 * 4 * v_a_bl0_array[a];
	// 	//write to lc_vkbuffer_p from other thread
	// 	// memcpy(lc_vkbuffer_p + l0, rgba_p_array[a] + lcs_write_fp_bl * 4, sizeof(float) * 4);
	// 	l0 += sizeof(float) * 4;
	// 	l_offset = l0;
	// }
	// else
	// {
	// 	l0 = lcm_vkdevicesize_p[lcm_joint_count_bl - 1] + NALI_LCM_BONE_BL * sizeof(float) * 4 * 4 * v_a_bl0_array[a] + sizeof(float) * 4;
	// 	l_offset = l0;
	// }

	// if (state_p_array[a][lcs_write_fp_bl] & NALI_LCS_U_A)
	// {
	// 	// //file
	// 	// uint8_t animate = 0;
	// 	// uint8_t key = 11;//80
	// 	// for (uint8_t l_1 = 0; l_1 < lckf_keyframe_p[animate][key].bone_bl; ++l_1)
	// 	// {
	// 	// 	memcpy(lc_vkbuffer_p + l0 + lckf_keyframe_p[animate][key].bone_p[l_1] * sizeof(float) * 4 * 3, lckf_keyframe_p[animate][key].animation_s_p[l_1], sizeof(float) * 3);
	// 	// 	memcpy(lc_vkbuffer_p + l0 + sizeof(float) * 4 + lckf_keyframe_p[animate][key].bone_p[l_1] * sizeof(float) * 4 * 3, lckf_keyframe_p[animate][key].animation_r_p[l_1], sizeof(float) * 4);
	// 	// 	memcpy(lc_vkbuffer_p + l0 + sizeof(float) * 4 * 2 + lckf_keyframe_p[animate][key].bone_p[l_1] * sizeof(float) * 4 * 3, lckf_keyframe_p[animate][key].animation_t_p[l_1], sizeof(float) * 3);
	// 	// }
	// 	// //data

	// 	// l_size = l0 + sizeof(float) * 4 * 3 * lcm_joint_count_p[j];
	// 	l_size = l0 + sizeof(float) * 4 * 3 * j;
	// }
	// else
	// {
	// 	l_size = ;
	// }

	if (state_p_array[a][lcs_write_fp_bl / 8] & 1 << lcs_write_fp_bl % 8)
	{
		lcs_vkmappedmemoryrange_p = realloc(lcs_vkmappedmemoryrange_p, sizeof(VkMappedMemoryRange) * (lcs_vkmappedmemoryrange_bl + 1));
		lcs_vkmappedmemoryrange_p[lcs_vkmappedmemoryrange_bl++] = (VkMappedMemoryRange)
		{
			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
			.memory = lc_vkdevicememory,
			.offset = vkdevicesize_p_array[a][lcs_write_fp_bl * 2],
			.size = (vkdevicesize_p_array[a][lcs_write_fp_bl * 2 + 1] + 63) & ~63,
			.pNext = VK_NULL_HANDLE
		};

		state_p_array[a][lcs_write_fp_bl / 8] &= 0xFFu - lcs_write_fp_bl % 8;
	}
}

static void animate(uint8_t a, uint16_t lcs_write_fp_bl)
{
	//init e and animate

	//l0 rgba b

	//l0 a
	v_b_vkdevicesize_p_array[a] + lcs_write_fp_bl * NALI_LCS_D_SIZE + 2;

	uint8_t animate = 0;
	uint8_t key = 11;//80
	for (uint8_t l_1 = 0; l_1 < lckf_keyframe_p[animate][key].bone_bl; ++l_1)
	{
		memcpy(lc_vkbuffer_p + l0 + lckf_keyframe_p[animate][key].bone_p[l_1] * sizeof(float) * 4 * 3, lckf_keyframe_p[animate][key].animation_s_p[l_1], sizeof(float) * 3);
		memcpy(lc_vkbuffer_p + l0 + sizeof(float) * 4 + lckf_keyframe_p[animate][key].bone_p[l_1] * sizeof(float) * 4 * 3, lckf_keyframe_p[animate][key].animation_r_p[l_1], sizeof(float) * 4);
		memcpy(lc_vkbuffer_p + l0 + sizeof(float) * 4 * 2 + lckf_keyframe_p[animate][key].bone_p[l_1] * sizeof(float) * 4 * 3, lckf_keyframe_p[animate][key].animation_t_p[l_1], sizeof(float) * 3);
	}
}

static void pre_update(uint8_t a, uint16_t lcs_write_fp_bl)
{
	//write to lc_vkbuffer_p
	animate();
	lcs_write_fp[lcs_write_fp_bl] = update;
}

void e_pomi0_add()
{
	add();
}