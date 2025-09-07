//! test data/server data
/*
static const uint8_t ebpomi2_map_p[] =
{
	10,
	SMPTReMAc + SMPTReM_POMI_PAPI,
	SMPTReMA_FE0000_000,
	SMPTReMA_FE0000_001,
	SMPTReMA_FE00_000,
	SMPTReMA_FE00_001,
	SMPTReMA_FE0_000,
	SMPTReMA_FE0_001,
	SMPTReMA_M0,
	SMPTReMA_IShovel
};
static const SMPTRB_AKT lb_ak_p[1][3] =
{
	{0, 3, 5}
};
*/
#ifdef SMPT_CM_VK
	VkDescriptorSet *smptr_cemPvkdescriptorset;

	VkBuffer *smptr_cemPvkbuffer;
	static void **smptr_cemPbuffer_map;
	static VkDeviceMemory *Pvkdevicememory;

	static VkWriteDescriptorSet *Pvkwritedescriptorset;
	static VkDescriptorBufferInfo *Pvkdescriptorbufferinfo;
	static SMPTRtMI Ldst = 0;
#endif

struct SMPTR_CEMsM0
{
	SMPTRtMI ii;
	SMPTRtM m;
	SMPTRtMK k;
	SMPTRtMT t;
};
static struct SMPTR_CEMsM0 smptr_cemPm0[SMPTRmMI];

struct SMPTR_CEMsM1 *smptr_cemPm1;
uint32_t smptr_cemLm1 = 0;

void smptr_cemMset()
{
	smptr_cemPm1 = malloc(0);

	#ifdef SMPT_CM_VK
		smptr_cemPvkdescriptorset = malloc(0);

		smptr_cemPvkbuffer = malloc(0);
		smptr_cemPbuffer_map = malloc(0);
		Pvkdevicememory = malloc(0);

		Pvkwritedescriptorset = malloc(0);
		Pvkdescriptorbufferinfo = malloc(0);
	#endif

	//! test
	smptrPm = malloc(sizeof(struct SMPTRsM));
	smptrPm[0].l = 9;

	smptrPm[0].Pa = malloc(sizeof(SMPTRtMA) * smptrPm[0].l);
	smptrPm[0].Pa[0] = SMPTReMAc + SMPTReM_POMI_PAPI;
	smptrPm[0].Pa[1] = SMPTReMA_FE0000_000;
	smptrPm[0].Pa[2] = SMPTReMA_FE0000_001;
	smptrPm[0].Pa[3] = SMPTReMA_FE00_000;
	smptrPm[0].Pa[4] = SMPTReMA_FE00_001;
	smptrPm[0].Pa[5] = SMPTReMA_FE0_000;
	smptrPm[0].Pa[6] = SMPTReMA_FE0_001;
	smptrPm[0].Pa[7] = SMPTReMA_M0;
	smptrPm[0].Pa[8] = SMPTReMA_IShovel;
	++smptrLm;
}

//.i server always sync n-mn
//.i mii always ++
static SMPTRtMI Lm0 = 0;
void smptr_cemMread()
{
	#ifndef SMPT_CM_RAW
		SMPTRtMI count = *(SMPTRtMI *)smptr_cePnet;
		smptr_ceLnet += sizeof(SMPTRtMI);

		for (SMPTRtMI l0 = 0; l0 < count; ++l0)
		{
			SMPTRtMI mi = *(SMPTRtMI *)smptr_cePnet;
			smptr_ceLnet += sizeof(SMPTRtMI);
			uint8_t mii = *(uint8_t *)smptr_cePnet;
			smptr_ceLnet += sizeof(uint8_t) * l;

			uint8_t l = *(uint8_t *)smptr_cePnet;
			smptr_ceLnet += sizeof(uint8_t);

			SMPTRtMA maP[l];
			memcpy(maP, smptr_cePnet + smptr_ceLnet, sizeof(SMPTRtMA) * l);
			smptr_ceLnet += sizeof(SMPTRtMA) * l;

			//.i if > ma -> mb ++
			//.i add m
			for (uint8_t l1 = 0; l1 < l; ++l1)
			{
				++smptrLm;
				smptrPm = realloc(smptrPm, sizeof(SMPTRsM) * smptrLm);
				smptrPm[l0] = ;
			}
		}
	#endif

	//.i clean m0
	#ifdef SMPT_CM_VK
		VkDevice vkdevice = smpt_rd_vkq_dv_p[smpt_rd_vk_device];

		if (smptrLm < Lm0)
		{
			vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstsp, (Lm0 - smptrLm) * smpt_rd_vk_swc_image, smptr_cemPvkdescriptorset + smptrLm * smpt_rd_vk_swc_image);
			for (SMPTRtMI l0 = smptrLm * smpt_rd_vk_swc_image; l0 < Lm0 * smpt_rd_vk_swc_image; ++l0)
			{
				vkUnmapMemory(vkdevice, Pvkdevicememory[l0]);
				vkDestroyBuffer(vkdevice, smptr_cemPvkbuffer[l0], VK_NULL_HANDLE);
				vkFreeMemory(vkdevice, Pvkdevicememory[l0], VK_NULL_HANDLE);
			}
		}
		smptr_cemPvkdescriptorset = realloc(smptr_cemPvkdescriptorset, sizeof(VkDescriptorSet) * smpt_rd_vk_swc_image * smptrLm);
		smptr_cemPvkbuffer = realloc(smptr_cemPvkbuffer, sizeof(VkBuffer) * smpt_rd_vk_swc_image * smptrLm);
		smptr_cemPbuffer_map = realloc(smptr_cemPbuffer_map, sizeof(void *) * smpt_rd_vk_swc_image * smptrLm);
		Pvkdevicememory = realloc(Pvkdevicememory, sizeof(VkDeviceMemory) * smpt_rd_vk_swc_image * smptrLm);
		for (SMPTRtMI l0 = Lm0 * smpt_rd_vk_swc_image; l0 < smptrLm * smpt_rd_vk_swc_image; ++l0)
			smptr_cemPvkdescriptorset[l0] = 0;

		Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, 0);
		Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, 0);
	#endif

	//.i update m
	//! update buffer
	smpt_rd_vk_swc_frame_buffer = (smpt_rd_vk_swc_frame_buffer + 1) % smpt_rd_vk_swc_image;
	smptr_cemLm1 = 0;
	for (SMPTRtMI l0 = 0; l0 < smptrLm; ++l0)
	{
		struct SMPTRsM m = smptrPm[l0];
		struct SMPTR_CEMsM0 *Pm0 = smptr_cemPm0 + l0;
		uint8_t state = 0;

		#ifdef SMPT_CM_VK
			if (Lm0 <= l0 || !smptr_cemPvkdescriptorset[l0] || Pm0->m != m.m)
		#endif
		{
			state |= 1;
			Pm0->m = m.m;
		}

		if (Pm0->ii != m.ii)
		{
			state |= 2;
			Pm0->ii = m.ii;
		}

//		SMPT_DB_N2L("state %d", state)
		if (state & 1)
		{
			#ifdef SMPT_CM_VK
				if (smptr_cemPvkdescriptorset[l0])
				{
					vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstsp, smpt_rd_vk_swc_image, smptr_cemPvkdescriptorset + l0 * smpt_rd_vk_swc_image);
					for (uint8_t l1 = 0; l1 < smpt_rd_vk_swc_image; ++l1)
					{
						vkUnmapMemory(vkdevice, Pvkdevicememory[l0 * smpt_rd_vk_swc_image + l1]);
						vkDestroyBuffer(vkdevice, smptr_cemPvkbuffer[l0 * smpt_rd_vk_swc_image + l1], VK_NULL_HANDLE);
						vkFreeMemory(vkdevice, Pvkdevicememory[l0 * smpt_rd_vk_swc_image + l1], VK_NULL_HANDLE);
					}
				}

				for (uint8_t l1 = 0; l1 < smpt_rd_vk_swc_image; ++l1)
				{
					VkDeviceSize vkdevicesize = sizeof(float) * 4 * 4 * (m.m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[m.m]);

					VkMemoryRequirements vkmemoryrequirements;
					vkdevicesize = (vkdevicesize + (smpt_rd_vk_non_coherent_atom_size - 1)) & ~(smpt_rd_vk_non_coherent_atom_size - 1);
					SMPT_RD_VK_BF_MAKE(smpt_rd_vk_device, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_cemPvkbuffer[l1 + l0 * smpt_rd_vk_swc_image], Pvkdevicememory[l1 + l0 * smpt_rd_vk_swc_image], vkmemoryrequirements)
					SMPT_DB_R2L("vkMapMemory %d", vkMapMemory(vkdevice, Pvkdevicememory[l1 + l0 * smpt_rd_vk_swc_image], 0, vkdevicesize, 0, &smptr_cemPbuffer_map[(l1 + l0 * smpt_rd_vk_swc_image)]))
				}

				++Ldst;
				Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, SMPT_RD_VKW_DSTSLO_L * smpt_rd_vk_swc_image * Ldst * sizeof(VkWriteDescriptorSet));
				Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, (3 + 2 * smpt_rd_vk_swc_image * Ldst) * sizeof(VkDescriptorBufferInfo));

//				SMPT_DB_N2L("smptr_cemPvkdescriptorset %p", smptr_cemPvkdescriptorset)
				for (uint8_t l1 = 0; l1 < smpt_rd_vk_swc_image; ++l1)
				{
					smpt_rd_vkw_dsts_make(smpt_rd_vk_device, smptr_cemPvkdescriptorset + l1 + l0 * smpt_rd_vk_swc_image);
//					SMPT_DB_N2L("l1 + l0 * smpt_rd_vk_swc_image %d", l1 + l0 * smpt_rd_vk_swc_image)
//					SMPT_DB_N2L("smptr_cemPvkdescriptorset + l1 + l0 * smpt_rd_vk_swc_image %p", smptr_cemPvkdescriptorset + l1 + l0 * smpt_rd_vk_swc_image)
				}
				smpt_rd_vkw_dsts
				(
					//! check
					smptr_cemPvkdescriptorset + l0 * smpt_rd_vk_swc_image,
					Pvkdescriptorbufferinfo + (Ldst - 1) * smpt_rd_vk_swc_image,
					Pvkwritedescriptorset + (Ldst - 1) * smpt_rd_vk_swc_image,
					l0,
					m.m < lcp_joint_count_bl ? m.m : 0,
					m.m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[m.m]
				);
			#endif

			Pm0->k = m.k;
			Pm0->t = m.t;

			//! m4x4
			for (uint8_t l1 = 0; l1 < 4; ++l1)
			{
				*(float *)(smptr_cemPbuffer_map[smpt_rd_vk_swc_frame_buffer + l0 * smpt_rd_vk_swc_image] + l1 * sizeof(float)) = 1.0;
			}
			memcpy(smptr_cemPbuffer_map[smpt_rd_vk_swc_frame_buffer + l0 * smpt_rd_vk_swc_image] + 4 * sizeof(float), lcp_a_p[m.m], lcp_joint_count_p[m.m] * 4 * 3 * sizeof(float));
			//apply r
			mv4_q(0, NALI_M_D2R(-45), NALI_M_D2R(-180), smptr_cemPbuffer_map[smpt_rd_vk_swc_frame_buffer + l0 * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4);
			//apply t
			*(float *)(smptr_cemPbuffer_map[smpt_rd_vk_swc_frame_buffer + l0 * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 2 + 2 * sizeof(float)) = -3.0;
			vkFlushMappedMemoryRanges(vkdevice, 1, &(VkMappedMemoryRange)
			{
				.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
				.memory = Pvkdevicememory[smpt_rd_vk_swc_frame_buffer],
				.offset = 0,
				.size = ((sizeof(float) * 4 * 4 * (m.m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[m.m])) + (smpt_rd_vk_non_coherent_atom_size - 1)) & ~(smpt_rd_vk_non_coherent_atom_size - 1),
				.pNext = VK_NULL_HANDLE
			});
		}
		else if (state & 2)
		{
			Pm0->k = m.k;
			Pm0->t = m.t;
		}
		else
		{
			//.i k t *d
		}

		smptr_cemLm1 += m.l;
	}
	Lm0 = smptrLm;
	#ifdef SMPT_CM_VK
		vkUpdateDescriptorSets(vkdevice, SMPT_RD_VKW_DSTSLO_L * smpt_rd_vk_swc_image * Ldst, Pvkwritedescriptorset, 0, VK_NULL_HANDLE);
		Ldst = 0;
		Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, 0);
		Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, 0);
	#endif

	//.i add m1
	smptr_cemPm1 = realloc(smptr_cemPm1, sizeof(struct SMPTR_CEMsM1) * smptr_cemLm1);
	smptr_cemLm1 = 0;
	for (SMPTRtMI l0 = 0; l0 < Lm0; ++l0)
	{
		struct SMPTRsM m = smptrPm[l0];
		for (uint8_t l1 = 0; l1 < m.l; ++l1)
		{
			struct SMPTR_CEMsM1 *Pm1 = smptr_cemPm1 + smptr_cemLm1++;
			Pm1->i = l0;
			Pm1->a = m.Pa[l1];
			//! set offset
			Pm1->b = Pm1->a < SMPTReMAc + SMPTReMc ? smptrPmb[Pm1->a] : Pm1->a;
//			SMPT_DB_N2L("Pm1->b %d", Pm1->b)
			//! find depth
			Pm1->d = 0;
		}
	}
}

void smptr_cemMfree()
{
	#ifdef SMPT_CM_VK
		VkDevice vkdevice = smpt_rd_vkq_dv_p[smpt_rd_vk_device];

		free(Pvkdescriptorbufferinfo);
		free(Pvkwritedescriptorset);

		vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstsp, Lm0 * smpt_rd_vk_swc_image, smptr_cemPvkdescriptorset);
		for (SMPTRtMI l0 = 0; l0 < Lm0 * smpt_rd_vk_swc_image; ++l0)
		{
			vkUnmapMemory(vkdevice, Pvkdevicememory[l0]);
			vkDestroyBuffer(vkdevice, smptr_cemPvkbuffer[l0], VK_NULL_HANDLE);
			vkFreeMemory(vkdevice, Pvkdevicememory[l0], VK_NULL_HANDLE);
		}
		free(Pvkdevicememory);
		free(smptr_cemPbuffer_map);
		free(smptr_cemPvkbuffer);

		free(smptr_cemPvkdescriptorset);
	#endif

	free(smptr_cemPm1);
	//! test
	free(smptrPm);
}

////! sync
////.i cull on server
////.i cull on client
////.i client do render/input only
////.i both
//void smpt_ar_md_set()
//{
//	VkDevice vkdevice = smpt_rd_vkq_dv_p[smpt_rd_vk_device];
//	#define NALI_TEST_map_p ebpomi2_map_p
//	#define NALI_TEST_mab 1
//	#define NALI_TEST_m SMPTReM_POMI_PAPI
//	#define NALI_TEST_ds 0
//
//	//! in loop
//	lcm_ds_bl = 1;
//	lcm_vkbuffer_p = realloc(lcm_vkbuffer_p, sizeof(VkBuffer) * smpt_rd_vk_swc_image * lcm_ds_bl);
//	lcm_vkbuffer_mp = realloc(lcm_vkbuffer_mp, sizeof(void *) * smpt_rd_vk_swc_image * lcm_ds_bl);
//	lcm_vkdevicememory_p = realloc(lcm_vkdevicememory_p, sizeof(VkDeviceMemory) * smpt_rd_vk_swc_image * lcm_ds_bl);
//	for (uint8_t l_0 = 0; l_0 < smpt_rd_vk_swc_image; ++l_0)
//	{
//		for (uint8_t l_1 = 0; l_1 < lcm_ds_bl; ++l_1)
//		{
//			//! m
//			VkDeviceSize vkdevicesize = sizeof(float) * 4 * 4 * (NALI_TEST_m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[NALI_TEST_m]);
//
//			VkMemoryRequirements vkmemoryrequirements;
//			vkdevicesize = (vkdevicesize + (smpt_rd_vk_non_coherent_atom_size - 1)) & ~(smpt_rd_vk_non_coherent_atom_size - 1);
//			SMPT_RD_VK_BF_MAKE(smpt_rd_vk_device, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, lcm_vkbuffer_p[l_0 + l_1 * smpt_rd_vk_swc_image], lcm_vkdevicememory_p[l_0 + l_1 * smpt_rd_vk_swc_image], vkmemoryrequirements)
//			SMPT_DB_R2L("vkMapMemory %d", vkMapMemory(vkdevice, lcm_vkdevicememory_p[l_0 + l_1 * smpt_rd_vk_swc_image], 0, vkdevicesize, 0, &lcm_vkbuffer_mp[(l_0 + l_1 * smpt_rd_vk_swc_image)]))
//		}
//	}
//
//	VkWriteDescriptorSet vkwritedescriptorset_p[SMPT_RD_VKW_DSTSLO_L * smpt_rd_vk_swc_image * lcm_ds_bl];
//	VkDescriptorBufferInfo vkdescriptorbufferinfo_p[3 + 2 * smpt_rd_vk_swc_image * lcm_ds_bl];
//	smptr_ce_sd_sti_l = NALI_TEST_map_p[0] - 1;
//	smptr_ce_sd_sti_p = realloc(smptr_ce_sd_sti_p, sizeof(struct smptr_ce_sd_sti) * smptr_ce_sd_sti_l);
//	//.i ds == 1
//	//! need free
//	VkDescriptorSet *vkdescriptorset_p = malloc(sizeof(VkDescriptorSet) * smpt_rd_vk_swc_image * lcm_ds_bl);
//	for (uint8_t l_0 = 0; l_0 < smpt_rd_vk_swc_image * lcm_ds_bl; ++l_0)
//	{
//		smpt_rd_vkw_dsts_make(smpt_rd_vk_device, vkdescriptorset_p + l_0);
//	}
//	smpt_rd_vkw_dsts
//	(
//		vkdescriptorset_p,
//		vkdescriptorbufferinfo_p,
//		vkwritedescriptorset_p,
//		0,
//		NALI_TEST_m < lcp_joint_count_bl ? NALI_TEST_m : 0,
//		NALI_TEST_m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[NALI_TEST_m]//mj
//	);
//	vkUpdateDescriptorSets(vkdevice, SMPT_RD_VKW_DSTSLO_L * smpt_rd_vk_swc_image * lcm_ds_bl, vkwritedescriptorset_p, 0, VK_NULL_HANDLE);
//	smptr_ce_sd_st_p[0].vkdescriptorset_p = vkdescriptorset_p;
//	for (uint8_t l_0 = 1; l_0 < NALI_TEST_map_p[0]; ++l_0)
//	{
//		uint8_t ma = NALI_TEST_map_p[l_0];
//		smptr_ce_sd_sti_p[l_0 - 1].mi = 0;
//		smptr_ce_sd_sti_p[l_0 - 1].ma = ma;
//		smptr_ce_sd_sti_p[l_0 - 1].mab = NALI_TEST_mab;
//	}
//
//	//a
//	if (NALI_TEST_m < lcp_joint_count_bl)
//	{
//		//apply rgba
//		for (uint8_t l_0 = 0; l_0 < 4; ++l_0)
//		{
//			*(float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + l_0 * sizeof(float)) = 1.0;
//		}
//		//apply default a
//		memcpy(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float), lcp_a_p[NALI_TEST_m], lcp_joint_count_p[NALI_TEST_m] * 4 * 3 * sizeof(float));
//		//apply a 0
//		uint8_t l_kf_a = 0;
//		uint8_t key = 10;//1
//		struct lckf l_lckf = lckf_p[l_kf_a][key];
//		for (uint8_t l_0 = 0; l_0 < l_lckf.bone_bl; ++l_0)
//		{
//			memcpy(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3, l_lckf.s_p[l_0], sizeof(float) * 3);
//			memcpy(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4, l_lckf.r_p[l_0], sizeof(float) * 4);
//			memcpy(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4 * 2, l_lckf.t_p[l_0], sizeof(float) * 3);
//		}
//		//mv4_q(NALI_M_D2R(45), 0, 0, lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 + 1 * sizeof(float) * 4 * 3);
////		//apply s to mid
////		*(float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 12) = 0;
////		*(float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 12 + 1 * sizeof(float)) = 0;
////		*(float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 12 + 2 * sizeof(float)) = 0;
////		//apply s to tail
////		*(float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 2) = 0;
////		*(float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 2 + 1 * sizeof(float)) = 0;
////		*(float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 3 * 2 + 2 * sizeof(float)) = 0;
//		//apply r to top
//		//mv4_q(0, NALI_M_D2R(-45), 0, lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 + 31 * sizeof(float) * 4 * 3);
//		//apply r
//		mv4_q(0, NALI_M_D2R(-45), NALI_M_D2R(-180), lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4);
//		//apply t
//		//*(float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 2 + 0 * sizeof(float)) = 1.0;
//		//*(float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 2 + 1 * sizeof(float)) = -1.0;
//		*(float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 2 + 2 * sizeof(float)) = -3.0;
//	}
//	//update m v p later
//	//update buffer
//	//! use atom to all flush
//	//! avoid flush if able
//	vkFlushMappedMemoryRanges(vkdevice, 1, &(VkMappedMemoryRange)
//	{
//		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
//		.memory = lcm_vkdevicememory_p[smpt_rd_vk_swc_frame_buffer],
//		.offset = 0,
//		.size = ((sizeof(float) * 4 * 4 * (NALI_TEST_m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[NALI_TEST_m])) + (smpt_rd_vk_non_coherent_atom_size - 1)) & ~(smpt_rd_vk_non_coherent_atom_size - 1),
//		.pNext = VK_NULL_HANDLE
//	});
//}
//
////.i /255
//static uint8_t aki = 0;
//static uint8_t
//	l_ak_current,
//	l_ak_next;
//
//static double t_s_kf = 3 * 255;
//static uint16_t t_s2c_kf = 0;
//
//////.i kf 3 4 5
////static uint8_t key = 3;
////static uint8_t l_kf_a = 0;
//static struct timespec frame_start = {0}, frame_end;
//void smpt_ar_md_loop()
//{
//	#ifdef SMPT_CM_RAW
//		SMPTRB_AKT
//			a = lb_ak_p[aki][0],
//			k_s = lb_ak_p[aki][1],
//			k_e = lb_ak_p[aki][2];
//
//		smpt_rd_vk_swc_frame_buffer = (smpt_rd_vk_swc_frame_buffer + 1) % smpt_rd_vk_swc_image;
//		if (NALI_TEST_m < lcp_joint_count_bl)
//		{
//			//apply rgba
//			for (uint8_t l_0 = 0; l_0 < 4; ++l_0)
//			{
//				*(float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + l_0 * sizeof(float)) = 1.0;
//			}
//			//apply default a
//			memcpy(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float), lcp_a_p[NALI_TEST_m], lcp_joint_count_p[NALI_TEST_m] * 4 * 3 * sizeof(float));
//		}
//
//		//.i apply default view
//		mv4_q(0, NALI_M_D2R(-45), NALI_M_D2R(-180), lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4);
//		*(float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + sizeof(float) * 4 * 2 + 2 * sizeof(float)) = -3.0;
//
//	//	//.i apply a loop
//	//	lckf l_lckf = lckf_p[l_kf_a][key];
//	//	for (uint8_t l_0 = 0; l_0 < l_lckf.bone_bl; ++l_0)
//	//	{
//	//		memcpy(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3, l_lckf.s_p[l_0], sizeof(float) * 3);
//	//		memcpy(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4, l_lckf.r_p[l_0], sizeof(float) * 4);
//	//		memcpy(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4 * 2, l_lckf.t_p[l_0], sizeof(float) * 3);
//	//	}
//	//	if (frame_time >= 1.0)
//	//	{
//	//		frame_start = frame_end;
//	//		key = (key + 1);
//	//		if (key == 6)
//	//		{
//	//			key = 3;
//	//		}
//	//	}
//
//		//.i float -> uint -> float
//		clock_gettime(CLOCK_MONOTONIC, &frame_end);
//		double frame_time = frame_end.tv_sec + (double)frame_end.tv_nsec / 1e9 - frame_start.tv_sec - (double)frame_start.tv_nsec / 1e9;
//		t_s_kf += 255 * 4 * frame_time;
//		frame_start = frame_end;
//		t_s_kf = NALI_M_WRAP_F(t_s_kf, k_s * 255, k_e * 255);
//	//	SMPT_DB_N2L("t_s_kf %f", t_s_kf);
//		double kff = t_s_kf / 255;
//		l_ak_current = kff;
//		kff -= l_ak_current;
//
//		l_ak_next = NALI_M_WRAP_I(l_ak_current + 1, k_s, k_e);
//		struct lckf l_lckf = lckf_p[a][l_ak_current];
//		for (uint8_t l_0 = 0; l_0 < l_lckf.bone_bl; ++l_0)
//		{
//			memcpy(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3, l_lckf.s_p[l_0], sizeof(float) * 3);
//			memcpy(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4, l_lckf.r_p[l_0], sizeof(float) * 4);
//			memcpy(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4 * 2, l_lckf.t_p[l_0], sizeof(float) * 3);
//		}
//
//		l_lckf = lckf_p[a][l_ak_next];
//		for (uint8_t l_0 = 0; l_0 < l_lckf.bone_bl; ++l_0)
//		{
//			for (uint8_t l_3 = 0; l_3 < 3; ++l_3)
//			{
//				NALI_M_LERP(((float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3))[l_3], l_lckf.s_p[l_0][l_3], kff);
//				NALI_M_LERP(((float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4 * 2))[l_3], l_lckf.t_p[l_0][l_3], kff);
//			}
//
//			for (uint8_t l_3 = 0; l_3 < 4; ++l_3)
//			{
//				NALI_M_LERP(((float *)(lcm_vkbuffer_mp[smpt_rd_vk_swc_frame_buffer + NALI_TEST_ds * smpt_rd_vk_swc_image] + 4 * sizeof(float) + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4))[l_3], l_lckf.r_p[l_0][l_3], kff);
//			}
//		}
//	//	SMPT_DB_N2L("kff %f", kff);
//	//	SMPT_DB_N2L("l_ak_current %d", l_ak_current);
//	//	SMPT_DB_N2L("l_ak_next %d", l_ak_next);
//
//		vkFlushMappedMemoryRanges(smpt_rd_vkq_dv_p[smpt_rd_vk_device], 1, &(VkMappedMemoryRange)
//		{
//			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
//			.memory = lcm_vkdevicememory_p[smpt_rd_vk_swc_frame_buffer],
//			.offset = 0,
//			.size = ((sizeof(float) * 4 * 4 * (NALI_TEST_m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[NALI_TEST_m])) + (smpt_rd_vk_non_coherent_atom_size - 1)) & ~(smpt_rd_vk_non_coherent_atom_size - 1),
//			.pNext = VK_NULL_HANDLE
//		});
//	#else
//		//! check data
//		nc_send();
//
//		// clock_gettime(CLOCK_MONOTONIC, &delta_end);
//		// lc_delta = delta_end.tv_sec + (double)delta_end.tv_nsec / 1e9 - delta_start.tv_sec - (double)delta_start.tv_nsec / 1e9;
//		// // ry += M_MIN(0.5F * (delta_end.tv_sec + delta_end.tv_nsec / 1e9 - delta_start.tv_sec - delta_start.tv_nsec / 1e9), 1.0F);
//		// delta_start = delta_end;
//
//		// for (uint8_t l_0 = 0; l_0 < vk_cmd_d_fp_bl; ++l_0)
//		// {
//		// 	//model add/update
//		// 	vk_cmd_d_fp[l_0]();
//		// }
//
//		nc_get();
//		lcu_update();
//		lcm_update();
//		// lcs_loop();
//	#endif
//}
