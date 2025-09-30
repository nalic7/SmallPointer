//! a vkbuffer 1 ds
//! macro vkbuffer
#ifdef SMPT_CM_VK
	#define SMPTR_CEAuBUFFER (1 + 3 * smpt_rd_vk_swcUimage)
	VkDescriptorSet *smptr_ceaPvkdescriptorset;

	//! mix to vkbuffer model
		//! + 1 + a * smpt_rd_vk_swcUimage
		//! a own frame_buffer
//	VkBuffer *smptr_ceaPvkbuffer;
//	static void **Pbuffer_map;
//	static VkDeviceMemory *Pvkdevicememory;

	static VkMappedMemoryRange *Pvkmappedmemoryrange;
	SMPT_RD_VK_BFmFREE_F
#endif

struct sA0
{
	float *Pv;
	uint8_t
		*Pc,
		Lv,
		Uf;
};
static struct sA0 *Pa0;

struct SMPTR_CEAsA *smptr_ceaPa;
uint32_t smptr_ceaLa = 0;

void smptr_ceaMset()
{
	smptr_ceaPa = malloc(0);
	Pa0 = malloc(0);

	#ifdef SMPT_CM_VK
		Pvkmappedmemoryrange = malloc(0);
		SMPT_RD_VK_BFmFREE_SET
	#endif
}

#ifdef SMPT_CM_VK
	void smptr_ceaMvk()
	{
		VkDevice vkdevice = smpt_rd_vkq_dvP[SMPT_RD_VKQuDV];

		VkWriteDescriptorSet Pvkwritedescriptorset[SMPT_RD_VKW_DSTS_LOl * smpt_rd_vk_swcUimage];
		VkDescriptorBufferInfo Pvkdescriptorbufferinfo[2 + 3 * smpt_rd_vk_swcUimage];
		for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
		{
			SMPT_RD_VKW_DSTSmMAKE(SMPT_RD_VKQuDV, 0, smptr_ceaPvkdescriptorset + l0)
		}
		//.i bindpose s 1+
		Pvkdescriptorbufferinfo[0] = (VkDescriptorBufferInfo)
		{
			.buffer = smptr_ce_mdPvkbuffer[0],
			.offset = 0,
			.range = 0
		};
		//.i src_color s
		Pvkdescriptorbufferinfo[1] = (VkDescriptorBufferInfo)
		{
			.buffer = smptr_ce_mdPvkbuffer[1],
			.offset = 0,
			.range = smptr_ce_mdLrgba
		};
		for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
		{
			//.i gui/world d
			Pvkdescriptorbufferinfo[2 + l0 * 3 + 2] = (VkDescriptorBufferInfo)
			{
				.buffer = smptr_ce_mdPvkbuffer[1 + 2 * smpt_rd_vk_swcUimage + l0],
				.offset = 0,
				.range = sizeof(float) * 16 * 2
			};
			//.i animate d
			Pvkdescriptorbufferinfo[2 + l0 * 3] = (VkDescriptorBufferInfo)
			{
				.buffer = smptr_ce_mdPvkbuffer[1 + 2 * smpt_rd_vk_swcUimage + l0],
				.offset = sizeof(float) * 4,
				.range = sizeof(float) * 4 * 3
			};
			//.i color d
			Pvkdescriptorbufferinfo[2 + l0 * 3 + 1] = (VkDescriptorBufferInfo)
			{
				.buffer = smptr_ce_mdPvkbuffer[1 + 2 * smpt_rd_vk_swcUimage + l0],
				.offset = 0,
				.range = sizeof(float) * 4
			};
			SMPT_RD_VKWmDSTS(0, VK_NULL_HANDLE, Pvkdescriptorbufferinfo + 2 + l0 * 3 + 2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, smptr_ceaPvkdescriptorset[l0], Pvkwritedescriptorset[l0 * SMPT_RD_VKW_DSTS_LOl]);
			SMPT_RD_VKWmDSTS(1, VK_NULL_HANDLE, Pvkdescriptorbufferinfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, smptr_ceaPvkdescriptorset[l0], Pvkwritedescriptorset[l0 * SMPT_RD_VKW_DSTS_LOl + 1]);
			SMPT_RD_VKWmDSTS(2, VK_NULL_HANDLE, Pvkdescriptorbufferinfo + 2 + l0 * 3, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, smptr_ceaPvkdescriptorset[l0], Pvkwritedescriptorset[l0 * SMPT_RD_VKW_DSTS_LOl + 2]);
			SMPT_RD_VKWmDSTS(3, VK_NULL_HANDLE, Pvkdescriptorbufferinfo + 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, smptr_ceaPvkdescriptorset[l0], Pvkwritedescriptorset[l0 * SMPT_RD_VKW_DSTS_LOl + 3]);
			SMPT_RD_VKWmDSTS(4, VK_NULL_HANDLE, Pvkdescriptorbufferinfo + 2 + l0 * 3 + 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, smptr_ceaPvkdescriptorset[l0], Pvkwritedescriptorset[l0 * SMPT_RD_VKW_DSTS_LOl + 4]);
		}
		vkUpdateDescriptorSets(vkdevice, SMPT_RD_VKW_DSTS_LOl * smpt_rd_vk_swcUimage, Pvkwritedescriptorset, 0, VK_NULL_HANDLE);
	}
#endif

static void Mfree_a(SMPTRtA Us, SMPTRtA Ue)
{
	for (SMPTRtA l0 = Us; l0 < Ue; ++l0)
	{
		if (smptr_ceaPa[l0].Sa.Ua == l0)
		{
			free(smptr_ceaPa[l0].Sa.Pv);
			free(smptr_ceaPa[l0].Sa.Pc);
		}
	}
}

static void Mfree_vk(SMPTRtA Us, SMPTRtA Ue)
{
//	SMPT_DBmN2L("Us %d", Us)
//	SMPT_DBmN2L("Ue %d", Ue)
//	SMPT_DBmN2L("Lfree %d", Lfree)
	SMPT_RD_VK_BFmFREE_HELP(smptr_ce_mdPvkbuffer + SMPTR_CEAuBUFFER, smptr_ce_mdPvkdevicememory + SMPTR_CEAuBUFFER)
//	SMPT_DBmN2L("Lfree %d", Lfree)
}

//.i sync n-mn
static SMPTRtA La0 = 0;
void smptr_ceaMread()
{
	//.i get data
	SMPTRtA Ucount = *(SMPTRtA *)(smptr_cePnet + smptr_ceLnet);
	smptr_ceLnet += sizeof(SMPTRtA);

	Mfree_a(Ucount, smptr_ceaLa);
	smptr_ceaLa = Ucount;
	smptr_ceaPa = realloc(smptr_ceaPa, sizeof(struct SMPTR_CEAsA) * smptr_ceaLa);
	Pa0 = realloc(Pa0, sizeof(struct sA0) * smptr_ceaLa);

	//SMPT_DBmN2L("Ucount %d", Ucount)
	for (SMPTRtA l0 = 0; l0 < Ucount; ++l0)
	{
		struct SMPTR_CEAsA *Pa = smptr_ceaPa + l0;

		Pa->Sa.Ua = *(SMPTRtA *)(smptr_cePnet + smptr_ceLnet);
		smptr_ceLnet += sizeof(SMPTRtA);
		//SMPT_DBmN2L("Pa->Sa.Ua %d", Pa->Sa.Ua)
		if (Pa->Sa.Ua == l0)
		{
			Pa->Sa.Lv = *(uint8_t *)(smptr_cePnet + smptr_ceLnet);
			smptr_ceLnet += sizeof(uint8_t);

			Pa->Sa.Pv = malloc(sizeof(float) * 3 * Pa->Sa.Lv);
			memcpy(Pa->Sa.Pv, smptr_cePnet + smptr_ceLnet, sizeof(float) * 3 * Pa->Sa.Lv);
			smptr_ceLnet += sizeof(float) * 3 * Pa->Sa.Lv;

			Pa->Sa.Pc = malloc(sizeof(uint8_t) * Pa->Sa.Lv);
			memcpy(Pa->Sa.Pc, smptr_cePnet + smptr_ceLnet, sizeof(uint8_t) * Pa->Sa.Lv);
			smptr_ceLnet += sizeof(uint8_t) * Pa->Sa.Lv;
		}
	}

	//.i clean a0
	#ifdef SMPT_CM_VK
		VkDevice vkdevice = smpt_rd_vkq_dvP[SMPT_RD_VKQuDV];

		if (smptr_ceaLa < La0)
			Mfree_vk(smptr_ceaLa, La0);
		smptr_ce_mdPvkbuffer = realloc(smptr_ce_mdPvkbuffer, sizeof(VkBuffer) * (SMPTR_CEAuBUFFER + smptr_ceaLa));
		smptr_ce_mdPvkdevicememory = realloc(smptr_ce_mdPvkdevicememory, sizeof(VkDeviceMemory) * (SMPTR_CEAuBUFFER + smptr_ceaLa));
		smptr_ce_mdPbuffer_map = realloc(smptr_ce_mdPbuffer_map, sizeof(void *) * (SMPTR_CEAuBUFFER + smptr_ceaLa));
		for (SMPTRtA l0 = La0; l0 < smptr_ceaLa; ++l0)
			smptr_ce_mdPvkbuffer[SMPTR_CEAuBUFFER + l0 * smpt_rd_vk_swcUimage] = 0;
	#endif

	//.i update a
	for (SMPTRtA l0 = 0; l0 < smptr_ceaLa; ++l0)
	{
		struct SMPTR_CEAsA *Pa = smptr_ceaPa + l0;
		struct sA0 *Pa0_0 = Pa0 + l0;

		if (Pa->Sa.Ua != l0)
		{
			if (smptr_ce_mdPvkbuffer[SMPTR_CEAuBUFFER + l0 * smpt_rd_vk_swcUimage])
			{
				Mfree_vk(l0, l0 + 1);
				smptr_ce_mdPvkbuffer[SMPTR_CEAuBUFFER + l0 * smpt_rd_vk_swcUimage] = 0;
			}
		}
		else
		{
			#ifdef SMPT_CM_VK
				if (La0 <= l0 || !smptr_ce_mdPvkbuffer[SMPTR_CEAuBUFFER + l0 * smpt_rd_vk_swcUimage])
			#endif
			{
				#ifdef SMPT_CM_VK
					if (smptr_ce_mdPvkbuffer[SMPTR_CEAuBUFFER + l0 * smpt_rd_vk_swcUimage])
					{
						Mfree_vk(l0, l0 + 1);
						smptr_ce_mdPvkbuffer[SMPTR_CEAuBUFFER + l0 * smpt_rd_vk_swcUimage] = 0;
					}

					for (uint8_t l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
					{
						VkDeviceSize vkdevicesize = sizeof(float) * 3 * Pa->Sa.Lv + sizeof(uint32_t) * Pa->Sa.Lv;

						VkMemoryRequirements vkmemoryrequirements;
						vkdevicesize = (vkdevicesize + (smpt_rd_vkUnon_coherent_atom_size - 1)) & ~(smpt_rd_vkUnon_coherent_atom_size - 1);
						SMPT_RD_VK_BFmMAKE(SMPT_RD_VKQuDV, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_ce_mdPvkbuffer[SMPTR_CEAuBUFFER + l1 + l0 * smpt_rd_vk_swcUimage], smptr_ce_mdPvkdevicememory[SMPTR_CEAuBUFFER + l1 + l0 * smpt_rd_vk_swcUimage], vkmemoryrequirements)
						SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(vkdevice, smptr_ce_mdPvkdevicememory[SMPTR_CEAuBUFFER + l1 + l0 * smpt_rd_vk_swcUimage], 0, vkdevicesize, 0, &smptr_ce_mdPbuffer_map[SMPTR_CEAuBUFFER + l1 + l0 * smpt_rd_vk_swcUimage]))
						for (uint8_t l2 = 0; l2 < Pa->Sa.Lv; ++l2)
						{
							memcpy(smptr_ce_mdPbuffer_map[SMPTR_CEAuBUFFER + l1 + l0 * smpt_rd_vk_swcUimage] + l2 * (sizeof(float) * 3 + sizeof(uint32_t)), Pa->Sa.Pv + l2 * 3, sizeof(float) * 3);
							*(uint32_t *)(smptr_ce_mdPbuffer_map[SMPTR_CEAuBUFFER + l1 + l0 * smpt_rd_vk_swcUimage] + l2 * (sizeof(float) * 3 + sizeof(uint32_t) + sizeof(float) * 3)) = Pa->Sa.Pc[l2];
						}
					}
				#endif

				Pa0_0->Lv = Pa->Sa.Lv;

				Pa0_0->Uf = SMPTR_CEuFPS;
				memcpy(Pa0_0->Pv, Pa->Sa.Pv, sizeof(float) * 3 * Pa->Sa.Lv);
				memcpy(Pa0_0->Pc, Pa->Sa.Pc, sizeof(uint8_t) * Pa->Sa.Lv);
			}
			else if (Pa0_0->Lv != Pa->Sa.Lv)
			{
				Pa0_0->Lv = Pa->Sa.Lv;

				Pa0_0->Uf = SMPTR_CEuFPS;
				memcpy(Pa0_0->Pv, Pa->Sa.Pv, sizeof(float) * 3 * Pa->Sa.Lv);
				memcpy(Pa0_0->Pc, Pa->Sa.Pc, sizeof(uint8_t) * Pa->Sa.Lv);
			}
			else if (memcmp(Pa0_0->Pv, Pa->Sa.Pv, sizeof(float) * 3 * Pa->Sa.Lv) || memcmp(Pa0_0->Pc, Pa->Sa.Pc, sizeof(uint8_t) * Pa->Sa.Lv))
			{
				//! enable animate?
//				Pa0_0->Uf = 0;
//				for (uint8_t l1 = 0; l1 < Pa->Sa.Lv; ++l1)
//				{
//					Pa->Pv[l1] = (Pa->Sa.Pv[l1] - Pa0_0->Pv[l1]) / 255.0F * SMPTR_CEuDELTA;
//					Pa->Pc[l1] = (Pa->Sa.Pc[l1] - Pa0_0->Pc[l1]) / 255.0F * SMPTR_CEuDELTA;
//				}
			}
		}
	}
	La0 = smptr_ceaLa;
}

void smptr_ceaMloop()
{
	#ifdef SMPT_CM_VK
		VkDevice vkdevice = smpt_rd_vkq_dvP[SMPT_RD_VKQuDV];

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
		VkDevice vkdevice = smpt_rd_vkq_dvP[SMPT_RD_VKQuDV];

		if (Lfree)
		{
			for (uint32_t l0 = 0; l0 < Lfree; ++l0)
			{
				if (SMPT_RD_VK_BFmFREE_ABLE(l0))
				{
					if (Pvkbuffer_free[l0 * smpt_rd_vk_swcUimage])
					{
						SMPT_RD_VK_BFmFREE_DO(l0, l1)
						Pvkbuffer_free[l0 * smpt_rd_vk_swcUimage] = 0;
					}
				}
			}
		}
		SMPT_RD_VK_BFmFREE_CLEAN

		free(Pvkmappedmemoryrange);

		vkFreeDescriptorSets(vkdevice, smpt_rd_vkw_dstspP[0], smpt_rd_vk_swcUimage, smptr_ceaPvkdescriptorset);
		for (SMPTRtA l0 = 0; l0 < smptr_ceaLa; ++l0)
		{
			struct SMPTR_CEAsA a = smptr_ceaPa[l0];
			if (a.Sa.Ua == l0)
			{
				for (SMPTRtA l1 = 0; l1 < smpt_rd_vk_swcUimage; ++l1)
				{
					vkUnmapMemory(vkdevice, smptr_ce_mdPvkdevicememory[SMPTR_CEAuBUFFER + l0 * smpt_rd_vk_swcUimage + l1]);
					vkDestroyBuffer(vkdevice, smptr_ce_mdPvkbuffer[SMPTR_CEAuBUFFER + l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
					vkFreeMemory(vkdevice, smptr_ce_mdPvkdevicememory[SMPTR_CEAuBUFFER + l0 * smpt_rd_vk_swcUimage + l1], VK_NULL_HANDLE);
				}
			}
		}
		smptr_ce_mdPvkbuffer = realloc(smptr_ce_mdPvkbuffer, sizeof(VkBuffer) * SMPTR_CEAuBUFFER);
		smptr_ce_mdPvkdevicememory = realloc(smptr_ce_mdPvkdevicememory, sizeof(VkDeviceMemory) * SMPTR_CEAuBUFFER);
		smptr_ce_mdPbuffer_map = realloc(smptr_ce_mdPbuffer_map, sizeof(void *) * SMPTR_CEAuBUFFER);

		free(smptr_ceaPvkdescriptorset);
	#endif

	Mfree_a(0, smptr_ceaLa);
	free(Pa0);
	free(smptr_ceaPa);
}
