uint32_t s_width = 1;
uint32_t s_height = 1;
uint8_t s_pointer_id = 1;

uint8_t m_surface_state = 0;

uint8_t s_pointer_state = 0;

float s_pointer_x = 0, s_pointer_y = 0;

float
	s_rx = 0.0F,
	s_ry = 0.0F,
	s_rz = MATH_D2R(180.0F),
	
	s_deltra = 0;

void s_loopPointer()
{
	s_rx = s_pointer_y * s_deltra;
	s_ry = -s_pointer_x * s_deltra;

	if (s_pointer_x != 0)
	{
		s_pointer_x = 0;
		// s_pointer_x -= ;
	}

	if (s_pointer_y != 0)
	{
		s_pointer_y = 0;
		// s_pointer_y -= ;
	}

	// s_rx = 0;
	// s_ry = 0;
}