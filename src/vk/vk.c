VkInstance m_vkinstance;

//D
uint32_t m_max_device;

VkPhysicalDevice* m_vkphysicaldevice_ptr;
uint8_t* m_max_graphic_ptr;
uint32_t** m_graphic_ptr;
VkQueue** m_vkqueue_ptr;

VkDevice* m_vkdevice_ptr;
//D

//S
VkSurfaceKHR m_vksurfacekhr;

VkSwapchainKHR* m_vkswapchainkhr_ptr;

VkSurfaceCapabilitiesKHR* m_vksurfacecapabilitieskhr_ptr;

VkSurfaceFormatKHR** m_vksurfaceformatkhr_ptr;
uint32_t* m_vkswapchainkhr_format_ptr;

VkPresentModeKHR** m_vkpresentmodekhr_ptr;
uint32_t* m_vkswapchainkhr_present_mode_ptr;

VkImage** m_vkswapchainkhr_vkimage_ptr;
VkExtent2D* m_vkswapchainkhr_vkextent2d_ptr;
VkFormat* m_vkswapchainkhr_vkformat_ptr;
VkRenderPass* m_vkswapchainkhr_vkrenderpass_ptr;
// VkRenderPass** m_vkswapchainkhr_vkrenderpass_ptr;
VkImageView** m_vkswapchainkhr_vkimageview_ptr;
VkFramebuffer** m_vkswapchainkhr_vkframebuffer_ptr;

VkFence** m_vkfence_ptr;
VkSemaphore*** m_vksemaphore_ptr;

VkCommandPool** m_vkcommandpool_ptr;
//S

uint32_t m_device = 0;
uint32_t m_queue_graphic = 0;
uint32_t m_queue_render = 0;//need sync

#ifdef NALI_VK_DEBUG
	VkDebugUtilsMessengerEXT m_vkdebugutilsmessengerext;
#endif

static void clean()
{
	//exit
	// for (uint32_t d = 0; d < m_max_device; ++d)
	// {
	// }
	// vkDestroySurfaceKHR(m_vkinstance, m_vksurfacekhr, NULL);
	// vkDestroyInstance(m_vkinstance, NULL);
	m_vkinstance = VK_NULL_HANDLE;
}

enum render_state_enum
{
	RSE_MULTIPLE_QUEUE = 1
};

static int loop(void* arg)
{
	// m_queue_graphic = 0;
	// m_queue_render = 0;
	VkDevice vkdevice = m_vkdevice_ptr[m_device];
	VkFence* graphic_vkfence_ptr = &m_vkfence_ptr[m_device][0];
	VkFence* transfer_vkfence_ptr = &m_vkfence_ptr[m_device][1];
	VkSwapchainKHR vkswapchainkhr = m_vkswapchainkhr_ptr[m_device];
	VkExtent2D vkextent2d = m_vkswapchainkhr_vkextent2d_ptr[m_device];

	VkSemaphore render_transfer_vksemaphore = m_vksemaphore_ptr[m_device][m_queue_render][1];

	VkSemaphore image_vksemaphore = m_vksemaphore_ptr[m_device][m_queue_graphic][0];
	// VkSemaphore image_vksemaphore = m_vksemaphore_ptr[m_device][m_queue_render][0];
	VkSemaphore render_vksemaphore = m_vksemaphore_ptr[m_device][m_queue_graphic][1];
	// VkSemaphore render_vksemaphore = m_vksemaphore_ptr[m_device][m_queue_render][1];
	VkQueue vkqueue_graphic = m_vkqueue_ptr[m_device][m_queue_graphic];
	VkQueue vkqueue_render = m_vkqueue_ptr[m_device][m_queue_render];

	char render_state = m_queue_graphic != m_queue_render ? RSE_MULTIPLE_QUEUE : 0;
	VkSemaphore* render_vksemaphore_ptr = (render_state & RSE_MULTIPLE_QUEUE) == 0 ? &render_vksemaphore : &render_transfer_vksemaphore;

	VkPipelineLayout vkpipelinelayout;
	VkPipeline vkpipeline;
	vk_makeGraphicsPipeline(m_device, 0, &m_vkswapchainkhr_vkrenderpass_ptr[m_device], &vkpipelinelayout, &vkpipeline);

	VkCommandBuffer vkcommandbuffer;
	vk_makeCommandBuffer(m_device, m_queue_graphic, &vkcommandbuffer, 1);
	// vk_makeCommandBuffer(m_device, m_queue_render, &vkcommandbuffer, 1);

	VkCommandBufferBeginInfo vkcommandbufferbegininfo =
	{
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		.pInheritanceInfo = VK_NULL_HANDLE,

		// .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
		.flags = 0,
		.pNext = VK_NULL_HANDLE
	};

	VkSwapchainKHR swapChains[] = {vkswapchainkhr};
	VkPresentInfoKHR vkpresentinfokhr =
	{
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.waitSemaphoreCount = 1,
		.pWaitSemaphores = &render_vksemaphore,

		.swapchainCount = 1,
		.pSwapchains = swapChains,

		// .pImageIndices = &image_index,

		.pResults = VK_NULL_HANDLE,
		.pNext = VK_NULL_HANDLE
	};

	while ((m_surface_state & NALI_SURFACE_C_S_CLEAN) == 0)
	{
		vkWaitForFences(vkdevice, 1, graphic_vkfence_ptr, VK_TRUE, UINT64_MAX);
		vkResetFences(vkdevice, 1, graphic_vkfence_ptr);

		if ((render_state & RSE_MULTIPLE_QUEUE) == RSE_MULTIPLE_QUEUE)
		{
			vkWaitForFences(vkdevice, 1, transfer_vkfence_ptr, VK_TRUE, UINT64_MAX);
			vkResetFences(vkdevice, 1, transfer_vkfence_ptr);
		}

		if ((m_surface_state & NALI_SURFACE_C_S_RE) == NALI_SURFACE_C_S_RE)
		{
			//recreate
			m_surface_state &= 255 - NALI_SURFACE_C_S_RE;
		}

		uint32_t image_index;
		VkResult vkresult = vkAcquireNextImageKHR(vkdevice, vkswapchainkhr, UINT64_MAX, image_vksemaphore, VK_NULL_HANDLE, &image_index);
		// info("image %d", imageIndex)
		// info("vkextent2d.width %d", vkextent2d.width)
		// info("vkextent2d.height %d", vkextent2d.height)
		// if (vkresult != VK_SUCCESS && vkresult != VK_SUBOPTIMAL_KHR)
		if (vkresult != VK_SUCCESS)
		{
			error("vkAcquireNextImageKHR %d", vkresult)
		}

		// VkPipelineLayout vkpipelinelayout;
		// VkPipeline vkpipeline;
		// vk_makeGraphicsPipeline(m_device, 0, &m_vkswapchainkhr_vkrenderpass_ptr[m_device][imageIndex], &vkpipelinelayout, &vkpipeline);

		// VkCommandBuffer vkcommandbuffer;
		// vk_makeCommandBuffer(m_device, m_graphic, &vkcommandbuffer, 1);

		// VkCommandBufferBeginInfo vkcommandbufferbegininfo =
		// {
		// 	.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
		// 	.pInheritanceInfo = VK_NULL_HANDLE,

		// 	// .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
		// 	.flags = 0,
		// 	.pNext = VK_NULL_HANDLE
		// };

		//s0-command
		// vkResetCommandPool(vkdevice, m_vkcommandpool_ptr[m_device][m_graphic], 0);
		// vkResetCommandBuffer(vkcommandbuffer, 0);
		vkBeginCommandBuffer(vkcommandbuffer, &vkcommandbufferbegininfo);

			VkClearColorValue vkclearcolorvalue =
			{
				.float32 = {1.0F, 0.0F, 0.0F, 1.0F}
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
				.renderPass = m_vkswapchainkhr_vkrenderpass_ptr[m_device],
				// .renderPass = m_vkswapchainkhr_vkrenderpass_ptr[m_device][imageIndex],
				.framebuffer = m_vkswapchainkhr_vkframebuffer_ptr[m_device][image_index],
				.renderArea.offset = {0, 0},
				.renderArea.extent = vkextent2d,
				.clearValueCount = 2,
				.pClearValues = vkclearvalue,

				.pNext = VK_NULL_HANDLE
			};

			vkCmdBeginRenderPass(vkcommandbuffer, &vkrenderpassbegininfo, VK_SUBPASS_CONTENTS_INLINE);

				vkCmdBindPipeline(vkcommandbuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vkpipeline);

				VkViewport vkviewport =
				{
					.x = 0.0F,
					.y = 0.0F,
					.width = vkextent2d.width,
					.height = vkextent2d.height,
					.minDepth = 0.0F,
					.maxDepth = 1.0F
				};
				vkCmdSetViewport(vkcommandbuffer, 0, 1, &vkviewport);

				VkRect2D vkrect2d =
				{
					.offset = {0, 0},
					.extent = vkextent2d
				};
				vkCmdSetScissor(vkcommandbuffer, 0, 1, &vkrect2d);

				vkCmdDraw(vkcommandbuffer, 3, 1, 0, 0);

			vkCmdEndRenderPass(vkcommandbuffer);

		vkEndCommandBuffer(vkcommandbuffer);
		//e0-command

		VkSubmitInfo vksubmitinfo =
		{
			.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
			.waitSemaphoreCount = 1,
			.pWaitSemaphores = &image_vksemaphore,
			.pWaitDstStageMask = (VkPipelineStageFlags[]){VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT},
			.commandBufferCount = 1,
			.pCommandBuffers = &vkcommandbuffer,
			.signalSemaphoreCount = 1,
			.pSignalSemaphores = render_vksemaphore_ptr,

			.pNext = VK_NULL_HANDLE
		};

		// vkQueueWaitIdle(vkqueue_render);
		vkQueueSubmit(vkqueue_graphic, 1, &vksubmitinfo, *graphic_vkfence_ptr);
		// vkQueueSubmit(vkqueue_render, 1, &vksubmitinfo, *vkfence_ptr);

		vkpresentinfokhr.pImageIndices = &image_index;
		if ((render_state & RSE_MULTIPLE_QUEUE) == RSE_MULTIPLE_QUEUE)
		{
			VkSubmitInfo vksubmitinfo =
			{
				.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
				.waitSemaphoreCount = 1,
				.pWaitSemaphores = &render_transfer_vksemaphore,
				.pWaitDstStageMask = (VkPipelineStageFlags[]){VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT},
				.commandBufferCount = 0,
				.signalSemaphoreCount = 1,
				.pSignalSemaphores = &render_vksemaphore,

				.pNext = VK_NULL_HANDLE
			};
			vkQueueSubmit(vkqueue_render, 1, &vksubmitinfo, *transfer_vkfence_ptr);

			vkQueuePresentKHR(vkqueue_render, &vkpresentinfokhr);
		}
		else
		{
			vkQueuePresentKHR(vkqueue_graphic, &vkpresentinfokhr);
		}

		// struct timespec ts = {5, 0};//5sec
		// thrd_sleep(&ts, NULL);

		// vkFreeCommandBuffers(vkdevice, m_vkcommandpool_ptr[m_device][m_graphic], 1, &vkcommandbuffer);
		// vkDestroyPipeline(vkdevice, vkpipeline, VK_NULL_HANDLE);
		// vkDestroyPipelineLayout(vkdevice, vkpipelinelayout, VK_NULL_HANDLE);
	}

	clean();

	return 0;
}

static void checkE(uint32_t d)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_ptr[d];

	uint32_t extensions = 0;
	vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, VK_NULL_HANDLE);

	VkExtensionProperties* vkextensionproperties_ptr = malloc(extensions * sizeof(VkExtensionProperties));
	vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, vkextensionproperties_ptr);

	uint32_t device_extensions_size = sizeof(deviceextensions) / sizeof(deviceextensions[0]);
	uint32_t device_extensions = 0;
	for (uint32_t x = 0; x < extensions; ++x)
	{
		VkExtensionProperties vkextensionproperties = vkextensionproperties_ptr[x];
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
		VkExtensionProperties vkextensionproperties = vkextensionproperties_ptr[x];
		info("extensionName %s", vkextensionproperties.extensionName)
	}

	free(vkextensionproperties_ptr);
	char extensionssupported = device_extensions == device_extensions_size;
	info("device_extension_support %d", extensionssupported)
}

static void checkIE()
{
	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &extensionCount, VK_NULL_HANDLE);

	VkExtensionProperties* extensions = malloc(sizeof(VkExtensionProperties) * extensionCount);
	if (extensions == VK_NULL_HANDLE)
	{
		error("VkExtensionProperties VK_NULL_HANDLE")
	}

	VkResult vkresult = vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &extensionCount, extensions);
	if (vkresult != VK_SUCCESS)
	{
		error("vkEnumerateInstanceExtensionProperties %d", vkresult)
	}

	for (uint32_t i = 0; i < extensionCount; ++i)
	{
		info("%d %s", i, extensions[i].extensionName)
	}

	free(extensions);
}

static void vinfo(uint32_t device)
{
	VkPhysicalDeviceProperties vkphysicaldeviceproperties;
	vkGetPhysicalDeviceProperties(m_vkphysicaldevice_ptr[device], &vkphysicaldeviceproperties);
	info("Name %s", vkphysicaldeviceproperties.deviceName)
	info
	(
		"Vulkan MAJOR MINOR PATCH %d.%d.%d", 
		VK_VERSION_MAJOR(vkphysicaldeviceproperties.apiVersion),
		VK_VERSION_MINOR(vkphysicaldeviceproperties.apiVersion),
		VK_VERSION_PATCH(vkphysicaldeviceproperties.apiVersion)
	)
}

void vk_init()
{
	checkIE();
	vk_makeInstance(0);
	vk_makeSurface(0);
	#ifdef NALI_VK_DEBUG
		vk_makeDebug(0);
	#endif
	vk_makePhysicalDevice();

	m_vkdevice_ptr = malloc(sizeof(VkDevice) * m_max_device);

	m_vkswapchainkhr_ptr = malloc(sizeof(VkSwapchainKHR) * m_max_device);
	m_vkswapchainkhr_vkimage_ptr = malloc(sizeof(VkImage*) * m_max_device);

	m_vksurfacecapabilitieskhr_ptr = malloc(sizeof(VkSurfaceCapabilitiesKHR) * m_max_device);
	m_vkswapchainkhr_vkextent2d_ptr = malloc(sizeof(VkExtent2D) * m_max_device);
	m_vkswapchainkhr_vkformat_ptr = malloc(sizeof(VkFormat) * m_max_device);
	m_vkswapchainkhr_vkrenderpass_ptr = malloc(sizeof(VkRenderPass) * m_max_device);
	// m_vkswapchainkhr_vkrenderpass_ptr = malloc(sizeof(VkRenderPass*) * m_max_device);
	m_vkswapchainkhr_vkimageview_ptr = malloc(sizeof(VkImageView*) * m_max_device);
	m_vkswapchainkhr_vkframebuffer_ptr = malloc(sizeof(VkFramebuffer*) * m_max_device);

	m_vkswapchainkhr_format_ptr = malloc(sizeof(uint32_t) * m_max_device);
	m_vkswapchainkhr_present_mode_ptr = malloc(sizeof(uint32_t) * m_max_device);
	m_vksurfaceformatkhr_ptr = malloc(sizeof(VkSurfaceFormatKHR*) * m_max_device);
	m_vkpresentmodekhr_ptr = malloc(sizeof(VkPresentModeKHR*) * m_max_device);

	m_vkfence_ptr = malloc(sizeof(VkFence*) * m_max_device);
	m_vksemaphore_ptr = malloc(sizeof(VkSemaphore *) * m_max_device);

	m_vkcommandpool_ptr = malloc(sizeof(VkCommandPool *) * m_max_device);

	for (uint32_t d = 0; d < m_max_device; ++d)
	{
		info("device %d", d)
		checkE(d);
		vinfo(d);

		m_graphic_ptr[d] = malloc(sizeof(uint32_t));

		vk_makeQueue(d);
		vk_makeDevice(d, 0, 0);
		vk_makeSwapchain(d, 0);

		m_vkfence_ptr[d] = malloc(sizeof(VkFence) * 2);
		for (uint32_t gi = 0; gi < 2; ++gi)
		{
			vk_makeFence(d, &m_vkfence_ptr[d][gi]);
		}

		uint8_t max_graphics = m_max_graphic_ptr[d];

		m_vksemaphore_ptr[d] = malloc(sizeof(VkSemaphore **) * max_graphics);

		m_vkcommandpool_ptr[d] = malloc(sizeof(VkCommandPool) * max_graphics);

		for (uint8_t g = 0; g < max_graphics; ++g)
		{
			m_vksemaphore_ptr[d][g] = malloc(sizeof(VkSemaphore) * 2);

			vk_makeSemaphore(d, g, 0);
			vk_makeCommandPool(d, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, g);
		}
	}

	thrd_t thread;
	int result = thrd_create(&thread, loop, NULL);
	if (result != thrd_success)
	{
		error("thrd_create")
	}
}