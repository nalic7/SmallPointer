static void smpt_rd_vkwMdsts_write(uint32_t device, uint32_t bind, VkDescriptorImageInfo *Pvkdescriptorimageinfo, VkDescriptorBufferInfo *Pvkdescriptorbufferinfo, VkDescriptorType vkdescriptortype, VkDescriptorSet vkdescriptorset, VkWriteDescriptorSet *Pvkwritedescriptorset)
{
	*Pvkwritedescriptorset = (VkWriteDescriptorSet)
	{
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.dstSet = vkdescriptorset,
		.dstBinding = bind,
		.dstArrayElement = 0,
		.descriptorType = vkdescriptortype,//VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
		.descriptorCount = 1,

		.pImageInfo = Pvkdescriptorimageinfo,
		.pBufferInfo = Pvkdescriptorbufferinfo,
		.pTexelBufferView = VK_NULL_HANDLE,

		.pNext = VK_NULL_HANDLE
	};
	// vkUpdateDescriptorSets(smpt_rd_vkq_dvP[device], 1, &vkwritedescriptorset, 0, VK_NULL_HANDLE);
}

void smpt_rd_vkwMdsts(VkDescriptorSet *Pvkdescriptorset, VkDescriptorBufferInfo *Pvkdescriptorbufferinfo, VkWriteDescriptorSet *Pvkwritedescriptorset, SMPTRtMI ds, uint8_t j, uint8_t mj, uint8_t s)
{
	//.i bindpose s 1+
	Pvkdescriptorbufferinfo[0] = (VkDescriptorBufferInfo)
	{
		.buffer = smptr_ce_mdPvkbuffer[0],
		.offset = smptr_ce_mdPvkdevicesize[j] - sizeof(float) * 16 * 2,
		.range = (mj - 1) * sizeof(float) * 16 * 2
	};

	//.i src_color s
	Pvkdescriptorbufferinfo[1] = (VkDescriptorBufferInfo)
	{
		.buffer = smptr_ce_mdPvkbuffer[0],
		.offset = 0,
		.range = lcp_rgba_bl
	};

	for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
	{
		//.i gui/world d
		Pvkdescriptorbufferinfo[2 + l0 * 3 + 2] = (VkDescriptorBufferInfo)
		{
			.buffer = smptr_ce_mdPvkbuffer[s + l0],
			.offset = 0,
			.range = sizeof(float) * 16 * 2
		};

		//.i animate d
		Pvkdescriptorbufferinfo[2 + l0 * 3] = (VkDescriptorBufferInfo)
		{
			.buffer = smptr_cemPvkbuffer[l0 + ds * smpt_rd_vk_swcUimage],
			.offset = mj * (sizeof(float) * 4 + sizeof(float) * 4 * 3) * ds + sizeof(float) * 4,
			.range = mj * sizeof(float) * 4 * 3
		};

		//.i color d
		Pvkdescriptorbufferinfo[2 + l0 * 3 + 1] = (VkDescriptorBufferInfo)
		{
			.buffer = smptr_cemPvkbuffer[l0 + ds * smpt_rd_vk_swcUimage],
			.offset = mj * (sizeof(float) * 4 + sizeof(float) * 4 * 3) * ds,
			.range = sizeof(float) * 4
		};

		smpt_rd_vkwMdsts_write(smpt_rd_vkUdevice, 0, VK_NULL_HANDLE, Pvkdescriptorbufferinfo + 2 + l0 * 3 + 2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l0], Pvkwritedescriptorset + l0 * SMPT_RD_VKW_DSTS_LOl);

		smpt_rd_vkwMdsts_write(smpt_rd_vkUdevice, 1, VK_NULL_HANDLE, Pvkdescriptorbufferinfo, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l0], Pvkwritedescriptorset + l0 * SMPT_RD_VKW_DSTS_LOl + 1);

		smpt_rd_vkwMdsts_write(smpt_rd_vkUdevice, 2, VK_NULL_HANDLE, Pvkdescriptorbufferinfo + 2 + l0 * 3, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l0], Pvkwritedescriptorset + l0 * SMPT_RD_VKW_DSTS_LOl + 2);

		smpt_rd_vkwMdsts_write(smpt_rd_vkUdevice, 3, VK_NULL_HANDLE, Pvkdescriptorbufferinfo + 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l0], Pvkwritedescriptorset + l0 * SMPT_RD_VKW_DSTS_LOl + 3);

		smpt_rd_vkwMdsts_write(smpt_rd_vkUdevice, 4, VK_NULL_HANDLE, Pvkdescriptorbufferinfo + 2 + l0 * 3 + 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, Pvkdescriptorset[l0], Pvkwritedescriptorset + l0 * SMPT_RD_VKW_DSTS_LOl + 4);
	}
}
