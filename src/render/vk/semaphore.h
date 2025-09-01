#ifndef _RD_VK_SMP_H
	#define _RD_VK_SMP_H

	#define _RD_VK_SMP_MAKE(device, vksemaphore_p) \
		_DB_R2L \
		( \
			"vkCreateSemaphore %d", \
			vkCreateSemaphore \
			( \
				_rd_vkq_dv_p[device], \
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
