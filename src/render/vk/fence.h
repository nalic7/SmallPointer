#ifndef SMPT_RD_VKF_H
	#define SMPT_RD_VKF_H

	#define SMPT_RD_VKF_MAKE(device, vkfence_p) \
		SMPT_DB_R2L \
		( \
			"vkCreateFence %d", \
			vkCreateFence \
			( \
				smpt_rd_vkq_dv_p[device], \
				&(VkFenceCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, \
					.flags = VK_FENCE_CREATE_SIGNALED_BIT, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				vkfence_p \
			) \
		)
#endif
