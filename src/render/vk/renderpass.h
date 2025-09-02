#ifndef SMPT_RD_VK_RDP_H
	#define SMPT_RD_VK_RDP_H

	#define SMPT_RD_VK_RDP_MAKE(device, vkrenderpass_p) \
		SMPT_DB_R2L \
		( \
			"vkCreateRenderPass %d", \
			vkCreateRenderPass \
			( \
				smpt_rd_vkq_dv_p[device], \
				&(VkRenderPassCreateInfo) \
				{ \
					.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO, \
					.attachmentCount = 3, \
					.pAttachments = (VkAttachmentDescription[]) \
					{ \
						{ \
							.format = SMPT_RD_VK_COLOR_FORMAT, \
							.samples = SMPT_RD_VK_SAMPLE_C, \
							.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR, \
							.storeOp = VK_ATTACHMENT_STORE_OP_STORE, \
							.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE, \
							.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE, \
							.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED, \
							.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, \
							.flags = 0 \
						}, \
						{ \
							.format = SMPT_RD_VK_DEPTH_FORMAT, \
							.samples = SMPT_RD_VK_SAMPLE_C, \
							.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR, \
							.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE, \
							.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE, \
							.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE, \
							.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED, \
							.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, \
							.flags = 0 \
						}, \
						{ \
							.format = SMPT_RD_VK_COLOR_FORMAT, \
							.samples = VK_SAMPLE_COUNT_1_BIT, \
							.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE, \
							.storeOp = VK_ATTACHMENT_STORE_OP_STORE, \
							.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE, \
							.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE, \
							.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED, \
							.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, \
							.flags = 0 \
						}, \
					}, \
					.subpassCount = 1, \
					.pSubpasses = &(VkSubpassDescription) \
					{ \
						.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS, \
						.colorAttachmentCount = 1, \
						.pColorAttachments = &(VkAttachmentReference) \
						{ \
							.attachment = 0, \
							.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL \
						}, \
						.inputAttachmentCount = 0, \
						.pInputAttachments = VK_NULL_HANDLE, \
						.pResolveAttachments = &(VkAttachmentReference) \
						{ \
							.attachment = 2, \
							.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL \
						}, \
						.pDepthStencilAttachment = &(VkAttachmentReference) \
						{ \
							.attachment = 1, \
							.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL \
						}, \
						.preserveAttachmentCount = 0, \
						.pPreserveAttachments = VK_NULL_HANDLE, \
						.flags = 0, \
					}, \
					.dependencyCount = 1, \
					.pDependencies = &(VkSubpassDependency) \
					{ \
						.srcSubpass = VK_SUBPASS_EXTERNAL, \
						.dstSubpass = 0, \
						.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT, \
						.srcAccessMask = 0, \
						.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT, \
						.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT, \
						.dependencyFlags = 0 \
					}, \
					.flags = 0, \
					.pNext = VK_NULL_HANDLE \
				}, \
				VK_NULL_HANDLE, \
				vkrenderpass_p \
			) \
		)
#endif
