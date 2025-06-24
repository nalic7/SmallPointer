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
	s_rz = M_D2R(180.0F),

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
	memcpy(lt_v4_array, mm4x4_array + 12, sizeof(float) * 4);
	memcpy(q0_m4x4_array, mm4x4_array, sizeof(mm4x4_array));
}

void s_loop()
{
	if (s_key & NALI_S_KEY_W)
		lt_v4_array[2] = 1.0F * s_deltra;
	else if (s_key & NALI_S_KEY_S)
		lt_v4_array[2] = -1.0F * s_deltra;
	else
		lt_v4_array[2] = 0;

	if (s_key & NALI_S_KEY_A)
		lt_v4_array[0] = -1.0F * s_deltra;
	else if (s_key & NALI_S_KEY_D)
		lt_v4_array[0] = 1.0F * s_deltra;
	else
		lt_v4_array[0] = 0;

	if (s_key & NALI_S_KEY_LEFTCTRL)
		s_ty += 1.0F * s_deltra;
	if (s_key & NALI_S_KEY_SPACE)
		s_ty -= 1.0F * s_deltra;

	s_rx += s_pointer_y * s_deltra;
	s_ry += s_pointer_x * s_deltra;

	if (s_rx > M_D2R(90.0F+45))
	{
		s_rx = M_D2R(90.0F+45);
	}
	else if (s_rx < M_D2R(-90.0F-45))
	{
		s_rx = M_D2R(-90.0F-45);
	}

	// NALI_D_LOG("0 s_ry %f", s_ry)
	s_ry = M_NORMALIZE(s_ry, M_D2R(360.0F));
	// NALI_D_LOG("1 s_ry %f", s_ry)

	s_pointer_x = 0;
	s_pointer_y = 0;

	if (s_pointer_state & NALI_S_PS_REROTATE)
	{
		s_rx = 0;
		s_ry = 0;
		s_pointer_state &= 0xFFu - NALI_S_PS_REROTATE;
	}


	memcpy(lc_vkbuffer_p, mm4x4_array, sizeof(mm4x4_array));

	mv4_q(0, 0, s_rz, q_v4_array);
	mv4_q2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, lc_vkbuffer_p, sizeof(float) * 16);
	mm4x4_m(q1_m4x4_array, q0_m4x4_array, lc_vkbuffer_p);

	mv4_q(0, s_ry, 0, q_v4_array);
	mv4_q2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, lc_vkbuffer_p, sizeof(float) * 16);
	mm4x4_m(q1_m4x4_array, q0_m4x4_array, lc_vkbuffer_p);

	mv4_m4(lc_vkbuffer_p, lt_v4_array, gt_v4_array);

	mv4_q(s_rx, 0, 0, q_v4_array);
	mv4_q2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, lc_vkbuffer_p, sizeof(float) * 16);
	mm4x4_m(q1_m4x4_array, q0_m4x4_array, lc_vkbuffer_p);

	memcpy(q2_m4x4_array, mm4x4_array, sizeof(mm4x4_array));

	// m_v4_m4(m_vkbuffer_p, lt_v4_array, q2_m4x4_array + 12);
	s_tx += gt_v4_array[0] / gt_v4_array[3];
	// s_ty += gt_v4_array[1] / gt_v4_array[3];
	s_tz += gt_v4_array[2] / gt_v4_array[3];
	q2_m4x4_array[12] = s_tx;
	q2_m4x4_array[13] = s_ty;
	q2_m4x4_array[14] = s_tz;
	memcpy(q1_m4x4_array, lc_vkbuffer_p, sizeof(float) * 16);
	mm4x4_m(q2_m4x4_array, q1_m4x4_array, lc_vkbuffer_p);
	// ((float *)m_vkbuffer_p)[12] = s_tx;
	// ((float *)m_vkbuffer_p)[13] = s_ty;
	// ((float *)m_vkbuffer_p)[14] = s_tz;
}