#ifdef SMPT_CM_VK
	VkDescriptorSet *smptr_cemPvkdescriptorset;

	VkBuffer *smptr_cemPvkbuffer;
	static void **smptr_cemPbuffer_map;
	static VkDeviceMemory *Pvkdevicememory;

	static VkWriteDescriptorSet *Pvkwritedescriptorset;
	static VkDescriptorBufferInfo *Pvkdescriptorbufferinfo;
	static SMPTRtMI Ldst = 0;

	static VkMappedMemoryRange *Pvkmappedmemoryrange;

	static VkDescriptorSet *Pvkdescriptorset_free;
	static VkBuffer *Pvkbuffer_free;
	static VkDeviceMemory *Pvkdevicememory_free;
	static uint8_t *Pfree;
	static uint32_t Lfree;
#endif

struct SMPTR_CEMsM
{
	struct SMPTRsM Sm;
	float Ft;
	//float Pttr[3 + 1 + 2];
};
static struct SMPTR_CEMsM *smptr_cemPm;
static SMPTRtMI smptr_cemLm = 0;

struct SMPTR_CEMsM0
{
	SMPTRtM Um;
	SMPTRtMK Uk;
	SMPTRtMT Ut;
	//float Ptr[3 + 1 + 2];
};
static struct SMPTR_CEMsM0 smptr_cemPm0[SMPTRmMI];

struct SMPTR_CEMsM01
{
	uint8_t Uf;
	float Ft;
	//float Ptr[3 + 1 + 2];
};
static struct SMPTR_CEMsM01 smptr_cemPm01[SMPTRmMI];

struct SMPTR_CEMsM1 *smptr_cemPm1;
uint32_t smptr_cemLm1 = 0;

void smptr_cemMset()
{
	smptr_cemPm = malloc(0);

	smptr_cemPm1 = malloc(0);

	#ifdef SMPT_CM_VK
		smptr_cemPvkdescriptorset = malloc(0);

		smptr_cemPvkbuffer = malloc(0);
		smptr_cemPbuffer_map = malloc(0);
		Pvkdevicememory = malloc(0);

		Pvkwritedescriptorset = malloc(0);
		Pvkdescriptorbufferinfo = malloc(0);

		Pvkmappedmemoryrange = malloc(0);

		Pvkdescriptorset_free = malloc(0);
		Pvkbuffer_free = malloc(0);
		Pvkdevicememory_free = malloc(0);
		Pfree = malloc(0);
	#endif
}

static void Mfree_m(SMPTRtMI Us, SMPTRtMI Ue)
{
	for (SMPTRtMI l0 = Us; l0 < Ue; ++l0)
	{
		if (smptr_cemPm[l0].Sm.Um != SMPTRvM)
		{
			free(smptr_cemPm[l0].Sm.Pa);
			free(smptr_cemPm[l0].Sm.Sm0.Ptr);
		}
	}
}

static void Mfree_vk(SMPTRtMI Us, SMPTRtMI Ue)
{
	Pvkdescriptorset_free = realloc(Pvkdescriptorset_free, sizeof(VkDescriptorSet) * (Lfree + Ue - Us) * smpt_rd_vk_swcUimage);
	Pvkbuffer_free = realloc(Pvkbuffer_free, sizeof(VkBuffer) * (Lfree + Ue - Us) * smpt_rd_vk_swcUimage);
	Pvkdevicememory_free = realloc(Pvkdevicememory_free, sizeof(VkDeviceMemory) * (Lfree + Ue - Us) * smpt_rd_vk_swcUimage);
	Pfree = realloc(Pfree, sizeof(uint8_t) * (Lfree + Ue - Us));
	for (uint32_t l0 = Lfree; l0 < Lfree + Ue - Us; ++l0)
	{
		Pfree[l0] = 1 << smpt_rd_vk_swcUimage;
	}
	memcpy(Pvkdescriptorset_free + Lfree * smpt_rd_vk_swcUimage, smptr_cemPvkdescriptorset + Us * smpt_rd_vk_swcUimage, sizeof(VkDescriptorSet) * (Ue - Us) * smpt_rd_vk_swcUimage);
	memcpy(Pvkbuffer_free + Lfree * smpt_rd_vk_swcUimage, smptr_cemPvkbuffer + Us * smpt_rd_vk_swcUimage, sizeof(VkBuffer) * (Ue - Us) * smpt_rd_vk_swcUimage);
	memcpy(Pvkdevicememory_free + Lfree * smpt_rd_vk_swcUimage, smptr_cemPvkbuffer + Us * smpt_rd_vk_swcUimage, sizeof(VkDeviceMemory) * (Ue - Us) * smpt_rd_vk_swcUimage);
	Lfree += Ue - Us;
}

//.i sync n-mn
static SMPTRtMI Lm0 = 0;
void smptr_cemMread()
{
	//.i get data
	SMPTRtMI Ucount = *(SMPTRtMI *)(smptr_cePnet + smptr_ceLnet);
	smptr_ceLnet += sizeof(SMPTRtMI);

	Mfree_m(Ucount, smptr_cemLm);
	smptr_cemLm = Ucount;
	smptr_cemPm = realloc(smptr_cemPm, sizeof(struct SMPTR_CEMsM) * smptr_cemLm);

	//SMPT_DBmN2L("Ucount %d", Ucount)
	for (SMPTRtMI l0 = 0; l0 < Ucount; ++l0)
	{
		struct SMPTR_CEMsM *Pm = smptr_cemPm + l0;

		Pm->Sm.Um = *(SMPTRtM *)(smptr_cePnet + smptr_ceLnet);
		smptr_ceLnet += sizeof(SMPTRtM);
		//SMPT_DBmN2L("Pm->Sm.Um %d", Pm->Sm.Um)
		if (Pm->Sm.Um != SMPTRvM)
		{
			Pm->Sm.La = *(uint8_t *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(uint8_t);

			Pm->Sm.Pa = malloc(sizeof(SMPTRtMA) * Pm->Sm.La);
			memcpy(Pm->Sm.Pa, smptr_cePnet + smptr_ceLnet, sizeof(SMPTRtMA) * Pm->Sm.La);
			smptr_ceLnet += sizeof(SMPTRtMA) * Pm->Sm.La;

			Pm->Sm.Uk = *(SMPTRtMK *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(SMPTRtMK);

			Pm->Sm.Ut = *(SMPTRtMT *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(SMPTRtMT);
			//SMPT_DBmN2L("Pm->Sm.Ut %d", Pm->Sm.Ut)

			Pm->Sm.Sm0.Ltr = *(uint8_t *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(uint8_t);

			Pm->Sm.Sm0.Ptr = malloc(sizeof(float) * Pm->Sm.Sm0.Ltr);
			memcpy(Pm->Sm.Sm0.Ptr, smptr_cePnet + smptr_ceLnet, sizeof(float) * Pm->Sm.Sm0.Ltr);
			smptr_ceLnet += sizeof(float) * Pm->Sm.Sm0.Ltr;
		}
	}

	//.i clean m0
	#ifdef SMPT_CM_VK
		VkDevice vkdevice = smpt_rd_vkq_dv_p[smpt_rd_vk_device];

		if (smptr_cemLm < Lm0)
		{
			Mfree_vk(smptr_cemLm, Lm0);

//			vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstsp, (Lm0 - smptr_cemLm) * smpt_rd_vk_swcUimage, smptr_cemPvkdescriptorset + smptr_cemLm * smpt_rd_vk_swcUimage);
//			for (SMPTRtMI l0 = smptr_cemLm * smpt_rd_vk_swcUimage; l0 < Lm0 * smpt_rd_vk_swcUimage; ++l0)
//			{
//				vkUnmapMemory(vkdevice, Pvkdevicememory[l0]);
//				vkDestroyBuffer(vkdevice, smptr_cemPvkbuffer[l0], VK_NULL_HANDLE);
//				vkFreeMemory(vkdevice, Pvkdevicememory[l0], VK_NULL_HANDLE);
//			}
		}
		smptr_cemPvkdescriptorset = realloc(smptr_cemPvkdescriptorset, sizeof(VkDescriptorSet) * smpt_rd_vk_swcUimage * smptr_cemLm);
		smptr_cemPvkbuffer = realloc(smptr_cemPvkbuffer, sizeof(VkBuffer) * smpt_rd_vk_swcUimage * smptr_cemLm);
		smptr_cemPbuffer_map = realloc(smptr_cemPbuffer_map, sizeof(void *) * smpt_rd_vk_swcUimage * smptr_cemLm);
		Pvkdevicememory = realloc(Pvkdevicememory, sizeof(VkDeviceMemory) * smpt_rd_vk_swcUimage * smptr_cemLm);
		for (SMPTRtMI l0 = Lm0 * smpt_rd_vk_swcUimage; l0 < smptr_cemLm * smpt_rd_vk_swcUimage; ++l0)
			smptr_cemPvkdescriptorset[l0] = 0;

		Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, 0);
		Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, 0);
	#endif

	//.i update m
	smptr_cemLm1 = 0;
	for (SMPTRtMI l0 = 0; l0 < smptr_cemLm; ++l0)
	{
		struct SMPTR_CEMsM *Pm = smptr_cemPm + l0;
		if (Pm->Sm.Um == SMPTRvM)
		{
			if (smptr_cemPvkdescriptorset[l0])
			{
				vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstsp, smpt_rd_vk_swcUimage, smptr_cemPvkdescriptorset + l0 * smpt_rd_vk_swcUimage);
				for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
				{
					vkUnmapMemory(vkdevice, Pvkdevicememory[l0 * smpt_rd_vk_swcUimage + l1]);
					vkDestroyBuffer(vkdevice, smptr_cemPvkbuffer[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
					vkFreeMemory(vkdevice, Pvkdevicememory[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
				}
			}
		}
		else
		{
			struct SMPTR_CEMsM0 *Pm0 = smptr_cemPm0 + l0;
			struct SMPTR_CEMsM01 *Pm01 = smptr_cemPm01 + l0;

			#ifdef SMPT_CM_VK
				if (Lm0 <= l0 || !smptr_cemPvkdescriptorset[l0] || Pm0->Um != Pm->Sm.Um)
			#endif
			{
				#ifdef SMPT_CM_VK
					if (smptr_cemPvkdescriptorset[l0])
					{
						Mfree_vk(l0, l0 + 1);

//						vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstsp, smpt_rd_vk_swcUimage, smptr_cemPvkdescriptorset + l0 * smpt_rd_vk_swcUimage);
//						for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
//						{
//							vkUnmapMemory(vkdevice, Pvkdevicememory[l0 * smpt_rd_vk_swcUimage + l1]);
//							vkDestroyBuffer(vkdevice, smptr_cemPvkbuffer[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
//							vkFreeMemory(vkdevice, Pvkdevicememory[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
//						}
					}

					for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
					{
						VkDeviceSize vkdevicesize = sizeof(float) * 4 * 4 * (Pm->Sm.Um >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[Pm->Sm.Um]);

						VkMemoryRequirements vkmemoryrequirements;
						vkdevicesize = (vkdevicesize + (smpt_rd_vk_non_coherent_atom_size - 1)) & ~(smpt_rd_vk_non_coherent_atom_size - 1);
						SMPT_RD_VK_BF_MAKE(smpt_rd_vk_device, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_cemPvkbuffer[l1 + l0 * smpt_rd_vk_swcUimage], Pvkdevicememory[l1 + l0 * smpt_rd_vk_swcUimage], vkmemoryrequirements)
						SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(vkdevice, Pvkdevicememory[l1 + l0 * smpt_rd_vk_swcUimage], 0, vkdevicesize, 0, &smptr_cemPbuffer_map[(l1 + l0 * smpt_rd_vk_swcUimage)]))
					}

					++Ldst;
					Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, SMPT_RD_VKW_DSTSLO_L * smpt_rd_vk_swcUimage * Ldst * sizeof(VkWriteDescriptorSet));
					Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, (2 + 3 * smpt_rd_vk_swcUimage * Ldst) * sizeof(VkDescriptorBufferInfo));

					for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
					{
						smpt_rd_vkw_dsts_make(smpt_rd_vk_device, smptr_cemPvkdescriptorset + l1 + l0 * smpt_rd_vk_swcUimage);
					}
					smpt_rd_vkw_dsts
					(
						smptr_cemPvkdescriptorset + l0 * smpt_rd_vk_swcUimage,
						Pvkdescriptorbufferinfo + (Ldst - 1) * smpt_rd_vk_swcUimage,
						Pvkwritedescriptorset + (Ldst - 1) * smpt_rd_vk_swcUimage,
						l0,
						Pm->Sm.Um < lcp_joint_count_bl ? Pm->Sm.Um : 0,
						Pm->Sm.Um >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[Pm->Sm.Um],
						1 + 1 * smpt_rd_vk_swcUimage
					);
				#endif

				Pm01->Uf = SMPTR_CEuFPS;
				Pm01->Ft = Pm->Sm.Ut / 255.0F;
				Pm0->Uk = Pm->Sm.Uk;
				Pm0->Ut = Pm->Sm.Ut;
				Pm0->Um = Pm->Sm.Um;
			}
			else if (Pm0->Uk != Pm->Sm.Uk)
			{
				Pm01->Uf = SMPTR_CEuFPS;
				Pm01->Ft = Pm->Sm.Ut / 255.0F;
				Pm0->Uk = Pm->Sm.Uk;
				Pm0->Ut = Pm->Sm.Ut;
			}
			else if (Pm0->Ut != Pm->Sm.Ut)
			{
				const SMPTRtMK *Pk = smptrPmk[Pm->Sm.Uk];

				Pm01->Uf = 0;
//				Pm->Ft = (Pm->Sm.Ut - Pm0->Ut) / 255.0F * SMPTR_CEuDELTA;
				if (Pm->Sm.Ut < Pm0->Ut)
				{
					Pm->Ft = Pk[2] * 255 - Pm0->Ut + Pm->Sm.Ut - Pk[1] * 255;
				}
				else
				{
					Pm->Ft = Pm->Sm.Ut - Pm0->Ut;
				}
				//Pm->Ft /= 255.0F;
				Pm->Ft *= SMPTR_CEuDELTA;

				Pm0->Ut = Pm->Sm.Ut;
			}

			smptr_cemLm1 += Pm->Sm.La;
		}
	}
	#ifdef SMPT_CM_VK
		vkUpdateDescriptorSets(vkdevice, SMPT_RD_VKW_DSTSLO_L * smpt_rd_vk_swcUimage * Ldst, Pvkwritedescriptorset, 0, VK_NULL_HANDLE);
		Ldst = 0;
		Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, 0);
		Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, 0);
	#endif

	//.i add m1
	smptr_cemPm1 = realloc(smptr_cemPm1, sizeof(struct SMPTR_CEMsM1) * smptr_cemLm1);
	smptr_cemLm1 = 0;
	for (SMPTRtMI l0 = 0; l0 < smptr_cemLm; ++l0)
	{
		struct SMPTR_CEMsM m = smptr_cemPm[l0];
		if (m.Sm.Um != SMPTRvM)
			for (uint8_t l1 = 0; l1 < m.Sm.La; ++l1)
			{
				struct SMPTR_CEMsM1 *Pm1 = smptr_cemPm1 + smptr_cemLm1++;
				Pm1->Ui = l0;
				Pm1->Ua = m.Sm.Pa[l1];
				//! set offset
				Pm1->Ub = Pm1->Ua < SMPTReMAc + SMPTReMc ? smptrPmb[Pm1->Ua] : Pm1->Ua;
//				SMPT_DBmN2L("Pm1->Ub %d", Pm1->Ub)
				//! find depth
				Pm1->Fd = 0;
			}
	}

	Lm0 = smptr_cemLm;
}

void smptr_cemMloop()
{
	#ifdef SMPT_CM_VK
		VkDevice vkdevice = smpt_rd_vkq_dv_p[smpt_rd_vk_device];

		//.i free
		uint32_t Ufree = Lfree;
		for (uint32_t l0 = 0; l0 < Lfree; ++l0)
		{
			if ((Pfree[l0] = Pfree[l0] >> 1) == 0)
			{
				vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstsp, smpt_rd_vk_swcUimage, Pvkdescriptorset_free + l0 * smpt_rd_vk_swcUimage);
				for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
				{
					vkUnmapMemory(vkdevice, Pvkdevicememory_free[l0 * smpt_rd_vk_swcUimage + l1]);
					vkDestroyBuffer(vkdevice, Pvkbuffer_free[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
					vkFreeMemory(vkdevice, Pvkdevicememory_free[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
				}
				if (Ufree == Lfree)
					Ufree = l0;
			}
			else
			{
				Ufree = Lfree;
			}
		}
		Pvkdescriptorset_free = realloc(Pvkdescriptorset_free, sizeof(VkDescriptorSet) * Ufree * smpt_rd_vk_swcUimage);
		Pvkbuffer_free = realloc(Pvkbuffer_free, sizeof(VkBuffer) * Ufree * smpt_rd_vk_swcUimage);
		Pvkdevicememory_free = realloc(Pvkdevicememory_free, sizeof(VkDeviceMemory) * Ufree * smpt_rd_vk_swcUimage);
		Pfree = realloc(Pfree, sizeof(uint8_t) * Ufree);
		Lfree = Ufree;

		//! find depth
		//.i update buffer
		//SMPT_DBmN2L("smptr_cemLm %d", smptr_cemLm)
		SMPTRtMI L = 0;
		for (SMPTRtMI l0 = 0; l0 < smptr_cemLm; ++l0)
		{
			struct SMPTR_CEMsM m = smptr_cemPm[l0];
			struct SMPTR_CEMsM01 *Pm01 = smptr_cemPm01 + l0;
			//SMPT_DBmN2L("m.Sm.Um %d", m.Sm.Um)

			if (m.Sm.Um != SMPTRvM)
			{
				float *Pbuffer = smptr_cemPbuffer_map[smpt_rd_vk_swcUframe_buffer + l0 * smpt_rd_vk_swcUimage];
				for (uint8_t l1 = 0; l1 < 4; ++l1)
				{
					*(float *)(Pbuffer + l1) = 1.0;
				}
				memcpy(Pbuffer + 4, lcp_a_p[m.Sm.Um], lcp_joint_count_p[m.Sm.Um] * 4 * 3 * sizeof(float));
				if (m.Sm.Um < lcp_joint_count_bl)
				{
					const SMPTRtMK *Pk = smptrPmk[m.Sm.Uk];

					if (Pm01->Uf != SMPTR_CEuFPS)
					{
						Pm01->Ft += m.Ft;
						Pm01->Ft = NALI_M_WRAP_F(Pm01->Ft, Pk[1], Pk[2]);
						++Pm01->Uf;
					}

					SMPTRtMK Uks = Pm01->Ft;
					float Fkf = Pm01->Ft - Uks;
					SMPTRtMK Uke = SMPTMmWRAP_I(Uks + 1, Pk[1], Pk[2]);
					struct lckf l_lckf = lckf_p[Pk[0]][Uks];
					//SMPT_DBmN2L("Uks %d", Uks)
					//SMPT_DBmN2L("Fkf %f", Fkf)
					//SMPT_DBmN2L("Uke %d", Uke)
					for (uint8_t l_0 = 0; l_0 < l_lckf.bone_bl; ++l_0)
					{
						memcpy(Pbuffer + 4 + l_lckf.bone_p[l_0] * 4 * 3, l_lckf.s_p[l_0], sizeof(float) * 3);
						memcpy(Pbuffer + 4 + l_lckf.bone_p[l_0] * 4 * 3 + 4, l_lckf.r_p[l_0], sizeof(float) * 4);
						memcpy(Pbuffer + 4 + l_lckf.bone_p[l_0] * 4 * 3 + 4 * 2, l_lckf.t_p[l_0], sizeof(float) * 3);
					}

					l_lckf = lckf_p[Pk[0]][Uke];
					for (uint8_t l_0 = 0; l_0 < l_lckf.bone_bl; ++l_0)
					{
						for (uint8_t l_3 = 0; l_3 < 3; ++l_3)
						{
							SMPTMmLERP(((float *)(Pbuffer + 4 + l_lckf.bone_p[l_0] * 4 * 3))[l_3], l_lckf.s_p[l_0][l_3], Fkf);
							SMPTMmLERP(((float *)(Pbuffer + 4 + l_lckf.bone_p[l_0] * 4 * 3 + 4 * 2))[l_3], l_lckf.t_p[l_0][l_3], Fkf);
						}

						for (uint8_t l_3 = 0; l_3 < 4; ++l_3)
						{
							SMPTMmLERP(((float *)(Pbuffer + 4 + l_lckf.bone_p[l_0] * 4 * 3 + 4))[l_3], l_lckf.r_p[l_0][l_3], Fkf);
						}
					}
				}
//				smptm_v4Mq(0, SMPTMmD2R(-45), 0, Pbuffer + 4 + 4);
				*(float *)(Pbuffer + 4 + 4 * 2) = m.Sm.Sm0.Ptr[0];
				*(float *)(Pbuffer + 4 + 4 * 2 + 1) = m.Sm.Sm0.Ptr[1];
				*(float *)(Pbuffer + 4 + 4 * 2 + 2) = m.Sm.Sm0.Ptr[2];
				Pvkmappedmemoryrange = realloc(Pvkmappedmemoryrange, sizeof(VkMappedMemoryRange) * (L + 1));
				Pvkmappedmemoryrange[L++] = (VkMappedMemoryRange)
				{
					.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
					.memory = Pvkdevicememory[smpt_rd_vk_swcUframe_buffer],
					.offset = 0,
					.size = ((sizeof(float) * 4 * 4 * (m.Sm.Um >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[m.Sm.Um])) + (smpt_rd_vk_non_coherent_atom_size - 1)) & ~(smpt_rd_vk_non_coherent_atom_size - 1),
					.pNext = VK_NULL_HANDLE
				};
			}
		}
		//SMPT_DBmN2L("L %d", L)
		if (L)
			vkFlushMappedMemoryRanges(vkdevice, L, Pvkmappedmemoryrange);
	#endif
}

void smptr_cemMfree()
{
	#ifdef SMPT_CM_VK
		VkDevice vkdevice = smpt_rd_vkq_dv_p[smpt_rd_vk_device];

		if (Lfree)
		{
			vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstsp, Lfree * smpt_rd_vk_swcUimage, Pvkdescriptorset_free);
			for (uint32_t l0 = 0; l0 < Lfree; ++l0)
			{
				for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
				{
					vkUnmapMemory(vkdevice, Pvkdevicememory_free[l0 * smpt_rd_vk_swcUimage + l1]);
					vkDestroyBuffer(vkdevice, Pvkbuffer_free[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
					vkFreeMemory(vkdevice, Pvkdevicememory_free[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
				}
			}
		}
		free(Pfree);
		free(Pvkdevicememory_free);
		free(Pvkbuffer_free);
		free(Pvkdescriptorset_free);

		free(Pvkmappedmemoryrange);

		free(Pvkdescriptorbufferinfo);
		free(Pvkwritedescriptorset);

		for (SMPTRtMI l0 = 0; l0 < Lm0; ++l0)
		{
			struct SMPTR_CEMsM m = smptr_cemPm[l0];
			if (m.Sm.Um != SMPTRvM)
			{
				vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstsp, smpt_rd_vk_swcUimage, smptr_cemPvkdescriptorset + l0 * smpt_rd_vk_swcUimage);

				for (SMPTRtMI l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
				{
					vkUnmapMemory(vkdevice, Pvkdevicememory[l0 * smpt_rd_vk_swcUimage + l1]);
					vkDestroyBuffer(vkdevice, smptr_cemPvkbuffer[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
					vkFreeMemory(vkdevice, Pvkdevicememory[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
				}
			}
		}
		free(Pvkdevicememory);
		free(smptr_cemPbuffer_map);
		free(smptr_cemPvkbuffer);

		free(smptr_cemPvkdescriptorset);
	#endif

	free(smptr_cemPm1);

	Mfree_m(0, Lm0);
	free(smptr_cemPm);
}
