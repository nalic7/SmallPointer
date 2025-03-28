void vk_makeSemaphore(uint32_t device, VkSemaphore *vksemaphore_p)
{
	VkSemaphoreCreateInfo vksemaphorecreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		.pNext = VK_NULL_HANDLE,
		.flags = 0
	};
	vkCreateSemaphore(m_vkdevice_p[device], &vksemaphorecreateinfo, VK_NULL_HANDLE, vksemaphore_p);
}
