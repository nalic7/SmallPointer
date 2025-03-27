void vk_makeFrameBuffer(uint32_t device, VkImageView *vkimageview_p, uint32_t vkimageview_size, VkRenderPass *vkrenderpass_p, VkFramebuffer *vkframebuffer_p)
{
	VkExtent2D vkextent2d = m_vkswapchainkhr_vkextent2d_p[device];
	VkFramebufferCreateInfo vkframebuffercreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
		.renderPass = *vkrenderpass_p,
		.attachmentCount = vkimageview_size,
		.pAttachments = vkimageview_p,
		.width = vkextent2d.width,
		.height = vkextent2d.height,
		.layers = 1,
		.flags = 0,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateFramebuffer(m_vkdevice_p[device], &vkframebuffercreateinfo, VK_NULL_HANDLE, vkframebuffer_p);
}