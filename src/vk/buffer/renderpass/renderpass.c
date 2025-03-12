void vk_makeRenderPass(uint32_t device, VkAttachmentDescriptionFlags vkattachmentdescriptionflags, VkSubpassDescriptionFlags vksubpassdescriptionflags, VkRenderPassCreateFlags vkrenderpasscreateflags, VkDependencyFlags vkdependencyflags, VkRenderPass* vkrenderpass_ptr)
{
	VkAttachmentDescription vkattachmentdescription =
	{
		.format = m_vkswapchainkhr_vkformat_ptr[device],
		.samples = VK_SAMPLE_COUNT_1_BIT,
		.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
		.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
		.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
		.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
		.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,

		.flags = vkattachmentdescriptionflags
	};

	VkAttachmentReference vkattachmentreference =
	{
		.attachment = 0,
		.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
	};

	VkSubpassDescription vksubpassdescription =
	{
		.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.colorAttachmentCount = 1,
		.pColorAttachments = &vkattachmentreference,

		.inputAttachmentCount = 0,
		.pInputAttachments = VK_NULL_HANDLE,
		.pResolveAttachments = VK_NULL_HANDLE,
		.pDepthStencilAttachment = VK_NULL_HANDLE,
		.preserveAttachmentCount = 0,
		.pPreserveAttachments = VK_NULL_HANDLE,
		.flags = vksubpassdescriptionflags,
	};

	VkSubpassDependency vksubpassdependency =
	{
		.srcSubpass = VK_SUBPASS_EXTERNAL,
		.dstSubpass = 0,
		.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.srcAccessMask = 0,
		// .srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		// .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.dependencyFlags = vkdependencyflags
	};
	VkRenderPassCreateInfo vkrenderpasscreateinfo =
	{
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
		.attachmentCount = 1,
		.pAttachments = &vkattachmentdescription,
		.subpassCount = 1,
		.pSubpasses = &vksubpassdescription,

		.dependencyCount = 1,
		.pDependencies = &vksubpassdependency,

		.flags = vkrenderpasscreateflags,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateRenderPass(m_vkdevice_ptr[device], &vkrenderpasscreateinfo, VK_NULL_HANDLE, vkrenderpass_ptr);
	// VkResult vkresult = vkCreateRenderPass(m_vkdevice_ptr[device], &vkrenderpasscreateinfo, VK_NULL_HANDLE, vkrenderpass_ptr);
	// if (vkresult != VK_SUCCESS)
	// {
	// 	error("vkCreateRenderPass %d", vkresult)
	// }
}