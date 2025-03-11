void vk_makeFrameBuffer(uint32_t device, VkFramebufferCreateFlags vkframebuffercreateflags, VkImageView* vkimageview_ptr, VkRenderPass* vkrenderpass_ptr, VkFramebuffer* vkframebuffer_ptr)
{
	VkExtent2D vkextent2d = m_vkswapchainkhr_vkextent2d_ptr[device];
	VkFramebufferCreateInfo vkframebuffercreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
		.renderPass = *vkrenderpass_ptr,
		.attachmentCount = 1,
		.pAttachments = vkimageview_ptr,
		.width = vkextent2d.width,
		.height = vkextent2d.height,
		.layers = 1,
		.flags = vkframebuffercreateflags,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateFramebuffer(m_vkdevice_ptr[device], &vkframebuffercreateinfo, VK_NULL_HANDLE, vkframebuffer_ptr);
}