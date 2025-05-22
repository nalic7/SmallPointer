uint32_t
	s_width = 1,
	s_height = 1;

uint8_t
	s_pointer_id = 1,
	s_surface_state = 0,
	s_pointer_state = 0,

	s_key;

float
	s_pointer_x = 0, s_pointer_y = 0,
	s_rx = 0.0F,
	s_ry = 0.0F,
	s_rz = MATH_D2R(180.0F),

	s_tx = 0.0F,
	s_ty = -1.5F,
	s_tz = -2.0F,

	s_deltra = 0;

static float
	q_v4_array[4],
	q0_m4x4_array[16],
	q1_m4x4_array[16],
	q2_m4x4_array[16],

	lt_v4_array[4],
	gt_v4_array[4];

void s_set()
{
	memcpy(lt_v4_array, m_m4x4_array + 12, sizeof(float) * 4);
	memcpy(q0_m4x4_array, m_m4x4_array, sizeof(float) * 16);
}

void s_loop()
{
	if (s_key & NALI_KEY_W)
		lt_v4_array[2] = 1.0F * s_deltra;
	else if (s_key & NALI_KEY_S)
		lt_v4_array[2] = -1.0F * s_deltra;
	else
		lt_v4_array[2] = 0;

	if (s_key & NALI_KEY_A)
		lt_v4_array[0] = -1.0F * s_deltra;
	else if (s_key & NALI_KEY_D)
		lt_v4_array[0] = 1.0F * s_deltra;
	else
		lt_v4_array[0] = 0;

	if (s_key & NALI_KEY_LEFTCTRL)
		s_ty += 1.0F * s_deltra;
	if (s_key & NALI_KEY_SPACE)
		s_ty -= 1.0F * s_deltra;

	s_rx += s_pointer_y * s_deltra;
	s_ry += s_pointer_x * s_deltra;

	if (s_rx > MATH_D2R(90.0F+45))
	{
		s_rx = MATH_D2R(90.0F+45);
	}
	else if (s_rx < MATH_D2R(-90.0F-45))
	{
		s_rx = MATH_D2R(-90.0F-45);
	}

	// nali_log("0 s_ry %f", s_ry)
	s_ry = MATH_NORMALIZE(s_ry, MATH_D2R(360.0F));
	// nali_log("1 s_ry %f", s_ry)

	s_pointer_x = 0;
	s_pointer_y = 0;

	if (s_pointer_state & NALI_P_STATE_REROTATE)
	{
		s_rx = 0;
		s_ry = 0;
		s_pointer_state &= 0xFFu - NALI_P_STATE_REROTATE;
	}


	memcpy(lc_vkbuffer_p, m_m4x4_array, sizeof(float) * 16);

	m_v4_q(0, 0, s_rz, q_v4_array);
	m_v4_q2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, lc_vkbuffer_p, sizeof(float) * 16);
	m_m4x4_m(q1_m4x4_array, q0_m4x4_array, lc_vkbuffer_p);

	m_v4_q(0, s_ry, 0, q_v4_array);
	m_v4_q2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, lc_vkbuffer_p, sizeof(float) * 16);
	m_m4x4_m(q1_m4x4_array, q0_m4x4_array, lc_vkbuffer_p);

	m_v4_m4(lc_vkbuffer_p, lt_v4_array, gt_v4_array);

	m_v4_q(s_rx, 0, 0, q_v4_array);
	m_v4_q2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, lc_vkbuffer_p, sizeof(float) * 16);
	m_m4x4_m(q1_m4x4_array, q0_m4x4_array, lc_vkbuffer_p);

	memcpy(q2_m4x4_array, m_m4x4_array, sizeof(float) * 16);

	// m_v4_m4(m_vkbuffer_p, lt_v4_array, q2_m4x4_array + 12);
	s_tx += gt_v4_array[0] / gt_v4_array[3];
	// s_ty += gt_v4_array[1] / gt_v4_array[3];
	s_tz += gt_v4_array[2] / gt_v4_array[3];
	q2_m4x4_array[12] = s_tx;
	q2_m4x4_array[13] = s_ty;
	q2_m4x4_array[14] = s_tz;
	memcpy(q1_m4x4_array, lc_vkbuffer_p, sizeof(float) * 16);
	m_m4x4_m(q2_m4x4_array, q1_m4x4_array, lc_vkbuffer_p);
	// ((float *)m_vkbuffer_p)[12] = s_tx;
	// ((float *)m_vkbuffer_p)[13] = s_ty;
	// ((float *)m_vkbuffer_p)[14] = s_tz;
}