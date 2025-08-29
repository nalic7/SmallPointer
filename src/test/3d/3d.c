void t_3d()
{
	VkDevice vkdevice = _vkq_dv_p[_vk_device];
	#define NALI_TEST_map_p ebpomi2_map_p
	#define NALI_TEST_mab NALI_EBPOMI2_MAB
	#define NALI_TEST_m NALI_EBPOMI2_M
	#define NALI_TEST_ds 0

	//! ds == sc_image
	//! in loop
	lcm_ds_bl = 1;
	lcm_vkbuffer_p = realloc(lcm_vkbuffer_p, sizeof(VkBuffer) * _vk_swc_image * lcm_ds_bl);
	lcm_vkbuffer_mp = realloc(lcm_vkbuffer_mp, sizeof(void *) * _vk_swc_image * lcm_ds_bl);
	lcm_vkdevicememory_p = realloc(lcm_vkdevicememory_p, sizeof(VkDeviceMemory) * _vk_swc_image * lcm_ds_bl);
	for (uint8_t l_0 = 0; l_0 < _vk_swc_image; ++l_0)
	{
		for (uint8_t l_1 = 0; l_1 < lcm_ds_bl; ++l_1)
		{
			//! m
			VkDeviceSize vkdevicesize = sizeof(float) * 4 * 4 * (NALI_TEST_m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[NALI_TEST_m]);

			VkMemoryRequirements vkmemoryrequirements;
			vkdevicesize = (vkdevicesize + (_vk_non_coherent_atom_size - 1)) & ~(_vk_non_coherent_atom_size - 1);
			_VK_BF_MAKE(_vk_device, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, lcm_vkbuffer_p[l_0 + l_1 * _vk_swc_image], lcm_vkdevicememory_p[l_0 + l_1 * _vk_swc_image], vkmemoryrequirements)
			_DB_R2L("vkMapMemory %d", vkMapMemory(vkdevice, lcm_vkdevicememory_p[l_0 + l_1 * _vk_swc_image], 0, vkdevicesize, 0, &lcm_vkbuffer_mp[(l_0 + l_1 * _vk_swc_image)]))
		}
	}

	VkWriteDescriptorSet vkwritedescriptorset_p[_RD_VK_DSTSLO_L * _vk_swc_image * lcm_ds_bl];
	VkDescriptorBufferInfo vkdescriptorbufferinfo_p[3 + 2 * _vk_swc_image * lcm_ds_bl];
	lcs_s_bl = NALI_TEST_map_p[0] - 1;
	lcs_s_p = realloc(lcs_s_p, sizeof(lcs_s) * lcs_s_bl);
	//.i ds == 1
	//! need free
	VkDescriptorSet *vkdescriptorset_p = malloc(sizeof(VkDescriptorSet) * _vk_swc_image * lcm_ds_bl);
	for (uint8_t l_0 = 0; l_0 < _vk_swc_image * lcm_ds_bl; ++l_0)
	{
		_vk_dsps_make(_vk_device, vkdescriptorset_p + l_0);
	}
	lcs_setVkWriteDescriptorSet
	(
		vkdescriptorset_p,
		vkdescriptorbufferinfo_p,
		vkwritedescriptorset_p,
		0,
		NALI_TEST_m < lcp_joint_count_bl ? NALI_TEST_m : 0,
		NALI_TEST_m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[NALI_TEST_m]//mj
	);
	vkUpdateDescriptorSets(vkdevice, _RD_VK_DSTSLO_L * _vk_swc_image * lcm_ds_bl, vkwritedescriptorset_p, 0, VK_NULL_HANDLE);
	lcs___p[0].vkdescriptorset_p = vkdescriptorset_p;
	lcs___p[0].mab = NALI_TEST_mab;
	for (uint8_t l_0 = 1; l_0 < NALI_TEST_map_p[0]; ++l_0)
	{
		uint8_t ma = NALI_TEST_map_p[l_0];
		lcs_s_p[l_0 - 1]._ = 0;
		lcs_s_p[l_0 - 1].i = ma;
	}

	//a
	if (NALI_TEST_m < lcp_joint_count_bl)
	{
		//apply rgba
		for (uint8_t l_0 = 0; l_0 < 4; ++l_0)
		{
			*(float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + l_0 * sizeof(float)) = 1.0;
		}
		//apply default a
		memcpy(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float), lcp_a_p[NALI_TEST_m], lcp_joint_count_p[NALI_TEST_m] * 4 * 3 * sizeof(float));
		//apply a 0
		uint8_t l_kf_a = 0;
		uint8_t key = 10;//1
		lckf l_lckf = lckf_p[l_kf_a][key];
		for (uint8_t l_0 = 0; l_0 < l_lckf.bone_bl; ++l_0)
		{
			memcpy(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3, l_lckf.s_p[l_0], sizeof(float) * 3);
			memcpy(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4, l_lckf.r_p[l_0], sizeof(float) * 4);
			memcpy(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4 * 2, l_lckf.t_p[l_0], sizeof(float) * 3);
		}
		//mv4_q(NALI_M_D2R(45), 0, 0, lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 + 1 * sizeof(float) * 4 * 3);
//		//apply s to mid
//		*(float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 12) = 0;
//		*(float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 12 + 1 * sizeof(float)) = 0;
//		*(float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 12 + 2 * sizeof(float)) = 0;
//		//apply s to tail
//		*(float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 2) = 0;
//		*(float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 2 + 1 * sizeof(float)) = 0;
//		*(float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 2 + 2 * sizeof(float)) = 0;
		//apply r to top
		//mv4_q(0, NALI_M_D2R(-45), 0, lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 + 31 * sizeof(float) * 4 * 3);
		//apply r
		mv4_q(0, NALI_M_D2R(-45), NALI_M_D2R(-180), lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4);
		//apply t
		//*(float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 2 + 0 * sizeof(float)) = 1.0;
		//*(float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 2 + 1 * sizeof(float)) = -1.0;
		*(float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 2 + 2 * sizeof(float)) = -3.0;
	}
	//update m v p later
	//update buffer
	//! use atom to all flush
	//! avoid flush if able
	vkFlushMappedMemoryRanges(vkdevice, 1, &(VkMappedMemoryRange)
	{
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = lcm_vkdevicememory_p[_vk_swc_frame_buffer],
		.offset = 0,
		.size = ((sizeof(float) * 4 * 4 * (NALI_TEST_m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[NALI_TEST_m])) + (_vk_non_coherent_atom_size - 1)) & ~(_vk_non_coherent_atom_size - 1),
		.pNext = VK_NULL_HANDLE
	});
}

//.i /255
static uint8_t aki = 0;
static uint8_t
	l_ak_current,
	l_ak_next;

static double t_s_kf = 3 * 255;
static uint16_t t_s2c_kf = 0;

////.i kf 3 4 5
//static uint8_t key = 3;
//static uint8_t l_kf_a = 0;
static struct timespec frame_start = {0}, frame_end;
void t_3d_buffer()
{
	NALI_LB_AKT
		a = lb_ak_p[aki][0],
		k_s = lb_ak_p[aki][1],
		k_e = lb_ak_p[aki][2];

	_vk_swc_frame_buffer = (_vk_swc_frame_buffer + 1) % _vk_swc_image;
	if (NALI_TEST_m < lcp_joint_count_bl)
	{
		//apply rgba
		for (uint8_t l_0 = 0; l_0 < 4; ++l_0)
		{
			*(float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + l_0 * sizeof(float)) = 1.0;
		}
		//apply default a
		memcpy(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float), lcp_a_p[NALI_TEST_m], lcp_joint_count_p[NALI_TEST_m] * 4 * 3 * sizeof(float));
	}

	//.i apply default view
	mv4_q(0, NALI_M_D2R(-45), NALI_M_D2R(-180), lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4);
	*(float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 2 + 2 * sizeof(float)) = -3.0;

//	//.i apply a loop
//	lckf l_lckf = lckf_p[l_kf_a][key];
//	for (uint8_t l_0 = 0; l_0 < l_lckf.bone_bl; ++l_0)
//	{
//		memcpy(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3, l_lckf.s_p[l_0], sizeof(float) * 3);
//		memcpy(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4, l_lckf.r_p[l_0], sizeof(float) * 4);
//		memcpy(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4 * 2, l_lckf.t_p[l_0], sizeof(float) * 3);
//	}
//	if (frame_time >= 1.0)
//	{
//		frame_start = frame_end;
//		key = (key + 1);
//		if (key == 6)
//		{
//			key = 3;
//		}
//	}

	//.i float -> uint -> float
	clock_gettime(CLOCK_MONOTONIC, &frame_end);
	double frame_time = frame_end.tv_sec + (double)frame_end.tv_nsec / 1e9 - frame_start.tv_sec - (double)frame_start.tv_nsec / 1e9;
	t_s_kf += 255 * 4 * frame_time;
	frame_start = frame_end;
	t_s_kf = NALI_M_WRAP_F(t_s_kf, k_s * 255, k_e * 255);
//	_DB_N2L("t_s_kf %f", t_s_kf);
	double kff = t_s_kf / 255;
	l_ak_current = kff;
	kff -= l_ak_current;

	l_ak_next = NALI_M_WRAP_I(l_ak_current + 1, k_s, k_e);
	lckf l_lckf = lckf_p[a][l_ak_current];
	for (uint8_t l_0 = 0; l_0 < l_lckf.bone_bl; ++l_0)
	{
		memcpy(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3, l_lckf.s_p[l_0], sizeof(float) * 3);
		memcpy(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4, l_lckf.r_p[l_0], sizeof(float) * 4);
		memcpy(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4 * 2, l_lckf.t_p[l_0], sizeof(float) * 3);
	}

	l_lckf = lckf_p[a][l_ak_next];
	for (uint8_t l_0 = 0; l_0 < l_lckf.bone_bl; ++l_0)
	{
		for (uint8_t l_3 = 0; l_3 < 3; ++l_3)
		{
			NALI_M_LERP(((float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3))[l_3], l_lckf.s_p[l_0][l_3], kff);
			NALI_M_LERP(((float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4 * 2))[l_3], l_lckf.t_p[l_0][l_3], kff);
		}

		for (uint8_t l_3 = 0; l_3 < 4; ++l_3)
		{
			NALI_M_LERP(((float *)(lcm_vkbuffer_mp[_vk_swc_frame_buffer + NALI_TEST_ds * _vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4))[l_3], l_lckf.r_p[l_0][l_3], kff);
		}
	}
//	_DB_N2L("kff %f", kff);
//	_DB_N2L("l_ak_current %d", l_ak_current);
//	_DB_N2L("l_ak_next %d", l_ak_next);

	vkFlushMappedMemoryRanges(_vkq_dv_p[_vk_device], 1, &(VkMappedMemoryRange)
	{
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = lcm_vkdevicememory_p[_vk_swc_frame_buffer],
		.offset = 0,
		.size = ((sizeof(float) * 4 * 4 * (NALI_TEST_m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[NALI_TEST_m])) + (_vk_non_coherent_atom_size - 1)) & ~(_vk_non_coherent_atom_size - 1),
		.pNext = VK_NULL_HANDLE
	});
}
