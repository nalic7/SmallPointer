//! a vkbuffer 1 ds
//! macro vkbuffer
#ifdef SMPT_CM_VK
	VkDescriptorSet *smptr_ceaPvkdescriptorset;

	VkBuffer *smptr_ceaPvkbuffer;
	static void **Pbuffer_map;
	static VkDeviceMemory *Pvkdevicememory;

	static VkWriteDescriptorSet *Pvkwritedescriptorset;
	static VkDescriptorBufferInfo *Pvkdescriptorbufferinfo;
	static SMPTRtMI Ldst = 0;

	static VkMappedMemoryRange *Pvkmappedmemoryrange;
#endif

struct SMPTR_CEAsA
{
	struct SMPTRsA Sm;
	float Ft;
	//float Pttr[3 + 1 + 2];
};
static struct SMPTR_CEAsA *smptr_ceaPa;
static SMPTRtMI La = 0;

struct SMPTR_CEAsA0
{
	SMPTRtM Um;
	SMPTRtMK Uk;
	SMPTRtMT Ut;
	//float Ptr[3 + 1 + 2];
};
static struct SMPTR_CEAsA0 smptr_ceaPa0[SMPTRlMI];

struct SMPTR_CEAsA01
{
	uint8_t Uf;
	float Ft;
	//float Ptr[3 + 1 + 2];
};
static struct SMPTR_CEAsA01 smptr_ceaPa01[SMPTRlMI];

uint32_t smptr_ceaLa1 = 0;

void smptr_cemMset()
{
	smptr_ceaPa = malloc(0);

	#ifdef SMPT_CM_VK
		smptr_ceaPvkdescriptorset = malloc(0);

		smptr_ceaPvkbuffer = malloc(0);
		Pbuffer_map = malloc(0);
		Pvkdevicememory = malloc(0);

		Pvkwritedescriptorset = malloc(0);
		Pvkdescriptorbufferinfo = malloc(0);

		Pvkmappedmemoryrange = malloc(0);
	#endif
}

static void Mfree_m(SMPTRtMI Us, SMPTRtMI Ue)
{
	for (SMPTRtMI l0 = Us; l0 < Ue; ++l0)
	{
		if (smptr_ceaPa[l0].Sm.Um != SMPTRvM)
		{
			free(smptr_ceaPa[l0].Sm.Pv);
			free(smptr_ceaPa[l0].Sm.Pc);
		}
	}
}

//.i sync n-mn
static SMPTRtMI Lm0 = 0;
void smptr_cemMread()
{
	//.i get data
	SMPTRtMI Ucount = *(SMPTRtMI *)(smptr_cePnet + smptr_ceLnet);
	smptr_ceLnet += sizeof(SMPTRtMI);

	Mfree_m(Ucount, La);
	La = Ucount;
	smptr_ceaPa = realloc(smptr_ceaPa, sizeof(struct SMPTR_CEAsA) * La);

	//SMPT_DBmN2L("Ucount %d", Ucount)
	for (SMPTRtMI l0 = 0; l0 < Ucount; ++l0)
	{
		struct SMPTR_CEAsA *Pm = smptr_ceaPa + l0;

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
		VkDevice vkdevice = smpt_rd_vkq_dvP[smpt_rd_vkUdevice];

		if (La < Lm0)
			Mfree_vk(La, Lm0);
		smptr_ceaPvkdescriptorset = realloc(smptr_ceaPvkdescriptorset, sizeof(VkDescriptorSet) * smpt_rd_vk_swcUimage * La);
		smptr_ceaPvkbuffer = realloc(smptr_ceaPvkbuffer, sizeof(VkBuffer) * smpt_rd_vk_swcUimage * La);
		Pbuffer_map = realloc(Pbuffer_map, sizeof(void *) * smpt_rd_vk_swcUimage * La);
		Pvkdevicememory = realloc(Pvkdevicememory, sizeof(VkDeviceMemory) * smpt_rd_vk_swcUimage * La);
		for (SMPTRtMI l0 = Lm0; l0 < La; ++l0)
			smptr_ceaPvkdescriptorset[l0 * smpt_rd_vk_swcUimage] = 0;

		Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, 0);
		Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, 0);
	#endif

	//.i update m
	smptr_ceaLa1 = 0;
	for (SMPTRtMI l0 = 0; l0 < La; ++l0)
	{
		struct SMPTR_CEAsA *Pm = smptr_ceaPa + l0;
		struct SMPTR_CEAsA0 *Pm0 = smptr_ceaPa0 + l0;

		if (Pm->Sm.Um == SMPTRvM)
		{
			Pm0->Um = SMPTRvM;
			if (smptr_ceaPvkdescriptorset[l0 * smpt_rd_vk_swcUimage])
			{
				Mfree_vk(l0, l0 + 1);
				smptr_ceaPvkdescriptorset[l0 * smpt_rd_vk_swcUimage] = 0;
			}
		}
		else
		{
			struct SMPTR_CEAsA01 *Pm01 = smptr_ceaPa01 + l0;

			#ifdef SMPT_CM_VK
				if (Lm0 <= l0 || !smptr_ceaPvkdescriptorset[l0 * smpt_rd_vk_swcUimage] || Pm0->Um != Pm->Sm.Um)
			#endif
			{
				#ifdef SMPT_CM_VK
					if (smptr_ceaPvkdescriptorset[l0 * smpt_rd_vk_swcUimage])
						Mfree_vk(l0, l0 + 1);

					for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
					{
						VkDeviceSize vkdevicesize = sizeof(float) * 4 * 4 * (Pm->Sm.Um >= smptr_ce_mdLj ? 1 : smptr_ce_mdPj[Pm->Sm.Um]);

						VkMemoryRequirements vkmemoryrequirements;
						vkdevicesize = (vkdevicesize + (smpt_rd_vkUnon_coherent_atom_size - 1)) & ~(smpt_rd_vkUnon_coherent_atom_size - 1);
						SMPT_RD_VK_BFmMAKE(smpt_rd_vkUdevice, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_ceaPvkbuffer[l1 + l0 * smpt_rd_vk_swcUimage], Pvkdevicememory[l1 + l0 * smpt_rd_vk_swcUimage], vkmemoryrequirements)
						SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(vkdevice, Pvkdevicememory[l1 + l0 * smpt_rd_vk_swcUimage], 0, vkdevicesize, 0, &Pbuffer_map[(l1 + l0 * smpt_rd_vk_swcUimage)]))
					}

					++Ldst;
					Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, SMPT_RD_VKW_DSTS_LOl * smpt_rd_vk_swcUimage * Ldst * sizeof(VkWriteDescriptorSet));
					Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, (2 + 3 * smpt_rd_vk_swcUimage * Ldst) * sizeof(VkDescriptorBufferInfo));

					for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
					{
						smpt_rd_vkw_dstsMmake(smpt_rd_vkUdevice, smptr_ceaPvkdescriptorset + l1 + l0 * smpt_rd_vk_swcUimage);
					}
					smpt_rd_vkwMdsts
					(
						smptr_ceaPvkdescriptorset + l0 * smpt_rd_vk_swcUimage,
						Pvkdescriptorbufferinfo + (Ldst - 1) * smpt_rd_vk_swcUimage,
						Pvkwritedescriptorset + (Ldst - 1) * smpt_rd_vk_swcUimage,
						l0,
						Pm->Sm.Um < smptr_ce_mdLj ? Pm->Sm.Um : 0,
						Pm->Sm.Um >= smptr_ce_mdLj ? 1 : smptr_ce_mdPj[Pm->Sm.Um],
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

			smptr_ceaLa1 += Pm->Sm.La;
		}
	}
	#ifdef SMPT_CM_VK
		vkUpdateDescriptorSets(vkdevice, SMPT_RD_VKW_DSTS_LOl * smpt_rd_vk_swcUimage * Ldst, Pvkwritedescriptorset, 0, VK_NULL_HANDLE);
		Ldst = 0;
		Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, 0);
		Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, 0);
	#endif

	//! add a to m1

	Lm0 = La;
}

void smptr_cemMloop()
{
	#ifdef SMPT_CM_VK
	#endif
}

void smptr_cemMfree()
{
	#ifdef SMPT_CM_VK
		VkDevice vkdevice = smpt_rd_vkq_dvP[smpt_rd_vkUdevice];

		free(Pvkmappedmemoryrange);

		free(Pvkdescriptorbufferinfo);
		free(Pvkwritedescriptorset);

		for (SMPTRtMI l0 = 0; l0 < Lm0; ++l0)
		{
			struct SMPTR_CEAsA m = smptr_ceaPa[l0];
			if (m.Sm.Um != SMPTRvM)
			{
				vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstspV, smpt_rd_vk_swcUimage, smptr_ceaPvkdescriptorset + l0 * smpt_rd_vk_swcUimage);

				for (SMPTRtMI l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
				{
					vkUnmapMemory(vkdevice, Pvkdevicememory[l0 * smpt_rd_vk_swcUimage + l1]);
					vkDestroyBuffer(vkdevice, smptr_ceaPvkbuffer[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
					vkFreeMemory(vkdevice, Pvkdevicememory[l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
				}
			}
		}
		free(Pvkdevicememory);
		free(Pbuffer_map);
		free(smptr_ceaPvkbuffer);

		free(smptr_ceaPvkdescriptorset);
	#endif

	Mfree_m(0, Lm0);
	free(smptr_ceaPa);
}
