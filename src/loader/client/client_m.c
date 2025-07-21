// void (*lcm_fp[NALI_LB_N_MAX])() =
// {
// 	ecpomi0_set
// };

LB_M **lcm_lb_m_p;
NALI_LB_MIT *lcm_bl_p;

typedef struct
{
	NALI_LB_MIT ds_bl;
	//mi/update
	NALI_LB_MIT *ds_p;
} _M;
#define NALI_LCM_M_BL 3*3*3
static _M _m[NALI_LCM_M_BL];
#define NALI_LCM_M_S_VIEW 1
static uint8_t _m_state_p[NALI_LCM_M_BL];
// static NALI_LB_MIT re_ds_bl = 0;
// static NALI_LB_MIT *re_ds_p;
static VkDescriptorBufferInfo *vkdescriptorbufferinfo_p;
static VkWriteDescriptorSet *vkwritedescriptorset_p;
static VkMappedMemoryRange *vkmappedmemoryrange_p;
static NALI_LB_MIT all_ds_bl = 0;

static uint16_t vkmappedmemoryrange_bl = 0;

void lcm_set()
{
	lcm_lb_m_p = malloc(0);
	lcm_bl_p = malloc(0);

	vkdescriptorbufferinfo_p = malloc(0);
	vkwritedescriptorset_p = malloc(0);
	vkmappedmemoryrange_p = malloc(0);
	for (uint8_t l_0 = 0; l_0 < NALI_LCM_M_BL; ++l_0)
	{
		_m[l_0].ds_bl = 0;
		_m[l_0].ds_p = malloc(0);
	}
}

void lcm_update()
{
	NALI_LB_MIT l_mm_bl = 0;

	for (uint8_t l_0 = 0; l_0 < lcu_ch_bl; ++l_0)
	{
		for (NALI_LB_MIT l_1 = 0; l_1 < lcm_bl_p[l_0]; ++l_1)
		{
			lcs__ _ = lcs___p[lcm_lb_m_p[l_0][l_1].update];

			if (!_.m.rt_frame)
			{
				for (uint8_t l_2 = 0; l_2 < 3 + 2; ++l_2)
				{
					_.m._rt_p[l_2] = (lcm_lb_m_p[l_0][l_1].rt_p[l_2] - _.m.rt_p[l_2]) * NALI_LC_D;
				}
			}

			if (++_.m.rt_frame >= NALI_LC_MAX_F)
			{
				if (_.m.rt_frame == NALI_LC_MAX_F)
				{
					memcpy(_.m.rt_p, lcm_lb_m_p[l_0][l_1].rt_p, sizeof(float) * (3 + 2));
				}
				else
				{
					--_.m.rt_frame;
				}
			}
			else
			{
				for (uint8_t l_2 = 0; l_2 < 3 + 2; ++l_2)
				{
					_.m.rt_p[l_2] += _.m._rt_p[l_2];
				}
			}

			//new MemoF2
			//start _.m.a_f
			//end lcm_lb_m_p[l_0][l_1].af / 255.0F
			//next _.m._a_f
			//delta NALI_LC_D
			//frame _.m.a_f_frame
			//min k_s
			//max_value k_e
			NALI_LB_AKT
				k_s,
				k_e;
			if (!_.m.a_f_frame)
			{
				float start = _.m.a_f;
				float end = lcm_lb_m_p[l_0][l_1].af / 255.0F;
				if (start > end)
				{
					float extra = k_e - start + end - k_s;

					_.m._a_f = extra * NALI_LC_D;
				}
				else
				{
					_.m._a_f = (end - start) * NALI_LC_D;
				}
			}

			if (++_.m.a_f_frame >= NALI_LC_MAX_F)
			{
				if (_.m.a_f_frame == NALI_LC_MAX_F)
				{
					_.m.a_f = lcm_lb_m_p[l_0][l_1].af / 255.0F;
				}
				else
				{
					--_.m.a_f_frame;
				}
			}
			else
			{
				_.m.a_f += _.m._a_f;
				_.m.a_f = NALI_M_WRAP_F(_.m.a_f, k_s, k_e);
			}

			NALI_LB_AKT l_ak_current = _.m.a_f;
			NALI_LB_AKT l_ak_next = NALI_M_WRAP_I(l_ak_current + 1, k_s, k_e);
			//server control speed
			float l_a_f = _.m.a_f - (int32_t)_.m.a_f;

			//apply rt2a rgba a
			if (_.m.m < lcp_joint_count_bl)
			{
				//ak=1 == af=255 
				//ak -> ak  0 -> 2 af+=255*2
				//af -> af
				//default a
				for (uint8_t l_2 = 0; l_2 < lcp_joint_count_p[_.m.m]; ++l_2)
				{
					memcpy(lc_vkbuffer_p + l_2 * sizeof(float) * 4 * 3, ?, sizeof(float) * 4 * 3);
				}

				//apply k_s k_e
				//NALI_M_LERP
				lckf lckf = lckf_p[_.m.a][_.m.ak];
				for (uint8_t l_2 = 0; l_2 < lckf_bl_p[_.m.ak]; ++l_2)
				{
					for (uint8_t l_3 = 0; l_3 < lckf.bone_bl; ++l_3)
					{
						uint8_t bone = lckf.bone_p[l_3];
						lckf.s_p[l_3];
						lckf.r_p[l_3];
						lckf.t_p[l_3];
					}
				}
				memcpy(lc_vkbuffer_p, ?, ?);

				vkmappedmemoryrange_p = realloc(vkmappedmemoryrange_p, sizeof(VkMappedMemoryRange) * (l_mm_bl + 1));
				vkmappedmemoryrange_p[l_mm_bl++] = (VkMappedMemoryRange)
				{
					.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
					.memory = lc_vkdevicememory,
					.offset = ?,
					.size = (? + 63) & ~63,
					.pNext = VK_NULL_HANDLE
				};
			}
		}
	}

	vkFlushMappedMemoryRanges(vkqd_vkdevice_p[vk_device], l_mm_bl, vkmappedmemoryrange_p);
}

void lcm_read()
{
	NALI_LB_MIT l_ds_bl = 0;
	lcs_s_bl = 0;
	// NALI_LB_MIT l_mm_bl = 0;

	lcm_bl_p = realloc(lcm_bl_p, sizeof(NALI_LB_MIT) * lcu_ch_bl);
	lcm_lb_m_p = realloc(lcm_lb_m_p, sizeof(LB_M *) * lcu_ch_bl);

	VkDevice vkdevice = vkqd_vkdevice_p[vk_device];

	memset(_m_state_p, 0, NALI_LCM_M_BL);
	NALI_LB_CT l_x = NALI_M_H3X(lcu_ch_p[0], NALI_LB_CIBL);
	NALI_LB_CT l_y = NALI_M_H3Y(lcu_ch_p[0], NALI_LB_CIBL);
	NALI_LB_CT l_z = NALI_M_H3Z(lcu_ch_p[0], NALI_LB_CIBL);
	for (uint8_t l_0 = 0; l_0 < lcu_ch_bl; ++l_0)
	{
		//find ds from u
		//s0-c
		NALI_LB_CT l_0x = NALI_M_H3X(lcu_ch_p[l_0], NALI_LB_CIBL);
		NALI_LB_CT l_0y = NALI_M_H3Y(lcu_ch_p[l_0], NALI_LB_CIBL);
		NALI_LB_CT l_0z = NALI_M_H3Z(lcu_ch_p[l_0], NALI_LB_CIBL);
		NALI_LB_CT x = l_0x - l_x;
		NALI_LB_CT y = l_0y - l_y;
		NALI_LB_CT z = l_0z - l_z;
		//-1 0 1
		//3 * 3 * 3
		uint8_t _mi = NALI_M_H3(x, y, z, 3);
		//e0-c

		lcm_bl_p[l_0] = *(NALI_LB_MIT *)(lc_net_p + lc_net_bl);
		lc_net_bl += sizeof(NALI_LB_MIT);

		lcm_lb_m_p[l_0] = malloc(sizeof(LB_M) * lcm_bl_p[l_0]);
		memcpy(lcm_lb_m_p[l_0], lc_net_p + lc_net_bl, sizeof(LB_M) * lcm_bl_p[l_0]);
		lc_net_bl += sizeof(LB_M) * lcm_bl_p[l_0];

		//free ds

		_m_state_p[_mi] |= NALI_LCM_M_S_VIEW;
		if (lcm_bl_p[l_0] != _m[_mi].ds_bl)
		{
			//free vk
			for (NALI_LB_MIT l_1 = lcm_bl_p[l_0]; l_1 < _m[_mi].ds_bl; ++l_1)
			{
				vkFreeDescriptorSets(vkdevice, lcs_vkdescriptorpool, 1, &lcs___p[_m[_mi].ds_p[l_1]].vkdescriptorset);
				--all_ds_bl;

				// re_ds_p = realloc(re_ds_p, sizeof(NALI_LB_MIT) * (re_ds_bl + 1));
				// re_ds_p[re_ds_bl++] = _m[_mi].ds_p[l_1];
			}

			_m[_mi].ds_p = realloc(_m[_mi].ds_p, sizeof(NALI_LB_MIT) * lcm_bl_p[l_0]);
			_m[_mi].ds_bl = lcm_bl_p[l_0];
		}

		//new ds
		for (NALI_LB_MIT l_1 = 0; l_1 < lcm_bl_p[l_0]; ++l_1)
		{
			lcs__ _ = lcs___p[lcm_lb_m_p[l_0][l_1].update];
			if (_.m.ch != lcu_ch_p[l_0] || _.m.mi != l_1)
			{
				_.m.state ^= NALI_LCM__UPDATE_S_AD;

				// lcm_fp[lcm_lb_m_p[l_0][l_1].ms]();
				if (_.m.m == lcm_lb_m_p[l_0][l_1].m)
				{
					//current ds
					if (_.m.ma != lcm_lb_m_p[l_0][l_1].ma)
					{
						_.a_p = lb_map_p[lcm_lb_m_p[l_0][l_1].ma];
					}

					if (_.m.a != lcm_lb_m_p[l_0][l_1].a)
					{
						_.m.a_f_frame = 0;
						_.m.a_f = lcm_lb_m_p[l_0][l_1].af / 255.0F;
						// _.m.ak = lcm_lb_m_p[l_0][l_1].ak;

						// //apply a
						// lckf_p[lcm_lb_m_p[l_0][l_1].a];

						// vkmappedmemoryrange_p = realloc(vkmappedmemoryrange_p, sizeof(VkMappedMemoryRange) * (l_mm_bl + 1));
						// vkmappedmemoryrange_p[l_mm_bl++] = (VkMappedMemoryRange)
						// {
						// 	.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
						// 	.memory = lc_vkdevicememory,
						// 	.offset = ?,
						// 	.size = (? + 63) & ~63,
						// 	.pNext = VK_NULL_HANDLE
						// };
					}

					if (memcmp(_.m.rt_p, lcm_lb_m_p[l_0][l_1].rt_p, sizeof(float) * (3 + 2)))
					{
						_.m.rt_frame = 0;
					}

					// if (_.mab != lb_mab_p[lcm_lb_m_p[l_0][l_1].m])
					// {
					// 	_.mab = lb_mab_p[lcm_lb_m_p[l_0][l_1].m];
					// }
				}
				else
				{
					_.ds = all_ds_bl;
					vkdescriptorbufferinfo_p = realloc(vkdescriptorbufferinfo_p, (l_ds_bl + 1) * NALI_LCS_D_SIZE * sizeof(VkDescriptorBufferInfo));
					vkwritedescriptorset_p = realloc(vkwritedescriptorset_p, (l_ds_bl + 1) * NALI_LCS_D_SIZE * sizeof(VkWriteDescriptorSet));

					_m[_mi].ds_p[l_1] = lcm_lb_m_p[l_0][l_1].update;
					if (!_.m.state)
					{
						//new ds
						vkds_make(vk_device, lcs_vkdescriptorpool, &lcs_vkdescriptorsetlayout, 1, &_.vkdescriptorset);
					}

					uint8_t mj = lcm_lb_m_p[l_0][l_1].m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[lcm_lb_m_p[l_0][l_1].m];
					lcs_setVkWriteDescriptorSet
					(
						_.vkdescriptorset,
						vkdescriptorbufferinfo_p + l_ds_bl * NALI_LCS_D_SIZE,
						vkwritedescriptorset_p + l_ds_bl * NALI_LCS_D_SIZE,
						all_ds_bl++,
						lcm_lb_m_p[l_0][l_1].m < lcp_joint_count_bl ? lcm_lb_m_p[l_0][l_1].m : 0,
						(sizeof(float) * 4 + sizeof(float) * 4 * 3) * mj
					);

					//fix lcm__rt_p
					_.m.rt_frame = 0;
					memcpy(_.m.rt_p, lcm_lb_m_p[l_0][l_1].rt_p, sizeof(float) * (3 + 2));
					_.m.a_f_frame = 0;
					_.m.a_f = lcm_lb_m_p[l_0][l_1].af / 255.0F;
					// _.m.ak = lcm_lb_m_p[l_0][l_1].ak;
					_.a_p = lb_map_p[lcm_lb_m_p[l_0][l_1].ma];
					// _.mab = lb_mab_p[lcm_lb_m_p[l_0][l_1].m];

					// //apply a
					// lckf_p[lcm_lb_m_p[l_0][l_1].a];

					++l_ds_bl;
				}

				memcpy(lcs___p, lcm_lb_m_p[l_0] + l_1, sizeof(NALI_LB_MT) + sizeof(NALI_LB_MAT) + sizeof(NALI_LB_AT));
				_.mab = lb_mab_p[lcm_lb_m_p[l_0][l_1].m];
			}

			//sort depth
			for (NALI_LCS_AIT l_2 = 1; l_2 < _.a_p[0]; ++l_2)
			{
				lcs_s_p = realloc(lcs_s_p, ++lcs_s_bl * sizeof(lcs_s));
				const float *md_p = lb_mdp_p[_.a_p[l_2]];
				lcs_s lcs_s =
				{
					._ = _m[_mi].ds_p[l_1],
					.i = _.a_p[l_2],
					//should sub u_r
					.d = NALI_M_SIZE
					(
						_.m.rt_p[0] + md_p[0] + NALI_LB_CMFL * x - l_x,
						_.m.rt_p[1] + md_p[1] + NALI_LB_CMFL * y - l_y,
						_.m.rt_p[2] + md_p[2] + NALI_LB_CMFL * z - l_z
					)
				};

				// if (lb_mdp_p[_.a_p[l_2]])
				// {
				//translucent
				uint32_t lcs_s_i = 0;

				//find depth
				for (uint32_t l_3 = lcs_s_bl; l_3 > 0; --l_3)
				{
					//use u_t+head_t2m_t
					if (lcs_s_p[l_3].d < lcs_s.d)
					{
						//old near
						lcs_s_i = l_3;
						break;
					}
					else
					{
						//old far
					}
				}

				lcs_s_p[lcs_s_i] = lcs_s;
				// }
				// else
				// {
				// 	//opaque
				// }
			}
		}
	}

	vkUpdateDescriptorSets(vkdevice, l_ds_bl, vkwritedescriptorset_p, 0, VK_NULL_HANDLE);
	// vkFlushMappedMemoryRanges(vkqd_vkdevice_p[vk_device], l_mm_bl, vkmappedmemoryrange_p);

	//free vk
	for (uint8_t l_0 = 0; l_0 < NALI_LCM_M_BL; ++l_0)
	{
		if (!_m_state_p[l_0])
		{
			for (uint8_t l_1 = 0; l_1 < _m[l_0].ds_bl; ++l_1)
			{
				vkFreeDescriptorSets(vkdevice, lcs_vkdescriptorpool, 1, &lcs___p[_m[l_0].ds_p[l_1]].vkdescriptorset);
				--all_ds_bl;
			}
		}
	}

	//x1 bypass sort and draw in a
	// lcs_a_bl_p = realloc(lcs_a_bl_p, );

	//2 sort and draw in ds
	//need extra z/depth on part need
	// lcs_s_p = realloc(lcs_s_p, all_ds_bl * sizeof(lcs_s));
	// for (uint8_t l_0 = 0; l_0 < all_ds_bl; ++l_0)
	// {

	// }
}

void lcm_re()
{
	for (uint8_t l_0 = 0; l_0 < lcu_ch_bl; ++l_0)
	{
		free(lcm_lb_m_p[l_0]);
	}
}

void lcm_free()
{
	lcm_re();

	free(lcm_lb_m_p);
	free(lcm_bl_p);

	free(vkdescriptorbufferinfo_p);
	free(vkwritedescriptorset_p);
	free(vkmappedmemoryrange_p);
	for (uint8_t l_0 = 0; l_0 < NALI_LCM_M_BL; ++l_0)
	{
		free(_m[l_0].ds_p);
	}
}