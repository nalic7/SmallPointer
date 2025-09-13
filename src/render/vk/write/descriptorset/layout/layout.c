VkDescriptorSetLayout smpt_rd_vkw_dsts_loV;

void smpt_rd_vkw_dsts_loMmake(uint32_t device)
{
	SMPT_DBmR2L
	(
		"vkCreateDescriptorSetLayout %d",
		vkCreateDescriptorSetLayout
		(
			smpt_rd_vkq_dvP[device],
			&(VkDescriptorSetLayoutCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
				.bindingCount = SMPT_RD_VKW_DSTS_LOl,
				.pBindings = (VkDescriptorSetLayoutBinding[])
				{
					{
						.binding = 0,
						.descriptorCount = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.pImmutableSamplers = VK_NULL_HANDLE,
						.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
					},
					{
						.binding = 1,
						.descriptorCount = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.pImmutableSamplers = VK_NULL_HANDLE,
						.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
					},
					{
						.binding = 2,
						.descriptorCount = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.pImmutableSamplers = VK_NULL_HANDLE,
						.stageFlags = VK_SHADER_STAGE_VERTEX_BIT
					},
					{
						.binding = 3,
						.descriptorCount = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.pImmutableSamplers = VK_NULL_HANDLE,
						.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
					},
					{
						.binding = 4,
						.descriptorCount = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
						.pImmutableSamplers = VK_NULL_HANDLE,
						.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT
					}
				},

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&smpt_rd_vkw_dsts_loV
		)
	)
}

void smpt_rd_vkw_dsts_loMfree(uint32_t device)
{
	vkDestroyDescriptorSetLayout(smpt_rd_vkq_dvP[device], smpt_rd_vkw_dsts_loV, VK_NULL_HANDLE);
}
