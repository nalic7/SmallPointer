#ifndef SMPT_RD_VKWhDSTS
	#define SMPT_RD_VKWhDSTS

	#define SMPT_RD_VKW_DSTSmMAKE(Udevice, Ui, Pvkdescriptorset) \
		SMPT_DBmR2L \
		( \
			"vkAllocateDescriptorSets %d", \
			vkAllocateDescriptorSets \
			( \
				smpt_rd_vkq_dvP[Udevice], \
				&(VkDescriptorSetAllocateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO, \
					.descriptorPool = smpt_rd_vkw_dstspP[Ui], \
					.descriptorSetCount = 1, \
					.pSetLayouts = &smpt_rd_vkw_dsts_loP[Ui], \
					.pNext = VK_NULL_HANDLE \
				}, \
				Pvkdescriptorset \
			) \
		)
#endif
