#ifndef NALI_VK_FENCE_H
#define NALI_VK_FENCE_H

#define VK_makeFence(device, vkfence_p) \
	NALI_D_INFO \
	( \
		"vkCreateFence %d", \
		vkCreateFence \
		( \
			vkqd_vkdevice_p[device], \
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