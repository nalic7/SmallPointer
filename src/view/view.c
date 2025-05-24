//v j1c1
//v c1
//v j1t1u1v1
//v t1u1v1
uint8_t
	**v_a_p,
	v_a_bl = 0;

//j1c1
//c1
VkDeviceSize v_a_vkdevicesize_array[];

uint32_t *v_i_p;

void v_set()
{
	v_a_p = malloc(sizeof(uint8_t *) * lcm_joint_count_bl);
	for (uint8_t l_0 = 0; l_0 < lcm_joint_count_bl; ++l_0)
	{
		v_a_p[l_0] = malloc(4);
	}
	v_a_p[0][0] = 9;
	v_a_p[0][1] = 4;
	v_a_p[0][2] = 6;
	v_a_p[0][3] = 8;
	v_a_bl = 4;
}

void v_loop()
{
	vsf_loop();
}

void v_free()
{
	for (uint8_t l_0 = 0; l_0 < lcm_joint_count_bl; ++l_0)
	{
		free(v_a_p[l_0]);
	}

	free(v_a_p);
}