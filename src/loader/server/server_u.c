// typedef struct
// {
// 	float
// 		half_width,
// 		half_height,
// 		t_p[3];
// } m_cube;

static float
	w_p[16],
	u_t_p[4] = {0, 0, 0, 1},
	q_v4_array[4],
	q0_m4x4_array[16] =
	{
		1.0F, 0.0F, 0.0F, 0.0F,
		0.0F, 1.0F, 0.0F, 0.0F,
		0.0F, 0.0F, 1.0F, 0.0F,
		0.0F, 0.0F, 0.0F, 1.0F
	},
	q1_m4x4_array[16],
	uc_t_p[4];
void lsu_update()
{
	for (NALI_LB_UT l_0 = 0; l_0 < NALI_LB_UM; ++l_0)
	{
		//k
		lb_u_update(w_p, ns_p[l_0].lb_u.rt_p[4], q_v4_array, q0_m4x4_array, q1_m4x4_array);
		mv4_m4(w_p, u_t_p, uc_t_p);

		// m_v4_m4(m_vkbuffer_p, t_p, q2_m4x4_array + 12);
		ns_p[l_0].lb_u.rt_p[0] += uc_t_p[0] / uc_t_p[3];
		// ns_p[l_0].lb_u.rt_p[1] += uc_t_p[1] / uc_t_p[3];
		ns_p[l_0].lb_u.rt_p[2] += uc_t_p[2] / uc_t_p[3];

		//c
		float *rt_p = ns_p[l_0].lb_u.rt_p;
		if (memcmp(ns_p[l_0]._rt_p, rt_p, sizeof(float) * (3 + 2)))
		{
			//offset
			for (uint8_t l_1 = 0; l_1 < 3; ++l_1)
			{
				if (rt_p[l_1] > NALI_LB_CMFL || rt_p[l_1] < -NALI_LB_CMFL)
				{
					ns_p[l_0].c_p[l_1] += NALI_M_NORMALP_I(ns_p[l_0].c_p[l_1] + (int32_t)(rt_p[l_1] / NALI_LB_CMFL), NALI_LB_CIBL);
					rt_p[l_1] = NALI_M_NORMALP_F(rt_p[l_1], NALI_LB_CMFL);
				}
			}

			//ray
			//dis
			// float t_p[3];
			// float r2t_p[3];
			// r2t_p[0] = NALI_M_YP2X(rt_p[3], rt_p[4]);
			// r2t_p[1] = NALI_M_P2Y(rt_p[4]);
			// r2t_p[2] = NALI_M_YP2Z(rt_p[3], rt_p[4]);
			
			// NALI_LB_C_ST x = ns_p[l_0].c_p[0] - 1;
			// NALI_LB_C_ST y = ns_p[l_0].c_p[1] - 1;
			// NALI_LB_C_ST z = ns_p[l_0].c_p[2] - 1;
			ns_p[l_0].ch_bl = 1;
			ns_p[l_0].ch_p = realloc(ns_p[l_0].ch_p, ns_p[l_0].ch_bl);
			for (uint8_t l_1 = 0; l_1 < 3; ++l_1)
			{
				for (uint8_t l_2 = 0; l_2 < 3; ++l_2)
				{
					for (uint8_t l_3 = 0; l_3 < 3; ++l_3)
					{
						// t_p[0] = NALI_LB_CMFL * NALI_M_NORMALP_I(x + l_1, NALI_LB_CIBL) + NALI_LB_CMFL / 2;
						// t_p[1] = NALI_LB_CMFL * NALI_M_NORMALP_I(y + l_2, NALI_LB_CIBL) + NALI_LB_CMFL / 2;
						// t_p[2] = NALI_LB_CMFL * NALI_M_NORMALP_I(z + l_3, NALI_LB_CIBL) + NALI_LB_CMFL / 2;
						// if (m_ray(t_p, rt_p, r2t_p))

						if (fabsf(rt_p[3] - NALI_M_XZ2YAW(m_i_p[l_1], m_i_p[l_3])) < NALI_LSU_EPSILON && fabsf(rt_p[4] - NALI_M_XYZ2PITCH(m_i_p[l_1], m_i_p[l_2], m_i_p[l_3])) < NALI_LSU_EPSILON)
						{
							++ns_p[l_0].ch_bl;
							ns_p[l_0].ch_p = realloc(ns_p[l_0].ch_p, ns_p[l_0].ch_bl);
							// ns_p[l_0].ch_p[ns_p[l_0].ch_bl - 1] = NALI_M_H3(x + l_1, y + l_2, z + l_3, NALI_LB_CIBL);
							ns_p[l_0].ch_p[ns_p[l_0].ch_bl - 1] = NALI_M_H3
							(
								NALI_M_NORMALP_I(ns_p[l_0].c_p[0] + m_i_p[l_1], NALI_LB_CIBL),
								NALI_M_NORMALP_I(ns_p[l_0].c_p[1] + m_i_p[l_2], NALI_LB_CIBL),
								NALI_M_NORMALP_I(ns_p[l_0].c_p[2] + m_i_p[l_3], NALI_LB_CIBL),
								NALI_LB_CIBL
							);
						}
					}
				}
			}

			memcpy(ns_p[l_0]._rt_p, rt_p, sizeof(float) * (3 + 2));
		}
	}
}

void lsu_send(NALI_LB_UT u)
{
	memcpy(ls_net_p + ls_net_bl, &ns_p[u].lb_u, sizeof(LB_U));
	ls_net_bl += sizeof(LB_U);

	*(ls_net_p + ls_net_bl) = ns_p[u].ch_bl;
	ls_net_bl += sizeof(uint8_t);

	memcpy(ls_net_p + ls_net_bl, ns_p[u].ch_p, sizeof(NALI_LB_CHT) * ns_p[u].ch_bl);
	ls_net_bl += sizeof(NALI_LB_CHT) * ns_p[u].ch_bl;
}

static float xy_p[2];
void lsu_read(NALI_LB_UT u)
{
	uint8_t k = *(ls_net_p + ls_net_bl);
	ls_net_bl += sizeof(uint8_t);

	memcpy(xy_p, ls_net_p + ls_net_bl, sizeof(float) * 2);
	ls_net_bl += sizeof(float) * 2;

	if (k & NALI_LB_K_W)
		u_t_p[2] = 1.0F / NALI_LB_MAX_RW;
	else if (k & NALI_LB_K_S)
		u_t_p[2] = -1.0F / NALI_LB_MAX_RW;
	else
		u_t_p[2] = 0;

	if (k & NALI_LB_K_A)
		u_t_p[0] = -1.0F / NALI_LB_MAX_RW;
	else if (k & NALI_LB_K_D)
		u_t_p[0] = 1.0F / NALI_LB_MAX_RW;
	else
		u_t_p[0] = 0;

	if (k & NALI_LB_K_DIG)
		ns_p[u].lb_u.rt_p[1] += 1.0F / NALI_LB_MAX_RW;
	if (k & NALI_LB_K_JUMP)
		ns_p[u].lb_u.rt_p[1] -= 1.0F / NALI_LB_MAX_RW;

	ns_p[u].lb_u.rt_p[3] += xy_p[1] / NALI_LB_MAX_RW;
	ns_p[u].lb_u.rt_p[4] += xy_p[0] / NALI_LB_MAX_RW;

	if (ns_p[u].lb_u.rt_p[3] > NALI_M_D2R(90.0F+45))
	{
		ns_p[u].lb_u.rt_p[3] = NALI_M_D2R(90.0F+45);
	}
	else if (ns_p[u].lb_u.rt_p[3] < NALI_M_D2R(-90.0F-45))
	{
		ns_p[u].lb_u.rt_p[3] = NALI_M_D2R(-90.0F-45);
	}

	// NALI_D_LOG("0 s_ry %f", s_ry)
	ns_p[u].lb_u.rt_p[4] = NALI_M_NORMALN_F(ns_p[u].lb_u.rt_p[4], NALI_M_D2R(360.0F));
	// NALI_D_LOG("1 s_ry %f", s_ry)

	if (k & NALI_LB_K_REROTATE)
	{
		ns_p[u].lb_u.rt_p[3] = 0;
		ns_p[u].lb_u.rt_p[4] = 0;
	}
}

void lsu_open()
{
	if (ls_file_p)
	{
		for (NALI_LB_UT l_0 = 0; l_0 < NALI_LB_UM; ++l_0)
		{
			NALI_LB_CHT ch;
			fread(&ch, sizeof(NALI_LB_CHT), 1, ls_file_p);
			ns_p[l_0].c_p[0] = NALI_M_H3X(ch, NALI_LB_CIBL);
			ns_p[l_0].c_p[1] = NALI_M_H3Y(ch, NALI_LB_CIBL);
			ns_p[l_0].c_p[2] = NALI_M_H3Z(ch, NALI_LB_CIBL);
			// ns_p[l_0].ch_bl = 1;
			// fread(ns_p[l_0].ch_p, sizeof(NALI_LB_CHT), 1, ls_file_p);
			fread(ns_p[l_0].lb_u.rt_p, sizeof(float), 5, ls_file_p);
		}
	}
	else
	{
		for (NALI_LB_UT l_0 = 0; l_0 < NALI_LB_UM; ++l_0)
		{
			//random spawn
			for (uint8_t l_1 = 0; l_1 < NALI_LB_UM; ++l_1)
			{
				ns_p[l_0].c_p[l_1] = rand() % NALI_LB_CIBL;
			}
			// ns_p[l_0].ch_bl = 1;
			// ns_p[l_0].ch_p = malloc(sizeof(NALI_LB_CHT));
			// ns_p[l_0].ch_p[0] = NALI_M_H3(rand() % NALI_LB_CIBL, rand() % NALI_LB_CIBL, rand() % NALI_LB_CIBL, NALI_LB_CIBL);

			// s_tx = 0.0F
			// s_ty = -1.5F
			// s_tz = -2.0F
			//world / space
			//-NALI_LB_CFBL 0 NALI_LB_CFBL
			memset(ns_p[l_0].lb_u.rt_p, 0, sizeof(float) * (3 + 2));
		}
	}
}

void lsu_save()
{
	for (NALI_LB_UT l_0 = 0; l_0 < NALI_LB_UM; ++l_0)
	{
		//save only c had u
		fwrite(ns_p[l_0].ch_p, sizeof(NALI_LB_CHT), 1, ls_file_p);
		fwrite(ns_p[l_0].lb_u.rt_p, sizeof(float), 5, ls_file_p);
	}
}