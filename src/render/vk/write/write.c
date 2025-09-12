static void smpt_rd_vkw_dsts_write(uint32_t device, uint32_t bind, VkDescriptorImageInfo *vkdescriptorimageinfo_p, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkDescriptorType vkdescriptortype, VkDescriptorSet vkdescriptorset, VkWriteDescriptorSet *vkwritedescriptorset_p)
{
	*vkwritedescriptorset_p = (VkWriteDescriptorSet)
	{
		.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
		.dstSet = vkdescriptorset,
		.dstBinding = bind,
		.dstArrayElement = 0,
		.descriptorType = vkdescriptortype,//VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER
		.descriptorCount = 1,

		.pImageInfo = vkdescriptorimageinfo_p,
		.pBufferInfo = vkdescriptorbufferinfo_p,
		.pTexelBufferView = VK_NULL_HANDLE,

		.pNext = VK_NULL_HANDLE
	};
	// vkUpdateDescriptorSets(smpt_rd_vkq_dv_p[device], 1, &vkwritedescriptorset, 0, VK_NULL_HANDLE);
}

void smpt_rd_vkw_dsts(VkDescriptorSet *vkdescriptorset_p, VkDescriptorBufferInfo *vkdescriptorbufferinfo_p, VkWriteDescriptorSet *vkwritedescriptorset_p, SMPTRtMI ds, uint8_t j, uint8_t mj, uint8_t s)
{
	//.i bindpose s 1+
	vkdescriptorbufferinfo_p[0] = (VkDescriptorBufferInfo)
	{
		.buffer = smptr_ce_mdPvkbuffer[0],
		.offset = smptr_ce_mdPvkdevicesize[j] - sizeof(float) * 16 * 2,
		.range = (mj - 1) * sizeof(float) * 16 * 2
	};

	//.i src_color s
	vkdescriptorbufferinfo_p[1] = (VkDescriptorBufferInfo)
	{
		.buffer = smptr_ce_mdPvkbuffer[0],
		.offset = 0,
		.range = lcp_rgba_bl
	};

	for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
	{
		//.i gui/world d
		vkdescriptorbufferinfo_p[2 + l0 * 3 + 2] = (VkDescriptorBufferInfo)
		{
			.buffer = smptr_ce_mdPvkbuffer[s + l0],
			.offset = 0,
			.range = sizeof(float) * 16 * 2
		};

		//.i animate d
		vkdescriptorbufferinfo_p[2 + l0 * 3] = (VkDescriptorBufferInfo)
		{
			.buffer = smptr_cemPvkbuffer[l0 + ds * smpt_rd_vk_swcUimage],
			.offset = mj * (sizeof(float) * 4 + sizeof(float) * 4 * 3) * ds + sizeof(float) * 4,
			.range = mj * sizeof(float) * 4 * 3
		};

		//.i color d
		vkdescriptorbufferinfo_p[2 + l0 * 3 + 1] = (VkDescriptorBufferInfo)
		{
			.buffer = smptr_cemPvkbuffer[l0 + ds * smpt_rd_vk_swcUimage],
			.offset = mj * (sizeof(float) * 4 + sizeof(float) * 4 * 3) * ds,
			.range = sizeof(float) * 4
		};

		smpt_rd_vkw_dsts_write(smpt_rd_vk_device, 0, VK_NULL_HANDLE, vkdescriptorbufferinfo_p + 2 + l0 * 3 + 2, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset_p[l0], vkwritedescriptorset_p + l0 * SMPT_RD_VKW_DSTSLO_L);

		smpt_rd_vkw_dsts_write(smpt_rd_vk_device, 1, VK_NULL_HANDLE, vkdescriptorbufferinfo_p, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset_p[l0], vkwritedescriptorset_p + l0 * SMPT_RD_VKW_DSTSLO_L + 1);

		smpt_rd_vkw_dsts_write(smpt_rd_vk_device, 2, VK_NULL_HANDLE, vkdescriptorbufferinfo_p + 2 + l0 * 3, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset_p[l0], vkwritedescriptorset_p + l0 * SMPT_RD_VKW_DSTSLO_L + 2);

		smpt_rd_vkw_dsts_write(smpt_rd_vk_device, 3, VK_NULL_HANDLE, vkdescriptorbufferinfo_p + 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset_p[l0], vkwritedescriptorset_p + l0 * SMPT_RD_VKW_DSTSLO_L + 3);

		smpt_rd_vkw_dsts_write(smpt_rd_vk_device, 4, VK_NULL_HANDLE, vkdescriptorbufferinfo_p + 2 + l0 * 3 + 1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, vkdescriptorset_p[l0], vkwritedescriptorset_p + l0 * SMPT_RD_VKW_DSTSLO_L + 4);
	}
}
