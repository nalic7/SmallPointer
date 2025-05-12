uint32_t
	*m_ji_p,
	*m_ai_index_count_p;
VkDeviceSize *m_ai_vkdevicesize_p;

typedef struct
{
	uint8_t
		//8->32
		*joint_p,
		joint_bl,

		*time_s_p,
		time_s_bl,
		*time_r_p,
		time_r_bl,
		*time_t_p,
		time_t_bl;

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
	*joint_count_p;
uint8_t m_joint_count_bl;

//8->32
static uint8_t
	**bs_p,
	**be_p;

static uint32_t **index_p;
static uint32_t *index_bl_p;
static uint8_t **attribute_p;
static uint32_t *attribute_bl_p;
static uint8_t model_il;

static float *rgba_p;
uint32_t m_rgba_bl;

void lcm_init()
{
	long step = 0;
	long data_bl;
	uint8_t *data_p = f_read(NALI_HOME "asset.bin", &data_bl);

	m_joint_count_bl = *(uint8_t *)data_p;
	step += sizeof(uint8_t);

	m_ji_p = malloc(sizeof(uint32_t) * m_joint_count_bl);

	bs_p = malloc(sizeof(uint8_t *) * m_joint_count_bl);
	be_p = malloc(sizeof(uint8_t *) * m_joint_count_bl);

	joint_count_p = malloc(m_joint_count_bl);
	memcpy(joint_count_p, data_p + step, m_joint_count_bl);
	step += m_joint_count_bl;

	uint16_t bone_bl = 0;
	srt_bone_p = malloc(0);
	uint16_t l = 0;
	for (uint8_t l_0 = 0; l_0 < m_joint_count_bl; ++l_0)
	{
		if (m_max_joint < joint_count_p[l_0])
		{
			m_max_joint = joint_count_p[l_0];
		}

		m_ji_p[l_0] = joint_count_p[l_0] * 2 * sizeof(uint32_t);

		bs_p[l_0] = malloc(joint_count_p[l_0]);
		be_p[l_0] = malloc(joint_count_p[l_0]);
		bs_p[l_0][0] = 0;

		srt_bone_p = realloc(srt_bone_p, sizeof(srt_bone) * (bone_bl + joint_count_p[l_0]));

		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			uint8_t size = *(uint8_t *)(data_p + step);
			step += sizeof(uint8_t);

			srt_bone_p[l] = (srt_bone){0};
			srt_bone_p[l].joint_bl = size;
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

		bone_bl += joint_count_p[l_0];
	}

	uint8_t joint_head_bl = ceil(bone_bl * 3.0F / 8);
	uint8_t *joint_head_p = malloc(joint_head_bl);
	memcpy(joint_head_p, data_p + step, joint_head_bl);
	step += joint_head_bl;

	uint8_t
		bit_step = 0;
	l = 0;
	for (uint8_t l_0 = 0; l_0 < joint_head_bl; ++l_0)
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

	uint32_t animation_bl = *(uint32_t *)(data_p + step);
	step += sizeof(uint32_t);

	uint32_t l_step = 0;
	uint8_t time_bl;
	l = 0;
	while (l_step != animation_bl)
	{
		// /b\ 1
		time_bl = *(uint8_t *)(data_p + step);
		step += sizeof(uint8_t);
		l_step += sizeof(uint8_t);

		srt_bone_p[l].time_t_bl = time_bl;
		srt_bone_p[l].time_t_p = malloc(time_bl);
		memcpy(srt_bone_p[l].time_t_p, data_p + step, time_bl);
		step += time_bl;
		l_step += time_bl;

		srt_bone_p[l].animation_t_p = malloc(sizeof(float) * 3 * time_bl);
		memcpy(srt_bone_p[l].animation_t_p, data_p + step, sizeof(float) * 3 * time_bl);
		step += sizeof(float) * 3 * time_bl;
		l_step += sizeof(float) * 3 * time_bl;

		time_bl = *(uint8_t *)(data_p + step);
		step += sizeof(uint8_t);
		l_step += sizeof(uint8_t);

		srt_bone_p[l].time_r_bl = time_bl;
		srt_bone_p[l].time_r_p = malloc(time_bl);
		memcpy(srt_bone_p[l].time_r_p, data_p + step, time_bl);
		step += time_bl;
		l_step += time_bl;

		srt_bone_p[l].animation_r_p = malloc(sizeof(float) * 4 * time_bl);
		memcpy(srt_bone_p[l].animation_r_p, data_p + step, sizeof(float) * 4 * time_bl);
		step += sizeof(float) * 4 * time_bl;
		l_step += sizeof(float) * 4 * time_bl;

		time_bl = *(uint8_t *)(data_p + step);
		step += sizeof(uint8_t);
		l_step += sizeof(uint8_t);

		srt_bone_p[l].time_s_bl = time_bl;
		srt_bone_p[l].time_s_p = malloc(time_bl);
		memcpy(srt_bone_p[l].time_s_p, data_p + step, time_bl);
		step += time_bl;
		l_step += time_bl;

		srt_bone_p[l].animation_s_p = malloc(sizeof(float) * 3 * time_bl);
		memcpy(srt_bone_p[l].animation_s_p, data_p + step, sizeof(float) * 3 * time_bl);
		step += sizeof(float) * 3 * time_bl;
		l_step += sizeof(float) * 3 * time_bl;
		++l;
	}

	uint32_t ia_bl = *(uint32_t *)(data_p + step);
	step += sizeof(uint32_t);
	model_il = ia_bl / 2 / sizeof(uint32_t);

	m_ai_index_count_p = malloc(sizeof(uint32_t) * model_il * 2);
	m_ai_vkdevicesize_p = malloc(sizeof(VkDeviceSize) * model_il);

	index_bl_p = malloc(sizeof(uint32_t) * model_il);
	attribute_bl_p = malloc(sizeof(uint32_t) * model_il);
	l_step = 0;
	while (l_step != ia_bl)
	{
		index_bl_p[l_step / (sizeof(uint32_t) * 2)] = *(uint32_t *)(data_p + step);
		step += sizeof(uint32_t);

		attribute_bl_p[l_step / (sizeof(uint32_t) * 2)] = *(uint32_t *)(data_p + step);
		step += sizeof(uint32_t);

		l_step += sizeof(uint32_t) * 2;
	}

	index_p = malloc(sizeof(uint32_t *) * model_il);
	attribute_p = malloc(sizeof(uint8_t *) * model_il);

	for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	{
		index_p[l_0] = malloc(index_bl_p[l_0]);
		memcpy(index_p[l_0], data_p + step, index_bl_p[l_0]);
		step += index_bl_p[l_0];
		m_ai_index_count_p[l_0 + 1] = index_bl_p[l_0] / sizeof(uint32_t);
	}
	for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	{
		//add extra byte
		uint32_t l_size = attribute_bl_p[l_0] / (sizeof(float) * 3 + 3);
		attribute_bl_p[l_0] += l_size;
		attribute_p[l_0] = malloc(attribute_bl_p[l_0]);
		// memcpy(attribute_p[l_0], data_p + step, attribute_bl_p[l_0]);
		// step += attribute_bl_p[l_0];
		for (uint32_t l_1 = 0; l_1 < l_size; ++l_1)
		{
			memcpy(attribute_p[l_0] + l_1 * (sizeof(float) * 3 + 3) + l_1, data_p + step, sizeof(float) * 3 + 3);
			*(attribute_p[l_0] + l_1 * (sizeof(float) * 3 + 3) + l_1 + (sizeof(float) * 3 + 3)) = 0;
			step += sizeof(float) * 3 + 3;
		}
	}

	m_rgba_bl = data_bl - step;
	rgba_p = malloc(m_rgba_bl);
	memcpy(rgba_p, data_p + step, m_rgba_bl);

	lcmv_init();
	m_vkdevicesize =
		NALI_LC_MVP_BL +
		m_rgba_bl +
		//a
		m_max_joint * sizeof(float) * 3 * 2 +//s t
		m_max_joint * sizeof(float) * 4;//r

	//b
	l = 0;
	for (uint32_t l_0 = 0; l_0 < m_joint_count_bl; ++l_0)
	{
		m_vkdevicesize +=
			joint_count_p[l_0] * sizeof(uint32_t) * 2 +//s e
			joint_count_p[l_0] * 3 * 2 * sizeof(float) +
			joint_count_p[l_0] * 4 * sizeof(float);

		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			m_vkdevicesize += srt_bone_p[l].joint_bl * sizeof(uint32_t);
			++l;
		}
	}

	for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	{
		m_ai_index_count_p[l_0] = m_vkdevicesize;
		m_vkdevicesize += index_bl_p[l_0];
	}

	for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	{
		m_ai_vkdevicesize_p[l_0] = m_vkdevicesize;
		m_vkdevicesize += attribute_bl_p[l_0];
	}

	m_vkdevicesize = (m_vkdevicesize + 63) & ~63;
}

void lcm_vk()
{
	lcmv_vk();

	uint32_t
		l = 0,
		step = NALI_LC_MVP_BL;

	memcpy(m_vkbuffer_p + step, rgba_p, m_rgba_bl);
	step += m_rgba_bl;

	//ssboa
	memset(m_vkbuffer_p + step, 1, m_max_joint * sizeof(float) * 3);
	step += m_max_joint * sizeof(float) * 3;

	memset(m_vkbuffer_p + step, 0, m_max_joint * sizeof(float) * 4);
	step += m_max_joint * sizeof(float) * 4;

	memset(m_vkbuffer_p + step, 0, m_max_joint * sizeof(float) * 3);
	step += m_max_joint * sizeof(float) * 3;

	//ssbob
	for (uint32_t l_0 = 0; l_0 < m_joint_count_bl; ++l_0)
	{
		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			*(uint32_t *)(m_vkbuffer_p + step) = bs_p[l_0][l_1];
			step += sizeof(uint32_t);
		}
		free(bs_p[l_0]);

		for (uint8_t l_1 = 0; l_1 < joint_count_p[l_0]; ++l_1)
		{
			for (uint8_t l_2 = 0; l_2 < srt_bone_p[l].joint_bl; ++l_2)
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

	for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	{
		memcpy(m_vkbuffer_p + step, index_p[l_0], index_bl_p[l_0]);
		step += index_bl_p[l_0];
	}

	for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	{
		memcpy(m_vkbuffer_p + step, attribute_p[l_0], attribute_bl_p[l_0]);
		step += attribute_bl_p[l_0];
	}

	//update vkbuffer
	vkFlushMappedMemoryRanges(m_vkdevice_p[m_device], 1, &(VkMappedMemoryRange)
	{
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = m_vkdevicememory,
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