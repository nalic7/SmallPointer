// void (**vk_cmd_d_fp)();
// uint16_t vk_cmd_d_fp_bl = 0;
// mtx_t *m_mtx_t_draw_p = &(mtx_t){};

// static clock_t frame_start, frame_end;
static struct timespec frame_start = {0}, frame_end;
// static struct timespec delta_start = {0}, delta_end;
static uint32_t frame;
// static clock_t frame_time;
static double frame_time = 0;

//s0-share
static VkDevice vkdevice;
static VkQueue vkqueue_graphic;
//e0-share

//s0-s
static VkPipelineLayout vkpipelinelayout;
static VkPipeline vkpipeline;
//e0-s

//s0-cmd
static VkCommandBufferBeginInfo vkcommandbufferbegininfo =
{
	.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
	.pInheritanceInfo = VK_NULL_HANDLE,

	.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
	.pNext = VK_NULL_HANDLE
};

static VkCommandBuffer *vkcommandbuffer_p;
//e0-cmd

//s0-draw
static VkClearValue vkclearvalue_array[2] =
{
	{.color = {.float32 = {0.0F, 0.0F, 0.0F, 1.0F}}},
	{.depthStencil =
		{
			.depth = 1.0F,
			.stencil = 0.0F
		}
	}
};
static VkRenderPassBeginInfo vkrenderpassbegininfo =
{
	.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
	.renderArea.offset = {0, 0},
	.clearValueCount = 2,
	.pClearValues = vkclearvalue_array,

	.pNext = VK_NULL_HANDLE
};
static VkViewport vkviewport =
{
	.x = 0.0F,
	.y = 0.0F,
	.minDepth = 0.0F,
	.maxDepth = 1.0F
};
static VkRect2D vkrect2d =
{
	.offset = {0, 0}
};
//s1-queue

//graphic
static VkFence *vkfence_p;
//image render
//[vksc_image][2]
static VkSemaphore **vksemaphore_p;

static VkSubmitInfo image_vksubmitinfo =
{
	.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
	.waitSemaphoreCount = 1,
	.pWaitDstStageMask = (VkPipelineStageFlags[]){VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT},
	.commandBufferCount = 1,
	.signalSemaphoreCount = 1,

	.pNext = VK_NULL_HANDLE
};
static VkPresentInfoKHR vkpresentinfokhr =
{
	.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
	.waitSemaphoreCount = 1,

	.swapchainCount = 1,
	.pSwapchains = &vksc_vkswapchainkhr,

	.pResults = VK_NULL_HANDLE,
	.pNext = VK_NULL_HANDLE
};
//e1-queue
//e0-draw

void vk_cmd_draw_set()
{
	// vk_cmd_d_fp = malloc(0);

	//s0-share
	vkdevice = vkqd_vkdevice_p[vk_device];
	vkqueue_graphic = vkq_vkqueue_p[vk_device][vk_queue_g];
	//e0-share

	//s0-s
	VkShaderModule vkshadermodule_vert;
	VkShaderModule vkshadermodule_frag;
	VkPipelineShaderStageCreateInfo vkpipelineshaderstagecreateinfo_array[2];

	// const char shader_type[] = ".spv";

	// const char vert_shader_path[] = NALI_F_HOME NALI_F_HOME_SHADER NALI_F_HOME_SHADER_VERT "/";
	// uint32_t vert_index = 0;
	// uint8_t vert_name_index = sizeof(vert_shader_path)-1;
	// char *vert_file = malloc(vert_name_index + M_LENGTH(vert_index) + sizeof(shader_type)-1 + 1);
	// strcpy(vert_file, vert_shader_path);
	// sprintf(vert_file + vert_name_index, "%u", vert_index);
	// strcat(vert_file, shader_type);

	// const char frag_shader_path[] = NALI_F_HOME NALI_F_HOME_SHADER NALI_F_HOME_SHADER_FRAG "/";
	// uint32_t frag_index = 0;
	// uint8_t frag_name_index = sizeof(frag_shader_path)-1;
	// char *frag_file = malloc(frag_name_index + M_LENGTH(frag_index) + sizeof(shader_type)-1 + 1);
	// strcpy(frag_file, frag_shader_path);
	// sprintf(frag_file + frag_name_index, "%u", frag_index);
	// strcat(frag_file, shader_type);

	// vk_setVkPipelineShaderStageCreateInfo(vk_device, vert_file, frag_file, &vkshadermodule_vert, &vkshadermodule_frag, vkpipelineshaderstagecreateinfo_array);
	// vk_setVkPipelineShaderStageCreateInfo(vk_device, NALI_F_HOME NALI_F_HOME_SHADER "vert.spv", NALI_F_HOME NALI_F_HOME_SHADER "frag.spv", &vkshadermodule_vert, &vkshadermodule_frag, vkpipelineshaderstagecreateinfo_array);
	vk_setVkPipelineShaderStageCreateInfo(vk_device, NALI_F_HOME_VERT, NALI_F_HOME_FRAG, &vkshadermodule_vert, &vkshadermodule_frag, vkpipelineshaderstagecreateinfo_array);
	// free(vert_file);
	// free(frag_file);

	//s1-s
	vkgplpllo_make(vk_device, &lcs_vkdescriptorsetlayout, 1, &vkpipelinelayout);
	vkgpl_make(vk_device, vkpipelineshaderstagecreateinfo_array, vksc_vkrenderpass, vkpipelinelayout, &vkpipeline);
	//e1-s

	vkDestroyShaderModule(vkdevice, vkshadermodule_frag, VK_NULL_HANDLE);
	vkDestroyShaderModule(vkdevice, vkshadermodule_vert, VK_NULL_HANDLE);
	//e0-s

	//s0-draw
	vkcommandbuffer_p = malloc(sizeof(VkCommandBuffer) * vksc_image);
	vkfence_p = malloc(sizeof(VkFence) * vksc_image);
	vksemaphore_p = malloc(sizeof(VkSemaphore *) * vksc_image);
	for (uint8_t l_0 = 0; l_0 < vksc_image; ++l_0)
	{
		//s0-cmd
		vkcb_make(vk_device, vk_queue_g, vkcommandbuffer_p + l_0, 1);
		vk_cmd(vkcommandbuffer_p[l_0], &vkcommandbufferbegininfo, vkqueue_graphic);
		//e0-cmd

		//!need check again
		// //s0-ubo
		// // lc_setVkWriteDescriptorSet(vkdescriptorset, &vkdescriptorbufferinfo, &vkdescriptorimageinfo, vkwritedescriptorset_array);
		// lc_setVkWriteDescriptorSet(vkdescriptorset, &vkdescriptorbufferinfo, vkwritedescriptorset_array);
		// //s1-update
		// vkUpdateDescriptorSets(vkdevice, 6, vkwritedescriptorset_array, 0, VK_NULL_HANDLE);
		// //e1-update
		// //e0-ubo

		VK_makeFence(vk_device, vkfence_p + l_0)

		vksemaphore_p[l_0] = malloc(sizeof(VkSemaphore) * 2);
		for (uint8_t l_1 = 0; l_1 < 2; ++l_1)
		{
			vksp_make(vk_device, vksemaphore_p[l_0] + l_1);
		}
	}

	vkrenderpassbegininfo.renderPass = vksc_vkrenderpass;
	vkrenderpassbegininfo.renderArea.extent = vksc_vkextent2d;

	vkviewport.width = vksc_vkextent2d.width;
	vkviewport.height = vksc_vkextent2d.height;

	vkrect2d.extent = vksc_vkextent2d;

	//e0-draw

	// //s0-mtx
	// NALI_D_INFO("mtx_init %d", mtx_init(m_mtx_t_draw_p, mtx_plain))
	// //e0-mtx

	// // frame_start = time(0);
	// clock_gettime(CLOCK_MONOTONIC, &frame_start);
}

void freeCmdDraw()
{
	NALI_D_INFO("vkQueueWaitIdle %d", vkQueueWaitIdle(vkqueue_graphic))

	for (uint8_t l_0 = 0; l_0 < vksc_image; ++l_0)
	{
		vkFreeCommandBuffers(vkdevice, vkcbcp_vkcommandpool_p[vk_device][vk_queue_g], 1, vkcommandbuffer_p + l_0);

		vkDestroyFence(vkdevice, vkfence_p[l_0], VK_NULL_HANDLE);

		for (uint8_t l_1 = 0; l_1 < 2; ++l_1)
		{
			vkDestroySemaphore(vkdevice, vksemaphore_p[l_0][l_1], VK_NULL_HANDLE);
		}
		free(vksemaphore_p[l_0]);
	}
	vkDestroyPipeline(vkdevice, vkpipeline, VK_NULL_HANDLE);
	vkDestroyPipelineLayout(vkdevice, vkpipelinelayout, VK_NULL_HANDLE);

	free(vkcommandbuffer_p);
	free(vkfence_p);
	free(vksemaphore_p);

	vk_free();

	lc_freeloop();

	// free(vk_cmd_d_fp);
	// mtx_destroy(m_mtx_t_draw_p);
}

// static void c1j1()
// {
// }

// static void c1j0()
// {
// }

// static void (*a_fp[NALI_LCS_A_BL])() = {c1j1, c1j0};
static uint8_t vk_cmd_draw_f = 0;
#ifdef C_NALI_S_ANDROID
	int vk_cmd_draw_loop(void *p)
#else
	void vk_cmd_draw_loop()
#endif
{
	lb_free0();
//	//wait wayland ready
//	//still random wayland crash on startup
//	#ifndef C_NALI_S_ANDROID
//		vkDeviceWaitIdle(vkdevice);
//		//NALI_D_LOG("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 10, .tv_nsec = 0}, NULL))
//		//vk_freeSurface();
//		//NALI_D_LOG("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 10, .tv_nsec = 0}, NULL))
//		//vk_makeSurface();
//	#endif

	//!test model
	//s0-test
	//include gui
	//!need test loop data
	//write data
	#define NALI_TEST_map_p ebpomi2_map_p
	#define NALI_TEST_mab NALI_EBPOMI2_MAB
	#define NALI_TEST_m NALI_EBPOMI2_M
	VkWriteDescriptorSet vkwritedescriptorset_p[NALI_LCS_D_SIZE];
	VkDescriptorBufferInfo vkdescriptorbufferinfo_p[NALI_LCS_D_SIZE];
	lcs_s_bl = NALI_TEST_map_p[0] - 1;
	lcs_s_p = realloc(lcs_s_p, sizeof(lcs_s) * NALI_TEST_map_p[0]);

	VkDescriptorSet vkdescriptorset;
	vkds_make(vk_device, lcs_vkdescriptorpool, &lcs_vkdescriptorsetlayout, 1, &vkdescriptorset);
	lcs_setVkWriteDescriptorSet
	(
		vkdescriptorset,
		vkdescriptorbufferinfo_p,
		vkwritedescriptorset_p,
		0,
		NALI_TEST_m < lcp_joint_count_bl ? NALI_TEST_m : 0,
		NALI_TEST_m >= lcp_joint_count_bl ? 1 : lcp_joint_count_p[NALI_TEST_m]//mj
	);
	vkUpdateDescriptorSets(vkdevice, NALI_LCS_D_SIZE, vkwritedescriptorset_p, 0, VK_NULL_HANDLE);
	lcs___p[0].vkdescriptorset = vkdescriptorset;
	for (uint8_t l_0 = 1; l_0 < NALI_TEST_map_p[0]; ++l_0)
	{
		uint8_t ma = NALI_TEST_map_p[l_0];
		lcs_s_p[l_0 - 1]._ = 0;
		lcs_s_p[l_0 - 1].i = ma;
		lcs___p[l_0 - 1].mab = NALI_TEST_mab;
	}
	//a
	if (NALI_TEST_m < lcp_joint_count_bl)
	{
		VkDeviceSize vkdevicesize = lcp_vkdevicesize_p[lcp_joint_count_bl];
		//apply rgba
		for (uint8_t l_0 = 0; l_0 < 4; ++l_0)
		{
			*(float *)(lc_vkbuffer_p + vkdevicesize + l_0 * sizeof(float)) = 1.0;
		}
		vkdevicesize += 4 * sizeof(float);
		//apply default a
		memcpy(lc_vkbuffer_p + vkdevicesize, lcp_a_p[NALI_TEST_m], lcp_joint_count_p[NALI_TEST_m] * 4 * 3 * sizeof(float));
		//apply a 0
		uint8_t l_kf_a = 0;
		uint8_t key = 10;//1
		lckf l_lckf = lckf_p[l_kf_a][key];
		for (uint8_t l_0 = 0; l_0 < l_lckf.bone_bl; ++l_0)
		{
			memcpy(lc_vkbuffer_p + vkdevicesize + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3, l_lckf.s_p[l_0], sizeof(float) * 3);
			memcpy(lc_vkbuffer_p + vkdevicesize + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4, l_lckf.r_p[l_0], sizeof(float) * 4);
			memcpy(lc_vkbuffer_p + vkdevicesize + l_lckf.bone_p[l_0] * sizeof(float) * 4 * 3 + sizeof(float) * 4 * 2, l_lckf.t_p[l_0], sizeof(float) * 3);
		}
		//mv4_q(NALI_M_D2R(45), 0, 0, lc_vkbuffer_p + vkdevicesize + sizeof(float) * 4 + 1 * sizeof(float) * 4 * 3);
//		//apply s to mid
//		*(float *)(lc_vkbuffer_p + vkdevicesize + sizeof(float) * 4 * 3 * 12) = 0;
//		*(float *)(lc_vkbuffer_p + vkdevicesize + sizeof(float) * 4 * 3 * 12 + 1 * sizeof(float)) = 0;
//		*(float *)(lc_vkbuffer_p + vkdevicesize + sizeof(float) * 4 * 3 * 12 + 2 * sizeof(float)) = 0;
//		//apply s to tail
//		*(float *)(lc_vkbuffer_p + vkdevicesize + sizeof(float) * 4 * 3 * 2) = 0;
//		*(float *)(lc_vkbuffer_p + vkdevicesize + sizeof(float) * 4 * 3 * 2 + 1 * sizeof(float)) = 0;
//		*(float *)(lc_vkbuffer_p + vkdevicesize + sizeof(float) * 4 * 3 * 2 + 2 * sizeof(float)) = 0;
		//apply r to top
		//mv4_q(0, NALI_M_D2R(-45), 0, lc_vkbuffer_p + vkdevicesize + sizeof(float) * 4 + 31 * sizeof(float) * 4 * 3);
		//apply r
		mv4_q(0, NALI_M_D2R(-45), NALI_M_D2R(-180), lc_vkbuffer_p + vkdevicesize + sizeof(float) * 4);
		//apply t
		//*(float *)(lc_vkbuffer_p + vkdevicesize + sizeof(float) * 4 * 2 + 0 * sizeof(float)) = 1.0;
		//*(float *)(lc_vkbuffer_p + vkdevicesize + sizeof(float) * 4 * 2 + 1 * sizeof(float)) = -1.0;
		*(float *)(lc_vkbuffer_p + vkdevicesize + sizeof(float) * 4 * 2 + 2 * sizeof(float)) = -3.0;
	}
	//update m v p later
	//update buffer
	//!use atom to all flush
	vkFlushMappedMemoryRanges(vkqd_vkdevice_p[vk_device], 1, &(VkMappedMemoryRange)
	{
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = lc_vkdevicememory,
		.offset = (lcp_vkdevicesize_p[lcp_joint_count_bl] / vk_non_coherent_atom_size) * vk_non_coherent_atom_size,
		.size = ((4 * sizeof(float) + lcp_joint_count_p[NALI_TEST_m] * 4 * 3) * sizeof(float) + (vk_non_coherent_atom_size - 1)) & ~(vk_non_coherent_atom_size - 1),
		.pNext = VK_NULL_HANDLE
	});
	//e0-test
	while (!(s_state & NALI_S_S_CLEAN))
	{
		vkWaitForFences(vkdevice, 1, vkfence_p + vk_cmd_draw_f, VK_TRUE, UINT64_MAX);
		vkResetFences(vkdevice, 1, &vkfence_p[vk_cmd_draw_f]);

		image_vksubmitinfo.pCommandBuffers = &vkcommandbuffer_p[vk_cmd_draw_f];

		image_vksubmitinfo.pWaitSemaphores = vksemaphore_p[vk_cmd_draw_f];
		image_vksubmitinfo.pSignalSemaphores = vksemaphore_p[vk_cmd_draw_f] + 1;

		vkpresentinfokhr.pWaitSemaphores = vksemaphore_p[vk_cmd_draw_f] + 1;

		//p. u m dat
		//!read data
//		nc_send();
//
//		// clock_gettime(CLOCK_MONOTONIC, &delta_end);
//		// lc_delta = delta_end.tv_sec + (double)delta_end.tv_nsec / 1e9 - delta_start.tv_sec - (double)delta_start.tv_nsec / 1e9;
//		// // ry += M_MIN(0.5F * (delta_end.tv_sec + delta_end.tv_nsec / 1e9 - delta_start.tv_sec - delta_start.tv_nsec / 1e9), 1.0F);
//		// delta_start = delta_end;
//
//		// for (uint8_t l_0 = 0; l_0 < vk_cmd_d_fp_bl; ++l_0)
//		// {
//		// 	//model add/update
//		// 	vk_cmd_d_fp[l_0]();
//		// }
//
//		nc_get();
//		lcu_update();
//		lcm_update();
//		// lcs_loop();

		if (s_state & NALI_S_S_RE)
		{
			vkQueueWaitIdle(vkqueue_graphic);

			//!re-create wl if crash before vk_sc
			//wait like 1 sec to detect wl crash
			//but need check data first
			vksc_free();

			#ifdef C_NALI_S_ANDROID
				sa_wait();
			#endif

			vksc_make(vkq_max_queue_surface_p[vk_device] == 1 ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT);

			vkrenderpassbegininfo.renderPass = vksc_vkrenderpass;
			vkviewport.width = vksc_vkextent2d.width;
			vkviewport.height = vksc_vkextent2d.height;
			vkrenderpassbegininfo.renderArea.extent = vksc_vkextent2d;
			vkrect2d.extent = vksc_vkextent2d;

			MM4X4_P(tanf(90.0F * (M_PI / 180.0F) / 2.0F), s_width / s_height, 0.1F, 100.0F, (float *)lc_vkbuffer_p + 16 * 3)
//			if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR || m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
//			{
//				rz = 0.0F;
//			}
//			else
//			{
//				rz = 180.0F;
//			}
			vkFlushMappedMemoryRanges(vkqd_vkdevice_p[vk_device], 1, &(VkMappedMemoryRange)
			{
				.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
				.memory = lc_vkdevicememory,
				.offset = 16 * 3 * sizeof(float),
				.size = 16 * sizeof(float),
				.pNext = VK_NULL_HANDLE
			});
			s_state &= 0xFFu - NALI_S_S_RE;
		}

		uint32_t image_index;
		VkResult vkresult = vkAcquireNextImageKHR(vkdevice, vksc_vkswapchainkhr, UINT64_MAX, vksemaphore_p[vk_cmd_draw_f][0], VK_NULL_HANDLE, &image_index);
		if (vkresult != VK_SUCCESS)
		{
			//support recreate vkswapchainkhr if need
			NALI_D_LOG("vkAcquireNextImageKHR %d", vkresult)
		}

		vkrenderpassbegininfo.framebuffer = vksc_vkswapchainkhr_vkframebuffer_p[image_index];
		vkpresentinfokhr.pImageIndices = &image_index;

		vkBeginCommandBuffer(vkcommandbuffer_p[vk_cmd_draw_f], &vkcommandbufferbegininfo);

			vkCmdBeginRenderPass(vkcommandbuffer_p[vk_cmd_draw_f], &vkrenderpassbegininfo, VK_SUBPASS_CONTENTS_INLINE);

				vkCmdBindPipeline(vkcommandbuffer_p[vk_cmd_draw_f], VK_PIPELINE_BIND_POINT_GRAPHICS, vkpipeline);

				//s0-VkDynamicState
				// if (update)
				// {
				vkCmdSetViewport(vkcommandbuffer_p[vk_cmd_draw_f], 0, 1, &vkviewport);
				vkCmdSetScissor(vkcommandbuffer_p[vk_cmd_draw_f], 0, 1, &vkrect2d);
				// 	update = 0;
				// }
				//e0-VkDynamicState

				// // mtx_lock(m_mtx_t_draw_p);

				// for (uint8_t l_0 = 0; l_0 < NALI_LCS_A_BL; ++l_0)
				// {
				// 	vkCmdBindVertexBuffers(vkcommandbuffer_p[vk_cmd_draw_f], 0, 1, &lc_vkbuffer, lcs_a_vkdevicesize_p + l_0);

				// 	// a_fp[l_0]();
				// 	// for (uint8_t l_1 = 0; l_1 < lcm_joint_count_bl; ++l_1)
				// 	for (NALI_LCS_DSIT l_1 = 0; l_1 < lcs_a_bl_p[l_0]; ++l_1)
				// 	{
				// 		// vkCmdBindDescriptorSets(vkcommandbuffer_p[vk_cmd_draw_f], VK_PIPELINE_BIND_POINT_GRAPHICS, vkpipelinelayout, 0, 1, lcs_vkdescriptorset_p + l_1, 0, VK_NULL_HANDLE);
				// 		vkCmdBindDescriptorSets(vkcommandbuffer_p[vk_cmd_draw_f], VK_PIPELINE_BIND_POINT_GRAPHICS, vkpipelinelayout, 0, 1, &lcs___p[lcs__i_p[l_0][l_1]].vkdescriptorset, 0, VK_NULL_HANDLE);

				// 		//mix all to one to use address
				// 		for (NALI_LCS_AIT l_2 = 1; l_2 < lcs___p[lcs__i_p[l_0][l_1]].a_p[0]; ++l_2)
				// 		{
				// 			vkCmdBindIndexBuffer(vkcommandbuffer_p[vk_cmd_draw_f], lc_vkbuffer, lcs_i_p[lcs___p[lcs__i_p[l_0][l_1]].a_p[l_2]], VK_INDEX_TYPE_UINT32);
				// 			vkCmdDrawIndexed(vkcommandbuffer_p[vk_cmd_draw_f], lcs_ic_p[lcs___p[lcs__i_p[l_0][l_1]].a_p[l_2]], 1, 0, 0, 0);
				// 		}
				// 	}
				// }

				for (NALI_LCS_DSIT l_0 = 0; l_0 < lcs_s_bl; ++l_0)
				{
					lcs__ _ = lcs___p[lcs_s_p[l_0]._];
					vkCmdBindDescriptorSets(vkcommandbuffer_p[vk_cmd_draw_f], VK_PIPELINE_BIND_POINT_GRAPHICS, vkpipelinelayout, 0, 1, &_.vkdescriptorset, 0, VK_NULL_HANDLE);
					vkCmdBindVertexBuffers(vkcommandbuffer_p[vk_cmd_draw_f], 0, 1, &lc_vkbuffer, lcs_a_vkdevicesize_p + _.mab);

					vkCmdBindIndexBuffer(vkcommandbuffer_p[vk_cmd_draw_f], lc_vkbuffer, lcs_ib_p[lcs_s_p[l_0].i], VK_INDEX_TYPE_UINT32);
					vkCmdDrawIndexed(vkcommandbuffer_p[vk_cmd_draw_f], lcs_ic_p[lcs_s_p[l_0].i], 1, 0, 0, 0);
				}

			vkCmdEndRenderPass(vkcommandbuffer_p[vk_cmd_draw_f]);

		vkEndCommandBuffer(vkcommandbuffer_p[vk_cmd_draw_f]);

		vkQueueSubmit(vkqueue_graphic, 1, &image_vksubmitinfo, vkfence_p[vk_cmd_draw_f]);
		vkQueuePresentKHR(vkqueue_graphic, &vkpresentinfokhr);

		++frame;
		// frame_end = time(0);
		// frame_time = frame_end - frame_start;
		clock_gettime(CLOCK_MONOTONIC, &frame_end);
		frame_time = frame_end.tv_sec + (double)frame_end.tv_nsec / 1e9 - frame_start.tv_sec - (double)frame_start.tv_nsec / 1e9;
		// if (frame_time > 0)
		// if (frame == 144)
		if (frame_time >= 1.0)
		{
			// end = clock();
			// cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			frame_start = frame_end;
			// NALI_D_LOG("time %ld", frame_time)
			NALI_D_LOG("time %f", frame_time)
			NALI_D_LOG("frame %d", frame)
			frame = 0;
		}

		vk_cmd_draw_f = (vk_cmd_draw_f + 1) % vksc_image;
//		#ifdef C_NALI_S_ANDROID
//			sa_wait();
//		#endif
	}

//	#ifdef C_NALI_S_ANDROID
//		m_surface_state &= 0xFFu - NALI_S_S_CLEAN;
//	#else
	freeCmdDraw();
	#ifdef C_NALI_S_ANDROID
		return 0;
	#endif
//	#endif
}
