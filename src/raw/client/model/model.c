uint8_t
	*smptr_ce_mdPj,
	smptr_ce_mdLj,
	**smptr_ce_mdPb;

#ifdef SMPT_CM_VK
	uint32_t
		*smptr_ce_mdPil,
		smptr_ce_mdLrgba;

	VkDeviceSize smptr_ce_mdPai[SMPTR_CE_MDlA];
	VkDeviceSize *smptr_ce_mdPli;

	VkBuffer *smptr_ce_mdPvkbuffer;
	VkDeviceMemory *smptr_ce_mdPvkdevicememory;
	void **smptr_ce_mdPbuffer_map;
	VkDeviceSize *smptr_ce_mdPvkdevicesize;
#endif

struct sBONE
{
	uint8_t
		*Pj,
		Lj;
};

static float **Pbp;
static struct sBONE *Pbone;

static uint32_t **Pi;
static uint32_t *Pil;
static uint8_t *Pa[SMPTR_CE_MDlA];
static uint32_t Pal[SMPTR_CE_MDlA];
static uint8_t Li;

static float *Prgba;

void smptr_ce_mdMset()
{
	smptr_ce_mdLj = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
	smptrPcache->d_bl_p[1] += sizeof(uint8_t);

	smptrPcache->bs_p = malloc(sizeof(uint16_t *) * smptr_ce_mdLj);
	smptrPcache->be_p = malloc(sizeof(uint16_t *) * smptr_ce_mdLj);

	smptr_ce_mdPj = malloc(smptr_ce_mdLj);
	memcpy(smptr_ce_mdPj, smptrPcache->d_p + smptrPcache->d_bl_p[1], smptr_ce_mdLj);
	smptrPcache->d_bl_p[1] += smptr_ce_mdLj;

	uint16_t Lbone = 0;
	Pbone = malloc(0);

	Pbp = malloc(sizeof(float *) * smptr_ce_mdLj);
	smptr_ce_mdPb = malloc(sizeof(uint8_t *) * smptr_ce_mdLj);

	smptr_ce_mdPvkdevicesize = malloc(sizeof(VkDeviceSize) * smptr_ce_mdLj);

	for (uint8_t l0 = 0; l0 < smptr_ce_mdLj; ++l0)
	{
		smptrPcache->bs_p[l0] = malloc(sizeof(uint16_t) * smptr_ce_mdPj[l0]);
		smptrPcache->be_p[l0] = malloc(sizeof(uint16_t) * smptr_ce_mdPj[l0]);
		smptrPcache->bs_p[l0][0] = 0;

		Pbone = realloc(Pbone, sizeof(struct sBONE) * (Lbone + smptr_ce_mdPj[l0]));
		Pbp[l0] = malloc(sizeof(float) * 16 * 2 * (smptr_ce_mdPj[l0] - 1));

		for (uint8_t l_1 = 0; l_1 < smptr_ce_mdPj[l0]; ++l_1)
		{
			uint8_t size = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
			smptrPcache->d_bl_p[1] += sizeof(uint8_t);

			memset(Pbone + Lbone + l_1, 0, sizeof(struct sBONE));
			if (l_1 != 0)
			{
				smptrPcache->bs_p[l0][l_1] = smptrPcache->be_p[l0][l_1 - 1];
			}
			Pbone[Lbone + l_1].Lj = size;
			Pbone[Lbone + l_1].Pj = malloc(size);
			memcpy(Pbone[Lbone + l_1].Pj, smptrPcache->d_p + smptrPcache->d_bl_p[1], size);
			smptrPcache->be_p[l0][l_1] = smptrPcache->bs_p[l0][l_1] + size;
			smptrPcache->d_bl_p[1] += size;
		}
		smptrPcache->bs_p[l0][0] = 0xFFFFu;

		Lbone += smptr_ce_mdPj[l0];
	}

	for (uint8_t l0 = 0; l0 < smptr_ce_mdLj; ++l0)
	{
		for (uint8_t l_1 = 0; l_1 < smptr_ce_mdPj[l0] - 1; ++l_1)
		{
			memcpy(Pbp[l0] + l_1 * 16 * 2, smptrPcache->d_p + smptrPcache->d_bl_p[1] + l_1 * sizeof(float) * 16, sizeof(float) * 16);
			memcpy(Pbp[l0] + l_1 * 16 * 2 + 16, Pbp[l0] + l_1 * 16 * 2, sizeof(float) * 16);
			smptm_m4x4Mi(Pbp[l0] + l_1 * 16 * 2 + 16);
		}
		smptrPcache->d_bl_p[1] += sizeof(float) * 16 * (smptr_ce_mdPj[l0] - 1);
	}

	Li = *(uint32_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]) / sizeof(uint32_t);
	smptrPcache->d_bl_p[1] += sizeof(uint32_t);

	#ifdef SMPT_CM_VK
		smptr_ce_mdPli = malloc(sizeof(VkDeviceSize) * Li);
		smptr_ce_mdPil = malloc(sizeof(uint32_t) * Li);

		Pil = malloc(sizeof(uint32_t) * Li);
		uint32_t l_step = 0;
		while (l_step != Li)
		{
			Pil[l_step] = *(uint32_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
			smptrPcache->d_bl_p[1] += sizeof(uint32_t);

			++l_step;
		}

		Pi = malloc(sizeof(uint32_t *) * Li);

		for (uint32_t l0 = 0; l0 < Li; ++l0)
		{
			Pi[l0] = malloc(Pil[l0]);
			memcpy(Pi[l0], smptrPcache->d_p + smptrPcache->d_bl_p[1], Pil[l0]);
			smptrPcache->d_bl_p[1] += Pil[l0];
			smptr_ce_mdPil[l0] = Pil[l0] / sizeof(uint32_t);
		}

		smptr_ce_mdLrgba = *(uint8_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
		smptrPcache->d_bl_p[1] += sizeof(uint8_t);
		smptr_ce_mdLrgba *= 4 * sizeof(float);
		Prgba = malloc(smptr_ce_mdLrgba);
		memcpy(Prgba, smptrPcache->d_p + smptrPcache->d_bl_p[1], smptr_ce_mdLrgba);
		smptrPcache->d_bl_p[1] += smptr_ce_mdLrgba;
		//.i pow Prgba
		for (uint32_t l0 = 0; l0 < smptr_ce_mdLrgba / sizeof(float); ++l0)
		{
			Prgba[l0] = pow(Prgba[l0], 1.0F / 5.0F);
		}

		//.i c1
		uint32_t l_c1_bl = *(uint32_t *)(smptrPcache->d_p + smptrPcache->d_bl_p[1]);
		smptrPcache->d_bl_p[1] += sizeof(uint32_t);

		Pal[0] = l_c1_bl * (sizeof(float) * 3 + sizeof(uint32_t));
		Pa[0] = malloc(Pal[0]);
		//.i c1 a
		for (uint32_t l0 = 0; l0 < l_c1_bl; ++l0)
		{
			memcpy(Pa[0] + l0 * (sizeof(float) * 3 + sizeof(uint32_t)), smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 3 + 1);
			memset((Pa[0] + l0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 1)), 0, 3);
			smptrPcache->d_bl_p[1] += sizeof(float) * 3 + 1;
		}

		//.i c1j1
		Pal[1] = smptrPcache->d_bl_p[0] - smptrPcache->d_bl_p[1];

		//.i c1j1 a
		uint32_t l_c1j1_size = Pal[1] / (sizeof(float) * 3 + 2);
		Pal[1] += l_c1j1_size * 2;
		Pa[1] = malloc(Pal[1]);
		for (uint32_t l0 = 0; l0 < l_c1j1_size; ++l0)
		{
			memcpy(Pa[1] + l0 * (sizeof(float) * 3 + sizeof(uint32_t)), smptrPcache->d_p + smptrPcache->d_bl_p[1], sizeof(float) * 3 + 2);
			memset((Pa[1] + l0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 2)), 0, 2);
			//t. s0-test j
			//memset((Pa[1] + l0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 1)), 0, 3);
			//*(uint8_t *)(Pa[1] + l0 * (sizeof(float) * 3 + sizeof(uint32_t)) + (sizeof(float) * 3 + 1)) = 40;
			//t. e0-test j
//			if ((smptrPcache->d_p + smptrPcache->d_bl_p[1] + sizeof(float) * 3 + 1) == 0)
//			{
//				SMPT_DBmN2L("nali_buffer c1j1 j0 %d", (smptrPcache->d_p + smptrPcache->d_bl_p[1] + sizeof(float) * 3 + 1))
//			}
			smptrPcache->d_bl_p[1] += sizeof(float) * 3 + 2;
		}

		//.i set default a
		for (uint8_t l0 = 0; l0 < smptr_ce_mdLj; ++l0)
		{
			l_step = 0;
			smptr_ce_mdPb[l0] = malloc(sizeof(float) * 4 * 3 * smptr_ce_mdPj[l0]);

			for (uint8_t l_1 = 0; l_1 < smptr_ce_mdPj[l0]; ++l_1)
			{
				//.i s
				for (uint8_t l_2 = 0; l_2 < 3; ++l_2)
				{
					*(float *)(smptr_ce_mdPb[l0] + l_step + l_2 * sizeof(float)) = 1;
				}
				//.i b_s b_e
				*(uint32_t *)(smptr_ce_mdPb[l0] + l_step + 3 * sizeof(float)) = smptrPcache->bs_p[l0][l_1] | smptrPcache->be_p[l0][l_1] << (8 + 8);
				//.t bs_p be_p
				//*(uint32_t *)(smptr_ce_mdPb[l0] + l_step + 3 * sizeof(float)) = 51 | 51 << (8 + 8);
				l_step += 4 * sizeof(float);

				//.i r
				memcpy(smptr_ce_mdPb[l0] + l_step, smptmPm4x4 + 12, 4 * sizeof(float));
				l_step += 4 * sizeof(float);

				//.i t
				memset(smptr_ce_mdPb[l0] + l_step, 0, 4 * sizeof(float));
				//.t a->t vec4
				//*(uint32_t *)(smptr_ce_mdPb[l0] + l_step + 3 * sizeof(float)) = 0xFFFFFFFFu;
				l_step += 4 * sizeof(float);
			}

			free(smptrPcache->bs_p[l0]);
			free(smptrPcache->be_p[l0]);
		}
		free(smptrPcache->bs_p);
		free(smptrPcache->be_p);

		//.i b
		Lbone = 0;
		for (uint8_t l0 = 0; l0 < smptr_ce_mdLj; ++l0)
		{
			l_step = 0;
			uint8_t l_0_0 = 0;

			for (uint8_t l_1 = 0; l_1 < smptr_ce_mdPj[l0]; ++l_1)
			{
				for (uint8_t l_2 = 0; l_2 < Pbone[Lbone + l_1].Lj; ++l_2)
				{
					*(uint32_t *)(smptr_ce_mdPb[l0] + l_step + 3 * sizeof(float) + sizeof(float) * 4 * 2) |= Pbone[Lbone + l_1].Pj[l_2] << l_0_0 * 8;
					//.t Pbone
					//*(uint32_t *)(smptr_ce_mdPb[l0] + l_step + 3 * sizeof(float) + sizeof(float) * 4 * 2) |= 51 << l_0_0 * 8;

					if (++l_0_0 == 4)
					{
						l_step += sizeof(float) * 4 * 3;
						l_0_0 = 0;
					}
				}
			}

			Lbone += smptr_ce_mdPj[l0];
		}
	#endif
}


#ifdef SMPT_CM_VK
	void smptr_ce_mdMvk()
	{
		smptr_ce_mdPvkbuffer = malloc(sizeof(VkBuffer) * (1 + 2 * smpt_rd_vk_swcUimage));
		smptr_ce_mdPvkdevicememory = malloc(sizeof(VkDeviceMemory) * (1 + 2 * smpt_rd_vk_swcUimage));
		smptr_ce_mdPbuffer_map = malloc(sizeof(void *) * (1 + 2 * smpt_rd_vk_swcUimage));

		VkDeviceSize vkdevicesize = smptr_ce_mdLrgba;

		for (uint32_t l0 = 0; l0 < Li; ++l0)
		{
			smptr_ce_mdPli[l0] = vkdevicesize;
			vkdevicesize += Pil[l0];
		}

		for (uint32_t l0 = 0; l0 < SMPTR_CE_MDlA; ++l0)
		{
			smptr_ce_mdPai[l0] = vkdevicesize;
			vkdevicesize += Pal[l0];
		}

		for (uint32_t l0 = 0; l0 < smptr_ce_mdLj; ++l0)
		{
			smptr_ce_mdPvkdevicesize[l0] = vkdevicesize;
			vkdevicesize += sizeof(float) * 16 * 2 * (smptr_ce_mdPj[l0] - 1);
		}

		VkMemoryRequirements vkmemoryrequirements;
		vkdevicesize = (vkdevicesize + (smpt_rd_vkUnon_coherent_atom_size - 1)) & ~(smpt_rd_vkUnon_coherent_atom_size - 1);
		SMPT_RD_VK_BFmMAKE(smpt_rd_vkUdevice, vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_ce_mdPvkbuffer[0], smptr_ce_mdPvkdevicememory[0], vkmemoryrequirements)
		SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(smpt_rd_vkq_dvP[smpt_rd_vkUdevice], smptr_ce_mdPvkdevicememory[0], 0, vkdevicesize, 0, &smptr_ce_mdPbuffer_map[0]))

		//.i gui world
		for (uint8_t l0 = 1; l0 < (1 + 2 * smpt_rd_vk_swcUimage); ++l0)
		{
			SMPT_RD_VK_BFmMAKE(smpt_rd_vkUdevice, sizeof(float) * 16 * 2, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, smptr_ce_mdPvkbuffer[l0], smptr_ce_mdPvkdevicememory[l0], vkmemoryrequirements)
			SMPT_DBmR2L("vkMapMemory %d", vkMapMemory(smpt_rd_vkq_dvP[smpt_rd_vkUdevice], smptr_ce_mdPvkdevicememory[l0], 0, sizeof(float) * 16 * 2, 0, &smptr_ce_mdPbuffer_map[l0]))
			memcpy(smptr_ce_mdPbuffer_map[l0], smptmPm4x4, sizeof(float) * 16);
			memcpy(smptr_ce_mdPbuffer_map[l0] + sizeof(float) * 16, smptmPm4x4, sizeof(float) * 16);
		}

		vkdevicesize = 0;

		//.i rgba
		memcpy(smptr_ce_mdPbuffer_map[0] + vkdevicesize, Prgba, smptr_ce_mdLrgba);
		vkdevicesize += smptr_ce_mdLrgba;

		//.i ai index
		for (uint32_t l0 = 0; l0 < Li; ++l0)
		{
			memcpy(smptr_ce_mdPbuffer_map[0] + vkdevicesize, Pi[l0], Pil[l0]);
			vkdevicesize += Pil[l0];
		}

		//.i a index
		for (uint32_t l0 = 0; l0 < SMPTR_CE_MDlA; ++l0)
		{
			memcpy(smptr_ce_mdPbuffer_map[0] + vkdevicesize, Pa[l0], Pal[l0]);
			vkdevicesize += Pal[l0];
		}

		//.i UBOB
		for (uint32_t l0 = 0; l0 < smptr_ce_mdLj; ++l0)
		{
			memcpy(smptr_ce_mdPbuffer_map[0] + vkdevicesize, Pbp[l0], sizeof(float) * 16 * 2 * (smptr_ce_mdPj[l0] - 1));
			vkdevicesize += sizeof(float) * 16 * 2 * (smptr_ce_mdPj[l0] - 1);
		}

		vkFlushMappedMemoryRanges(smpt_rd_vkq_dvP[smpt_rd_vkUdevice], 1, &(VkMappedMemoryRange)
		{
			.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
			.memory = smptr_ce_mdPvkdevicememory[0],
			.offset = 0,
			.size = (vkdevicesize + (smpt_rd_vkUnon_coherent_atom_size - 1)) & ~(smpt_rd_vkUnon_coherent_atom_size - 1),
			.pNext = VK_NULL_HANDLE
		});
	}
#endif

void smptr_ce_mdMfree(uint32_t device)
{
	#ifdef SMPT_CM_VK
		for (uint8_t l0 = 0; l0 < 1 + 2 * smpt_rd_vk_swcUimage; ++l0)
		{
			VkDevice vkdevice = smpt_rd_vkq_dvP[device];
			vkUnmapMemory(smpt_rd_vkq_dvP[device], smptr_ce_mdPvkdevicememory[l0]);
			vkDestroyBuffer(vkdevice, smptr_ce_mdPvkbuffer[l0], VK_NULL_HANDLE);
			vkFreeMemory(vkdevice, smptr_ce_mdPvkdevicememory[l0], VK_NULL_HANDLE);
		}
		free(smptr_ce_mdPvkbuffer);
		free(smptr_ce_mdPvkdevicememory);
		free(smptr_ce_mdPbuffer_map);

		free(smptr_ce_mdPvkdevicesize);

		free(smptr_ce_mdPli);
		free(smptr_ce_mdPil);
	#endif

	for (uint8_t l0 = 0; l0 < smptr_ce_mdLj; ++l0)
	{
		free(Pbp[l0]);
		free(smptr_ce_mdPb[l0]);

		free(Pbone[l0].Pj);
	}
	free(Pbp);
	free(smptr_ce_mdPb);

	free(smptr_ce_mdPj);

	free(Pbone);

	for (uint32_t l0 = 0; l0 < Li; ++l0)
	{
		free(Pi[l0]);
	}
	free(Pi);
	free(Pil);
	for (uint8_t l0 = 0; l0 < SMPTR_CE_MDlA; ++l0)
	{
		free(Pa[l0]);
	}
	free(Prgba);
}
