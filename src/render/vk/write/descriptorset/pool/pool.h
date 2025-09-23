#ifndef SMPT_RD_VKW_DSTShP
	#define SMPT_RD_VKW_DSTShP

	extern VkDescriptorPool smpt_rd_vkw_dstspP[2];

	//! SMPTRlMI
	#define SMPT_RD_VKW_DSTSPmMAKE(Udevice, Umax_set, Ui) \
		SMPT_DBmR2L \
		( \
			"vkCreateDescriptorPool %d", \
			vkCreateDescriptorPool \
			( \
				smpt_rd_vkq_dvP[Udevice], \
				&(VkDescriptorPoolCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO, \
					.poolSizeCount = 1, \
					.pPoolSizes = &(VkDescriptorPoolSize) \
					{ \
						.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, \
						.descriptorCount = SMPTRlMI * SMPT_RD_VKW_DSTS_LOl \
					}, \
					.maxSets = Umax_set, \
					.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				smpt_rd_vkw_dstspP + i \
			) \
		)

	void smpt_rd_vkw_dstspMfree();
#endif
