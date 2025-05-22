void vksp_make(uint32_t device, VkSemaphore *vksemaphore_p)
{
	nali_info
	(
		"vkCreateSemaphore %d",
		vkCreateSemaphore
		(
			vkqd_vkdevice_p[device],
			&(VkSemaphoreCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
				.pNext = VK_NULL_HANDLE,
				.flags = 0
			},
			VK_NULL_HANDLE,
			vksemaphore_p
		)
	)
}
