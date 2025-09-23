#ifndef SMPT_RD_VKW_DSTShLO
	#define SMPT_RD_VKW_DSTShLO

	#define SMPT_RD_VKW_DSTS_LOl 5

	extern VkDescriptorSetLayout smpt_rd_vkw_dsts_loP[2];

	#define SMPT_RD_VKW_DSTS_LOmMAKE(device, i) \
		SMPT_DBmR2L \
		( \
			"vkCreateDescriptorSetLayout %d", \
			vkCreateDescriptorSetLayout \
			( \
				smpt_rd_vkq_dvP[device], \
				&(VkDescriptorSetLayoutCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO, \
					.bindingCount = SMPT_RD_VKW_DSTS_LOl, \
					.pBindings = (VkDescriptorSetLayoutBinding[]) \
					{ \
						{ \
							.binding = 0, \
							.descriptorCount = 1, \
							.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, \
							.pImmutableSamplers = VK_NULL_HANDLE, \
							.stageFlags = VK_SHADER_STAGE_VERTEX_BIT \
						}, \
						{ \
							.binding = 1, \
							.descriptorCount = 1, \
							.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, \
							.pImmutableSamplers = VK_NULL_HANDLE, \
							.stageFlags = VK_SHADER_STAGE_VERTEX_BIT \
						}, \
						{ \
							.binding = 2, \
							.descriptorCount = 1, \
							.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, \
							.pImmutableSamplers = VK_NULL_HANDLE, \
							.stageFlags = VK_SHADER_STAGE_VERTEX_BIT \
						}, \
						{ \
							.binding = 3, \
							.descriptorCount = 1, \
							.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, \
							.pImmutableSamplers = VK_NULL_HANDLE, \
							.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT \
						}, \
						{ \
							.binding = 4, \
							.descriptorCount = 1, \
							.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, \
							.pImmutableSamplers = VK_NULL_HANDLE, \
							.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT \
						} \
					}, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				smpt_rd_vkw_dsts_loP + i \
			) \
		)

	void smpt_rd_vkw_dsts_loMfree();
#endif
