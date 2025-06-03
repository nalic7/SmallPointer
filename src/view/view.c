uint8_t
	**v_a_p_array[NALI_V_A_BL],
	*v_a_bl1_p_array[NALI_V_A_BL];

uint16_t
	v_a_bl0_array[NALI_V_A_BL] = {0};

uint32_t *v_i_p;

VkDeviceSize 
	v_a_vkdevicesize_array[NALI_V_A_BL],
	*v_b_vkdevicesize_p_array[NALI_V_A_BL];

float **v_s_p_array[NALI_V_A_BL];

void v_set()
{
	for (uint8_t l_0 = 0; l_0 < NALI_V_A_BL; ++l_0)
	{
		v_a_p_array[l_0] = malloc(0);
		v_a_bl1_p_array[l_0] = malloc(0);

		v_b_vkdevicesize_p_array[l_0] = malloc(0);

		v_s_p_array[l_0] = malloc(0);
	}
}

void v_free()
{
	for (uint8_t l_0 = 0; l_0 < NALI_V_A_BL; ++l_0)
	{
		for (uint16_t l_1 = 0; l_1 < v_a_bl0_array[l_0]; ++l_1)
		{
			free(v_a_p_array[l_0][l_1]);
		}
		free(v_a_bl1_p_array[l_0]);
		free(v_a_p_array[l_0]);

		free(v_b_vkdevicesize_p_array[l_0]);

		free(v_s_p_array[l_0]);
	}

	free(v_i_p);
}