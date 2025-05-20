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

	s_move_x = 0, s_move_z = 0,
	s_tx = 0.0F,
	s_ty = 0.0F,
	s_tz = 0.0F,
	
	s_deltra = 0;

void s_loopPointer()
{
	if (s_key & NALI_KEY_W)
		s_move_z = 0.5F;
	else if (s_key & NALI_KEY_S)
		s_move_z = -0.5F;
	else
		s_move_z = 0;

	if (s_key & NALI_KEY_A)
		s_move_x = -0.5F;
	else if (s_key & NALI_KEY_D)
		s_move_x = 0.5F;
	else
		s_move_x = 0;

	s_rx = s_pointer_y * s_deltra;
	s_ry = s_pointer_x * s_deltra;

	s_tx = s_move_x * s_deltra;
	// s_ty = * s_deltra;
	s_tz = s_move_z * s_deltra;

	s_pointer_x = 0;
	s_pointer_y = 0;
}