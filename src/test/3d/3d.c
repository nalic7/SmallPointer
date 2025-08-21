void t_3d()
{
	VkDevice vkdevice = vkqd_vkdevice_p[vk_device];
	#define NALI_TEST_map_p ebpomi2_map_p
	#define NALI_TEST_mab NALI_EBPOMI2_MAB
	#define NALI_TEST_m NALI_EBPOMI2_M
	#define NALI_TEST_ds 0

	//! 1 ds == sc_image ds
	//! in loop
	lcm_ds_bl = 1;
	lcm_vkbuffer_p = realloc(lcm_vkbuffer_p, sizeof(VkBuffer) * vksc_image * lcm_ds_bl);
	lcm_vkbuffer_mp = realloc(lcm_vkbuffer_mp, sizeof(void *) * vksc_image * lcm_ds_bl);
	lcm_vkdevicememory_p = realloc(lcm_vkdevicememory_p, sizeof(VkDeviceMemory) * vksc_image * lcm_ds_bl);
	for (uint8_t l_0 = 0; l_0 < vksc_image; ++l_0)
	{
		for (uint8_t l_1 = 0; l_1 < lcm_ds_bl; ++l_1)
		{
			//! m
			VkDeviceSize vkdevicesize = sizeof(float) * 4 * 4 * (NALI_TEST_m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[NALI_TEST_m]);

			VkMemoryRequirements vkmemoryrequirements;
			vkdevicesize = (vkdevicesize + (vk_non_coherent_atom_size - 1)) & ~(vk_non_coherent_atom_size - 1);
			VK_makeBuffer(vk_device, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, lcm_vkbuffer_p[l_0 + l_1 * vksc_image], lcm_vkdevicememory_p[l_0 + l_1 * vksc_image], vkmemoryrequirements)
			NALI_D_INFO("vkMapMemory %d", vkMapMemory(vkqd_vkdevice_p[vk_device], lcm_vkdevicememory_p[l_0 + l_1 * vksc_image], 0, vkdevicesize, 0, &lcm_vkbuffer_mp[(l_0 + l_1 * vksc_image)]))
		}
	}

	VkWriteDescriptorSet vkwritedescriptorset_p[NALI_LCS_D_SIZE];
	VkDescriptorBufferInfo vkdescriptorbufferinfo_p[NALI_LCS_D_SIZE];
	lcs_s_bl = NALI_TEST_map_p[0] - 1;
	lcs_s_p = realloc(lcs_s_p, sizeof(lcs_s) * lcs_s_bl);
	//.i ds == 1
	VkDescriptorSet vkdescriptorset;
	vkds_make(vk_device, lcs_vkdescriptorpool, &lcs_vkdescriptorsetlayout, 1, &vkdescriptorset);
	lcs_setVkWriteDescriptorSet
	(
		vkdescriptorset,
		vkdescriptorbufferinfo_p,
		vkwritedescriptorset_p,
		0,
		NALI_TEST_m < lcp_joint_count_bl ? NALI_TEST_m : 0,
		NALI_TEST_m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[NALI_TEST_m]//mj
	);
	vkUpdateDescriptorSets(vkdevice, NALI_LCS_D_SIZE, vkwritedescriptorset_p, 0, VK_NULL_HANDLE);
	lcs___p[0].vkdescriptorset = vkdescriptorset;
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
			*(float *)(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + l_0 * sizeof(float)) = 1.0;
		}
		//apply default a
		memcpy(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float), lcp_a_p[NALI_TEST_m], lcp_joint_count_p[NALI_TEST_m] * 4 * 3 * sizeof(float));
		//apply a 0
		uint8_t l_kf_a = 0;
		uint8_t key = 10;//1
		lckf l_lckf = lckf_p[l_kf_a][key];
		for (uint8_t l_0 = 0; l_0 < l_lckf.bone_bl; ++l_0)
		{
			memcpy(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3, l_lckf.s_p[l_0], sizeof(float) * 3);
			memcpy(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4, l_lckf.r_p[l_0], sizeof(float) * 4);
			memcpy(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4 * 2, l_lckf.t_p[l_0], sizeof(float) * 3);
		}
		//mv4_q(NALI_M_D2R(45), 0, 0, lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + sizeof(float) * 4 + 1 * sizeof(float) * 4 * 3);
//		//apply s to mid
//		*(float *)(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 12) = 0;
//		*(float *)(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 12 + 1 * sizeof(float)) = 0;
//		*(float *)(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 12 + 2 * sizeof(float)) = 0;
//		//apply s to tail
//		*(float *)(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 2) = 0;
//		*(float *)(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 2 + 1 * sizeof(float)) = 0;
//		*(float *)(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 2 + 2 * sizeof(float)) = 0;
		//apply r to top
		//mv4_q(0, NALI_M_D2R(-45), 0, lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + sizeof(float) * 4 + 31 * sizeof(float) * 4 * 3);
		//apply r
		mv4_q(0, NALI_M_D2R(-45), NALI_M_D2R(-180), lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + sizeof(float) * 4);
		//apply t
		//*(float *)(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 2 + 0 * sizeof(float)) = 1.0;
		//*(float *)(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 2 + 1 * sizeof(float)) = -1.0;
		*(float *)(lcm_vkbuffer_mp[vksc_buffer_frame + NALI_TEST_ds * vksc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 2 + 2 * sizeof(float)) = -3.0;
	}
	//update m v p later
	//update buffer
	//! use atom to all flush
	vkFlushMappedMemoryRanges(vkqd_vkdevice_p[vk_device], 1, &(VkMappedMemoryRange)
	{
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = lcp_vkdevicememory,
		.offset = 0,
		.size = ((sizeof(float) * 4 * 4 * (NALI_TEST_m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[NALI_TEST_m])) + (vk_non_coherent_atom_size - 1)) & ~(vk_non_coherent_atom_size - 1),
		.pNext = VK_NULL_HANDLE
	});
}
