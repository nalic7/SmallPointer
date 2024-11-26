uint32_t image;

VkPipelineStageFlags vkpipelinestageflags[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

void vk_draw()
{
	VkDevice vkdevice = m_vkdevice_ptr[m_device];
	VkSwapchainKHR vkswapchainkhr = m_vkswapchainkhr_ptr[m_device];
	VkFence vkfence = m_vkfence_ptr[m_device];
	VkQueue vkqueue = m_vkqueue_graphics_ptr[m_graphic][m_graphic];
	VkSemaphore* vksemaphore_ptr = m_vksemaphore_ptr[m_graphic][m_graphic];
	VkSemaphore image_vksemaphore = vksemaphore_ptr[0];
	VkSemaphore render_vksemaphore = vksemaphore_ptr[1];

	vkWaitForFences(vkdevice, 1, &vkfence, VK_TRUE, UINT64_MAX);
	vkResetFences(vkdevice, 1, &vkfence);

	vkAcquireNextImageKHR(vkdevice, vkswapchainkhr, UINT64_MAX, image_vksemaphore, VK_NULL_HANDLE, &image);
	// if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)

	// vkResetCommandBuffer(commandBuffer, 0);
	vkBeginCommandBuffer(commandBuffer, &vkcommandbufferbegininfo);

	VkImageMemoryBarrier barrier;
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;//VK_ACCESS_TRANSFER_WRITE_BIT
	barrier.dstAccessMask = VK_ACCESS_MEMORY_WRITE_BIT;//VK_ACCESS_SHADER_READ_BIT
	barrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;//VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
	barrier.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;//VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
	barrier.image = m_vkswapchainkhr_vkimage_ptr[m_device][image];
	barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;

	// barrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL; // or whatever layout you used for rendering
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

	vkCmdPipelineBarrier
	(
		commandBuffer,
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,//VK_PIPELINE_STAGE_TRANSFER_BIT
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,//VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
		0,
		0, NULL,
		0, NULL,
		1, &barrier
	);

	VkRenderPassBeginInfo renderPassInfo =
	{
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.renderPass = renderPass,
		.framebuffer = framebuffers[imageIndex],
		.renderArea.offset = (VkOffset2D){0, 0},
		.renderArea.extent = swapchainExtent,
		.clearValueCount = 1,
		.pClearValues = &clearColor
	};

	vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
	// vkCmdClearColorImage(commandBuffer, colorImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clearColor, 1, &colorAttachmentRange);
	// vkCmdClearAttachments(commandBuffer, 2, clearValue, 1, &rect);
	vkCmdEndRenderPass(commandBuffer);
	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo;
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;
	submitInfo.pNext = NULL;
	submitInfo.pWaitDstStageMask = vkpipelinestageflags;
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &render_vksemaphore;
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &image_vksemaphore;

	vkQueueSubmit(vkqueue, 1, &submitInfo, vkfence);

	VkPresentInfoKHR presentInfo;
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.pNext = NULL; // No extensions
	presentInfo.waitSemaphoreCount = 1; // Number of semaphores to wait for
	presentInfo.pWaitSemaphores = &render_vksemaphore; // Semaphore to wait for before presenting
	presentInfo.swapchainCount = 1; // Number of swapchains to present to
	presentInfo.pSwapchains = &vkswapchainkhr; // The swapchain to present to
	presentInfo.pImageIndices = &image; // The index of the swapchain image to present
	// presentInfo.pImageIndices = &pImageIndices;
	presentInfo.pResults = NULL; // Optional, can be used to get results for each swapchain

	vkQueueWaitIdle(vkqueue);
	vkQueuePresentKHR(vkqueue, &presentInfo);
}
