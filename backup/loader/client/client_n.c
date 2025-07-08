void (*nlcf_data_fp[NALI_LCF_DATA_FP_BL])(uint8_t *) = {lcf_add_u_c, lcf_sync_all_u_c2new_u, lcf_rm_u_c, lcf_add_m_c, lcf_sync_all_m_c2new_u, lcf_rm_m_c};

// void lcf_read_data(uint8_t *data_p)
// {
// 	if (*data_p != 255)
// 	{
// 		nlcf_data_fp[*data_p](data_p + 1);
// 	}
// }

//should send u or id
void lcf_add_u_c(uint8_t *data_p)
{
	mtx_lock(lc_mtx_t_p);

	// lcu_p = realloc(lcu_p, (lcu_bl + 1) * sizeof(NALI_LB_UT));
	// lcu_p[lcu_bl] = *(NALI_LB_UT *)data_p;
	// data_p += sizeof(NALI_LB_UT);

	// lcu_rt_p = realloc(lcu_rt_p, (lcu_bl + 1) * sizeof(float) * (3 + 3));
	// memcpy(lcu_rt_p + lcu_bl * (3 + 3), data_p, sizeof(float) * (3 + 3));
	// data_p += (3 + 3) * sizeof(float);

	// lcu_c_p = realloc(lcu_c_p, (lcu_bl + 1) * sizeof(NALI_LB_CT) * 3);
	// memcpy(lcu_c_p + lcu_bl * 3, data_p, sizeof(NALI_LB_CT) * 3);
	// // data_p += 3 * sizeof(NALI_LB_CT);

	// ++lcu_bl;

	mtx_unlock(lc_mtx_t_p);
}

void lcf_sync_all_u_c2new_u(uint8_t *data_p)
{
	NALI_LB_UT u_m = *(NALI_LB_UT *)data_p;
	data_p += sizeof(NALI_LB_UT);

	uint8_t ch_m = *data_p;
	data_p += sizeof(uint8_t);

	NALI_LB_CHT ch = *(NALI_LB_CHT *)data_p;
	data_p += sizeof(NALI_LB_CHT);

	mtx_lock(lc_mtx_t_p);

	// lcu_hi_p = realloc(lcu_hi_p, sizeof(NALI_LB_CHT) * (lcu_hi_bl + 1));

	for (uint8_t l_0 = 0; l_0 < ch_m; ++l_0)
	{

	}

	// ++lcu_hi_bl;



	// lcu_p = realloc(lcu_p, max_u * sizeof(NALI_LB_UT));
	// memcpy(lcu_p, data_p, max_u * sizeof(NALI_LB_UT));
	// data_p += max_u * sizeof(NALI_LB_UT);

	// lcu_rt_p = realloc(lcu_rt_p, max_u * sizeof(float) * (3 + 3));
	// memcpy(lcu_rt_p, data_p, max_u * sizeof(float) * (3 + 3));
	// data_p += max_u * sizeof(float) * (3 + 3);

	// lcu_c_p = realloc(lcu_c_p, max_u * sizeof(NALI_LB_CT) * 3);
	// memcpy(lcu_c_p, data_p, max_u * sizeof(NALI_LB_CT) * 3);

	// lcu_bl += max_u;

	mtx_unlock(lc_mtx_t_p);
}

void lcf_rm_u_c(uint8_t *data_p)
{
	mtx_lock(lc_mtx_t_p);
	mtx_unlock(lc_mtx_t_p);
}

//-extra byte if more than 1-
//ma key? -> keyframe
//mal animate data? -> timeline /255
void lcf_add_m_c(uint8_t *data_p)
{
	NALI_LB_MIT mi = *(NALI_LB_MIT *)data_p;
	data_p += sizeof(NALI_LB_MIT);

	NALI_LB_MST ms = *(NALI_LB_MST *)data_p;
	data_p += sizeof(NALI_LB_MST);

	float *rt_p = (float *)data_p;
	data_p += sizeof(float) * (3 + 3);

	NALI_LB_MAT ma = *(NALI_LB_MAT *)data_p;
	data_p += sizeof(NALI_LB_MAT);

	NALI_LB_MALT mal = *(NALI_LB_MALT *)data_p;
	data_p += sizeof(NALI_LB_MALT);

	//s0-ms
	//m as j
	NALI_LB_MT m = lb_ms_p[ms];
	uint8_t a = lb_ms_a_p[m];
	uint8_t a_bl = lb_ms_abl_p[ms];
	uint8_t *a_p = lb_ms_ap_p[ms];
	//0 gui or world

	//e0-ms

	mtx_lock(lc_mtx_t_p);

	uint8_t mj = m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[m];

	lcs_vkdescriptorset_p[a] = realloc(lcs_vkdescriptorset_p[a], sizeof(VkDescriptorSet) * (lcs_a_bl0_p[a] + 1));
	VkWriteDescriptorSet vkwritedescriptorset_p[NALI_LCS_D_SIZE];
	VkDescriptorBufferInfo vkdescriptorbufferinfo_p[NALI_LCS_D_SIZE];

	lcs_a_p[a] = realloc(lcs_a_p[a], sizeof(uint8_t *) * (lcs_a_bl0_p[a] + 1));
	lcs_a_bl1_p[a] = realloc(lcs_a_bl1_p[a], lcs_a_bl0_p[a] + 1);

	lcs_b_vkdevicesize_p[a] = realloc(lcs_b_vkdevicesize_p[a], sizeof(VkDeviceSize) * NALI_LCS_D_SIZE * (lcs_a_bl0_p[a] + 1));
	lcs_b_vkdevicesize_p[a][NALI_LCS_D_SIZE * lcs_a_bl0_p[a]] = lb_ms_vkdevicesize_p[ms];
	lcs_b_vkdevicesize_p[a][NALI_LCS_D_SIZE * lcs_a_bl0_p[a] + 1] = lcp_vkdevicesize_p[m];
	lcs_b_vkdevicesize_p[a][NALI_LCS_D_SIZE * lcs_a_bl0_p[a] + 2] = lcp_vkdevicesize_p[lcp_joint_count_bl + 1] + NALI_LCP_BONE_BL * (sizeof(float) * 4 + sizeof(float) * 4 * 3) * lcs_a_bl0_p[a] + sizeof(float) * 4;
	lcs_b_vkdevicesize_p[a][NALI_LCS_D_SIZE * lcs_a_bl0_p[a] + 3] = NALI_LCP_VP_BL;
	lcs_b_vkdevicesize_p[a][NALI_LCS_D_SIZE * lcs_a_bl0_p[a] + 4] = lcp_vkdevicesize_p[lcp_joint_count_bl + 1] + NALI_LCP_BONE_BL * (sizeof(float) * 4 + sizeof(float) * 4 * 3) * lcs_a_bl0_p[a];

	vkds_make(vk_device, lcs_vkdescriptorpool, &lcs_vkdescriptorsetlayout, 1, lcs_vkdescriptorset_p[a] + lcs_a_bl0_p[a] + 1);

	lcs_setVkWriteDescriptorSet(lcs_vkdescriptorset_p[a][lcs_a_bl0_p[a] + 1], vkdescriptorbufferinfo_p, vkwritedescriptorset_p, lcs_b_vkdevicesize_p[a] + NALI_LCS_D_SIZE * lcs_a_bl0_p[a], (sizeof(float) * 4 + sizeof(float) * 4 * 3) * mj);

	lcs_a_p[a][lcs_a_bl0_p[a]] = a_p;
	lcs_a_bl1_p[a][lcs_a_bl0_p[a]] = a_bl;

	vkUpdateDescriptorSets(vkqd_vkdevice_p[vk_device], NALI_LCS_D_SIZE, vkwritedescriptorset_p, 0, VK_NULL_HANDLE);
	++lcs_a_bl0_p[a];

	//flush
	uint32_t l0;
	uint32_t l_offset;
	uint32_t l_size;
	l0 = lcs_b_vkdevicesize_p[a][NALI_LCS_D_SIZE * lcs_a_bl0_p[a] + 4];
	for (uint32_t l_1 = 0; l_1 < 4; ++l_1)
	{
		((float *)(lc_vkbuffer_p + l0))[l_1] = 1.0F;
	}
	l0 += sizeof(float) * 4;
	l_offset = l0;

	//UBOA
	memcpy(lc_vkbuffer_p + l0, lcp_a_p[m], sizeof(float) * 4 * 3 * mj);

	l_size = l0 + sizeof(float) * 4 * 3 * mj;

	lcs_vkmappedmemoryrange_p = realloc(lcs_vkmappedmemoryrange_p, sizeof(VkMappedMemoryRange) * (lcs_vkmappedmemoryrange_bl + 1));
	lcs_vkmappedmemoryrange_p[lcs_vkmappedmemoryrange_bl++] = (VkMappedMemoryRange)
	{
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = lc_vkdevicememory,
		.offset = l_offset,
		.size = (l_size + 63) & ~63,
		.pNext = VK_NULL_HANDLE
	};

	mtx_unlock(lc_mtx_t_p);
}

void lcf_sync_all_m_c2new_u(uint8_t *data_p)
{
	NALI_LB_MIT mi;
	float rt[3 + 3];
	mtx_lock(lc_mtx_t_p);

	uint8_t a;
	uint8_t ds_bl;
	uint8_t *ds_p;
	uint8_t *j_p;

	mtx_unlock(lc_mtx_t_p);
}

void lcf_rm_m_c(uint8_t *data_p)
{
	NALI_LB_MIT mi = *(NALI_LB_MIT *)data_p;
	data_p += sizeof(NALI_LB_MIT);

	mtx_lock(lc_mtx_t_p);

	NALI_LCS_DSIT dsi = lc_dsi_p[mi];
	uint8_t a = lc_a_p[mi];

	vkFreeDescriptorSets(vkqd_vkdevice_p[vk_device], lcs_vkdescriptorpool, 1, lcs_vkdescriptorset_p[a] + dsi);

	lcs_vkdescriptorset_p[a][dsi] = lcs_vkdescriptorset_p[a][--lcs_a_bl0_p[a]];

	free(lcs_a_p[a][dsi]);
	lcs_a_p[a][dsi] = lcs_a_p[a][lcs_a_bl0_p[a]];

	lcs_a_bl1_p[a][dsi] = lcs_a_bl1_p[a][lcs_a_bl0_p[a]];

	memcpy(lc_vkbuffer_p + lcs_b_vkdevicesize_p[a][dsi * NALI_LCS_D_SIZE + 4], lc_vkbuffer_p + lcs_b_vkdevicesize_p[a][lcs_a_bl0_p[a] * NALI_LCS_D_SIZE + 4], lcm_p[mi] >= lcp_joint_count_bl ? sizeof(float) * 4 + sizeof(float) * 4 * 3 : (sizeof(float) * 4 + sizeof(float) * 4 * 3) * lcp_joint_count_p[lcm_p[mi]]);
	memcpy(lcs_b_vkdevicesize_p[a] + dsi * NALI_LCS_D_SIZE, lcs_b_vkdevicesize_p[a] + lcs_a_bl0_p[a] * NALI_LCS_D_SIZE, sizeof(VkDeviceSize) * NALI_LCS_D_SIZE);

	lcs_vkdescriptorset_p[a] = realloc(lcs_vkdescriptorset_p[a], sizeof(VkDescriptorSet) * lcs_a_bl0_p[a]);
	lcs_a_p[a] = realloc(lcs_a_p[a], sizeof(uint8_t *) * lcs_a_bl0_p[a]);
	lcs_a_bl1_p[a] = realloc(lcs_a_bl1_p[a], lcs_a_bl0_p[a]);
	lcs_b_vkdevicesize_p[a] = realloc(lcs_b_vkdevicesize_p[a], sizeof(VkDeviceSize) * NALI_LCS_D_SIZE * lcs_a_bl0_p[a]);

	//remove data
	lcm_p[mi] = lcm_p[--lcm_bl];
	// lc_m_i_p[mi] = lc_m_i_p[lc_m_bl];
	memcpy(lcm_c_p + mi * sizeof(NALI_LB_CT) * 3, lcm_c_p + lcm_bl * sizeof(NALI_LB_CT) * 3, sizeof(NALI_LB_CT) * 3);
	memcpy(lcm_rt_p + mi * sizeof(float) * (3 + 3), lcm_rt_p + lcm_bl * sizeof(float) * (3 + 3), sizeof(float) * (3 + 3));
	lcm_p = realloc(lcm_p, sizeof(NALI_LB_MT) * lcm_bl);
	// lc_m_i_p = realloc(lc_m_i_p, sizeof(NALI_LB_MIT) * lc_m_bl);
	lcm_c_p = realloc(lcm_c_p, sizeof(NALI_LB_CT) * 3 * lcm_bl);
	lcm_rt_p = realloc(lcm_rt_p, sizeof(float) * (3 + 3) * lcm_bl);

	mtx_unlock(lc_mtx_t_p);
}

// static VkDeviceSize *vkdevicesize_p_array[NALI_LCS_A_BL];
// static void update(uint8_t a, uint16_t lcs_write_fp_bl)
// {
// 	// //write flush

// 	// uint32_t l0;
// 	// uint32_t l_offset;
// 	// uint32_t l_size;

// 	// //rgba b
// 	// if (state_p_array[a][lcs_write_fp_bl] & NALI_LCS_U_RGBA)
// 	// {
// 	// 	l0 = lcm_vkdevicesize_p[lcm_joint_count_bl - 1] + NALI_LCP_BONE_BL * sizeof(float) * 4 * 4 * v_a_bl0_array[a];
// 	// 	//write to lc_vkbuffer_p from other thread
// 	// 	// memcpy(lc_vkbuffer_p + l0, rgba_p_array[a] + lcs_write_fp_bl * 4, sizeof(float) * 4);
// 	// 	l0 += sizeof(float) * 4;
// 	// 	l_offset = l0;
// 	// }
// 	// else
// 	// {
// 	// 	l0 = lcm_vkdevicesize_p[lcm_joint_count_bl - 1] + NALI_LCP_BONE_BL * sizeof(float) * 4 * 4 * v_a_bl0_array[a] + sizeof(float) * 4;
// 	// 	l_offset = l0;
// 	// }

// 	// if (state_p_array[a][lcs_write_fp_bl] & NALI_LCS_U_A)
// 	// {
// 	// 	// //file
// 	// 	// uint8_t animate = 0;
// 	// 	// uint8_t key = 11;//80
// 	// 	// for (uint8_t l_1 = 0; l_1 < lckf_keyframe_p[animate][key].bone_bl; ++l_1)
// 	// 	// {
// 	// 	// 	memcpy(lc_vkbuffer_p + l0 + lckf_keyframe_p[animate][key].bone_p[l_1] * sizeof(float) * 4 * 3, lckf_keyframe_p[animate][key].animation_s_p[l_1], sizeof(float) * 3);
// 	// 	// 	memcpy(lc_vkbuffer_p + l0 + sizeof(float) * 4 + lckf_keyframe_p[animate][key].bone_p[l_1] * sizeof(float) * 4 * 3, lckf_keyframe_p[animate][key].animation_r_p[l_1], sizeof(float) * 4);
// 	// 	// 	memcpy(lc_vkbuffer_p + l0 + sizeof(float) * 4 * 2 + lckf_keyframe_p[animate][key].bone_p[l_1] * sizeof(float) * 4 * 3, lckf_keyframe_p[animate][key].animation_t_p[l_1], sizeof(float) * 3);
// 	// 	// }
// 	// 	// //data

// 	// 	// l_size = l0 + sizeof(float) * 4 * 3 * lcm_joint_count_p[j];
// 	// 	l_size = l0 + sizeof(float) * 4 * 3 * j;
// 	// }
// 	// else
// 	// {
// 	// 	l_size = ;
// 	// }

// 	if (vkdevicesize_p_array[a][lcs_write_fp_bl * 4 + 1])
// 	{
// 		lcs_vkmappedmemoryrange_p = realloc(lcs_vkmappedmemoryrange_p, sizeof(VkMappedMemoryRange) * (lcs_vkmappedmemoryrange_bl + 1));
// 		lcs_vkmappedmemoryrange_p[lcs_vkmappedmemoryrange_bl++] = (VkMappedMemoryRange)
// 		{
// 			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
// 			.memory = lc_vkdevicememory,
// 			.offset = vkdevicesize_p_array[a][lcs_write_fp_bl * 4],
// 			.size = (vkdevicesize_p_array[a][lcs_write_fp_bl * 4 + 1] + 63) & ~63,
// 			.pNext = VK_NULL_HANDLE
// 		};

// 		vkdevicesize_p_array[a][lcs_write_fp_bl * 4 + 1] = 0;
// 	}

// 	if (vkdevicesize_p_array[a][lcs_write_fp_bl * 4 + 3])
// 	{
// 		lcs_vkmappedmemoryrange_p = realloc(lcs_vkmappedmemoryrange_p, sizeof(VkMappedMemoryRange) * (lcs_vkmappedmemoryrange_bl + 1));
// 		lcs_vkmappedmemoryrange_p[lcs_vkmappedmemoryrange_bl++] = (VkMappedMemoryRange)
// 		{
// 			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
// 			.memory = lc_vkdevicememory,
// 			.offset = vkdevicesize_p_array[a][lcs_write_fp_bl * 4 + 2],
// 			.size = (vkdevicesize_p_array[a][lcs_write_fp_bl * 4 + 3] + 63) & ~63,
// 			.pNext = VK_NULL_HANDLE
// 		};

// 		vkdevicesize_p_array[a][lcs_write_fp_bl * 4 + 3] = 0;
// 	}
// }

// static void animate(uint8_t a, uint16_t lcs_write_fp_bl)
// {
// 	//init e and animate

// 	//l0 rgba b
// 	if (!vkdevicesize_p_array[a][lcs_write_fp_bl * 4 + 3])
// 	{
// 		VkDeviceSize l_vkdevicesize = lcs_b_vkdevicesize_p[a][lcs_write_fp_bl * NALI_LCS_D_SIZE + 4];
// 		memcpy(lc_vkbuffer_p + l_vkdevicesize, rgba_p, sizeof(float) * 4);
// 	}

// 	//l0 a
// 	uint8_t animate = vd_m_animate_p_array[a][lcs_write_fp_bl];//0
// 	if (animate != 255)
// 	{
// 		uint8_t keyframe = vd_m_keyframe_p_array[a][lcs_write_fp_bl];//11 <- 80

// 		VkDeviceSize l_vkdevicesize = lcs_b_vkdevicesize_p[a][lcs_write_fp_bl * NALI_LCS_D_SIZE + 2];

// 		for (uint8_t l_1 = 0; l_1 < lckf_keyframe_p[animate][keyframe].bone_bl; ++l_1)
// 		{
// 			memcpy(lc_vkbuffer_p + l_vkdevicesize + lckf_keyframe_p[animate][keyframe].bone_p[l_1] * sizeof(float) * 4 * 3, lckf_keyframe_p[animate][keyframe].animation_s_p[l_1], sizeof(float) * 3);
// 			memcpy(lc_vkbuffer_p + l_vkdevicesize + sizeof(float) * 4 + lckf_keyframe_p[animate][keyframe].bone_p[l_1] * sizeof(float) * 4 * 3, lckf_keyframe_p[animate][keyframe].animation_r_p[l_1], sizeof(float) * 4);
// 			memcpy(lc_vkbuffer_p + l_vkdevicesize + sizeof(float) * 4 * 2 + lckf_keyframe_p[animate][keyframe].bone_p[l_1] * sizeof(float) * 4 * 3, lckf_keyframe_p[animate][keyframe].animation_t_p[l_1], sizeof(float) * 3);
// 		}
// 	}
// }