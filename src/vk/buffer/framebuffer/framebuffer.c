void vk_makeFrameBuffer(uint32_t device, VkFramebufferCreateFlags vkframebuffercreateflags, VkImageView* vkimageview_p, VkRenderPass* vkrenderpass_p, VkFramebuffer* vkframebuffer_p)
{
	VkExtent2D vkextent2d = m_vkswapchainkhr_vkextent2d_p[device];
	VkFramebufferCreateInfo vkframebuffercreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
		.renderPass = *vkrenderpass_p,
		.attachmentCount = 1,
		.pAttachments = vkimageview_p,
		.width = vkextent2d.width,
		.height = vkextent2d.height,
		.layers = 1,
		.flags = vkframebuffercreateflags,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateFramebuffer(m_vkdevice_p[device], &vkframebuffercreateinfo, VK_NULL_HANDLE, vkframebuffer_p);
}