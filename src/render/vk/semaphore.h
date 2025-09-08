#ifndef SMPT_RD_VK_SMP_H
	#define SMPT_RD_VK_SMP_H

	#define SMPT_RD_VK_SMP_MAKE(device, vksemaphore_p) \
		SMPT_DBmR2L \
		( \
			"vkCreateSemaphore %d", \
			vkCreateSemaphore \
			( \
				smpt_rd_vkq_dv_p[device], \
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
