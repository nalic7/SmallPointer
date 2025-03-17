void vk_makeFence(uint32_t device, VkFence* vkfence_p)
{
	VkFenceCreateInfo vkfencecreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.flags = VK_FENCE_CREATE_SIGNALED_BIT,
		.pNext = VK_NULL_HANDLE
	};
	vkCreateFence(m_vkdevice_p[device], &vkfencecreateinfo, VK_NULL_HANDLE, vkfence_p);
}
