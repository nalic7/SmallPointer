LB_M **lcm_lb_m_p;
float ***lcm__rt_p;
NALI_LB_MIT *lcm_bl_p;

void lcm_set()
{
	lcm_lb_m_p = malloc(0);
	lcm__rt_p = malloc(0);
	lcm_bl_p = malloc(0);
}

void lcm_update()
{
	//use timeline
	for (uint8_t l_0 = 0; l_0 < lcu_ch_bl; ++l_0)
	{
		for (NALI_LB_MIT l_1 = 0; l_1 < lcm_bl_p[l_0]; ++l_1)
		{
			for (uint8_t l_2 = 0; l_2 < 3 + 2; ++l_2)
			{
				lcm__rt_p[l_0][l_1][l_2] += (lcm_lb_m_p[l_0][l_1].rt_p[l_2] - lcm__rt_p[l_0][l_1][l_2]) * lc_deltra;
			}
		}
	}

	//before switch c

	//should init _rt_p?
}

void lcm_read()
{
	lcm_bl_p = realloc(lcm_bl_p, sizeof(NALI_LB_MIT) * lcu_ch_bl);
	lcm_lb_m_p = realloc(lcm_lb_m_p, sizeof(LB_M *) * lcu_ch_bl);
	lcm__rt_p = realloc(lcm__rt_p, sizeof(float **) * lcu_ch_bl);

	for (uint8_t l_0 = 0; l_0 < lcu_ch_bl; ++l_0)
	{
		lcm_bl_p[l_0] = *(NALI_LB_MIT *)(lc_net_p + lc_net_bl);
		lc_net_bl += sizeof(NALI_LB_MIT);

		lcm_lb_m_p[l_0] = malloc(sizeof(LB_M) * lcm_bl_p[l_0]);
		memcpy(lcm_lb_m_p[l_0], lc_net_p + lc_net_bl, sizeof(LB_M) * lcm_bl_p[l_0]);
		lc_net_bl += sizeof(LB_M) * lcm_bl_p[l_0];

		lcm__rt_p[l_0] = malloc(sizeof(float *) * lcm_bl_p[l_0]);
		for (NALI_LB_MIT l_1 = 0; l_1 < lcm_bl_p[l_0]; ++l_1)
		{
			lcm__rt_p[l_0][l_1] = malloc(sizeof(float) * (3 + 2));
		}
	}

	//update vulkan
}

void lcm_re()
{
	for (uint8_t l_0 = 0; l_0 < lcu_ch_bl; ++l_0)
	{
		free(lcm_lb_m_p[l_0]);

		for (NALI_LB_MIT l_1 = 0; l_1 < lcm_bl_p[l_0]; ++l_1)
		{
			free(lcm__rt_p[l_0][l_1]);
		}
		free(lcm__rt_p[l_0]);
	}
}

void lcm_free()
{
	lcm_re();

	free(lcm_lb_m_p);
	free(lcm__rt_p);
	free(lcm_bl_p);
}