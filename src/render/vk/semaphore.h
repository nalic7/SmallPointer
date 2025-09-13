#ifndef SMPT_RD_VKhSMP
	#define SMPT_RD_VKhSMP

	#define SMPT_RD_VK_SMPmMAKE(device, vksemaphore_p) \
		SMPT_DBmR2L \
		( \
			"vkCreateSemaphore %d", \
			vkCreateSemaphore \
			( \
				smpt_rd_vkq_dvP[device], \
				&(VkSemaphoreCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, \
					.pNext = VK_NULL_HANDLE, \
					.flags = 0 \
				}, \
				VK_NULL_HANDLE, \
				vksemaphore_p \
			) \
		)
#endif
