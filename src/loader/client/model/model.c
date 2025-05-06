uint32_t
	*m_ji_p,
	*m_ai_p;

typedef struct
{
	uint8_t
		//8->32
		*joint_p,
		joint_size,

		*time_s_p,
		time_s_size,
		*time_r_p,
		time_r_size,
		*time_t_p,
		time_t_size;

	float
		*joint_s_p,
		*joint_r_p,
		*joint_t_p,
		
		*animation_s_p,
		*animation_r_p,
		*animation_t_p;
} srt_bone;

static srt_bone *srt_bone_p;

uint32_t m_max_joint = 0;
static uint8_t
	*joint_count_p,
	joint_count_size;

//8->32
static uint8_t
	**bs_p,
	**be_p;

static uint32_t **index_p;
static uint32_t *index_size_p;
static void **attribute_p;
static uint32_t *attribute_size_p;
static uint32_t model_size;

static float *rgba_p;
uint32_t m_rgba_size;

void lcm_init()
{
	long step = 0;
	long data_size;
	void *data_p = f_read(NALI_HOME "asset.bin", &data_size);

	joint_count_size = *(uint8_t *)data_p;
	step += sizeof(uint8_t);

	m_ji_p = malloc(sizeof(uint32_t) * joint_count_size);

	bs_p = malloc(sizeof(uint8_t *) * joint_count_size);
	be_p = malloc(sizeof(uint8_t *) * joint_count_size);

	joint_count_p = malloc(joint_count_size);
	memcpy(joint_count_p, data_p + step, joint_count_size);
	step += joint_count_size;

	uint16_t bone_size = 0;
	srt_bone_p = malloc(0);
	uint16_t l = 0;
	for (uint8_t l_0 = 0; l_0 < joint_count_size; ++l_0)
	{
		if (m_max_joint < joint_count_p[l_0])
		{
			m_max_joint = joint_count_p[l_0];
		}

		m_ji_p[l_0] = joint_count_p[l_0] * 2 * sizeof(uint32_t);

		bs_p[l_0] = malloc(joint_count_p[l_0]);
		be_p[l_0] = malloc(joint_count_p[l_0]);
		bs_p[l_0][0] = 0;

		srt_bone_p = realloc(srt_bone_p, sizeof(srt_bone) * (bone_size + joint_count_p[l_0]));

		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			uint8_t size = *(uint8_t *)(data_p + step);
			step += sizeof(uint8_t);

			srt_bone_p[l] = (srt_bone){0};
			srt_bone_p[l].joint_size = size;
			srt_bone_p[l].joint_p = malloc(size);
			memcpy(srt_bone_p[l].joint_p, data_p + step, size);
			step += size;

			if (l_1 != 0)
			{
				bs_p[l_0][l_1] = be_p[l_0][l_1 - 1];
			}
			be_p[l_0][l_1] = bs_p[l_0][l_1] + size;
			++l;

			m_ji_p[l_0] += size * sizeof(uint32_t);
		}

		bone_size += joint_count_p[l_0];
	}

	uint32_t joint_head_size = ceil(bone_size * 3.0F / 8);
	uint8_t *joint_head_p = malloc(joint_head_size);
	memcpy(joint_head_p, data_p + step, joint_head_size);
	step += joint_head_size;

	uint8_t
		bit_step = 0;
	l = 0;
	for (uint8_t l_0 = 0; l_0 < joint_head_size; ++l_0)
	{
		for (uint8_t l_1 = 0; l_1 < 8; ++l_1)
		{
			switch (bit_step)
			{
				case 0:
					if (joint_head_p[l_0] >> l_1 & 1)
					{
						srt_bone_p[l].joint_s_p = malloc(sizeof(float) * 3);
						memcpy(srt_bone_p[l].joint_s_p, data_p + step, sizeof(float) * 3);
						step += sizeof(float) * 3;
					}
					++bit_step;
					break;
				case 1:
					if (joint_head_p[l_0] >> l_1 & 1)
					{
						srt_bone_p[l].joint_r_p = malloc(sizeof(float) * 4);
						memcpy(srt_bone_p[l].joint_r_p, data_p + step, sizeof(float) * 4);
						step += sizeof(float) * 4;
					}
					++bit_step;
					break;
				default://2
					if (joint_head_p[l_0] >> l_1 & 1)
					{
						srt_bone_p[l].joint_t_p = malloc(sizeof(float) * 3);
						memcpy(srt_bone_p[l].joint_t_p, data_p + step, sizeof(float) * 3);
						step += sizeof(float) * 3;
						++l;
					}
					bit_step = 0;
			}
		}
	}

	uint32_t animation_size = *(uint32_t *)(data_p + step);
	step += sizeof(uint32_t);

	uint32_t l_step = 0;
	uint8_t time_size;
	l = 0;
	while (l_step != animation_size)
	{
		// /b\ 1
		time_size = *(uint8_t *)(data_p + step);
		step += sizeof(uint8_t);
		l_step += sizeof(uint8_t);

		srt_bone_p[l].time_t_size = time_size;
		srt_bone_p[l].time_t_p = malloc(time_size);
		memcpy(srt_bone_p[l].time_t_p, data_p + step, time_size);
		step += time_size;
		l_step += time_size;

		srt_bone_p[l].animation_t_p = malloc(sizeof(float) * 3 * time_size);
		memcpy(srt_bone_p[l].animation_t_p, data_p + step, sizeof(float) * 3 * time_size);
		step += sizeof(float) * 3 * time_size;
		l_step += sizeof(float) * 3 * time_size;

		time_size = *(uint8_t *)(data_p + step);
		step += sizeof(uint8_t);
		l_step += sizeof(uint8_t);

		srt_bone_p[l].time_r_size = time_size;
		srt_bone_p[l].time_r_p = malloc(time_size);
		memcpy(srt_bone_p[l].time_r_p, data_p + step, time_size);
		step += time_size;
		l_step += time_size;

		srt_bone_p[l].animation_r_p = malloc(sizeof(float) * 4 * time_size);
		memcpy(srt_bone_p[l].animation_r_p, data_p + step, sizeof(float) * 4 * time_size);
		step += sizeof(float) * 4 * time_size;
		l_step += sizeof(float) * 4 * time_size;

		time_size = *(uint8_t *)(data_p + step);
		step += sizeof(uint8_t);
		l_step += sizeof(uint8_t);

		srt_bone_p[l].time_s_size = time_size;
		srt_bone_p[l].time_s_p = malloc(time_size);
		memcpy(srt_bone_p[l].time_s_p, data_p + step, time_size);
		step += time_size;
		l_step += time_size;

		srt_bone_p[l].animation_s_p = malloc(sizeof(float) * 3 * time_size);
		memcpy(srt_bone_p[l].animation_s_p, data_p + step, sizeof(float) * 3 * time_size);
		step += sizeof(float) * 3 * time_size;
		l_step += sizeof(float) * 3 * time_size;
		++l;
	}

	uint32_t ia_size = *(uint32_t *)(data_p + step);
	step += sizeof(uint32_t);
	model_size = ia_size / 2 / sizeof(float);
	index_size_p = malloc(sizeof(uint32_t) * model_size);
	attribute_size_p = malloc(sizeof(uint32_t) * model_size);
	l_step = 0;
	while (l_step != ia_size)
	{
		index_size_p[l_step / (sizeof(uint32_t) * 2)] = *(uint32_t *)(data_p + step);
		step += sizeof(uint32_t);

		attribute_size_p[l_step / (sizeof(uint32_t) * 2)] = *(uint32_t *)(data_p + step);
		step += sizeof(uint32_t);

		l_step += sizeof(uint32_t) * 2;
	}

	index_p = malloc(sizeof(uint32_t *) * model_size);
	attribute_p = malloc(sizeof(void *) * model_size);

	for (uint32_t l_0 = 0; l_0 < model_size; ++l_0)
	{
		index_p[l_0] = malloc(index_size_p[l_0]);
		memcpy(index_p[l_0], data_p + step, index_size_p[l_0]);
		step += index_size_p[l_0];
	}
	for (uint32_t l_0 = 0; l_0 < model_size; ++l_0)
	{
		attribute_p[l_0] = malloc(attribute_size_p[l_0]);
		memcpy(attribute_p[l_0], data_p + step, attribute_size_p[l_0]);
		step += attribute_size_p[l_0];
	}

	m_rgba_size = data_size - step;
	rgba_p = malloc(m_rgba_size);
	memcpy(rgba_p, data_p + step, m_rgba_size);

	lcmv_init();
	m_vkdevicesize =
		NALI_LC_MVP_SIZE +
		m_rgba_size +
		//a
		m_max_joint * sizeof(float) * 3 * 2 +//s t
		m_max_joint * sizeof(float) * 4;//r

	//b
	l = 0;
	for (uint32_t l_0 = 0; l_0 < joint_count_size; ++l_0)
	{
		m_vkdevicesize += joint_count_p[l_0] * sizeof(uint32_t) * 2;//s e

		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			m_vkdevicesize += srt_bone_p[l].joint_size * sizeof(uint32_t);
			++l;
		}
	}

	for (uint32_t l_0 = 0; l_0 < model_size; ++l_0)
	{
		m_vkdevicesize += index_size_p[l_0];
		m_vkdevicesize += attribute_size_p[l_0];
	}
}

void lcm_vk()
{
	lcmv_vk();

	uint32_t
		l = 0,
		step = NALI_LC_MVP_SIZE;

	memcpy(m_vkbuffer_p + step, rgba_p, m_rgba_size);
	step += m_rgba_size;

	//ssboa
	memset(m_vkbuffer_p + step, 1, m_max_joint * sizeof(float) * 3);
	step += m_max_joint * sizeof(float) * 3;

	memset(m_vkbuffer_p + step, 0, m_max_joint * sizeof(float) * 4);
	step += m_max_joint * sizeof(float) * 4;

	memset(m_vkbuffer_p + step, 0, m_max_joint * sizeof(float) * 3);
	step += m_max_joint * sizeof(float) * 3;

	//ssbob
	for (uint32_t l_0 = 0; l_0 < joint_count_size; ++l_0)
	{
		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			*(uint32_t *)(m_vkbuffer_p + step) = bs_p[l_0][l_1];
			step += sizeof(uint32_t);
		}
		free(bs_p[l_0]);

		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			for (uint8_t l_2 = 0; l_2 < srt_bone_p[l].joint_size; ++l_2)
			{
				*(uint32_t *)(m_vkbuffer_p + step) = srt_bone_p[l].joint_p[l_2];
				step += sizeof(uint32_t);
			}
			++l;
		}

		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			*(uint32_t *)(m_vkbuffer_p + step) = be_p[l_0][l_1];
			step += sizeof(uint32_t);
		}
		free(be_p[l_0]);

		l = 0;
		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			if (srt_bone_p[l].joint_s_p == NULL)
			{
				memset(m_vkbuffer_p + step, 1, sizeof(float) * 3);
			}
			else
			{
				memcpy(m_vkbuffer_p + step, srt_bone_p[l].joint_s_p, sizeof(float) * 3);
			}
			step += sizeof(float) * 3;
			++l;
		}

		l = 0;
		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			if (srt_bone_p[l].joint_r_p == NULL)
			{
				memcpy(m_vkbuffer_p + step, m_m4x4_mat + 12, sizeof(float) * 4);
			}
			else
			{
				memcpy(m_vkbuffer_p + step, srt_bone_p[l].joint_r_p, sizeof(float) * 4);
			}
			step += sizeof(float) * 4;
			++l;
		}

		l = 0;
		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			if (srt_bone_p[l].joint_t_p == NULL)
			{
				memset(m_vkbuffer_p + step, 0, sizeof(float) * 3);
			}
			else
			{
				memcpy(m_vkbuffer_p + step, srt_bone_p[l].joint_t_p, sizeof(float) * 3);
			}
			step += sizeof(float) * 3;
			++l;
		}
	}

	free(bs_p);
	free(be_p);
	bs_p = NULL;
	be_p = NULL;

	for (uint32_t l_0 = 0; l_0 < model_size; ++l_0)
	{
		memcpy(m_vkbuffer_p + step, index_p + index_size_p[l_0], index_size_p[l_0]);
		step += index_size_p[l_0];
	}

	for (uint32_t l_0 = 0; l_0 < model_size; ++l_0)
	{
		memcpy(m_vkbuffer_p + step, attribute_p + attribute_size_p[l_0], attribute_size_p[l_0]);
		step += attribute_size_p[l_0];
	}
}