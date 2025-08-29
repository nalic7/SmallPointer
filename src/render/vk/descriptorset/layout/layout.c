VkDescriptorSetLayout _rd_vk_dstslo;

void _rd_vk_dsts_lo_make(uint32_t device)
{
	_DB_R2L
	(
		"vkCreateDescriptorSetLayout %d",
		vkCreateDescriptorSetLayout
		(
			_vkq_dv_p[device],
			&(VkDescriptorSetLayoutCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
				.bindingCount = _RD_VK_DSTSLO_L,
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
			&_rd_vk_dstslo
		)
	)
}

void _rd_vk_dsts_lo_free(uint32_t device)
{
	vkDestroyDescriptorSetLayout(_vkq_dv_p[device], _rd_vk_dstslo, VK_NULL_HANDLE);
}
