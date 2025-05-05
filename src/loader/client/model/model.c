typedef struct
{
	uint8_t
		*joint_p,

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
} nali_bone;

static nali_bone *nali_bone_p;

static uint8_t
	*joint_count_p,
	joint_count_size;

static uint32_t **index_p;
static uint32_t *index_size_p;
static void **attribute_p;
static uint32_t *attribute_size_p;
static uint32_t model_size;

static float *rgba_p;
static uint32_t rgba_size;

void lcm_init()
{
	long step = 0;
	long data_size;
	void *data_p = f_read(NALI_HOME "asset.bin", &data_size);

	joint_count_size = *(uint8_t *)data_p;
	step += sizeof(uint8_t);

	joint_count_p = malloc(joint_count_size);
	memcpy(joint_count_p, data_p + step, joint_count_size);
	step += joint_count_size;

	uint16_t bone_size = 0;
	nali_bone_p = malloc(0);
	uint16_t l = 0;
	for (uint8_t l_0 = 0; l_0 < joint_count_size; ++l_0)
	{
		nali_bone_p = realloc(nali_bone_p, sizeof(nali_bone) * (bone_size + joint_count_p[l_0]));

		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			uint8_t size = *(uint8_t *)(data_p + step);
			step += sizeof(uint8_t);

			nali_bone_p[l] = (nali_bone){0};
			nali_bone_p[l].joint_p = malloc(size);
			memcpy(nali_bone_p[l].joint_p, data_p + step, size);
			step += size;
			++l;
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
						nali_bone_p[l].joint_s_p = malloc(sizeof(float) * 3);
						memcpy(nali_bone_p[l].joint_s_p, data_p + step, sizeof(float) * 3);
						step += sizeof(float) * 3;
					}
					++bit_step;
					break;
				case 1:
					if (joint_head_p[l_0] >> l_1 & 1)
					{
						nali_bone_p[l].joint_r_p = malloc(sizeof(float) * 4);
						memcpy(nali_bone_p[l].joint_r_p, data_p + step, sizeof(float) * 4);
						step += sizeof(float) * 4;
					}
					++bit_step;
					break;
				default://2
					if (joint_head_p[l_0] >> l_1 & 1)
					{
						nali_bone_p[l].joint_t_p = malloc(sizeof(float) * 3);
						memcpy(nali_bone_p[l].joint_t_p, data_p + step, sizeof(float) * 3);
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

		nali_bone_p[l].time_t_size = time_size;
		nali_bone_p[l].time_t_p = malloc(time_size);
		memcpy(nali_bone_p[l].time_t_p, data_p + step, time_size);
		step += time_size;
		l_step += time_size;

		nali_bone_p[l].animation_t_p = malloc(sizeof(float) * 3 * time_size);
		memcpy(nali_bone_p[l].animation_t_p, data_p + step, sizeof(float) * 3 * time_size);
		step += sizeof(float) * 3 * time_size;
		l_step += sizeof(float) * 3 * time_size;

		time_size = *(uint8_t *)(data_p + step);
		step += sizeof(uint8_t);
		l_step += sizeof(uint8_t);

		nali_bone_p[l].time_r_size = time_size;
		nali_bone_p[l].time_r_p = malloc(time_size);
		memcpy(nali_bone_p[l].time_r_p, data_p + step, time_size);
		step += time_size;
		l_step += time_size;

		nali_bone_p[l].animation_r_p = malloc(sizeof(float) * 4 * time_size);
		memcpy(nali_bone_p[l].animation_r_p, data_p + step, sizeof(float) * 4 * time_size);
		step += sizeof(float) * 4 * time_size;
		l_step += sizeof(float) * 4 * time_size;

		time_size = *(uint8_t *)(data_p + step);
		step += sizeof(uint8_t);
		l_step += sizeof(uint8_t);

		nali_bone_p[l].time_s_size = time_size;
		nali_bone_p[l].time_s_p = malloc(time_size);
		memcpy(nali_bone_p[l].time_s_p, data_p + step, time_size);
		step += time_size;
		l_step += time_size;

		nali_bone_p[l].animation_s_p = malloc(sizeof(float) * 3 * time_size);
		memcpy(nali_bone_p[l].animation_s_p, data_p + step, sizeof(float) * 3 * time_size);
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

	rgba_size = data_size - step;
	rgba_p = malloc(rgba_size);
	memcpy(rgba_p, data_p + step, rgba_size);

	lcmv_init();
}

void lcm_vk()
{
	lcmv_vk();

	uint32_t step = NALI_LC_V0;
	for (uint32_t l_0 = 0; l_0 < joint_count_size; ++l_0)
	{
		memcpy(m_vkbuffer_p + step, , );
		step += ;

		memcpy(m_vkbuffer_p + step, , );
		step += ;

		memcpy(m_vkbuffer_p + step, , );
		step += ;

		memcpy(m_vkbuffer_p + step, , );
		step += ;
	}

	for (uint32_t l_0 = 0; l_0 < model_size; ++l_0)
	{
		memcpy(m_vkbuffer_p + step, rgba_p, rgba_size);
		step += rgba_size;

		memcpy(m_vkbuffer_p + step, index_p + index_size_p[l_0], index_size_p[l_0]);
		step += index_size_p[l_0];

		memcpy(m_vkbuffer_p + step, attribute_p + attribute_size_p[l_0], attribute_size_p[l_0]);
		step += attribute_size_p[l_0];
	}
}