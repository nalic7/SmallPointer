void (*lcm_fp[NALI_LB_N_MAX])() =
{
	ecpomi0_set
};

LB_M **lcm_lb_m_p;
float lcm__rt_p[NALI_LB_MIM][3 + 2];
NALI_LB_MIT lsm__update_p[NALI_LB_MIM];
NALI_LB_MIT *lcm_bl_p;

void lcm_set()
{
	lcm_lb_m_p = malloc(0);
	lcm_bl_p = malloc(0);

	for (NALI_LB_MIT l_0 = 0; l_0 < NALI_LB_MIM; ++l_0)
	{
		lcm__rt_p[l_0][0] = +INFINITY;
	}
}

static VkMappedMemoryRange *vkmappedmemoryrange_p;
static uint16_t vkmappedmemoryrange_bl = 0;
void lcm_update()
{
	vkmappedmemoryrange_p = malloc(0);

	// NALI_LB_CT l_x = NALI_M_H3X(lcu_ch_p[0], NALI_LB_CIBL);
	// NALI_LB_CT l_y = NALI_M_H3Y(lcu_ch_p[0], NALI_LB_CIBL);
	// NALI_LB_CT l_z = NALI_M_H3Z(lcu_ch_p[0], NALI_LB_CIBL);

	//use timeline
	for (uint8_t l_0 = 0; l_0 < lcu_ch_bl; ++l_0)
	{
		// //skip 0
		// //s0-xyz c
		// NALI_LB_CT l_0x = NALI_M_H3X(lcu_ch_p[l_0], NALI_LB_CIBL);
		// NALI_LB_CT l_0y = NALI_M_H3Y(lcu_ch_p[l_0], NALI_LB_CIBL);
		// NALI_LB_CT l_0z = NALI_M_H3Z(lcu_ch_p[l_0], NALI_LB_CIBL);
		// NALI_LB_CT x = l_0x - l_x;
		// NALI_LB_CT y = l_0y - l_y;
		// NALI_LB_CT z = l_0z - l_z;
		// //e0-xyz c

		for (NALI_LB_MIT l_1 = 0; l_1 < lcm_bl_p[l_0]; ++l_1)
		{
			if (isfinite(*lcm__rt_p[lcm_lb_m_p[l_0][l_1].update]))
			{
				for (uint8_t l_2 = 0; l_2 < 3 + 2; ++l_2)
				{
					lcm__rt_p[lcm_lb_m_p[l_0][l_1].update][l_2] += (lcm_lb_m_p[l_0][l_1].rt_p[l_2] - lcm__rt_p[lcm_lb_m_p[l_0][l_1].update][l_2]) * lc_deltra;
				}
			}
			else
			{
				memcpy(lcm__rt_p[lcm_lb_m_p[l_0][l_1].update], lcm_lb_m_p[l_0][l_1].rt_p, sizeof(float) * (3 + 2));
			}
		}
	}

	//before switch c

	//should init _rt_p?

	//vkFlushMappedMemoryRanges
	free(vkmappedmemoryrange_p);
}

void lcm_read()
{
	vkmappedmemoryrange_p = malloc(0);

	lcm_bl_p = realloc(lcm_bl_p, sizeof(NALI_LB_MIT) * lcu_ch_bl);
	lcm_lb_m_p = realloc(lcm_lb_m_p, sizeof(LB_M *) * lcu_ch_bl);

	for (uint8_t l_0 = 0; l_0 < lcu_ch_bl; ++l_0)
	{
		lcm_bl_p[l_0] = *(NALI_LB_MIT *)(lc_net_p + lc_net_bl);
		lc_net_bl += sizeof(NALI_LB_MIT);

		lcm_lb_m_p[l_0] = malloc(sizeof(LB_M) * lcm_bl_p[l_0]);
		memcpy(lcm_lb_m_p[l_0], lc_net_p + lc_net_bl, sizeof(LB_M) * lcm_bl_p[l_0]);
		lc_net_bl += sizeof(LB_M) * lcm_bl_p[l_0];

		//m method to pre init
		for (NALI_LB_MIT l_1 = 0; l_1 < lcm_bl_p[l_0]; ++l_1)
		{
			lcm_fp[lcm_lb_m_p[l_0][l_1].ms]();
		}
	}

	//vulkan
	VkDeviceSize *vkdevicesize_p[NALI_V_A_BL];
	for (uint8_t l_0 = 0; l_0 < NALI_V_A_BL; ++l_0)
	{
		//re
		// lcs_vkdescriptorset_bl[l_0] = 0;

		//update
		VkDescriptorBufferInfo vkdescriptorbufferinfo_p[NALI_LCS_D_SIZE * list_p[l_0]];
		VkWriteDescriptorSet vkwritedescriptorset_p[NALI_LCS_D_SIZE * list_p[l_0]];
		lcs_vkdescriptorset_p[l_0] = realloc(lcs_vkdescriptorset_p[l_0], sizeof(VkDescriptorSet) * list_p[l_0]);
		//client_n
		uint8_t mj = m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[m];

		for (uint32_t l_1 = 0; l_1 < list_p[l_1]; ++l_1)
		{
			vkds_make(vk_device, lcs_vkdescriptorpool, &lcs_vkdescriptorsetlayout, 1, lcs_vkdescriptorset_p[l_0] + l_1);
			lcs_setVkWriteDescriptorSet(lcs_vkdescriptorset_p[l_0][l_1], vkdescriptorbufferinfo_p, vkwritedescriptorset_p, vkdevicesize_p[l_0], (sizeof(float) * 4 + sizeof(float) * 4 * 3) * mj);
		}
	}

	//vkUpdateDescriptorSets

	//vkFlushMappedMemoryRanges
	free(vkmappedmemoryrange_p);
}

void lcm_re()
{
	for (uint8_t l_0 = 0; l_0 < lcu_ch_bl; ++l_0)
	{
		free(lcm_lb_m_p[l_0]);
	}

	//should reset lcm__rt_p? / won't need if c is large
}

void lcm_free()
{
	lcm_re();

	free(lcm_lb_m_p);
	free(lcm_bl_p);
}