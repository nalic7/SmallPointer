uint32_t lcp_rgba_bl;

uint8_t
	// lcm_max_j = 0,

	*lcp_joint_count_p,
	lcp_joint_count_bl,
	**lcp_a_p;

float **lcp_bp_p;

VkDeviceSize *lcp_vkdevicesize_p;
//cache

typedef struct
{
	uint8_t
		*joint_p,
		joint_bl;
} m_bone;

static m_bone *m_bone_p;

static uint32_t **index_p;
static uint32_t *index_bl_p;
// static uint8_t **attribute_p;
// static uint32_t *attribute_bl_p;
static uint8_t *a_p_array[NALI_LCS_A_BL];
static uint32_t a_bl_array[NALI_LCS_A_BL];
static uint8_t model_il;

static float *rgba_p;

void lcp_set()
{
	lcp_joint_count_bl = *(uint8_t *)(lb_c->d_p + lb_c->d_bl_p[1]);
	lb_c->d_bl_p[1] += sizeof(uint8_t);

	lb_c->bs_p = malloc(sizeof(uint16_t *) * lcp_joint_count_bl);
	lb_c->be_p = malloc(sizeof(uint16_t *) * lcp_joint_count_bl);

	lcp_joint_count_p = malloc(lcp_joint_count_bl);
	memcpy(lcp_joint_count_p, lb_c->d_p + lb_c->d_bl_p[1], lcp_joint_count_bl);
	lb_c->d_bl_p[1] += lcp_joint_count_bl;

	uint16_t l_bone_bl = 0;
	m_bone_p = malloc(0);

	lcp_bp_p = malloc(sizeof(float *) * lcp_joint_count_bl);
	lcp_a_p = malloc(sizeof(uint8_t *) * lcp_joint_count_bl);

	lcp_vkdevicesize_p = malloc(sizeof(VkDeviceSize) * (lcp_joint_count_bl + 2));

	for (uint8_t l_0 = 0; l_0 < lcp_joint_count_bl; ++l_0)
	{
		// if (lcm_max_j < lcm_joint_count_p[l_0])
		// {
		// 	lcm_max_j = lcm_joint_count_p[l_0];
		// }

		lb_c->bs_p[l_0] = malloc(sizeof(uint16_t) * lcp_joint_count_p[l_0]);
		lb_c->be_p[l_0] = malloc(sizeof(uint16_t) * lcp_joint_count_p[l_0]);
		lb_c->bs_p[l_0][0] = 0;

		m_bone_p = realloc(m_bone_p, sizeof(m_bone) * (l_bone_bl + lcp_joint_count_p[l_0]));
		lcp_bp_p[l_0] = malloc(sizeof(float) * 16 * 2 * lcp_joint_count_p[l_0]);

		for (uint8_t l_1 = 0; l_1 < lcp_joint_count_p[l_0]; ++l_1)
		{
			uint8_t size = *(uint8_t *)(lb_c->d_p + lb_c->d_bl_p[1]);
			lb_c->d_bl_p[1] += sizeof(uint8_t);

			memset(m_bone_p + l_bone_bl + l_1, 0, sizeof(m_bone));
			m_bone_p[l_bone_bl + l_1].joint_bl = size;
			m_bone_p[l_bone_bl + l_1].joint_p = malloc(size);
			memcpy(m_bone_p[l_bone_bl + l_1].joint_p, lb_c->d_p + lb_c->d_bl_p[1], size);
			lb_c->d_bl_p[1] += size;

			if (l_1 != 0)
			{
				lb_c->bs_p[l_0][l_1] = lb_c->be_p[l_0][l_1 - 1];
			}
			lb_c->be_p[l_0][l_1] = lb_c->bs_p[l_0][l_1] + size;
		}

		l_bone_bl += lcp_joint_count_p[l_0];
	}

	l_bone_bl = 0;
	for (uint8_t l_0 = 0; l_0 < lcp_joint_count_bl; ++l_0)
	{
		for (uint8_t l_1 = 0; l_1 < lcp_joint_count_p[l_0]; ++l_1)
		{
//			//s0-test
//			memcpy(lcp_bp_p[l_0] + l_1 * 16 * 2, mm4x4_array, sizeof(mm4x4_array));
//			memcpy(lcp_bp_p[l_0] + l_1 * 16 * 2 + 16, mm4x4_array, sizeof(mm4x4_array));
//			//e0-test
			memcpy(lcp_bp_p[l_0] + l_1 * 16 * 2, lb_c->d_p + lb_c->d_bl_p[1] + l_1 * sizeof(float) * 16, sizeof(float) * 16);
			memcpy(lcp_bp_p[l_0] + l_1 * 16 * 2 + 16, lcp_bp_p[l_0] + l_1 * 16 * 2, sizeof(float) * 16);
			mm4x4_i(lcp_bp_p[l_0] + l_1 * 16 * 2 + 16);
		}
		lb_c->d_bl_p[1] += sizeof(float) * 16 * lcp_joint_count_p[l_0];
		l_bone_bl += lcp_joint_count_p[l_0];
	}

	// l_bone_bl = 0;
	// for (uint8_t l_0 = 0; l_0 < m_joint_count_bl; ++l_0)
	// {
	// 	memcpy(bindpose_p + l_bone_bl * 16, data_p + step, m_joint_count_p[l_0] * sizeof(float) * 16);
	// 	step += sizeof(float) * 16 * m_joint_count_p[l_0];
	// 	l_bone_bl += m_joint_count_p[l_0];
	// }

	// uint32_t animation_bl = *(uint32_t *)(data_p + step);
	// step += sizeof(uint32_t);

	// uint32_t l_step = 0;
	// uint8_t time_bl;
	// l_bone_bl = 0;
	// while (l_step != animation_bl)
	// {
	// 	// /b\ 1
	// 	time_bl = *(uint8_t *)(data_p + step);
	// 	step += sizeof(uint8_t);
	// 	l_step += sizeof(uint8_t);

	// 	srt_bone_p[l_bone_bl].time_t_bl = time_bl;
	// 	srt_bone_p[l_bone_bl].time_t_p = malloc(time_bl);
	// 	memcpy(srt_bone_p[l_bone_bl].time_t_p, data_p + step, time_bl);
	// 	step += time_bl;
	// 	l_step += time_bl;

	// 	srt_bone_p[l_bone_bl].animation_t_p = malloc(sizeof(float) * 3 * time_bl);
	// 	memcpy(srt_bone_p[l_bone_bl].animation_t_p, data_p + step, sizeof(float) * 3 * time_bl);
	// 	step += sizeof(float) * 3 * time_bl;
	// 	l_step += sizeof(float) * 3 * time_bl;

	// 	time_bl = *(uint8_t *)(data_p + step);
	// 	step += sizeof(uint8_t);
	// 	l_step += sizeof(uint8_t);

	// 	srt_bone_p[l_bone_bl].time_r_bl = time_bl;
	// 	srt_bone_p[l_bone_bl].time_r_p = malloc(time_bl);
	// 	memcpy(srt_bone_p[l_bone_bl].time_r_p, data_p + step, time_bl);
	// 	step += time_bl;
	// 	l_step += time_bl;

	// 	srt_bone_p[l_bone_bl].animation_r_p = malloc(sizeof(float) * 4 * time_bl);
	// 	memcpy(srt_bone_p[l_bone_bl].animation_r_p, data_p + step, sizeof(float) * 4 * time_bl);
	// 	step += sizeof(float) * 4 * time_bl;
	// 	l_step += sizeof(float) * 4 * time_bl;

	// 	time_bl = *(uint8_t *)(data_p + step);
	// 	step += sizeof(uint8_t);
	// 	l_step += sizeof(uint8_t);

	// 	srt_bone_p[l_bone_bl].time_s_bl = time_bl;
	// 	srt_bone_p[l_bone_bl].time_s_p = malloc(time_bl);
	// 	memcpy(srt_bone_p[l_bone_bl].time_s_p, data_p + step, time_bl);
	// 	step += time_bl;
	// 	l_step += time_bl;

	// 	srt_bone_p[l_bone_bl].animation_s_p = malloc(sizeof(float) * 3 * time_bl);
	// 	memcpy(srt_bone_p[l_bone_bl].animation_s_p, data_p + step, sizeof(float) * 3 * time_bl);
	// 	step += sizeof(float) * 3 * time_bl;
	// 	l_step += sizeof(float) * 3 * time_bl;
	// 	++l_bone_bl;

	// 	// if (== animations_count_p[])
	// 	// {
	// 	// 	l_bone_bl = 0;
	// 	// }
	// }



	// uint8_t joint_head_bl = ceil(l_bone_bl * 3.0F / 8);
	// uint8_t *joint_head_p = malloc(joint_head_bl);
	// memcpy(joint_head_p, data_p + step, joint_head_bl);
	// step += joint_head_bl;

	// uint8_t
	// 	bit_step = 0;
	// l_bone_bl = 0;
	// for (uint8_t l_0 = 0; l_0 < joint_head_bl; ++l_0)
	// {
	// 	for (uint8_t l_1 = 0; l_1 < 8; ++l_1)
	// 	{
	// 		switch (bit_step)
	// 		{
	// 			case 0:
	// 				if (joint_head_p[l_0] >> l_1 & 1)
	// 				{
	// 					srt_bone_p[l_bone_bl].time_s_bl = *(uint8_t *)(data_p + step);
	// 					step += sizeof(uint8_t);

	// 					srt_bone_p[l_bone_bl].time_s_p = malloc(srt_bone_p[l_bone_bl].time_s_bl);
	// 					memcpy(srt_bone_p[l_bone_bl].time_s_p, data_p + step, srt_bone_p[l_bone_bl].time_s_bl);
	// 					step += srt_bone_p[l_bone_bl].time_s_bl;

	// 					srt_bone_p[l_bone_bl].animation_s_p = malloc(srt_bone_p[l_bone_bl].time_s_bl * sizeof(float) * 3);
	// 					memcpy(srt_bone_p[l_bone_bl].animation_s_p, data_p + step, srt_bone_p[l_bone_bl].time_s_bl * sizeof(float) * 3);
	// 					step += srt_bone_p[l_bone_bl].time_s_bl * sizeof(float) * 3;
	// 				}
	// 				++bit_step;
	// 				break;
	// 			case 1:
	// 				if (joint_head_p[l_0] >> l_1 & 1)
	// 				{
	// 					srt_bone_p[l_bone_bl].time_r_bl = *(uint8_t *)(data_p + step);
	// 					step += sizeof(uint8_t);

	// 					srt_bone_p[l_bone_bl].time_r_p = malloc(srt_bone_p[l_bone_bl].time_r_bl);
	// 					memcpy(srt_bone_p[l_bone_bl].time_r_p, data_p + step, srt_bone_p[l_bone_bl].time_r_bl);
	// 					step += srt_bone_p[l_bone_bl].time_r_bl;

	// 					srt_bone_p[l_bone_bl].animation_r_p = malloc(srt_bone_p[l_bone_bl].time_r_bl * sizeof(float) * 4);
	// 					memcpy(srt_bone_p[l_bone_bl].animation_r_p, data_p + step, srt_bone_p[l_bone_bl].time_r_bl * sizeof(float) * 4);
	// 					step += srt_bone_p[l_bone_bl].time_r_bl * sizeof(float) * 4;
	// 				}
	// 				++bit_step;
	// 				break;
	// 			default://2
	// 				if (joint_head_p[l_0] >> l_1 & 1)
	// 				{
	// 					srt_bone_p[l_bone_bl].time_t_bl = *(uint8_t *)(data_p + step);
	// 					step += sizeof(uint8_t);

	// 					srt_bone_p[l_bone_bl].time_t_p = malloc(srt_bone_p[l_bone_bl].time_t_bl);
	// 					memcpy(srt_bone_p[l_bone_bl].time_t_p, data_p + step, srt_bone_p[l_bone_bl].time_t_bl);
	// 					step += srt_bone_p[l_bone_bl].time_t_bl;

	// 					srt_bone_p[l_bone_bl].animation_t_p = malloc(srt_bone_p[l_bone_bl].time_t_bl * sizeof(float) * 3);
	// 					memcpy(srt_bone_p[l_bone_bl].animation_t_p, data_p + step, srt_bone_p[l_bone_bl].time_t_bl * sizeof(float) * 3);
	// 					step += srt_bone_p[l_bone_bl].time_t_bl * sizeof(float) * 3;
	// 				}
	// 				++l_bone_bl;
	// 				bit_step = 0;
	// 		}
	// 	}
	// }
	// free(joint_head_p);



	uint32_t ia_bl = *(uint32_t *)(lb_c->d_p + lb_c->d_bl_p[1]);
	lb_c->d_bl_p[1] += sizeof(uint32_t);
	// model_il = ia_bl / 2 / sizeof(uint32_t);
	model_il = ia_bl / sizeof(uint32_t);

	// m_ai_index_count_p = malloc(sizeof(uint32_t) * model_il * 2);
	lcs_ib_p = malloc(sizeof(VkDeviceSize) * model_il);
	lcs_ic_p = malloc(sizeof(uint32_t) * model_il);
	// m_ai_vkdevicesize_p = malloc(sizeof(VkDeviceSize) * model_il);

	index_bl_p = malloc(sizeof(uint32_t) * model_il);
	// attribute_bl_p = malloc(sizeof(uint32_t) * model_il);
	uint32_t l_step = 0;
	while (l_step != ia_bl)
	{
		// index_bl_p[l_step / (sizeof(uint32_t) * 2)] = *(uint32_t *)(data_p + step);
		index_bl_p[l_step / sizeof(uint32_t)] = *(uint32_t *)(lb_c->d_p + lb_c->d_bl_p[1]);
		lb_c->d_bl_p[1] += sizeof(uint32_t);

		// attribute_bl_p[l_step / (sizeof(uint32_t) * 2)] = *(uint32_t *)(data_p + step);
		// step += sizeof(uint32_t);

		// l_step += sizeof(uint32_t) * 2;
		l_step += sizeof(uint32_t);
	}

	index_p = malloc(sizeof(uint32_t *) * model_il);
	// attribute_p = malloc(sizeof(uint8_t *) * model_il);

	for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	{
		index_p[l_0] = malloc(index_bl_p[l_0]);
		memcpy(index_p[l_0], lb_c->d_p + lb_c->d_bl_p[1], index_bl_p[l_0]);
		lb_c->d_bl_p[1] += index_bl_p[l_0];
		lcs_ic_p[l_0] = index_bl_p[l_0] / sizeof(uint32_t);
	}

	lcp_rgba_bl = *(uint8_t *)(lb_c->d_p + lb_c->d_bl_p[1]);
	lb_c->d_bl_p[1] += sizeof(uint8_t);
	lcp_rgba_bl *= 4 * sizeof(float);
	rgba_p = malloc(lcp_rgba_bl);
	memcpy(rgba_p, lb_c->d_p + lb_c->d_bl_p[1], lcp_rgba_bl);
	lb_c->d_bl_p[1] += lcp_rgba_bl;
	//apply color
	for (uint32_t l_0 = 0; l_0 < lcp_rgba_bl / sizeof(float); ++l_0)
	{
		rgba_p[l_0] = pow(rgba_p[l_0], 1.0F / 5.0F);
	}

	//c1
	uint32_t l_c1_bl = *(uint32_t *)(lb_c->d_p + lb_c->d_bl_p[1]);
	lb_c->d_bl_p[1] += sizeof(uint32_t);

	a_bl_array[0] = l_c1_bl * (sizeof(float) * 3 + sizeof(uint32_t));
	a_p_array[0] = malloc(a_bl_array[0]);
	//c1 a
	for (uint32_t l_0 = 0; l_0 < l_c1_bl; ++l_0)
	{
		memcpy(a_p_array[0] + l_0 * (sizeof(float) * 3 + sizeof(uint32_t)), lb_c->d_p + lb_c->d_bl_p[1], sizeof(float) * 3 + 1);
		memset((a_p_array[0] + l_0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 1)), 0, 3);
		lb_c->d_bl_p[1] += sizeof(float) * 3 + 1;
	}

	//c1j1
	a_bl_array[1] = lb_c->d_bl_p[0] - lb_c->d_bl_p[1];

	//c1j1 a
	uint32_t l_c1j1_size = a_bl_array[1] / (sizeof(float) * 3 + 2);
	a_bl_array[1] += l_c1j1_size * 2;
	a_p_array[1] = malloc(a_bl_array[1]);
	//add extra byte
	// uint32_t l_size = attribute_bl_p[l_0] / (sizeof(float) * 3 + 2);
	// attribute_bl_p[l_0] += l_size * 2;
	// attribute_p[l_0] = malloc(attribute_bl_p[l_0]);
	// for (uint32_t l_1 = 0; l_1 < l_size; ++l_1)
	// {
	// 	memcpy(attribute_p[l_0] + l_1 * (sizeof(float) * 3 + sizeof(uint32_t)), data_p + step, sizeof(float) * 3 + 2);
	// 	memset((attribute_p[l_0] + l_1 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 2)), 0, 2);
	// 	step += sizeof(float) * 3 + 2;
	// }
	for (uint32_t l_0 = 0; l_0 < l_c1j1_size; ++l_0)
	{
		memcpy(a_p_array[1] + l_0 * (sizeof(float) * 3 + sizeof(uint32_t)), lb_c->d_p + lb_c->d_bl_p[1], sizeof(float) * 3 + 2);
		memset((a_p_array[1] + l_0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 2)), 0, 2);
		lb_c->d_bl_p[1] += sizeof(float) * 3 + 2;
	}

	//init data
	for (uint8_t l_0 = 0; l_0 < lcp_joint_count_bl; ++l_0)
	{
		l_step = 0;
		lcp_a_p[l_0] = malloc(sizeof(float) * 4 * 3 * lcp_joint_count_p[l_0]);

		for (uint8_t l_1 = 0; l_1 < lcp_joint_count_p[l_0]; ++l_1)
		{
			//s
			for (uint8_t l_2 = 0; l_2 < 3; ++l_2)
			{
				*(float *)(lcp_a_p[l_0] + l_step + l_2 * sizeof(float)) = 1;
			}

			//b_s b_e
			*(uint32_t *)(lcp_a_p[l_0] + l_step + 3 * sizeof(float)) = lb_c->bs_p[l_0][l_1] | lb_c->be_p[l_0][l_1] << (8 + 8);
			l_step += 4 * sizeof(float);

			//r
			memcpy(lcp_a_p[l_0] + l_step, mm4x4_array + 12, 4 * sizeof(float));
			l_step += 4 * sizeof(float);

			//t
			memset(lcp_a_p[l_0] + l_step, 0, 4 * sizeof(float));
			l_step += 4 * sizeof(float);
		}

		free(lb_c->bs_p[l_0]);
		free(lb_c->be_p[l_0]);
	}
	free(lb_c->bs_p);
	free(lb_c->be_p);

	//b
	l_bone_bl = 0;
	for (uint8_t l_0 = 0; l_0 < lcp_joint_count_bl; ++l_0)
	{
		l_step = 0;
		uint8_t l_0_0 = 0;

		for (uint8_t l_1 = 0; l_1 < lcp_joint_count_p[l_0]; ++l_1)
		{
			for (uint8_t l_2 = 0; l_2 < m_bone_p[l_bone_bl + l_1].joint_bl; ++l_2)
			{
				*(uint32_t *)(lcp_a_p[l_0] + l_step + 3 * sizeof(float) + sizeof(float) * 4 * 2) |= m_bone_p[l_bone_bl + l_1].joint_p[l_2] << l_0_0 * 8;

				if (++l_0_0 == 4)
				{
					l_step += sizeof(float) * 4 * 3;
					l_0_0 = 0;
				}
			}
		}

		l_bone_bl += lcp_joint_count_p[l_0];
	}

	//step
	uint64_t l_address = NALI_LCP_VP_BL + lcp_rgba_bl;

	for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	{
		lcs_ib_p[l_0] = l_address;
		l_address += index_bl_p[l_0];
	}

	for (uint32_t l_0 = 0; l_0 < NALI_LCS_A_BL; ++l_0)
	{
		lcs_a_vkdevicesize_p[l_0] = l_address;
		l_address += a_bl_array[l_0];
	}
}

void lcp_vk()
{
	uint32_t step = 0;

	//UBOS gui world
	memcpy(lc_vkbuffer_p + step, mm4x4_array, sizeof(mm4x4_array));
	step += sizeof(mm4x4_array);
	memcpy(lc_vkbuffer_p + step, mm4x4_array, sizeof(mm4x4_array));
	step += sizeof(mm4x4_array);

	memcpy(lc_vkbuffer_p + step, mm4x4_array, sizeof(mm4x4_array));
	step += sizeof(mm4x4_array);
	memset(lc_vkbuffer_p + step, 0, sizeof(float) * 16);
	step += sizeof(float) * 16;

	//static rgba
	memcpy(lc_vkbuffer_p + step, rgba_p, lcp_rgba_bl);
	step += lcp_rgba_bl;

	//ai index
	for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	{
		memcpy(lc_vkbuffer_p + step, index_p[l_0], index_bl_p[l_0]);
		step += index_bl_p[l_0];
	}

	//a index
	for (uint32_t l_0 = 0; l_0 < NALI_LCS_A_BL; ++l_0)
	{
		memcpy(lc_vkbuffer_p + step, a_p_array[l_0], a_bl_array[l_0]);
		step += a_bl_array[l_0];
	}

	//UBOB
	//use index 0 with limit as default
	lcp_vkdevicesize_p[lcp_joint_count_bl] = step;
	for (uint32_t l_0 = 0; l_0 < lcp_joint_count_bl; ++l_0)
	{
		lcp_vkdevicesize_p[l_0] = step;
		memcpy(lc_vkbuffer_p + step, lcp_bp_p[l_0], sizeof(float) * 16 * 2 * lcp_joint_count_p[l_0]);
		step += sizeof(float) * 16 * 2 * lcp_joint_count_p[l_0];
	}
	lcp_vkdevicesize_p[lcp_joint_count_bl + 1] = step;

	vkFlushMappedMemoryRanges(vkqd_vkdevice_p[vk_device], 1, &(VkMappedMemoryRange)
	{
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = lc_vkdevicememory,
		.offset = 0,
		.size = (step + (vk_non_coherent_atom_size - 1)) & ~(vk_non_coherent_atom_size - 1),
		.pNext = VK_NULL_HANDLE
	});

	//s0-ssboa default
	// uint16_t l_bone_bl = 0;
	// for (uint32_t l_0 = 0; l_0 < lcm_joint_count_bl; ++l_0)
	// {
	// 	uint32_t l_s_step = step;
	// 	for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
	// 	{
	// 		for (uint8_t l_2 = 0; l_2 < 3; ++l_2)
	// 		{
	// 			*(float *)(lc_vkbuffer_p + step + l_2 * sizeof(float)) = 1;
	// 		}

	// 		//start end
	// 		*(uint32_t *)(lc_vkbuffer_p + step + sizeof(float) * 3) = lb_c->bs_p[l_0][l_1] | lb_c->be_p[l_0][l_1] << 8;
	// 		step += sizeof(float) * 4;
	// 	}

	// 	uint32_t l_r_step = step;
	// 	for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
	// 	{
	// 		memcpy(lc_vkbuffer_p + step, m_m4x4_array + 12, sizeof(float) * 4);
	// 		step += sizeof(float) * 4;
	// 	}

	// 	uint8_t l_0_0 = 0;
	// 	uint32_t l_step_0 = step;

	// 	uint32_t l_t_step = step;
	// 	for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
	// 	{
	// 		memset(lc_vkbuffer_p + step, 0, sizeof(float) * 3);
	// 		step += sizeof(float) * 4;
	// 	}

	// 	for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
	// 	{
	// 		for (uint8_t l_2 = 0; l_2 < m_bone_p[l_bone_bl + l_1].joint_bl; ++l_2)
	// 		{
	// 			*(uint32_t *)(lc_vkbuffer_p + l_step_0 + sizeof(float) * 3) |= m_bone_p[l_bone_bl + l_1].joint_p[l_2] << l_0_0 * 8;

	// 			++l_0_0;
	// 			if (l_0_0 == 4)
	// 			{
	// 				l_0_0 = 0;
	// 				l_step_0 += sizeof(float) * 4;
	// 			}
	// 		}
	// 	}

	// 	//s0-animate
	// 	uint8_t key = 11;//80
	// 	for (uint8_t l_1 = 0; l_1 < lckf_keyframe_p[0][key].bone_bl; ++l_1)
	// 	{
	// 		memcpy(lc_vkbuffer_p + l_s_step + lckf_keyframe_p[0][key].bone_p[l_1] * sizeof(float) * 4, lckf_keyframe_p[0][key].animation_s_p[l_1], sizeof(float) * 3);
	// 		memcpy(lc_vkbuffer_p + l_r_step + lckf_keyframe_p[0][key].bone_p[l_1] * sizeof(float) * 4, lckf_keyframe_p[0][key].animation_r_p[l_1], sizeof(float) * 4);
	// 		memcpy(lc_vkbuffer_p + l_t_step + lckf_keyframe_p[0][key].bone_p[l_1] * sizeof(float) * 4, lckf_keyframe_p[0][key].animation_t_p[l_1], sizeof(float) * 3);
	// 	}
	// 	//e0-animate

	// 	l_bone_bl += lcm_joint_count_p[l_0];

	// 	free(lb_c->bs_p[l_0]);
	// 	free(lb_c->be_p[l_0]);
	// }

	// free(lb_c->bs_p);
	// free(lb_c->be_p);
	//e0-ssboa default
}

void lcp_free()
{
	for (uint8_t l_0 = 0; l_0 < lcp_joint_count_bl; ++l_0)
	{
		free(lcp_bp_p[l_0]);
		free(lcp_a_p[l_0]);
	}
	free(lcp_bp_p);
	free(lcp_a_p);

	free(lcp_joint_count_p);

	free(m_bone_p);
}
