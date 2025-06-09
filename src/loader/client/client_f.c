void (*nlcf_data_fp[NALI_NLC_DATA_FP_SIZE])(uint8_t *) = {lcf_sync_user, lcf_add_model, lcf_rm_model};

//pack
void lcf_read_data(uint8_t *data_p)
{
	if (*data_p != 255)
	{
		nlcf_data_fp[*data_p](data_p + 1);
	}
}

void lcf_sync_user(uint8_t *data_p)
{
	uint8_t id = *data_p;
	data_p += sizeof(uint8_t);

	memcpy(lc_rt_array + id * (3 + 3), data_p, (3 + 3) * sizeof(float));
	data_p += (3 + 3) * sizeof(float);

	lcf_read_data(data_p);
}

void lcf_add_model(uint8_t *data_p)
{
	uint8_t m_id = *data_p;
	data_p += sizeof(uint8_t);

	uint16_t id = *data_p;
	data_p += sizeof(uint16_t);

	lc_m_p_array[m_id] = realloc(lc_m_p_array[m_id], sizeof(uint16_t) * (lc_m_bl_array[m_id] + 1));
	lc_m_rt_p_array[m_id] = realloc(lc_m_rt_p_array[m_id], sizeof(float) * (3 + 3) * (lc_m_bl_array[m_id] + 1));

	lc_m_p_array[m_id][lc_m_bl_array[m_id]] = id;
	memcpy(lc_m_rt_p_array[m_id] + lc_m_bl_array[m_id], data_p, sizeof(float) * (3 + 3));
	data_p += sizeof(float) * (3 + 3);

	++lc_m_bl_array[m_id];

	uint8_t animate = *data_p;
	data_p += sizeof(uint8_t);
	if (animate != 255)
	{
		uint8_t keyframe = *data_p;
		data_p += sizeof(uint8_t);
	}

	mtx_lock(lc_mtx_t_p);
	vk_cmd_d_fp = realloc(vk_cmd_d_fp, sizeof(void (*)()) * (vk_cmd_d_fp_bl + 1));
	vk_cmd_d_fp[vk_cmd_d_fp_bl] = e_pomi0_add;
	++vk_cmd_d_fp_bl;
	mtx_unlock(lc_mtx_t_p);

	lcf_read_data(data_p);
}

void lc_sync_rt_entity(uint8_t *data_p)
{
	uint8_t id = *data_p;
	data_p += sizeof(uint8_t);

	float rt_p[3+3];
	lcf_read_data(data_p);
}

void lc_sync_c_entity(uint8_t *data_p)
{
	uint8_t id = *data_p;
	data_p += sizeof(uint8_t);

	float rt_p[4];
	lcf_read_data(data_p);
}

void lcf_rm_model(uint8_t *data_p)
{
	uint8_t id = *data_p;
	data_p += sizeof(uint8_t);

	lcf_read_data(data_p);
}

static void add(uint8_t a, uint8_t j, uint16_t *s_index_p, void (*fp)(uint8_t, uint16_t))
{
	// NALI_VD_M_POMI0;
	lcs_add_ds_p[a] = realloc(lcs_add_ds_p[a], lcs_add_i_bl_p[a] + 1);
	lcs_add_j_p[a] = realloc(lcs_add_j_p[a], lcs_add_i_bl_p[a] + 1);
	lcs_add_a_p[a] = realloc(lcs_add_a_p[a], lcs_add_i_bl_p[a] + 1);
	lcs_add_a_bl_p[a] = realloc(lcs_add_a_bl_p[a], lcs_add_i_bl_p[a] + 1);
	lcs_add_vkdevicesize_p[a] = realloc(lcs_add_vkdevicesize_p[a], sizeof(VkDeviceSize) * NALI_LCS_D_SIZE * (lcs_add_i_bl_p[a] + 1));

	lcs_add_ds_p[a][lcs_add_i_bl_p[a]] = v_a_bl0_array[a];
	lcs_add_j_p[a][lcs_add_i_bl_p[a]] = j;

	lcs_add_a_p[a][lcs_add_i_bl_p[a]] = malloc(4);
	lcs_add_a_p[a][lcs_add_i_bl_p[a]][0] = 9;
	lcs_add_a_p[a][lcs_add_i_bl_p[a]][1] = 4;
	lcs_add_a_p[a][lcs_add_i_bl_p[a]][2] = 6;
	lcs_add_a_p[a][lcs_add_i_bl_p[a]][3] = 8;

	lcs_add_a_bl_p[a][lcs_add_i_bl_p[a]] = 4;

	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_p[a] * NALI_LCS_D_SIZE] = sizeof(float) * 16 * 2;//world
	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_p[a] * NALI_LCS_D_SIZE + 1] = lcm_vkdevicesize_p[j];//b
	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_p[a] * NALI_LCS_D_SIZE + 2] = lcm_vkdevicesize_p[lcm_joint_count_bl + 1] + NALI_LCM_BONE_BL * sizeof(float) * 4 * 4 * v_a_bl0_array[a] + sizeof(float) * 4;//a
	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_p[a] * NALI_LCS_D_SIZE + 3] = NALI_LCM_VP_BL + lcm_rgba_bl;//rgba a
	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_p[a] * NALI_LCS_D_SIZE + 4] = lcm_vkdevicesize_p[lcm_joint_count_bl + 1] + NALI_LCM_BONE_BL * sizeof(float) * 4 * 4 * v_a_bl0_array[a];//rgba b
	
	?vd_m_bl_array
	?vd_m_p_array
	?vd_m_rt_p_array
	?vd_m_animate_p_array
	?vd_m_keyframe_p_array

	lcs_write_fp = realloc(lcs_write_fp, sizeof(void (*)()) * (lcs_write_fp_bl + 1));
	lcs_write_fp[lcs_write_fp_bl] = fp;//pre_update
	++lcs_write_fp_bl;

	*s_index_p = v_a_bl0_array[a];

	++v_a_bl0_array[a];
	++lcs_add_i_bl_p[a];
}