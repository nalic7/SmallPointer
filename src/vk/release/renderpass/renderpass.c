void vk_makeRenderPass(uint32_t device, VkAttachmentDescriptionFlags vkattachmentdescriptionflags, VkSubpassDescriptionFlags vksubpassdescriptionflags, VkRenderPassCreateFlags vkrenderpasscreateflags, VkDependencyFlags vkdependencyflags, VkRenderPass *vkrenderpass_p)
{
	VkAttachmentDescription vkattachmentdescription_array[2] =
	{
		{
			// .format = m_vkswapchainkhr_vkformat_p[device],
			.format = NALI_VK_COLOR_FORMAT,
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
			.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
			.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,

			.flags = vkattachmentdescriptionflags
		},
		{
			.format = NALI_VK_DEPTH_FORMAT,
			.samples = VK_SAMPLE_COUNT_1_BIT,
			.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
			.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
			.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,

			.flags = vkattachmentdescriptionflags
		}
	};

	VkSubpassDescription vksubpassdescription =
	{
		.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
		.colorAttachmentCount = 1,
		.pColorAttachments = &(VkAttachmentReference)
		{
			.attachment = 0,
			.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
		},

		.inputAttachmentCount = 0,
		.pInputAttachments = VK_NULL_HANDLE,
		.pResolveAttachments = VK_NULL_HANDLE,
		.pDepthStencilAttachment = &(VkAttachmentReference)
		{
			.attachment = 1,
			.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
		},
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
		.attachmentCount = 2,
		.pAttachments = vkattachmentdescription_array,
		.subpassCount = 1,
		.pSubpasses = &vksubpassdescription,

		.dependencyCount = 1,
		.pDependencies = &vksubpassdependency,

		.flags = vkrenderpasscreateflags,
		.pNext = VK_NULL_HANDLE
	};

	vkCreateRenderPass(m_vkdevice_p[device], &vkrenderpasscreateinfo, VK_NULL_HANDLE, vkrenderpass_p);
	// VkResult vkresult = vkCreateRenderPass(m_vkdevice_p[device], &vkrenderpasscreateinfo, VK_NULL_HANDLE, vkrenderpass_p);
	// if (vkresult != VK_SUCCESS)
	// {
	// 	error("vkCreateRenderPass %d", vkresult)
	// }
}