void vk_cmd(VkCommandBuffer vkcommandbuffer, VkCommandBufferBeginInfo *vkcommandbufferbegininfo_p, VkQueue vkqueue_graphic)
{
	VkSubmitInfo cmd_vksubmitinfo =
	{
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,

		.commandBufferCount = 1,
		.pCommandBuffers = &vkcommandbuffer,

		.waitSemaphoreCount = 0,
		.pWaitSemaphores = VK_NULL_HANDLE,
		// .pWaitDstStageMask = (VkPipelineStageFlags[]){VK_PIPELINE_STAGE_TRANSFER_BIT},
		.pWaitDstStageMask = VK_NULL_HANDLE,

		.signalSemaphoreCount = 0,
		// .pSignalSemaphores = &render_vksemaphore,
		.pSignalSemaphores = VK_NULL_HANDLE,

		.pNext = VK_NULL_HANDLE
	};
	vkBeginCommandBuffer(vkcommandbuffer, vkcommandbufferbegininfo_p);
	vk_cmdImage(vkcommandbuffer, vkqueue_graphic);
	vkEndCommandBuffer(vkcommandbuffer);
	vkQueueSubmit(vkqueue_graphic, 1, &cmd_vksubmitinfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(vkqueue_graphic);
}

void vk_cmdImage(VkCommandBuffer vkcommandbuffer, VkQueue vkqueue_graphic)
{
	VkImageMemoryBarrier vkimagememorybarrier;
	vk_setImageMemoryBarrier(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, m_nali_g_image_vkimage_p[0], VK_ACCESS_NONE, VK_ACCESS_TRANSFER_WRITE_BIT, &vkimagememorybarrier);
	vkCmdPipelineBarrier(vkcommandbuffer, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE, 1, &vkimagememorybarrier);
	VkBufferImageCopy vkbufferimagecopy;
	vk_setBufferImageCopy(m_nali_g_image_wh_uint32_t_p[0], m_nali_g_image_wh_uint32_t_p[1], &vkbufferimagecopy);
	vkCmdCopyBufferToImage(vkcommandbuffer, m_nali_g_image_vkbuffer_p[0], m_nali_g_image_vkimage_p[0], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &vkbufferimagecopy);
	// vkEndCommandBuffer(vkcommandbuffer);

	// // vkQueueSubmit(vkqueue_graphic, 1, &cmd_vksubmitinfo, *graphic_vkfence_p);
	// vkQueueSubmit(vkqueue_graphic, 1, &cmd_vksubmitinfo, VK_NULL_HANDLE);
	// // uint64_t semaphore_value = 0;
	// // VkSemaphoreWaitInfo vksemaphorewaitinfo =
	// // {
	// // 	.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
	// // 	.semaphoreCount = 1,
	// // 	.pSemaphores = &render_vksemaphore,

	// // 	.pValues = &semaphore_value,

	// // 	.flags = 0,
	// // 	.pNext = VK_NULL_HANDLE
	// // };
	// // vkWaitSemaphores(vkdevice, &vksemaphorewaitinfo, UINT64_MAX);
	// vkQueueWaitIdle(vkqueue_graphic);

	// // vkWaitForFences(vkdevice, 1, graphic_vkfence_p, VK_TRUE, UINT64_MAX);
	// // vkResetFences(vkdevice, 1, graphic_vkfence_p);
	// //

	// vkBeginCommandBuffer(vkcommandbuffer, &vkcommandbufferbegininfo);
	vk_setImageMemoryBarrier(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_GENERAL, m_nali_g_image_vkimage_p[0], VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT, &vkimagememorybarrier);
	vkCmdPipelineBarrier(vkcommandbuffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE, 1, &vkimagememorybarrier);
}