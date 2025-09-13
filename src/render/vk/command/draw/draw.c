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

static VkCommandBuffer *Pvkcommandbuffer;
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
static VkFence *Pvkfence;
//image render
//[smpt_rd_vk_swcUimage][2]
static VkSemaphore **Pvksemaphore;

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
	.pSwapchains = &smpt_rd_vk_swcVkhr,

	.pResults = VK_NULL_HANDLE,
	.pNext = VK_NULL_HANDLE
};
//e1-queue
//e0-draw

void smpt_rd_vk_cmdMset()
{
	// vk_cmd_d_fp = malloc(0);

	//s0-share
	vkdevice = smpt_rd_vkq_dvP[smpt_rd_vkUdevice];
	vkqueue_graphic = smpt_rd_vkqP[smpt_rd_vkUdevice][smpt_rd_vkUqueue_g];
	//e0-share

	//s0-s
	VkShaderModule vkshadermodule_vert;
	VkShaderModule vkshadermodule_frag;
	VkPipelineShaderStageCreateInfo vkpipelineshaderstagecreateinfo_array[2];

	// const char shader_type[] = ".spv";

	// const char vert_shader_path[] = SMPTFcHOME SMPTFcHOME_SHADER SMPTFcHOME_SHADER_VERT "/";
	// uint32_t vert_index = 0;
	// uint8_t vert_name_index = sizeof(vert_shader_path)-1;
	// char *vert_file = malloc(vert_name_index + M_LENGTH(vert_index) + sizeof(shader_type)-1 + 1);
	// strcpy(vert_file, vert_shader_path);
	// sprintf(vert_file + vert_name_index, "%u", vert_index);
	// strcat(vert_file, shader_type);

	// const char frag_shader_path[] = SMPTFcHOME SMPTFcHOME_SHADER SMPTFcHOME_SHADER_FRAG "/";
	// uint32_t frag_index = 0;
	// uint8_t frag_name_index = sizeof(frag_shader_path)-1;
	// char *frag_file = malloc(frag_name_index + M_LENGTH(frag_index) + sizeof(shader_type)-1 + 1);
	// strcpy(frag_file, frag_shader_path);
	// sprintf(frag_file + frag_name_index, "%u", frag_index);
	// strcat(frag_file, shader_type);

	// smpt_rd_vk_pl_sdMset(smpt_rd_vkUdevice, vert_file, frag_file, &vkshadermodule_vert, &vkshadermodule_frag, vkpipelineshaderstagecreateinfo_array);
	// smpt_rd_vk_pl_sdMset(smpt_rd_vkUdevice, SMPTFcHOME SMPTFcHOME_SHADER "vert.spv", SMPTFcHOME SMPTFcHOME_SHADER "frag.spv", &vkshadermodule_vert, &vkshadermodule_frag, vkpipelineshaderstagecreateinfo_array);
	smpt_rd_vk_pl_sdMset(smpt_rd_vkUdevice, SMPTFcHOME_VERT, SMPTFcHOME_FRAG, &vkshadermodule_vert, &vkshadermodule_frag, vkpipelineshaderstagecreateinfo_array);
	// free(vert_file);
	// free(frag_file);

	//s1-s
	smpt_rd_vk_pl_loMmake(smpt_rd_vkUdevice, &vkpipelinelayout);
	smpt_rd_vk_plMmake(smpt_rd_vkUdevice, vkpipelineshaderstagecreateinfo_array, smpt_rd_vk_swcVrdp, vkpipelinelayout, &vkpipeline);
	//e1-s

	vkDestroyShaderModule(vkdevice, vkshadermodule_frag, VK_NULL_HANDLE);
	vkDestroyShaderModule(vkdevice, vkshadermodule_vert, VK_NULL_HANDLE);
	//e0-s

	//s0-draw
	Pvkcommandbuffer = malloc(sizeof(VkCommandBuffer) * smpt_rd_vk_swcUimage);
	Pvkfence = malloc(sizeof(VkFence) * smpt_rd_vk_swcUimage);
	Pvksemaphore = malloc(sizeof(VkSemaphore *) * smpt_rd_vk_swcUimage);
	for (uint8_t l_0 = 0; l_0 < smpt_rd_vk_swcUimage; ++l_0)
	{
		//s0-cmd
		smpt_rd_vk_cm_bfMmake(smpt_rd_vkUdevice, smpt_rd_vkUqueue_g, Pvkcommandbuffer + l_0, 1);
		//e0-cmd

		//! need check again
		//vk_cmd(Pvkcommandbuffer[l_0], &vkcommandbufferbegininfo, vkqueue_graphic);
		// //s0-ubo
		// // smptr_ceMsetVkWriteDescriptorSet(vkdescriptorset, &vkdescriptorbufferinfo, &vkdescriptorimageinfo, vkwritedescriptorset_array);
		// smptr_ceMsetVkWriteDescriptorSet(vkdescriptorset, &vkdescriptorbufferinfo, vkwritedescriptorset_array);
		// //s1-update
		// vkUpdateDescriptorSets(vkdevice, 6, vkwritedescriptorset_array, 0, VK_NULL_HANDLE);
		// //e1-update
		// //e0-ubo

		SMPT_RD_VKFmMAKE(smpt_rd_vkUdevice, Pvkfence + l_0)

		Pvksemaphore[l_0] = malloc(sizeof(VkSemaphore) * 2);
		for (uint8_t l_1 = 0; l_1 < 2; ++l_1)
		{
			SMPT_RD_VK_SMPmMAKE(smpt_rd_vkUdevice, Pvksemaphore[l_0] + l_1)
		}
	}

	vkrenderpassbegininfo.renderPass = smpt_rd_vk_swcVrdp;
	vkrenderpassbegininfo.renderArea.extent = smpt_rd_vk_swcVet2d;

	vkviewport.width = smpt_rd_vk_swcVet2d.width;
	vkviewport.height = smpt_rd_vk_swcVet2d.height;

	vkrect2d.extent = smpt_rd_vk_swcVet2d;

	//e0-draw

	// //s0-mtx
	// SMPT_DBmR2L("mtx_init %d", mtx_init(m_mtx_t_draw_p, mtx_plain))
	// //e0-mtx

	// // frame_start = time(0);
	// clock_gettime(CLOCK_MONOTONIC, &frame_start);
}

static void re_sc()
{
	vkQueueWaitIdle(vkqueue_graphic);

	//! re-create wl if crash before vk_sc
	//wait like 1 sec to detect wl crash
//			#ifndef SMPT_CM_ST_ANDROID
//				if ()
//				{
//					vkDeviceWaitIdle(vkdevice);
//					smpt_rd_vk_sfMfree();
//					smpt_rd_vk_sfMmake();
//				}
//			#endif
	smpt_rd_vk_swcMfree();

	#ifdef SMPT_CM_ST_ANDROID
		sa_wait();
	#endif

	smpt_rd_vk_swcMmake(smpt_rd_vkqPmax_queue_surface[smpt_rd_vkUdevice] == 1 ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT);

	vkrenderpassbegininfo.renderPass = smpt_rd_vk_swcVrdp;
	vkviewport.width = smpt_rd_vk_swcVet2d.width;
	vkviewport.height = smpt_rd_vk_swcVet2d.height;
	vkrenderpassbegininfo.renderArea.extent = smpt_rd_vk_swcVet2d;
	vkrect2d.extent = smpt_rd_vk_swcVet2d;

	for (uint8_t l0 = 0; l0 < smpt_rd_vk_swcUimage; ++l0)
	{
		SMPTM_M4X4mP(tanf(90.0F * (M_PI / 180.0F) / 2.0F), smpt_sfUwidth / smpt_sfUheight, 0.1F, 100.0F, (float *)(smptr_ce_mdPbuffer_map[1 + 1 * smpt_rd_vk_swcUimage + l0] + sizeof(float) * 16))
	}
//			if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR || m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
//			{
//				rz = 0.0F;
//			}
//			else
//			{
//				rz = 180.0F;
//			}
	vkFlushMappedMemoryRanges(smpt_rd_vkq_dvP[smpt_rd_vkUdevice], 1, &(VkMappedMemoryRange)
	{
		.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
		.memory = smptr_ce_mdPvkdevicememory[2],
		.offset = sizeof(float) * 16,
		.size = sizeof(float) * 16,
		.pNext = VK_NULL_HANDLE
	});
	smpt_sfUstate &= 0xFFu - SMPT_SFuS_RE;
}

int smpt_rd_vk_cmdMloop(void *P)
{
	smptrMfree0();

	smpt_sfUstate |= SMPT_SFuS_RENDER;
	while (!(smpt_sfUstate & SMPT_SFuS_EXIT))
	{
		smpt_rd_vk_swcUframe_buffer = (smpt_rd_vk_swcUframe_buffer + 1) % smpt_rd_vk_swcUimage;

		#ifdef SMPT_CM_UDP
			smpt_nw_udp_ceMread();
		#endif
		smptr_ceMloop();
		#ifdef SMPT_CM_UDP
			smpt_nw_udp_ceMsend();
		#endif

		vkWaitForFences(vkdevice, 1, Pvkfence + smpt_rd_vk_swcUframe, VK_TRUE, UINT64_MAX);
		vkResetFences(vkdevice, 1, &Pvkfence[smpt_rd_vk_swcUframe]);

		image_vksubmitinfo.pCommandBuffers = &Pvkcommandbuffer[smpt_rd_vk_swcUframe];

		image_vksubmitinfo.pWaitSemaphores = Pvksemaphore[smpt_rd_vk_swcUframe];
		image_vksubmitinfo.pSignalSemaphores = Pvksemaphore[smpt_rd_vk_swcUframe] + 1;

		vkpresentinfokhr.pWaitSemaphores = Pvksemaphore[smpt_rd_vk_swcUframe] + 1;

		if (smpt_sfUstate & SMPT_SFuS_RE)
		{
			re_sc();
		}

		uint32_t image_index;
		VkResult vkresult = vkAcquireNextImageKHR(vkdevice, smpt_rd_vk_swcVkhr, UINT64_MAX, Pvksemaphore[smpt_rd_vk_swcUframe][0], VK_NULL_HANDLE, &image_index);
		if (vkresult != VK_SUCCESS)
		{
			//support recreate vkswapchainkhr if need
			SMPT_DBmN2L("vkAcquireNextImageKHR %d", vkresult)
			re_sc();
		}

		vkrenderpassbegininfo.framebuffer = smpt_rd_vk_swcPfbf[image_index];
		vkpresentinfokhr.pImageIndices = &image_index;

		vkBeginCommandBuffer(Pvkcommandbuffer[smpt_rd_vk_swcUframe], &vkcommandbufferbegininfo);

			vkCmdBeginRenderPass(Pvkcommandbuffer[smpt_rd_vk_swcUframe], &vkrenderpassbegininfo, VK_SUBPASS_CONTENTS_INLINE);

				vkCmdBindPipeline(Pvkcommandbuffer[smpt_rd_vk_swcUframe], VK_PIPELINE_BIND_POINT_GRAPHICS, vkpipeline);

				//s0-VkDynamicState
				// if (update)
				// {
				vkCmdSetViewport(Pvkcommandbuffer[smpt_rd_vk_swcUframe], 0, 1, &vkviewport);
				vkCmdSetScissor(Pvkcommandbuffer[smpt_rd_vk_swcUframe], 0, 1, &vkrect2d);
				// 	update = 0;
				// }
				//e0-VkDynamicState

//				SMPT_DBmN2L("smptr_cemLm1 %d", smptr_cemLm1)
				for (uint32_t l_0 = 0; l_0 < smptr_cemLm1; ++l_0)
				{
					struct SMPTR_CEMsM1 m1 = smptr_cemPm1[l_0];
					SMPTRtMA a = m1.Ua;
//					SMPT_DBmN2L("m1.Ui * smpt_rd_vk_swcUimage %d", m1.Ui * smpt_rd_vk_swcUimage)
//					SMPT_DBmN2L("m1.Ui %d", m1.Ui)
//					SMPT_DBmN2L("smpt_rd_vk_swcUframe_buffer %d", smpt_rd_vk_swcUframe_buffer)
//					SMPT_DBmN2L("smptr_cemPvkdescriptorset + m1.Ui * smpt_rd_vk_swcUimage + smpt_rd_vk_swcUframe_buffer %p", smptr_cemPvkdescriptorset + m1.Ui * smpt_rd_vk_swcUimage + smpt_rd_vk_swcUframe_buffer)
					vkCmdBindDescriptorSets(Pvkcommandbuffer[smpt_rd_vk_swcUframe], VK_PIPELINE_BIND_POINT_GRAPHICS, vkpipelinelayout, 0, 1, smptr_cemPvkdescriptorset + m1.Ui * smpt_rd_vk_swcUimage + smpt_rd_vk_swcUframe_buffer, 0, VK_NULL_HANDLE);
					//! use lcv_vkbuffer
					vkCmdBindVertexBuffers(Pvkcommandbuffer[smpt_rd_vk_swcUframe], 0, 1, &smptr_ce_mdPvkbuffer[0], r_cep_a_p + m1.Ub);

					//! use lcv_vkbuffer
					vkCmdBindIndexBuffer(Pvkcommandbuffer[smpt_rd_vk_swcUframe], smptr_ce_mdPvkbuffer[0], r_cep_ai_p[a], VK_INDEX_TYPE_UINT32);
					vkCmdDrawIndexed(Pvkcommandbuffer[smpt_rd_vk_swcUframe], r_cep_ai_l_p[a], 1, 0, 0, 0);
				}

			vkCmdEndRenderPass(Pvkcommandbuffer[smpt_rd_vk_swcUframe]);

		vkEndCommandBuffer(Pvkcommandbuffer[smpt_rd_vk_swcUframe]);

		vkQueueSubmit(vkqueue_graphic, 1, &image_vksubmitinfo, Pvkfence[smpt_rd_vk_swcUframe]);
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
			// SMPT_DBmN2L("time %ld", frame_time)
			SMPT_DBmN2L("time %f", frame_time)
			SMPT_DBmN2L("frame %d", frame)
			frame = 0;
		}

		smpt_rd_vk_swcUframe = (smpt_rd_vk_swcUframe + 1) % smpt_rd_vk_swcUimage;
	}
	smpt_sfUstate |= SMPT_SFuS_EXIT_RENDER;

	return 0;
}

void smpt_rd_vk_cmdMfree()
{
	for (uint8_t l_0 = 0; l_0 < smpt_rd_vk_swcUimage; ++l_0)
	{
		vkFreeCommandBuffers(vkdevice, smpt_rd_vk_cmpP[smpt_rd_vkUdevice][smpt_rd_vkUqueue_g], 1, Pvkcommandbuffer + l_0);

		vkDestroyFence(vkdevice, Pvkfence[l_0], VK_NULL_HANDLE);

		for (uint8_t l_1 = 0; l_1 < 2; ++l_1)
		{
			vkDestroySemaphore(vkdevice, Pvksemaphore[l_0][l_1], VK_NULL_HANDLE);
		}
		free(Pvksemaphore[l_0]);
	}
	vkDestroyPipeline(vkdevice, vkpipeline, VK_NULL_HANDLE);
	vkDestroyPipelineLayout(vkdevice, vkpipelinelayout, VK_NULL_HANDLE);

	free(Pvkcommandbuffer);
	free(Pvkfence);
	free(Pvksemaphore);

	smpt_rd_vkMfree();

	// free(vk_cmd_d_fp);
	// mtx_destroy(m_mtx_t_draw_p);
}
