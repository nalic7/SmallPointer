void vk_makeFrameBuffer(uint32_t device, VkImageView *vkimageview_p, uint32_t vkimageview_size, VkRenderPass vkrenderpass, VkFramebuffer *vkframebuffer_p)
{
	nali_info
	(
		"vkCreateFramebuffer %d",
		vkCreateFramebuffer
		(
			m_vkdevice_p[device],
			&(VkFramebufferCreateInfo)
			{
				.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
				.renderPass = vkrenderpass,
				.attachmentCount = vkimageview_size,
				.pAttachments = vkimageview_p,
				.width = m_vkextent2d.width,
				.height = m_vkextent2d.height,
				.layers = 1,
				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			vkframebuffer_p
		)
	)
}