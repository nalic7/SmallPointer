typedef struct
{
	uint8_t
		*joint_p,
		joint_bl;
	// 	*time_s_p,
	// 	time_s_bl,
	// 	*time_r_p,
	// 	time_r_bl,
	// 	*time_t_p,
	// 	time_t_bl;
	// float
	// 	*animation_s_p,
	// 	*animation_r_p,
	// 	*animation_t_p;
} m_bone;

static m_bone *m_bone_p;
static float
	*i_bindpose_p,
	*bindpose_p;

uint8_t
	*lcm_joint_count_p,
	lcm_joint_count_bl;

static uint32_t **index_p;
static uint32_t *index_bl_p;
// static uint8_t **attribute_p;
// static uint32_t *attribute_bl_p;
static uint8_t *a_p;
static uint32_t a_bl;
static uint8_t model_il;

static float *rgba_p;
uint32_t lcm_rgba_bl;

void lcm_set()
{
	lcm_joint_count_bl = *(uint8_t *)(NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1]);
	NALI_CACHE_P_D_BL_P[1] += sizeof(uint8_t);

	NALI_CACHE_P_BS_P = malloc(sizeof(uint8_t *) * lcm_joint_count_bl);
	NALI_CACHE_P_BE_P = malloc(sizeof(uint8_t *) * lcm_joint_count_bl);

	lcm_joint_count_p = malloc(lcm_joint_count_bl);
	memcpy(lcm_joint_count_p, NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1], lcm_joint_count_bl);
	NALI_CACHE_P_D_BL_P[1] += lcm_joint_count_bl;

	uint16_t l_bone_bl = 0;
	m_bone_p = malloc(0);
	i_bindpose_p = malloc(0);
	bindpose_p = malloc(0);
	for (uint8_t l_0 = 0; l_0 < lcm_joint_count_bl; ++l_0)
	{
		// if (m_max_joint < m_joint_count_p[l_0])
		// {
		// 	m_max_joint = m_joint_count_p[l_0];
		// }

		NALI_CACHE_P_BS_P[l_0] = malloc(lcm_joint_count_p[l_0]);
		NALI_CACHE_P_BE_P[l_0] = malloc(lcm_joint_count_p[l_0]);
		NALI_CACHE_P_BS_P[l_0][0] = 0;

		m_bone_p = realloc(m_bone_p, sizeof(m_bone) * (l_bone_bl + lcm_joint_count_p[l_0]));
		i_bindpose_p = realloc(i_bindpose_p, sizeof(float) * 16 * (l_bone_bl + lcm_joint_count_p[l_0]));
		bindpose_p = realloc(bindpose_p, sizeof(float) * 16 * (l_bone_bl + lcm_joint_count_p[l_0]));

		for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
		{
			uint8_t size = *(uint8_t *)(NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1]);
			NALI_CACHE_P_D_BL_P[1] += sizeof(uint8_t);

			m_bone_p[l_bone_bl + l_1] = (m_bone){0};
			m_bone_p[l_bone_bl + l_1].joint_bl = size;
			m_bone_p[l_bone_bl + l_1].joint_p = malloc(size);
			memcpy(m_bone_p[l_bone_bl + l_1].joint_p, NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1], size);
			NALI_CACHE_P_D_BL_P[1] += size;

			if (l_1 != 0)
			{
				NALI_CACHE_P_BS_P[l_0][l_1] = NALI_CACHE_P_BE_P[l_0][l_1 - 1];
			}
			NALI_CACHE_P_BE_P[l_0][l_1] = NALI_CACHE_P_BS_P[l_0][l_1] + size;
		}

		l_bone_bl += lcm_joint_count_p[l_0];
	}

	l_bone_bl = 0;
	for (uint8_t l_0 = 0; l_0 < lcm_joint_count_bl; ++l_0)
	{
		memcpy(i_bindpose_p + l_bone_bl * 16, NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1], lcm_joint_count_p[l_0] * sizeof(float) * 16);
		memcpy(bindpose_p + l_bone_bl * 16, NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1], lcm_joint_count_p[l_0] * sizeof(float) * 16);
		for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
		{
			m_m4x4_i(bindpose_p + (l_bone_bl + l_1) * 16);
		}
		NALI_CACHE_P_D_BL_P[1] += sizeof(float) * 16 * lcm_joint_count_p[l_0];
		l_bone_bl += lcm_joint_count_p[l_0];
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



	uint32_t ia_bl = *(uint32_t *)(NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1]);
	NALI_CACHE_P_D_BL_P[1] += sizeof(uint32_t);
	// model_il = ia_bl / 2 / sizeof(uint32_t);
	model_il = ia_bl / sizeof(uint32_t);

	// m_ai_index_count_p = malloc(sizeof(uint32_t) * model_il * 2);
	v_i_p = malloc(sizeof(uint32_t) * model_il * 2);
	// m_ai_vkdevicesize_p = malloc(sizeof(VkDeviceSize) * model_il);

	index_bl_p = malloc(sizeof(uint32_t) * model_il);
	// attribute_bl_p = malloc(sizeof(uint32_t) * model_il);
	uint32_t l_step = 0;
	while (l_step != ia_bl)
	{
		// index_bl_p[l_step / (sizeof(uint32_t) * 2)] = *(uint32_t *)(data_p + step);
		index_bl_p[l_step / sizeof(uint32_t)] = *(uint32_t *)(NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1]);
		NALI_CACHE_P_D_BL_P[1] += sizeof(uint32_t);

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
		memcpy(index_p[l_0], NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1], index_bl_p[l_0]);
		NALI_CACHE_P_D_BL_P[1] += index_bl_p[l_0];
		v_i_p[l_0 * 2 + 1] = index_bl_p[l_0] / sizeof(uint32_t);
	}

	lcm_rgba_bl = *(uint8_t *)(NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1]);
	NALI_CACHE_P_D_BL_P[1] += sizeof(uint8_t);
	lcm_rgba_bl *= 4 * sizeof(float);
	rgba_p = malloc(lcm_rgba_bl);
	memcpy(rgba_p, NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1], lcm_rgba_bl);
	NALI_CACHE_P_D_BL_P[1] += lcm_rgba_bl;
	//apply color
	for (uint32_t l_0 = 0; l_0 < lcm_rgba_bl / sizeof(float); ++l_0)
	{
		rgba_p[l_0] = pow(rgba_p[l_0], 1.0F / 5.0F);
	}

	a_bl = NALI_CACHE_P_D_BL_P[0] - NALI_CACHE_P_D_BL_P[1];

	//j1c1
	uint32_t l_size = a_bl / (sizeof(float) * 3 + 2);
	a_bl += l_size * 2;
	a_p = malloc(a_bl);
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
	for (uint32_t l_1 = 0; l_1 < l_size; ++l_1)
	{
		memcpy(a_p + l_1 * (sizeof(float) * 3 + sizeof(uint32_t)), NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1], sizeof(float) * 3 + 2);
		memset((a_p + l_1 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 2)), 0, 2);
		NALI_CACHE_P_D_BL_P[1] += sizeof(float) * 3 + 2;
	}

	lcmv_set();
	lc_vkdevicesize = NALI_LC_MVP_BL + lcm_rgba_bl;

	//b
	for (uint32_t l_0 = 0; l_0 < lcm_joint_count_bl; ++l_0)
	{
		lc_vkdevicesize += lcm_joint_count_p[l_0] * sizeof(float) * 16 * 2 + lcm_joint_count_p[l_0] * sizeof(float) * 4 * 3;
	}

	for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	{
		v_i_p[l_0 * 2] = lc_vkdevicesize;
		lc_vkdevicesize += index_bl_p[l_0];
	}

	// for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	// {
	// 	m_ai_vkdevicesize_p[l_0] = m_vkdevicesize;
	// 	m_vkdevicesize += attribute_bl_p[l_0];
	// }
	v_a_vkdevicesize_array[0] = lc_vkdevicesize;
	lc_vkdevicesize += a_bl;

	lc_vkdevicesize = (lc_vkdevicesize + 63) & ~63;
}

void lcm_vk()
{
	lcmv_vk();

	uint32_t
		step = NALI_LC_MVP_BL;

	memcpy(lc_vkbuffer_p + step, rgba_p, lcm_rgba_bl);
	step += lcm_rgba_bl;

	//s0-ssboa default
	uint16_t l_bone_bl = 0;
	// uint8_t keyframe = 75;
	for (uint32_t l_0 = 0; l_0 < lcm_joint_count_bl; ++l_0)
	{
		memcpy(lc_vkbuffer_p + step, i_bindpose_p + l_bone_bl * 16, sizeof(float) * 16 * lcm_joint_count_p[l_0]);
		step += sizeof(float) * 16 * lcm_joint_count_p[l_0];

		memcpy(lc_vkbuffer_p + step, bindpose_p + l_bone_bl * 16, sizeof(float) * 16 * lcm_joint_count_p[l_0]);
		step += sizeof(float) * 16 * lcm_joint_count_p[l_0];

		uint32_t l_s_step = step;
		for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
		{
			// // for (uint8_t l_2 = 0; l_2 < 3; ++l_2)
			// // {
			// // 	// if (l_1 == 19)
			// // 	// {
			// // 	// 	*(float *)(m_vkbuffer_p + step + l_2 * sizeof(float)) = 1.5F;
			// // 	// }
			// // 	// else
			// // 	// {
			// // 		*(float *)(m_vkbuffer_p + step + l_2 * sizeof(float)) = 1.0F;
			// // 	// }
			// // }

			// uint8_t l_key = 255;

			// for (uint8_t l_2 = 0; l_2 < m_bone_p[l_bone_bl + l_1].time_s_bl; ++l_2)
			// {
			// 	if (m_bone_p[l_bone_bl + l_1].time_s_p[l_2] == keyframe)
			// 	{
			// 		l_key = l_2;
			// 		break;
			// 	}
			// }

			// if (l_key == 255)
			// {
			for (uint8_t l_2 = 0; l_2 < 3; ++l_2)
			{
				*(float *)(lc_vkbuffer_p + step + l_2 * sizeof(float)) = 1;
			}
			// }
			// else
			// {
			// 	memcpy(m_vkbuffer_p + step, m_bone_p[l_bone_bl + l_1].animation_s_p + l_key * 3, sizeof(float) * 3);
			// }

			//start end
			*(uint32_t *)(lc_vkbuffer_p + step + sizeof(float) * 3) = NALI_CACHE_P_BS_P[l_0][l_1] | NALI_CACHE_P_BE_P[l_0][l_1] << 8;
			step += sizeof(float) * 4;
		}

		uint32_t l_r_step = step;
		for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
		{
			// uint8_t l_key = 255;

			// for (uint8_t l_2 = 0; l_2 < m_bone_p[l_bone_bl + l_1].time_r_bl; ++l_2)
			// {
			// 	if (m_bone_p[l_bone_bl + l_1].time_r_p[l_2] == keyframe)
			// 	{
			// 		l_key = l_2;
			// 		break;
			// 	}
			// }

			// if (l_key == 255)
			// {
			memcpy(lc_vkbuffer_p + step, m_m4x4_array + 12, sizeof(float) * 4);
			// }
			// else
			// {
			// 	memcpy(m_vkbuffer_p + step, m_bone_p[l_bone_bl + l_1].animation_r_p + l_key * 4, sizeof(float) * 4);
			// }

			// v4_q(0, MATH_D2R(90.0F), 0, m_vkbuffer_p + step);

			// if (l_1 == 12)
			// {
			// 	v4_q(0, MATH_D2R(90.0F), 0, m_vkbuffer_p + step);
			// }
			// else
			// {
			// 	memcpy(m_vkbuffer_p + step, m_m4x4_mat + 12, sizeof(float) * 4);
			// }

			// memcpy(m_vkbuffer_p + step, m_m4x4_mat + 12, sizeof(float) * 4);

			step += sizeof(float) * 4;
		}

		// memset(m_vkbuffer_p + step, 0, m_max_joint * sizeof(float) * 4);
		// *(float *)(m_vkbuffer_p + step + 4 * sizeof(float) * 4) = 0.5F;
		// step += m_max_joint * sizeof(float) * 4;

		uint8_t l_0_0 = 0;
		uint32_t l_step_0 = step;
		// memset(m_vkbuffer_p + step, 0, m_joint_count_p[l_0] * sizeof(float) * 4);

		uint32_t l_t_step = step;
		for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
		{
			// uint8_t l_key = 255;

			// for (uint8_t l_2 = 0; l_2 < m_bone_p[l_bone_bl + l_1].time_t_bl; ++l_2)
			// {
			// 	if (m_bone_p[l_bone_bl + l_1].time_t_p[l_2] == keyframe)
			// 	{
			// 		l_key = l_2;
			// 		break;
			// 	}
			// }

			// if (l_key == 255)
			// {
			memset(lc_vkbuffer_p + step, 0, sizeof(float) * 3);
			// }
			// else
			// {
			// 	memcpy(m_vkbuffer_p + step, m_bone_p[l_bone_bl + l_1].animation_t_p + l_key * 3, sizeof(float) * 3);
			// }
			step += sizeof(float) * 4;
		}

		for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
		{
			for (uint8_t l_2 = 0; l_2 < m_bone_p[l_bone_bl + l_1].joint_bl; ++l_2)
			// for (int16_t l_2 = srt_bone_p[l_bone_bl + l_1].joint_bl - 1; l_2 > -1; --l_2)
			{
				*(uint32_t *)(lc_vkbuffer_p + l_step_0 + sizeof(float) * 3) |= m_bone_p[l_bone_bl + l_1].joint_p[l_2] << l_0_0 * 8;

				++l_0_0;
				if (l_0_0 == 4)
				{
					l_0_0 = 0;
					l_step_0 += sizeof(float) * 4;
				}
			}
		}
		// step += sizeof(float) * 4 * m_joint_count_p[l_0];

		//s0-animate
		uint8_t key = 11;//80
		for (uint8_t l_1 = 0; l_1 < lckf_keyframe_p[0][key].bone_bl; ++l_1)
		{
			memcpy(lc_vkbuffer_p + l_s_step + lckf_keyframe_p[0][key].bone_p[l_1] * sizeof(float) * 4, lckf_keyframe_p[0][key].animation_s_p[l_1], sizeof(float) * 3);
			memcpy(lc_vkbuffer_p + l_r_step + lckf_keyframe_p[0][key].bone_p[l_1] * sizeof(float) * 4, lckf_keyframe_p[0][key].animation_r_p[l_1], sizeof(float) * 4);
			memcpy(lc_vkbuffer_p + l_t_step + lckf_keyframe_p[0][key].bone_p[l_1] * sizeof(float) * 4, lckf_keyframe_p[0][key].animation_t_p[l_1], sizeof(float) * 3);
		}

		// float q[4];
		// m_v4_q(MATH_D2R(90), 0, 0, q);
		// m_v4_q(MATH_D2R(90), 0, 0, m_vkbuffer_p + l_r_step + 1 * sizeof(float) * 4);

		//e0-animate

		l_bone_bl += lcm_joint_count_p[l_0];

		free(NALI_CACHE_P_BS_P[l_0]);
		free(NALI_CACHE_P_BE_P[l_0]);
	}

	free(NALI_CACHE_P_BS_P);
	free(NALI_CACHE_P_BE_P);
	//e0-ssboa default

	// //s0-ssboa file
	// uint8_t l_timeline = 0;
	// for (uint32_t l_0 = 0; l_0 < m_joint_count_bl; ++l_0)
	// {
	// 	l = 0;
	// 	for (uint8_t l_1 = 0; l_1 < m_joint_count_p[l_0]; ++l_1)
	// 	{
	// 		uint8_t l_key = 255;

	// 		// for (uint8_t l_2 = 0; l_2 < srt_bone_p[l].time_s_bl; ++l_2)
	// 		// {
	// 		// 	if (srt_bone_p[l].time_s_p[l_2] == l_timeline)
	// 		// 	{
	// 		// 		l_key = l_2;
	// 		// 		break;
	// 		// 	}
	// 		// }

	// 		if (l_key == 255)
	// 		{
	// 			for (uint8_t l_2 = 0; l_2 < 3; ++l_2)
	// 			{
	// 				*(float *)(m_vkbuffer_p + step + l_2 * sizeof(float)) = 1.0F;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			memcpy(m_vkbuffer_p + step, srt_bone_p[l].animation_s_p + l_key * 3, sizeof(float) * 3);
	// 		}

	// 		*(uint32_t *)(m_vkbuffer_p + step + sizeof(float) * 3) = 0;
	// 		step += sizeof(float) * 4;
	// 		++l;
	// 	}

	// 	l = 0;
	// 	for (uint8_t l_1 = 0; l_1 < m_joint_count_p[l_0]; ++l_1)
	// 	{
	// 		uint8_t l_key = 255;

	// 		for (uint8_t l_2 = 0; l_2 < srt_bone_p[l].time_r_bl; ++l_2)
	// 		{
	// 			if (srt_bone_p[l].time_r_p[l_2] == l_timeline)
	// 			{
	// 				l_key = l_2;
	// 				break;
	// 			}
	// 		}

	// 		// if (l_key == 255)
	// 		// {
	// 		// 	memcpy(m_vkbuffer_p + step, m_m4x4_mat + 12, sizeof(float) * 4);
	// 		// }
	// 		// else
	// 		// {
	// 			// memcpy(m_vkbuffer_p + step, srt_bone_p[l].animation_r_p + l_key * 4, sizeof(float) * 4);

	// 			// v4_q(0, MATH_D2R(-15.0F), 0, m_vkbuffer_p + step);

	// 			// *(float *)(m_vkbuffer_p + step) = (srt_bone_p[l].animation_r_p + l_key * 4)[0];
	// 			// *(float *)(m_vkbuffer_p + step + sizeof(float)) = (srt_bone_p[l].animation_r_p + l_key * 4)[1] ;
	// 			// *(float *)(m_vkbuffer_p + step + sizeof(float) * 2) = (srt_bone_p[l].animation_r_p + l_key * 4)[2];
	// 			// *(float *)(m_vkbuffer_p + step + sizeof(float) * 3) = (srt_bone_p[l].animation_r_p + l_key * 4)[3];

	// 			// *(float *)(m_vkbuffer_p + step) = (srt_bone_p[l].animation_r_p + l_key * 4)[3];
	// 			// *(float *)(m_vkbuffer_p + step + sizeof(float)) = (srt_bone_p[l].animation_r_p + l_key * 4)[0];
	// 			// *(float *)(m_vkbuffer_p + step + sizeof(float) * 2) = (srt_bone_p[l].animation_r_p + l_key * 4)[1];
	// 			// *(float *)(m_vkbuffer_p + step + sizeof(float) * 3) = (srt_bone_p[l].animation_r_p + l_key * 4)[2];
	// 		// }

	// 		step += sizeof(float) * 4;
	// 		++l;
	// 	}

	// 	l = 0;
	// 	for (uint8_t l_1 = 0; l_1 < m_joint_count_p[l_0]; ++l_1)
	// 	{
	// 		uint8_t l_key = 255;

	// 		// for (uint8_t l_2 = 0; l_2 < srt_bone_p[l].time_t_bl; ++l_2)
	// 		// {
	// 		// 	if (srt_bone_p[l].time_t_p[l_2] == l_timeline)
	// 		// 	{
	// 		// 		l_key = l_2;
	// 		// 		break;
	// 		// 	}
	// 		// }

	// 		if (l_key == 255)
	// 		{
	// 			memset(m_vkbuffer_p + step, 0, sizeof(float) * 3);
	// 		}
	// 		else
	// 		{
	// 			memcpy(m_vkbuffer_p + step, srt_bone_p[l].animation_t_p + l_key * 3, sizeof(float) * 3);
	// 		}

	// 		*(uint32_t *)(m_vkbuffer_p + step + sizeof(float) * 3) = 0;
	// 		step += sizeof(float) * 4;
	// 		++l;
	// 	}
	// }
	// //e0-ssboa file

	// //ssbob
	// for (uint32_t l_0 = 0; l_0 < m_joint_count_bl; ++l_0)
	// {
	// 	uint32_t l_step_0 = step;

	// 	l = 0;
	// 	for (uint8_t l_1 = 0; l_1 < m_joint_count_p[l_0]; ++l_1)
	// 	{
	// 		if (srt_bone_p[l].joint_s_p == NULL)
	// 		{
	// 			for (uint32_t l_2 = 0; l_2 < 3; ++l_2)
	// 			{
	// 				*(float *)(m_vkbuffer_p + step + l_2 * sizeof(float)) = 1.0F;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			memcpy(m_vkbuffer_p + step, srt_bone_p[l].joint_s_p, sizeof(float) * 3);
	// 		}

	// 		*(uint32_t *)(m_vkbuffer_p + step + sizeof(float) * 3) = 0;
	// 		step += sizeof(float) * 4;
	// 		++l;
	// 	}

	// 	l = 0;
	// 	uint8_t l_0_0 = 0;
	// 	for (uint8_t l_1 = 0; l_1 < m_joint_count_p[l_0]; ++l_1)
	// 	{
	// 		for (uint8_t l_2 = 0; l_2 < srt_bone_p[l].joint_bl; ++l_2)
	// 		// for (int16_t l_2 = srt_bone_p[l].joint_bl - 1; l_2 > -1; --l_2)
	// 		{
	// 			*(uint32_t *)(m_vkbuffer_p + l_step_0 + sizeof(float) * 3) |= srt_bone_p[l].joint_p[l_2] << l_0_0 * 8;

	// 			++l_0_0;
	// 			if (l_0_0 == 4)
	// 			{
	// 				l_0_0 = 0;
	// 				l_step_0 += sizeof(float) * 4;
	// 			}
	// 		}
	// 		++l;
	// 	}

	// 	l = 0;
	// 	for (uint8_t l_1 = 0; l_1 < m_joint_count_p[l_0]; ++l_1)
	// 	{
	// 		if (srt_bone_p[l].joint_r_p == NULL)
	// 		{
	// 			memcpy(m_vkbuffer_p + step, m_m4x4_mat + 12, sizeof(float) * 4);
	// 		}
	// 		else
	// 		{
	// 			memcpy(m_vkbuffer_p + step, srt_bone_p[l].joint_r_p, sizeof(float) * 4);
	// 		}
	// 		step += sizeof(float) * 4;
	// 		++l;
	// 	}

	// 	l = 0;
	// 	for (uint8_t l_1 = 0; l_1 < m_joint_count_p[l_0]; ++l_1)
	// 	{
	// 		if (srt_bone_p[l].joint_t_p == NULL)
	// 		{
	// 			memset(m_vkbuffer_p + step, 0, sizeof(float) * 3);
	// 		}
	// 		else
	// 		{
	// 			memcpy(m_vkbuffer_p + step, srt_bone_p[l].joint_t_p, sizeof(float) * 3);
	// 		}
	// 		//start end
	// 		*(uint32_t *)(m_vkbuffer_p + step + sizeof(float) * 3) = NALI_CACHE_P_BS_P[l_0][l_1] | NALI_CACHE_P_BE_P[l_0][l_1] << 8;
	// 		step += sizeof(float) * 4;
	// 		++l;
	// 	}

	// 	free(NALI_CACHE_P_BS_P[l_0]);
	// 	free(NALI_CACHE_P_BE_P[l_0]);
	// }

	// free(bs_p);
	// free(be_p);
	// bs_p = NULL;
	// be_p = NULL;

	for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	{
		memcpy(lc_vkbuffer_p + step, index_p[l_0], index_bl_p[l_0]);
		step += index_bl_p[l_0];
	}

	// for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	// {
	// 	memcpy(m_vkbuffer_p + step, attribute_p[l_0], attribute_bl_p[l_0]);
	// 	step += attribute_bl_p[l_0];
	// }
	memcpy(lc_vkbuffer_p + step, a_p, a_bl);
	step += a_bl;

	//update vkbuffer
	vkFlushMappedMemoryRanges(vkqd_vkdevice_p[vk_device], 1, &(VkMappedMemoryRange)
	{
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = lc_vkdevicememory,
		.offset = 0,
		.size = (step + 63) & ~63,
		// .size = step,
		// .size = 64,
		// .size = VK_WHOLE_SIZE,
		// .size = m_vkdevicesize
		.pNext = VK_NULL_HANDLE
	});
}

void lcm_free()
{

}