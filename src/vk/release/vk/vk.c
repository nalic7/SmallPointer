float m_limits_max_sampler_anisotropy;

uint32_t m_device = 0;
uint32_t m_queue_g = 0;
uint32_t m_queue_ct = 0;

// enum render_state_enum
// {
// 	RSE_MULTIPLE_QUEUE = 1
// };

static void clean()
{
	lc_clearVK(m_device);

	vk_freeCommandPool();

	vk_freeSwapchain();

	vk_freeQueue();
	vk_freeDevice();
	vk_freePhysicalDevice();

	#ifdef NALI_VK_DEBUG
		vk_freeDebug();
	#endif
	vk_freeSurface();
	vk_freeInstance();
}

int vk_loop(void *arg)
{
	//use only graphic
	// m_queue_graphic = 0;
	// m_queue_render = 0;

	VkFence m_vkfence_array[2];
	// VkSemaphore m_vksemaphore_array[3];
	VkSemaphore m_vksemaphore_array[2];

	for (uint8_t i = 0; i < 2; ++i)
	{
		vk_makeFence(m_device, &m_vkfence_array[i]);
		vk_makeSemaphore(m_device, &m_vksemaphore_array[i]);
	}
	// vk_makeSemaphore(m_device, &m_vksemaphore_array[2]);

	clock_t frame_start, frame_end;
	uint32_t frame;
	clock_t frame_time;

	//clock
	frame_start = time(0);

	VkDevice vkdevice = m_vkdevice_p[m_device];
	VkFence *graphic_vkfence_p = &m_vkfence_array[0];
	VkFence *transfer_vkfence_p = &m_vkfence_array[1];

	VkQueue vkqueue_graphic = m_vkqueue_p[m_device][m_queue_g];
	// VkQueue vkqueue_render = m_vkqueue_p[m_device][m_queue_ct];

	// char render_state = m_queue_g == m_queue_ct ? 0 : RSE_MULTIPLE_QUEUE;
	VkSemaphore image_vksemaphore = m_vksemaphore_array[0];
	VkSemaphore render_vksemaphore = m_vksemaphore_array[1];
	// VkSemaphore render_transfer_vksemaphore = m_vksemaphore_array[2];
	// VkSemaphore *render_vksemaphore_p = (render_state & RSE_MULTIPLE_QUEUE) == 0 ? &render_vksemaphore : &render_transfer_vksemaphore;

	// VkSubmitInfo render_vksubmitinfo;
	// VkPipelineStageFlags render_vkpipelinestageflags_array[] = {VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT};
	// if (render_state & RSE_MULTIPLE_QUEUE)
	// {
	// 	render_vksubmitinfo = (VkSubmitInfo)
	// 	{
	// 		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
	// 		.waitSemaphoreCount = 1,
	// 		.pWaitSemaphores = &render_transfer_vksemaphore,
	// 		.pWaitDstStageMask = render_vkpipelinestageflags_array,
	// 		.commandBufferCount = 0,
	// 		.signalSemaphoreCount = 1,
	// 		.pSignalSemaphores = &render_vksemaphore,

	// 		.pNext = VK_NULL_HANDLE
	// 	};
	// }

	//s0-u
	VkDescriptorPoolSize vkdescriptorpoolsize[2];
	lc_setVkDescriptorPoolSize(vkdescriptorpoolsize);

	VkDescriptorPool vkdescriptorpool;
	vk_makeDescriptorSetPool(m_device, vkdescriptorpoolsize, 2, &vkdescriptorpool);

	VkDescriptorSetLayout vkdescriptorsetlayout;
	lc_setVkDescriptorSetLayout(&vkdescriptorsetlayout);

	VkDescriptorSet vkdescriptorset;
	vk_makeDescriptorSet(m_device, vkdescriptorpool, &vkdescriptorsetlayout, 1, &vkdescriptorset);
	//e0-u

	//s0-s
	VkShaderModule vkshadermodule_vert;
	VkShaderModule vkshadermodule_frag;
	VkPipelineShaderStageCreateInfo vkpipelineshaderstagecreateinfo_array[2];

	const char shader_type[] = ".spv";

	const char vert_shader_path[] = NALI_HOME NALI_HOME_SHADER NALI_HOME_SHADER_VERT "/";
	uint32_t vert_index = 0;
	uint8_t vert_name_index = sizeof(vert_shader_path)-1;
	char *vert_file = malloc(vert_name_index + math_length(vert_index) + sizeof(shader_type)-1 + 1);
	strcpy(vert_file, vert_shader_path);
	sprintf(vert_file + vert_name_index, "%u", vert_index);
	strcat(vert_file, shader_type);

	const char frag_shader_path[] = NALI_HOME NALI_HOME_SHADER NALI_HOME_SHADER_FRAG "/";
	uint32_t frag_index = 0;
	uint8_t frag_name_index = sizeof(frag_shader_path)-1;
	char *frag_file = malloc(frag_name_index + math_length(frag_index) + sizeof(shader_type)-1 + 1);
	strcpy(frag_file, frag_shader_path);
	sprintf(frag_file + frag_name_index, "%u", frag_index);
	strcat(frag_file, shader_type);

	vk_setVkPipelineShaderStageCreateInfo(m_device, vert_file, frag_file, &vkshadermodule_vert, &vkshadermodule_frag, vkpipelineshaderstagecreateinfo_array);
	free(vert_file);
	free(frag_file);

	//s1-s
	VkPipelineLayout vkpipelinelayout;
	vk_makePipelineLayout(m_device, &vkdescriptorsetlayout, 1, &vkpipelinelayout);

	VkPipeline vkpipeline;
	vk_makeGraphicsPipeline(m_device, vkpipelineshaderstagecreateinfo_array, &m_vkrenderpass, &vkpipelinelayout, &vkpipeline);
	//e1-s

	vkDestroyShaderModule(vkdevice, vkshadermodule_frag, VK_NULL_HANDLE);
	vkDestroyShaderModule(vkdevice, vkshadermodule_vert, VK_NULL_HANDLE);
	//e0-s

	VkCommandBuffer vkcommandbuffer;
	vk_makeCommandBuffer(m_device, m_queue_g, &vkcommandbuffer, 1);

	VkSubmitInfo image_vksubmitinfo =
	{
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &image_vksemaphore,
		.pWaitDstStageMask = (VkPipelineStageFlags[]){VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT},
		.commandBufferCount = 1,
		.pCommandBuffers = &vkcommandbuffer,
		.signalSemaphoreCount = 1,
		// .pSignalSemaphores = render_vksemaphore_p,
		.pSignalSemaphores = &render_vksemaphore,

		.pNext = VK_NULL_HANDLE
	};

	VkCommandBufferBeginInfo vkcommandbufferbegininfo =
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pInheritanceInfo = VK_NULL_HANDLE,

		.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
		// .flags = 0,
		.pNext = VK_NULL_HANDLE
	};

	VkPresentInfoKHR vkpresentinfokhr =
	{
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &render_vksemaphore,

		.swapchainCount = 1,
		.pSwapchains = &m_vkswapchainkhr,

		// .pImageIndices = &image_index,

		.pResults = VK_NULL_HANDLE,
		.pNext = VK_NULL_HANDLE
	};

	//s0-buffer
	VkClearColorValue vkclearcolorvalue =
	{
		.float32 = {0.0F, 0.0F, 0.0F, 1.0F}
	};
	VkClearDepthStencilValue vkcleardepthstencilvalue =
	{
		.depth = 1.0F,
		.stencil = 0.0F
	};
	VkClearValue vkclearvalue[2] =
	{
		{.color = vkclearcolorvalue},
		{.depthStencil = vkcleardepthstencilvalue}
	};
	VkRenderPassBeginInfo vkrenderpassbegininfo =
	{
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.renderPass = m_vkrenderpass,
		// .renderPass = m_vkswapchainkhr_vkrenderpass_p[m_device][imageIndex],
		.renderArea.offset = {0, 0},
		.renderArea.extent = m_vkextent2d,
		.clearValueCount = 2,
		.pClearValues = vkclearvalue,

		.pNext = VK_NULL_HANDLE
	};
	//
	VkViewport vkviewport =
	{
		.x = 0.0F,
		.y = 0.0F,
		.width = m_vkextent2d.width,
		.height = m_vkextent2d.height,
		.minDepth = 0.0F,
		.maxDepth = 1.0F
	};
	VkRect2D vkrect2d =
	{
		.offset = {0, 0},
		.extent = m_vkextent2d
	};
	//e0-buffer

	//
	// vkWaitForFences(vkdevice, 1, graphic_vkfence_p, VK_TRUE, UINT64_MAX);
	// vkResetFences(vkdevice, 1, graphic_vkfence_p);

	vk_cmd(vkcommandbuffer, &vkcommandbufferbegininfo, vkqueue_graphic);

	// //s0-check
	// VkImageSubresource vkimagesubresource =
	// {
	// 	.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
	// 	.mipLevel = 0,
	// 	.arrayLayer = 0
	// };
	// VkSubresourceLayout vksubresourcelayout;
	// vkGetImageSubresourceLayout(vkdevice, m_nali_g_image_vkimage_p[0], &vkimagesubresource, &vksubresourcelayout);
	// info("vksubresourcelayout.rowPitch %ld", vksubresourcelayout.rowPitch)
	// info("vksubresourcelayout.depthPitch %ld", vksubresourcelayout.depthPitch)
	// //e0-check

	//s0-ubo
	VkWriteDescriptorSet vkwritedescriptorset_array[2];
	VkDescriptorBufferInfo vkdescriptorbufferinfo;
	VkDescriptorImageInfo vkdescriptorimageinfo;
	lc_setVkWriteDescriptorSet(vkdescriptorset, &vkdescriptorbufferinfo, &vkdescriptorimageinfo, vkwritedescriptorset_array);
	//e0-ubo

	//s0-update
	vkUpdateDescriptorSets(vkdevice, 2, vkwritedescriptorset_array, 0, VK_NULL_HANDLE);
	//e0-update

	while ((m_surface_state & NALI_SURFACE_C_S_CLEAN) == 0)
	{
		vkWaitForFences(vkdevice, 1, graphic_vkfence_p, VK_TRUE, UINT64_MAX);
		vkResetFences(vkdevice, 1, graphic_vkfence_p);

		// if (render_state & RSE_MULTIPLE_QUEUE)
		// {
		// 	vkWaitForFences(vkdevice, 1, transfer_vkfence_p, VK_TRUE, UINT64_MAX);
		// 	vkResetFences(vkdevice, 1, transfer_vkfence_p);
		// }

		if (m_surface_state & NALI_SURFACE_C_S_RE)
		{
			m_surface_state &= 255 - NALI_SURFACE_C_S_RE;
			vk_freeSwapchain();
			vk_makeSwapchain(m_max_queue_surface_p[m_device] == 1 ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT);

			vkrenderpassbegininfo.renderPass = m_vkrenderpass;
			vkviewport.width = m_vkextent2d.width;
			vkviewport.height = m_vkextent2d.height;
			vkrenderpassbegininfo.renderArea.extent = m_vkextent2d;
			vkrect2d.extent = m_vkextent2d;
		}

		uint32_t image_index;
		VkResult vkresult = vkAcquireNextImageKHR(vkdevice, m_vkswapchainkhr, UINT64_MAX, image_vksemaphore, VK_NULL_HANDLE, &image_index);
		// info("image %d", imageIndex)
		// info("vkextent2d.width %d", vkextent2d.width)
		// info("vkextent2d.height %d", vkextent2d.height)
		// if (vkresult != VK_SUCCESS && vkresult != VK_SUBOPTIMAL_KHR)
		if (vkresult != VK_SUCCESS)
		{
			//support recreate vkswapchainkhr if need
			error("vkAcquireNextImageKHR %d", vkresult)
		}

		vkrenderpassbegininfo.framebuffer = m_vkswapchainkhr_vkframebuffer_p[image_index];
		vkpresentinfokhr.pImageIndices = &image_index;

		//s0-command
		vkBeginCommandBuffer(vkcommandbuffer, &vkcommandbufferbegininfo);

			vkCmdBeginRenderPass(vkcommandbuffer, &vkrenderpassbegininfo, VK_SUBPASS_CONTENTS_INLINE);

				vkCmdBindPipeline(vkcommandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vkpipeline);

				vkCmdSetViewport(vkcommandbuffer, 0, 1, &vkviewport);

				vkCmdSetScissor(vkcommandbuffer, 0, 1, &vkrect2d);

				vkCmdBindVertexBuffers(vkcommandbuffer, 0, 1, m_nali_g_data_vkbuffer_p[0], (VkDeviceSize[]){0});
				vkCmdBindIndexBuffer(vkcommandbuffer, *m_nali_g_index_vkbuffer_p[0], 0, VK_INDEX_TYPE_UINT16);
				vkCmdBindDescriptorSets(vkcommandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vkpipelinelayout, 0, 1, &vkdescriptorset, 0, VK_NULL_HANDLE);
				vkCmdDrawIndexed(vkcommandbuffer, 6, 1, 0, 0, 0);

			vkCmdEndRenderPass(vkcommandbuffer);

		vkEndCommandBuffer(vkcommandbuffer);
		//e0-command

		vkQueueSubmit(vkqueue_graphic, 1, &image_vksubmitinfo, *graphic_vkfence_p);

		// if (render_state & RSE_MULTIPLE_QUEUE)
		// {
		// 	vkQueueSubmit(vkqueue_render, 1, &render_vksubmitinfo, *transfer_vkfence_p);

		// 	vkQueuePresentKHR(vkqueue_render, &vkpresentinfokhr);
		// }
		// else
		// {
		vkQueuePresentKHR(vkqueue_graphic, &vkpresentinfokhr);
		// }

		// struct timespec ts = {5, 0};//5sec
		// thrd_sleep(&ts, NULL);

		++frame;
		frame_end = time(0);
		frame_time = frame_end - frame_start;
		if (frame_time > 0)
		// if (frame == 144)
		{
			// end = clock();
			// cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
			frame_start = frame_end;
			info("time %ld", frame_time)
			info("frame %d", frame)
			frame = 0;
		}
	}

	// vkWaitForFences(vkdevice, 1, graphic_vkfence_p, VK_TRUE, UINT64_MAX);
	vkQueueWaitIdle(vkqueue_graphic);
	// if (render_state & RSE_MULTIPLE_QUEUE)
	// {
	// 	// vkWaitForFences(vkdevice, 1, transfer_vkfence_p, VK_TRUE, UINT64_MAX);
	// 	vkQueueWaitIdle(vkqueue_render);
	// }

	vkFreeCommandBuffers(vkdevice, m_vkcommandpool_p[m_device][m_queue_g], 1, &vkcommandbuffer);
	vkDestroyPipeline(vkdevice, vkpipeline, VK_NULL_HANDLE);
	vkDestroyPipelineLayout(vkdevice, vkpipelinelayout, VK_NULL_HANDLE);

	vkDestroyDescriptorSetLayout(vkdevice, vkdescriptorsetlayout, VK_NULL_HANDLE);
	vkDestroyDescriptorPool(vkdevice, vkdescriptorpool, VK_NULL_HANDLE);

	for (uint8_t i = 0; i < 2; ++i)
	{
		vkDestroyFence(vkdevice, m_vkfence_array[i], VK_NULL_HANDLE);
		vkDestroySemaphore(vkdevice, m_vksemaphore_array[i], VK_NULL_HANDLE);
	}
	// vkDestroySemaphore(vkdevice, m_vksemaphore_array[2], VK_NULL_HANDLE);

	clean();

	return 0;
}

static void einfo(uint32_t d)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[d];

	uint32_t extensions = 0;
	vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, VK_NULL_HANDLE);

	VkExtensionProperties *vkextensionproperties_p = malloc(extensions *sizeof(VkExtensionProperties));
	vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, vkextensionproperties_p);

	uint32_t device_extensions_size = sizeof(deviceextensions) / sizeof(deviceextensions[0]);
	uint32_t device_extensions = 0;
	for (uint32_t x = 0; x < extensions; ++x)
	{
		VkExtensionProperties vkextensionproperties = vkextensionproperties_p[x];
		for (uint32_t y = 0; y < device_extensions_size; ++y)
		{
			if (strcmp(deviceextensions[y], vkextensionproperties.extensionName) == 0)
			{
				++device_extensions;
			}
		}
	}
	info("extensions %d", extensions)
	for (uint32_t x = 0; x < extensions; ++x)
	{
		VkExtensionProperties vkextensionproperties = vkextensionproperties_p[x];
		info("extensionName %s", vkextensionproperties.extensionName)
	}

	free(vkextensionproperties_p);
	char extensionssupported = device_extensions == device_extensions_size;
	info("device_extension_support %d", extensionssupported)
}

static void ieinfo()
{
	uint32_t count = 0;
	vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, VK_NULL_HANDLE);

	VkExtensionProperties *vkextensionproperties_p = malloc(sizeof(VkExtensionProperties) * count);
	if (vkextensionproperties_p == VK_NULL_HANDLE)
	{
		error("VkExtensionProperties VK_NULL_HANDLE")
	}

	VkResult vkresult = vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &count, vkextensionproperties_p);
	if (vkresult != VK_SUCCESS)
	{
		error("vkEnumerateInstanceExtensionProperties %d", vkresult)
	}

	for (uint32_t i = 0; i < count; ++i)
	{
		info("%d %s", i, vkextensionproperties_p[i].extensionName)
	}

	free(vkextensionproperties_p);
}

static void vkinfo(uint32_t device)
{
	VkPhysicalDeviceProperties vkphysicaldeviceproperties;
	vkGetPhysicalDeviceProperties(m_vkphysicaldevice_p[device], &vkphysicaldeviceproperties);
	info("Name %s", vkphysicaldeviceproperties.deviceName)
	info
	(
		"Vulkan MAJOR MINOR PATCH %d.%d.%d", 
		VK_VERSION_MAJOR(vkphysicaldeviceproperties.apiVersion),
		VK_VERSION_MINOR(vkphysicaldeviceproperties.apiVersion),
		VK_VERSION_PATCH(vkphysicaldeviceproperties.apiVersion)
	)
	m_limits_max_sampler_anisotropy = vkphysicaldeviceproperties.limits.maxSamplerAnisotropy;
	info("maxSamplerAnisotropy %f", m_limits_max_sampler_anisotropy)

	//VkSampleCountFlagBits
	info("framebufferColorSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferColorSampleCounts);
	info("framebufferDepthSampleCounts %d", vkphysicaldeviceproperties.limits.framebufferDepthSampleCounts);
}

void vk_init()
{
	ieinfo();

	vk_makeInstance();
	vk_makeSurface();
	#ifdef NALI_VK_DEBUG
		vk_makeDebug();
	#endif
	vk_makePhysicalDevice();

	vk_initQueue();
	vk_initDevice();

	vk_initCommandPool();

	for (uint32_t d = 0; d < m_physical_device; ++d)
	{
		info("device %d", d)
		einfo(d);
		vkinfo(d);

		vk_setQueue(d);
		vk_makeDevice(d);
		vk_getQueue(d);
		vk_makeSwapchain(m_max_queue_surface_p[d] == 1 ? VK_SHARING_MODE_EXCLUSIVE : VK_SHARING_MODE_CONCURRENT);

		vk_makeCommandPool(d);
	}
}