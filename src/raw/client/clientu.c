//! lcm_vkbuffer_mp

NALI_LB_CHT *lcu_ch_p;
uint8_t lcu_ch_bl = 0;
uint8_t *lcu_xyz_p;

uint8_t lcu_rt_frame;
float lcu__rt_p[3 + 2];
float lcu_rt_p[3 + 2];
LB_U lcu_lb_u;

uint8_t lcu_k = 0;
float lcu_xy_p[2];

static float
	q_v4_array[4],
	q0_m4x4_array[16] =
	{
		1.0F, 0.0F, 0.0F, 0.0F,
		0.0F, 1.0F, 0.0F, 0.0F,
		0.0F, 0.0F, 1.0F, 0.0F,
		0.0F, 0.0F, 0.0F, 1.0F
	},
	q1_m4x4_array[16],
	q2_m4x4_array[16];

void lcu_set()
{
	lcu_ch_p = malloc(0);
	lcu_xyz_p = malloc(0);
}

static uint8_t lcu_state;
void lcu_update()
{
	lcu_state = 1;
	if (!lcu_rt_frame)
	{
		for (uint8_t l_2 = 0; l_2 < 3 + 2; ++l_2)
		{
			lcu__rt_p[l_2] = (lcu_lb_u.rt_p[l_2] - lcu_rt_p[l_2]) * NALI_LC_D;
		}
	}

	if (++lcu_rt_frame >= NALI_LC_MAX_F)
	{
		if (lcu_rt_frame == NALI_LC_MAX_F)
		{
			memcpy(lcu_rt_p, lcu_lb_u.rt_p, sizeof(float) * (3 + 2));
		}
		else
		{
			--lcu_rt_frame;
			lcu_state = 0;
		}
	}
	else
	{
		for (uint8_t l_2 = 0; l_2 < 3 + 2; ++l_2)
		{
			lcu_rt_p[l_2] += lcu__rt_p[l_2];
		}
	}

	//! use lcv_vkbuffer
//	if (lcu_state)
//	{
//		//lcu_lb_u.rt_p
//		lb_u_update(lcm_vkbuffer_mp, lcu_rt_p[4], q_v4_array, q0_m4x4_array, q1_m4x4_array);
//
//		mv4_q(lcu_rt_p[3], 0, 0, q_v4_array);
//		mv4_q2m(q_v4_array, q0_m4x4_array);
//		memcpy(q1_m4x4_array, lcm_vkbuffer_mp, sizeof(float) * 16);
//		mm4x4_m(q1_m4x4_array, q0_m4x4_array, lcm_vkbuffer_mp);
//
//		memcpy(q2_m4x4_array, mm4x4_array, sizeof(mm4x4_array));
//
//		q2_m4x4_array[12] = lcu_rt_p[0];
//		q2_m4x4_array[13] = lcu_rt_p[1];
//		q2_m4x4_array[14] = lcu_rt_p[2];
//		memcpy(q1_m4x4_array, lcm_vkbuffer_mp, sizeof(float) * 16);
//		mm4x4_m(q2_m4x4_array, q1_m4x4_array, lcm_vkbuffer_mp);
//		// ((float *)m_vkbuffer_p)[12] = s_tx;
//		// ((float *)m_vkbuffer_p)[13] = s_ty;
//		// ((float *)m_vkbuffer_p)[14] = s_tz;
//
//		vkFlushMappedMemoryRanges(_vkq_dv_p[vk_device], 1, &(VkMappedMemoryRange)
//		{
//			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
//			.memory = lcp_vkdevicememory,
//			.offset = 0,
//			.size = 16 * sizeof(float),
//			.pNext = VK_NULL_HANDLE
//		});
//	}
}

void lcu_send()
{
	mtx_lock(lb_mtx_t_p);

	*(lc_net_p + lc_net_bl) = lcu_k;
	lc_net_bl += sizeof(uint8_t);

	memcpy(lc_net_p + lc_net_bl, lcu_xy_p, sizeof(float) * 2);
	lc_net_bl += sizeof(float) * 2;

	mtx_unlock(lb_mtx_t_p);
}

void lcu_read()
{
	memcpy(&lcu_lb_u, lc_net_p + lc_net_bl, sizeof(LB_U));
	lc_net_bl += sizeof(LB_U);

	lcu_ch_bl = *(lc_net_p + lc_net_bl);
	lc_net_bl += sizeof(uint8_t);

	lcu_ch_p = realloc(lcu_ch_p, sizeof(NALI_LB_CHT) * lcu_ch_bl);
	lcu_xyz_p = realloc(lcu_xyz_p, 3 * lcu_ch_bl);
	memcpy(lcu_ch_p, lc_net_p + lc_net_bl, sizeof(NALI_LB_CHT) * lcu_ch_bl);
	lc_net_bl += sizeof(NALI_LB_CHT);
}

void lcu_free()
{
	free(lcu_ch_p);
	free(lcu_xyz_p);
}
