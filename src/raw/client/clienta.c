//! a vkbuffer 1 ds
//! macro vkbuffer
#ifdef SMPT_CM_VK
	VkDescriptorSet *smptr_ceaPvkdescriptorset;

	//! mix to vkbuffer model
	VkBuffer *smptr_ceaPvkbuffer;
	static void **Pbuffer_map;
	static VkDeviceMemory *Pvkdevicememory;

	static VkMappedMemoryRange *Pvkmappedmemoryrange;
	SMPT_RD_VK_BFmFREE_F
#endif

struct sA0
{
	SMPTRtA Ua;

	float *Pv;
	float *Pc;
};
static struct sA0 *Pa0;

struct SMPTR_CEAsA *smptr_ceaPa;
uint32_t smptr_ceaLa = 0;

void smptr_ceaMset()
{
	smptr_ceaPa = malloc(0);
	Pa0 = malloc(0);

	#ifdef SMPT_CM_VK
		smptr_ceaPvkbuffer = malloc(0);
		Pbuffer_map = malloc(0);
		Pvkdevicememory = malloc(0);

		Pvkmappedmemoryrange = malloc(0);
		SMPT_RD_VK_BFmFREE_SET
	#endif
}

#ifdef SMPT_CM_VK
	void smptr_ceaMvk()
	{
		//! after init vk
		smptr_ceaPvkdescriptorset = malloc(sizeof(VkDescriptorSet) * smpt_rd_vk_swcUimage);

		VkWriteDescriptorSet Pvkwritedescriptorset[SMPT_RD_VKW_DSTS_LOl * smpt_rd_vk_swcUimage];
		VkDescriptorBufferInfo Pvkdescriptorbufferinfo[2 + 3 * smpt_rd_vk_swcUimage];

		for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
		{
			smpt_rd_vkw_dstsMmake(smpt_rd_vkUdevice, smptr_ceaPvkdescriptorset + l1 + l0 * smpt_rd_vk_swcUimage);
		}
		smpt_rd_vkwMdsts
		(
			smptr_ceaPvkdescriptorset + l0 * smpt_rd_vk_swcUimage,
			Pvkdescriptorbufferinfo,
			Pvkwritedescriptorset,
			l0,
			0,
			1,
			1 + 1 * smpt_rd_vk_swcUimage
		);
		vkUpdateDescriptorSets(vkdevice, SMPT_RD_VKW_DSTS_LOl * smpt_rd_vk_swcUimage, Pvkwritedescriptorset, 0, VK_NULL_HANDLE);
	}
#endif

static void Mfree_a(SMPTRtMI Us, SMPTRtMI Ue)
{
	for (SMPTRtMI l0 = Us; l0 < Ue; ++l0)
	{
		if (smptr_ceaPa[l0].Sa.Ua != SMPTRvA)
		{
			free(smptr_ceaPa[l0].Sa.Pv);
			free(smptr_ceaPa[l0].Sa.Pc);
		}
	}
}

static void Mfree_vk(SMPTRtMI Us, SMPTRtMI Ue)
{
//	SMPT_DBmN2L("Us %d", Us)
//	SMPT_DBmN2L("Ue %d", Ue)
//	SMPT_DBmN2L("Lfree %d", Lfree)
	SMPT_RD_VK_BFmFREE_HELP
//	SMPT_DBmN2L("Lfree %d", Lfree)
}

//.i sync n-mn
static SMPTRtMI La0 = 0;
void smptr_ceaMread()
{
	//.i get data
	SMPTRtMI Ucount = *(SMPTRtMI *)(smptr_cePnet + smptr_ceLnet);
	smptr_ceLnet += sizeof(SMPTRtMI);

	Mfree_a(Ucount, smptr_ceaLa);
	smptr_ceaLa = Ucount;
	smptr_ceaPa = realloc(smptr_ceaPa, sizeof(struct SMPTR_CEAsA) * smptr_ceaLa);
	Pa0 = realloc(Pa0, sizeof(struct sA0) * smptr_ceaLa);

	//SMPT_DBmN2L("Ucount %d", Ucount)
	for (SMPTRtMI l0 = 0; l0 < Ucount; ++l0)
	{
		struct SMPTR_CEAsA *Pa = smptr_ceaPa + l0;

		Pa->Sa.Ua = *(SMPTRtA *)(smptr_cePnet + smptr_ceLnet);
		smptr_ceLnet += sizeof(SMPTRtA);
		//SMPT_DBmN2L("Pa->Sa.Ua %d", Pa->Sa.Ua)
		if (Pa->Sa.Ua != SMPTRvA)
		{
			Pa->Sa.Lv = *(uint8_t *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(uint8_t);

			Pa->Sa.Pv = malloc(sizeof(float) * 3 * Pa->Sa.Lv);
			memcpy(Pa->Sa.Pv, smptr_cePnet + smptr_ceLnet, sizeof(float) * 3 * Pa->Sa.Lv);
			smptr_ceLnet += sizeof(float) * 3 * Pa->Sa.Lv;

			Pa->Sa.Pc = malloc(sizeof(float) * 4 * Pa->Sa.Lv);
			memcpy(Pa->Sa.Pc, smptr_cePnet + smptr_ceLnet, sizeof(float) * 4 * Pa->Sa.Lv);
			smptr_ceLnet += sizeof(float) * 4 * Pa->Sa.Lv;
		}
	}

	//.i clean a0
	#ifdef SMPT_CM_VK
		VkDevice vkdevice = smpt_rd_vkq_dvP[smpt_rd_vkUdevice];

		if (smptr_ceaLa < La0)
			Mfree_vk(smptr_ceaLa, La0);
		smptr_ceaPvkbuffer = realloc(smptr_ceaPvkbuffer, sizeof(VkBuffer) * smpt_rd_vk_swcUimage * smptr_ceaLa);
		Pbuffer_map = realloc(Pbuffer_map, sizeof(void *) * smpt_rd_vk_swcUimage * smptr_ceaLa);
		Pvkdevicememory = realloc(Pvkdevicememory, sizeof(VkDeviceMemory) * smpt_rd_vk_swcUimage * smptr_ceaLa);
		for (SMPTRtMI l0 = La0; l0 < smptr_ceaLa; ++l0)
			smptr_ceaPvkbuffer[l0 * smpt_rd_vk_swcUimage] = 0;

		Pvkdescriptorbufferinfo = realloc(Pvkdescriptorbufferinfo, 0);
		Pvkwritedescriptorset = realloc(Pvkwritedescriptorset, 0);
	#endif

	//.i update a
	for (SMPTRtMI l0 = 0; l0 < smptr_ceaLa; ++l0)
	{
		struct SMPTR_CEAsA *Pa = smptr_ceaPa + l0;
		struct sA0 *Pa0_0 = Pa0 + l0;

		if (Pa->Sa.Ua == SMPTRvA)
		{
			Pa0_0->Ua = SMPTRvA;
			if (smptr_ceaPvkbuffer[l0 * smpt_rd_vk_swcUimage])
			{
				Mfree_vk(l0, l0 + 1);
				smptr_ceaPvkbuffer[l0 * smpt_rd_vk_swcUimage] = 0;
			}
		}
		else
		{
			struct SMPTR_CEAsA01 *Pa01 = smptr_ceaPa01 + l0;

			#ifdef SMPT_CM_VK
				if (La0 <= l0 || !smptr_ceaPvkbuffer[l0 * smpt_rd_vk_swcUimage] || Pm0->Um != Pm->Sm.Um)
			#endif
			{
				#ifdef SMPT_CM_VK
					if (smptr_ceaPvkbuffer[l0 * smpt_rd_vk_swcUimage])
					{
						Mfree_vk(l0, l0 + 1);
						smptr_ceaPvkbuffer[l0 * smpt_rd_vk_swcUimage] = 0;
					}

					for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
					{
						VkDeviceSize vkdevicesize = sizeof(float) * 4 * 4 * (Pm->Sm.Um >= smptr_ce_mdLj ? 1 : smptr_ce_mdPj[Pm->Sm.Um]);

						VkMemoryRequirements vkmemoryrequirements;
						vkdevicesize = (vkdevicesize + (smpt_rd_vkUnon_coherent_atom_size - 1)) & ~(smpt_rd_vkUnon_coherent_atom_size - 1);
						SMPT_RD_VK_BFmMAKE(smpt_rd_vkUdevice, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_ceaPvkbuffer[l1 + l0 * smpt_rd_vk_swcUimage], Pvkdevicememory[l1 + l0 * smpt_rd_vk_swcUimage], vkmemoryrequirements)
						SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(vkdevice, Pvkdevicememory[l1 + l0 * smpt_rd_vk_swcUimage], 0, vkdevicesize, 0, &Pbuffer_map[(l1 + l0 * smpt_rd_vk_swcUimage)]))
					}
				#endif

				Pa0_0->Ua = Pa->Sa.Ua;

				Pa0_0->Lv = Pa->Sa.Lv;

				Pm01->Uf = SMPTR_CEuFPS;
				memcpy(Pa0_0->Pv, Pa->Sa.Pv, sizeof(float) * 3 * Pa->Sa.Lv);
				memcpy(Pa0_0->Pc, Pa->Sa.Pc, sizeof(float) * 4 * Pa->Sa.Lv);
			}
			else if (Pa0_0->Lv != Pa->Sa.Lv)
			{
				Pa0_0->Lv = Pa->Sa.Lv;

				Pm01->Uf = SMPTR_CEuFPS;
				memcpy(Pa0_0->Pv, Pa->Sa.Pv, sizeof(float) * 3 * Pa->Sa.Lv);
				memcpy(Pa0_0->Pc, Pa->Sa.Pc, sizeof(float) * 4 * Pa->Sa.Lv);
			}
			else if (memcmp(Pa0_0->Pv, Pa->Sa.Pv, sizeof(float) * 3 * Pa->Sa.Lv) || memcmp(Pa0_0->Pc, Pa->Sa.Pc, sizeof(float) * 4 * Pa->Sa.Lv))
			{
				Pm01->Uf = 0;
				for (uint8_t l1 = 0; l1 < Pa->Sa.Lv; ++l1)
				{
					Pa->Pv[l1] = (Pa->Sa.Pv[l1] - Pa0_0->Pv[l1]) / 255.0F * SMPTR_CEuDELTA;
					Pa->Pc[l1] = (Pa->Sa.Pc[l1] - Pa0_0->Pc[l1]) / 255.0F * SMPTR_CEuDELTA;
				}
			}
		}
	}
	La0 = smptr_ceaLa;
}

void smptr_ceaMloop()
{
	#ifdef SMPT_CM_VK
		VkDevice vkdevice = smpt_rd_vkq_dvP[smpt_rd_vkUdevice];

		//.i free
		uint32_t Ufree = Lfree;
		for (uint32_t l0 = 0; l0 < Lfree; ++l0)
		{
			if (SMPT_RD_VK_BFmFREE_ABLE(l0))
			{
				if (Pvkbuffer_free[l0 * smpt_rd_vk_swcUimage])
				{
					SMPT_RD_VK_BFmFREE_DO(l0, l1)
					Pvkbuffer_free[l0 * smpt_rd_vk_swcUimage] = 0;
				}
				if (Ufree == Lfree)
					Ufree = l0;
			}
			else
			{
				Ufree = Lfree;
			}
		}
		Lfree = Ufree;
		SMPT_RD_VK_BFmFREE_RE

		//.i a to m1
	#endif
}

void smptr_ceaMfree()
{
	#ifdef SMPT_CM_VK
		VkDevice vkdevice = smpt_rd_vkq_dvP[smpt_rd_vkUdevice];

		if (Lfree)
		{
			for (uint32_t l0 = 0; l0 < Lfree; ++l0)
			{
				if (SMPT_RD_VK_BFmFREE_ABLE(l0))
				{
					if (Pvkbuffer_free[l0 * smpt_rd_vk_swcUimage])
					{
						vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstspV, smpt_rd_vk_swcUimage, Pvkdescriptorset_free + l0 * smpt_rd_vk_swcUimage);
						SMPT_RD_VK_BFmFREE_DO(l0, l1)
						Pvkbuffer_free[l0 * smpt_rd_vk_swcUimage] = 0;
					}
				}
			}
		}
		SMPT_RD_VK_BFmFREE_CLEAN

		free(Pvkmappedmemoryrange);

		vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstspV, smpt_rd_vk_swcUimage, smptr_ceaPvkdescriptorset);
		for (SMPTRtMI l0 = 0; l0 < smptr_ceaLa; ++l0)
		{
			struct SMPTR_CEAsA a = smptr_ceaPa[l0];
			if (a.Sa.Ua != SMPTRvA)
			{
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

	Mfree_a(0, smptr_ceaLa);
	free(Pa0);
	free(smptr_ceaPa);
}
