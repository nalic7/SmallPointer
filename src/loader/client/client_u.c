NALI_LB_CHT *lcu_ch_p;
uint8_t lcu_ch_bl = 0;
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

//s0-timeline
static float _rt_p[3 + 2];
//e0-timeline
void lcu_update()
{
	//use timeline
	for (uint8_t l_0 = 0; l_0 < 3 + 2; ++l_0)
	{
		_rt_p[l_0] += (lcu_lb_u.rt_p[l_0] - _rt_p[l_0]) * lc_delta;
	}

	//lcu_lb_u.rt_p
	lb_u_update(lc_vkbuffer_p, _rt_p[4], q_v4_array, q0_m4x4_array, q1_m4x4_array);

	mv4_q(_rt_p[3], 0, 0, q_v4_array);
	mv4_q2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, lc_vkbuffer_p, sizeof(float) * 16);
	mm4x4_m(q1_m4x4_array, q0_m4x4_array, lc_vkbuffer_p);

	memcpy(q2_m4x4_array, mm4x4_array, sizeof(mm4x4_array));

	q2_m4x4_array[12] = _rt_p[0];
	q2_m4x4_array[13] = _rt_p[1];
	q2_m4x4_array[14] = _rt_p[2];
	memcpy(q1_m4x4_array, lc_vkbuffer_p, sizeof(float) * 16);
	mm4x4_m(q2_m4x4_array, q1_m4x4_array, lc_vkbuffer_p);
	// ((float *)m_vkbuffer_p)[12] = s_tx;
	// ((float *)m_vkbuffer_p)[13] = s_ty;
	// ((float *)m_vkbuffer_p)[14] = s_tz;
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

	memcpy(lcu_ch_p, lc_net_p + lc_net_bl, sizeof(NALI_LB_CHT) * lcu_ch_bl);
	lc_net_bl += sizeof(NALI_LB_CHT);
}