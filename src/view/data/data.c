uint8_t vd_m_bl_array[NALI_VD_M_MAX];
uint16_t *vd_m_p_array[NALI_VD_M_MAX];
float *vd_m_rt_p_array[NALI_VD_M_MAX];

mtx_t *vd_mtx_t_p = &(mtx_t){};

void vd_set()
{
	for (uint8_t l_0 = 0; l_0 < NALI_VD_M_MAX; ++l_0)
	{
		vd_m_p_array[l_0] = malloc(0);
		vd_m_rt_p_array[l_0] = malloc(0);
	}

	nali_info("mtx_init %d", mtx_init(vd_mtx_t_p, mtx_plain))
	nali_info("thrd_create %d", thrd_create(&(thrd_t){}, vd_loop, NULL))
}

void vd_free()
{
	mtx_destroy(vd_mtx_t_p);

	for (uint8_t l_0 = 0; l_0 < NALI_VD_M_MAX; ++l_0)
	{
		free(vd_m_p_array[l_0]);
		free(vd_m_rt_p_array[l_0]);
	}
}

static void add(uint8_t a, uint8_t j, uint16_t *s_index_p, void (*fp)(uint8_t, uint16_t))
{
	// NALI_VD_M_POMI0;
	lcs_add_ds_p_array[a] = realloc(lcs_add_ds_p_array[a], lcs_add_i_bl_array[a] + 1);
	lcs_add_j_p_array[a] = realloc(lcs_add_j_p_array[a], lcs_add_i_bl_array[a] + 1);
	lcs_add_a_p_array[a] = realloc(lcs_add_a_p_array[a], lcs_add_i_bl_array[a] + 1);
	lcs_add_a_bl_p_array[a] = realloc(lcs_add_a_bl_p_array[a], lcs_add_i_bl_array[a] + 1);
	lcs_add_vkdevicesize_p[a] = realloc(lcs_add_vkdevicesize_p[a], sizeof(VkDeviceSize) * NALI_LCS_D_SIZE * (lcs_add_i_bl_array[a] + 1));

	lcs_add_ds_p_array[a][lcs_add_i_bl_array[a]] = v_a_bl0_array[a];
	lcs_add_j_p_array[a][lcs_add_i_bl_array[a]] = j;

	lcs_add_a_p_array[a][lcs_add_i_bl_array[a]] = malloc(4);
	lcs_add_a_p_array[a][lcs_add_i_bl_array[a]][0] = 9;
	lcs_add_a_p_array[a][lcs_add_i_bl_array[a]][1] = 4;
	lcs_add_a_p_array[a][lcs_add_i_bl_array[a]][2] = 6;
	lcs_add_a_p_array[a][lcs_add_i_bl_array[a]][3] = 8;

	lcs_add_a_bl_p_array[a][lcs_add_i_bl_array[a]] = 4;

	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_array[a] * NALI_LCS_D_SIZE] = sizeof(float) * 16 * 2;//world
	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_array[a] * NALI_LCS_D_SIZE + 1] = lcm_vkdevicesize_p[j];//b
	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_array[a] * NALI_LCS_D_SIZE + 2] = lcm_vkdevicesize_p[lcm_joint_count_bl + 1] + NALI_LCM_BONE_BL * sizeof(float) * 4 * 4 * v_a_bl0_array[a] + sizeof(float) * 4;//a
	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_array[a] * NALI_LCS_D_SIZE + 3] = NALI_LCM_VP_BL + lcm_rgba_bl;//rgba a
	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_array[a] * NALI_LCS_D_SIZE + 4] = lcm_vkdevicesize_p[lcm_joint_count_bl + 1] + NALI_LCM_BONE_BL * sizeof(float) * 4 * 4 * v_a_bl0_array[a];//rgba b

	lcs_write_fp = realloc(lcs_write_fp, sizeof(void (*)()) * (lcs_write_fp_bl + 1));
	lcs_write_fp[lcs_write_fp_bl] = fp;//pre_update
	++lcs_write_fp_bl;

	*s_index_p = v_a_bl0_array[a];

	++v_a_bl0_array[a];
	++lcs_add_i_bl_array[a];
}

int vd_loop(void *arg)
{
	while (1)
	{
		//map
		if (add_pomi)
		{
			mtx_lock(vd_mtx_t_p);
			vk_cmd_d_fp = realloc(vk_cmd_d_fp, sizeof(void (*)()) * (vk_cmd_d_fp_bl + 1));
			vk_cmd_d_fp[vk_cmd_d_fp_bl] = e_pomi0_add;
			++vk_cmd_d_fp_bl;
			mtx_unlock(vd_mtx_t_p);
		}
	}

	return 0;
}