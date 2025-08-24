#ifndef _VK_SMP_H
#define _VK_SMP_H
	#define _VK_SMP_MAKE(device, vksemaphore_p) \
		NALI_D_INFO \
		( \
			"vkCreateSemaphore %d", \
			vkCreateSemaphore \
			( \
				_vkq_dv_p[device], \
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
