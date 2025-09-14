//.i vk
#ifdef SMPT_CM_VK
	VkDeviceSize r_cep_a_p[SMPTR_CE_MDlA];
	VkDeviceSize *r_cep_ai_p;
#endif

uint32_t
	*r_cep_ai_l_p,
	lcp_rgba_bl;

uint8_t
	*lcp_joint_count_p,
	lcp_joint_count_bl,
	**lcp_a_p;

#ifdef SMPT_CM_VK
	VkBuffer *smptr_ce_mdPvkbuffer;
	VkDeviceMemory *smptr_ce_mdPvkdevicememory;
	void **smptr_ce_mdPbuffer_map;
	VkDeviceSize *smptr_ce_mdPvkdevicesize;
#endif

struct m_bone
{
	uint8_t
		*joint_p,
		joint_bl;
};

static float **lcp_bp_p;
static struct m_bone *m_bone_p;

static uint32_t **index_p;
static uint32_t *index_bl_p;
static uint8_t *a_p_array[SMPTR_CE_MDlA];
static uint32_t a_bl_array[SMPTR_CE_MDlA];
static uint8_t model_il;

static float *rgba_p;

void smptr_ce_mdMset()
{
	lcp_joint_count_bl = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
	smptrPcache->d_bl_p[1] += sizeof(uint8_t);

	smptrPcache->bs_p = malloc(sizeof(uint16_t *) * lcp_joint_count_bl);
	smptrPcache->be_p = malloc(sizeof(uint16_t *) * lcp_joint_count_bl);

	lcp_joint_count_p = malloc(lcp_joint_count_bl);
	memcpy(lcp_joint_count_p, smptrPcache->d_p + smptrPcache->d_bl_p[1], lcp_joint_count_bl);
	smptrPcache->d_bl_p[1] += lcp_joint_count_bl;

	uint16_t l_bone_bl = 0;
	m_bone_p = malloc(0);

	lcp_bp_p = malloc(sizeof(float *) * lcp_joint_count_bl);
	lcp_a_p = malloc(sizeof(uint8_t *) * lcp_joint_count_bl);

	smptr_ce_mdPvkdevicesize = malloc(sizeof(VkDeviceSize) * lcp_joint_count_bl);

	for (uint8_t l_0 = 0; l_0 < lcp_joint_count_bl; ++l_0)
	{
		smptrPcache->bs_p[l_0] = malloc(sizeof(uint16_t) * lcp_joint_count_p[l_0]);
		smptrPcache->be_p[l_0] = malloc(sizeof(uint16_t) * lcp_joint_count_p[l_0]);
		smptrPcache->bs_p[l_0][0] = 0;

		m_bone_p = realloc(m_bone_p, sizeof(struct m_bone) * (l_bone_bl + lcp_joint_count_p[l_0]));
		lcp_bp_p[l_0] = malloc(sizeof(float) * 16 * 2 * (lcp_joint_count_p[l_0] - 1));

		for (uint8_t l_1 = 0; l_1 < lcp_joint_count_p[l_0]; ++l_1)
		{
			uint8_t size = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
			smptrPcache->d_bl_p[1] += sizeof(uint8_t);

			memset(m_bone_p + l_bone_bl + l_1, 0, sizeof(struct m_bone));
			if (l_1 != 0)
			{
				smptrPcache->bs_p[l_0][l_1] = smptrPcache->be_p[l_0][l_1 - 1];
			}
			m_bone_p[l_bone_bl + l_1].joint_bl = size;
			m_bone_p[l_bone_bl + l_1].joint_p = malloc(size);
			memcpy(m_bone_p[l_bone_bl + l_1].joint_p, smptrPcache->d_p + smptrPcache->d_bl_p[1], size);
			smptrPcache->be_p[l_0][l_1] = smptrPcache->bs_p[l_0][l_1] + size;
			smptrPcache->d_bl_p[1] += size;
		}
		smptrPcache->bs_p[l_0][0] = 0xFFFFu;

		l_bone_bl += lcp_joint_count_p[l_0];
	}

	for (uint8_t l_0 = 0; l_0 < lcp_joint_count_bl; ++l_0)
	{
		for (uint8_t l_1 = 0; l_1 < lcp_joint_count_p[l_0] - 1; ++l_1)
		{
			memcpy(lcp_bp_p[l_0] + l_1 * 16 * 2, smptrPcache->d_p + smptrPcache->d_bl_p[1] + l_1 * sizeof(float) * 16, sizeof(float) * 16);
			memcpy(lcp_bp_p[l_0] + l_1 * 16 * 2 + 16, lcp_bp_p[l_0] + l_1 * 16 * 2, sizeof(float) * 16);
			smptm_m4x4Mi(lcp_bp_p[l_0] + l_1 * 16 * 2 + 16);
		}
		smptrPcache->d_bl_p[1] += sizeof(float) * 16 * (lcp_joint_count_p[l_0] - 1);
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



	model_il = *(uint32_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]) / sizeof(uint32_t);
	smptrPcache->d_bl_p[1] += sizeof(uint32_t);

	// m_ai_index_count_p = malloc(sizeof(uint32_t) * model_il * 2);
	r_cep_ai_p = malloc(sizeof(VkDeviceSize) * model_il);
	r_cep_ai_l_p = malloc(sizeof(uint32_t) * model_il);
	// m_ai_vkdevicesize_p = malloc(sizeof(VkDeviceSize) * model_il);

	index_bl_p = malloc(sizeof(uint32_t) * model_il);
	// attribute_bl_p = malloc(sizeof(uint32_t) * model_il);
	uint32_t l_step = 0;
	while (l_step != model_il)
	{
		// index_bl_p[l_step / (sizeof(uint32_t) * 2)] = *(uint32_t *)(data_p + step);
		index_bl_p[l_step] = *(uint32_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
		smptrPcache->d_bl_p[1] += sizeof(uint32_t);

		// attribute_bl_p[l_step / (sizeof(uint32_t) * 2)] = *(uint32_t *)(data_p + step);
		// step += sizeof(uint32_t);

		// l_step += sizeof(uint32_t) * 2;
		++l_step;
	}

	index_p = malloc(sizeof(uint32_t *) * model_il);
	// attribute_p = malloc(sizeof(uint8_t *) * model_il);

	for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
	{
		index_p[l_0] = malloc(index_bl_p[l_0]);
		memcpy(index_p[l_0], smptrPcache->d_p + smptrPcache->d_bl_p[1], index_bl_p[l_0]);
		smptrPcache->d_bl_p[1] += index_bl_p[l_0];
		r_cep_ai_l_p[l_0] = index_bl_p[l_0] / sizeof(uint32_t);
	}

	lcp_rgba_bl = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
	smptrPcache->d_bl_p[1] += sizeof(uint8_t);
	lcp_rgba_bl *= 4 * sizeof(float);
	rgba_p = malloc(lcp_rgba_bl);
	memcpy(rgba_p, smptrPcache->d_p + smptrPcache->d_bl_p[1], lcp_rgba_bl);
	smptrPcache->d_bl_p[1] += lcp_rgba_bl;
	//.i pow rgba_p
	for (uint32_t l_0 = 0; l_0 < lcp_rgba_bl / sizeof(float); ++l_0)
	{
		rgba_p[l_0] = pow(rgba_p[l_0], 1.0F / 5.0F);
	}

	//.i c1
	uint32_t l_c1_bl = *(uint32_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
	smptrPcache->d_bl_p[1] += sizeof(uint32_t);

	a_bl_array[0] = l_c1_bl * (sizeof(float) * 3 + sizeof(uint32_t));
	a_p_array[0] = malloc(a_bl_array[0]);
	//.i c1 a
	for (uint32_t l_0 = 0; l_0 < l_c1_bl; ++l_0)
	{
		memcpy(a_p_array[0] + l_0 * (sizeof(float) * 3 + sizeof(uint32_t)), smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 3 + 1);
		memset((a_p_array[0] + l_0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 1)), 0, 3);
		smptrPcache->d_bl_p[1] += sizeof(float) * 3 + 1;
	}

	//.i c1j1
	a_bl_array[1] = smptrPcache->d_bl_p[0] - smptrPcache->d_bl_p[1];

	//.i c1j1 a
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
		memcpy(a_p_array[1] + l_0 * (sizeof(float) * 3 + sizeof(uint32_t)), smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 3 + 2);
		memset((a_p_array[1] + l_0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 2)), 0, 2);
		//t. s0-test j
		//memset((a_p_array[1] + l_0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 1)), 0, 3);
		//*(uint8_t *)(a_p_array[1] + l_0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 1)) = 40;
		//t. e0-test j
//		if ((smptrPcache->d_p + smptrPcache->d_bl_p[1] + sizeof(float) * 3 + 1) == 0)
//		{
//			SMPT_DBmN2L("nali_buffer c1j1 j0 %d", (smptrPcache->d_p + smptrPcache->d_bl_p[1] + sizeof(float) * 3 + 1))
//		}
		smptrPcache->d_bl_p[1] += sizeof(float) * 3 + 2;
	}

	//.i set default a
	for (uint8_t l_0 = 0; l_0 < lcp_joint_count_bl; ++l_0)
	{
		l_step = 0;
		lcp_a_p[l_0] = malloc(sizeof(float) * 4 * 3 * lcp_joint_count_p[l_0]);

		for (uint8_t l_1 = 0; l_1 < lcp_joint_count_p[l_0]; ++l_1)
		{
			//.i s
			for (uint8_t l_2 = 0; l_2 < 3; ++l_2)
			{
				*(float *)(lcp_a_p[l_0] + l_step + l_2 * sizeof(float)) = 1;
			}
			//.i b_s b_e
			*(uint32_t *)(lcp_a_p[l_0] + l_step + 3 * sizeof(float)) = smptrPcache->bs_p[l_0][l_1] | smptrPcache->be_p[l_0][l_1] << (8 + 8);
			//.t bs_p be_p
			//*(uint32_t *)(lcp_a_p[l_0] + l_step + 3 * sizeof(float)) = 51 | 51 << (8 + 8);
			l_step += 4 * sizeof(float);

			//.i r
			memcpy(lcp_a_p[l_0] + l_step, smptmPm4x4 + 12, 4 * sizeof(float));
			l_step += 4 * sizeof(float);

			//.i t
			memset(lcp_a_p[l_0] + l_step, 0, 4 * sizeof(float));
			//.t a->t vec4
			//*(uint32_t *)(lcp_a_p[l_0] + l_step + 3 * sizeof(float)) = 0xFFFFFFFFu;
			l_step += 4 * sizeof(float);
		}

		free(smptrPcache->bs_p[l_0]);
		free(smptrPcache->be_p[l_0]);
	}
	free(smptrPcache->bs_p);
	free(smptrPcache->be_p);

	//.i b
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
				//.t m_bone_p
				//*(uint32_t *)(lcp_a_p[l_0] + l_step + 3 * sizeof(float) + sizeof(float) * 4 * 2) |= 51 << l_0_0 * 8;

				if (++l_0_0 == 4)
				{
					l_step += sizeof(float) * 4 * 3;
					l_0_0 = 0;
				}
			}
		}

		l_bone_bl += lcp_joint_count_p[l_0];
	}
}


#ifdef SMPT_CM_VK
	void smptr_ce_mdMvk()
	{
		smptr_ce_mdPvkbuffer = malloc(sizeof(VkBuffer) * (1 + 2 * smpt_rd_vk_swcUimage));
		smptr_ce_mdPvkdevicememory = malloc(sizeof(VkDeviceMemory) * (1 + 2 * smpt_rd_vk_swcUimage));
		smptr_ce_mdPbuffer_map = malloc(sizeof(void *) * (1 + 2 * smpt_rd_vk_swcUimage));

		VkDeviceSize vkdevicesize = lcp_rgba_bl;

		for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
		{
			r_cep_ai_p[l_0] = vkdevicesize;
			vkdevicesize += index_bl_p[l_0];
		}

		for (uint32_t l_0 = 0; l_0 < SMPTR_CE_MDlA; ++l_0)
		{
			r_cep_a_p[l_0] = vkdevicesize;
			vkdevicesize += a_bl_array[l_0];
		}

		for (uint32_t l_0 = 0; l_0 < lcp_joint_count_bl; ++l_0)
		{
			smptr_ce_mdPvkdevicesize[l_0] = vkdevicesize;
			vkdevicesize += sizeof(float) * 16 * 2 * (lcp_joint_count_p[l_0] - 1);
		}

		VkMemoryRequirements vkmemoryrequirements;
		vkdevicesize = (vkdevicesize + (smpt_rd_vkUnon_coherent_atom_size - 1)) & ~(smpt_rd_vkUnon_coherent_atom_size - 1);
		SMPT_RD_VK_BFmMAKE(smpt_rd_vkUdevice, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_ce_mdPvkbuffer[0], smptr_ce_mdPvkdevicememory[0], vkmemoryrequirements)
		SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(smpt_rd_vkq_dvP[smpt_rd_vkUdevice], smptr_ce_mdPvkdevicememory[0], 0, vkdevicesize, 0, &smptr_ce_mdPbuffer_map[0]))

		//.i gui world
		for (uint8_t l0 = 1; l0 < (1 + 2 * smpt_rd_vk_swcUimage); ++l0)
		{
			SMPT_RD_VK_BFmMAKE(smpt_rd_vkUdevice, sizeof(float) * 16 * 2, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_ce_mdPvkbuffer[l0], smptr_ce_mdPvkdevicememory[l0], vkmemoryrequirements)
			SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(smpt_rd_vkq_dvP[smpt_rd_vkUdevice], smptr_ce_mdPvkdevicememory[l0], 0, sizeof(float) * 16 * 2, 0, &smptr_ce_mdPbuffer_map[l0]))
			memcpy(smptr_ce_mdPbuffer_map[l0], smptmPm4x4, sizeof(float) * 16);
			memcpy(smptr_ce_mdPbuffer_map[l0] + sizeof(float) * 16, smptmPm4x4, sizeof(float) * 16);
		}

		vkdevicesize = 0;

		//static rgba
		memcpy(smptr_ce_mdPbuffer_map[0] + vkdevicesize, rgba_p, lcp_rgba_bl);
		vkdevicesize += lcp_rgba_bl;

		//.i ai index
		for (uint32_t l_0 = 0; l_0 < model_il; ++l_0)
		{
			memcpy(smptr_ce_mdPbuffer_map[0] + vkdevicesize, index_p[l_0], index_bl_p[l_0]);
			vkdevicesize += index_bl_p[l_0];
		}

		//.i a index
		for (uint32_t l_0 = 0; l_0 < SMPTR_CE_MDlA; ++l_0)
		{
			memcpy(smptr_ce_mdPbuffer_map[0] + vkdevicesize, a_p_array[l_0], a_bl_array[l_0]);
			vkdevicesize += a_bl_array[l_0];
		}

		//.i UBOB
		for (uint32_t l_0 = 0; l_0 < lcp_joint_count_bl; ++l_0)
		{
			memcpy(smptr_ce_mdPbuffer_map[0] + vkdevicesize, lcp_bp_p[l_0], sizeof(float) * 16 * 2 * (lcp_joint_count_p[l_0] - 1));
			vkdevicesize += sizeof(float) * 16 * 2 * (lcp_joint_count_p[l_0] - 1);
		}

		vkFlushMappedMemoryRanges(smpt_rd_vkq_dvP[smpt_rd_vkUdevice], 1, &(VkMappedMemoryRange)
		{
			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
			.memory = smptr_ce_mdPvkdevicememory[0],
			.offset = 0,
			.size = (vkdevicesize + (smpt_rd_vkUnon_coherent_atom_size - 1)) & ~(smpt_rd_vkUnon_coherent_atom_size - 1),
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
		// 			*(float *)(smptr_ce_mdPbuffer_map + step + l_2 * sizeof(float)) = 1;
		// 		}

		// 		//start end
		// 		*(uint32_t *)(smptr_ce_mdPbuffer_map + step + sizeof(float) * 3) = smptrPcache->bs_p[l_0][l_1] | smptrPcache->be_p[l_0][l_1] << 8;
		// 		step += sizeof(float) * 4;
		// 	}

		// 	uint32_t l_r_step = step;
		// 	for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
		// 	{
		// 		memcpy(smptr_ce_mdPbuffer_map + step, m_m4x4_array + 12, sizeof(float) * 4);
		// 		step += sizeof(float) * 4;
		// 	}

		// 	uint8_t l_0_0 = 0;
		// 	uint32_t l_step_0 = step;

		// 	uint32_t l_t_step = step;
		// 	for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
		// 	{
		// 		memset(smptr_ce_mdPbuffer_map + step, 0, sizeof(float) * 3);
		// 		step += sizeof(float) * 4;
		// 	}

		// 	for (uint8_t l_1 = 0; l_1 < lcm_joint_count_p[l_0]; ++l_1)
		// 	{
		// 		for (uint8_t l_2 = 0; l_2 < m_bone_p[l_bone_bl + l_1].joint_bl; ++l_2)
		// 		{
		// 			*(uint32_t *)(smptr_ce_mdPbuffer_map + l_step_0 + sizeof(float) * 3) |= m_bone_p[l_bone_bl + l_1].joint_p[l_2] << l_0_0 * 8;

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
		// 		memcpy(smptr_ce_mdPbuffer_map + l_s_step + lckf_keyframe_p[0][key].bone_p[l_1] * sizeof(float) * 4, lckf_keyframe_p[0][key].animation_s_p[l_1], sizeof(float) * 3);
		// 		memcpy(smptr_ce_mdPbuffer_map + l_r_step + lckf_keyframe_p[0][key].bone_p[l_1] * sizeof(float) * 4, lckf_keyframe_p[0][key].animation_r_p[l_1], sizeof(float) * 4);
		// 		memcpy(smptr_ce_mdPbuffer_map + l_t_step + lckf_keyframe_p[0][key].bone_p[l_1] * sizeof(float) * 4, lckf_keyframe_p[0][key].animation_t_p[l_1], sizeof(float) * 3);
		// 	}
		// 	//e0-animate

		// 	l_bone_bl += lcm_joint_count_p[l_0];

		// 	free(smptrPcache->bs_p[l_0]);
		// 	free(smptrPcache->be_p[l_0]);
		// }

		// free(smptrPcache->bs_p);
		// free(smptrPcache->be_p);
		//e0-ssboa default
	}
#endif

void smptr_ce_mdMfree(uint32_t device)
{
	#ifdef SMPT_CM_VK
		for (uint8_t l0 = 0; l0 < 1 + 2 * smpt_rd_vk_swcUimage; ++l0)
		{
			VkDevice vkdevice = smpt_rd_vkq_dvP[device];
			vkUnmapMemory(smpt_rd_vkq_dvP[device], smptr_ce_mdPvkdevicememory[l0]);
			vkDestroyBuffer(vkdevice, smptr_ce_mdPvkbuffer[l0], VK_NULL_HANDLE);
			vkFreeMemory(vkdevice, smptr_ce_mdPvkdevicememory[l0], VK_NULL_HANDLE);
		}
		free(smptr_ce_mdPvkbuffer);
		free(smptr_ce_mdPvkdevicememory);
		free(smptr_ce_mdPbuffer_map);

		free(smptr_ce_mdPvkdevicesize);
	#endif

	for (uint8_t l_0 = 0; l_0 < lcp_joint_count_bl; ++l_0)
	{
		free(lcp_bp_p[l_0]);
		free(lcp_a_p[l_0]);

		free(m_bone_p[l_0].joint_p);
	}
	free(lcp_bp_p);
	free(lcp_a_p);

	free(lcp_joint_count_p);

	free(m_bone_p);

	free(r_cep_ai_p);
	free(r_cep_ai_l_p);
}
