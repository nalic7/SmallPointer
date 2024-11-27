// VkExtent2D chooseSwapExtent(vk* vk, VkSurfaceCapabilitiesKHR vksurfacecapabilitieskhr)
// {
//	 // VkExtent2D vkextent2d =
//	 // {
//	 //	 m_width,
//	 //	 m_height
//	 // };

//	 // if (vksurfacecapabilitieskhr.currentTransform & VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR || vksurfacecapabilitieskhr.currentTransform & VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
//	 // {
//	 //	 vkextent2d.height = vulkanstructure.vulkansurfacestructure.surface->width;
//	 //	 vkextent2d.width = vulkanstructure.vulkansurfacestructure.surface->height;

//	 //	 vksurfacecapabilitieskhr.currentExtent.height = vulkanstructure.vulkansurfacestructure.surface->width;
//	 //	 vksurfacecapabilitieskhr.currentExtent.width = vulkanstructure.vulkansurfacestructure.surface->height;
//	 // }

//	 // ModelStructure* modelstructure = vulkanstructure.vulkansurfacestructure.modelstructure;

//	 // if (vksurfacecapabilitieskhr.currentTransform & VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR)
//	 // {
//	 //	 if (modelstructure->world_rotation_z == 0.0F)
//	 //	 {
//	 //		 modelstructure->world_rotation_z = -1.57079633F;
//	 //	 }
//	 //	 else
//	 //	 {
//	 //		 modelstructure->world_rotation_z = -3.14159265359F;
//	 //	 }
//	 // }
//	 // else if (vksurfacecapabilitieskhr.currentTransform & VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
//	 // {
//	 //	 if (modelstructure->world_rotation_z == 0.0F)
//	 //	 {
//	 //		 modelstructure->world_rotation_z = 1.57079633F;
//	 //	 }
//	 //	 else
//	 //	 {
//	 //		 modelstructure->world_rotation_z = 3.14159265359F;
//	 //	 }
//	 // }
//	 // else if (modelstructure->world_rotation_z != 0.0F)
//	 // {
//	 //	 if (modelstructure->world_rotation_z == 3.14159265359F)
//	 //	 {
//	 //		 modelstructure->world_rotation_z = 1.57079633F;
//	 //	 }
//	 //	 else if (modelstructure->world_rotation_z == -3.14159265359F)
//	 //	 {
//	 //		 modelstructure->world_rotation_z = -1.57079633F;
//	 //	 }

//	 //	 modelstructure->quaternion.multiply({0.0F, 0.0F, -modelstructure->world_rotation_z});
//	 //	 modelstructure->world_rotation_z = 0.0F;
//	 //	 return vksurfacecapabilitieskhr.currentExtent;
//	 // }

//	 // modelstructure->quaternion.multiply({0.0F, 0.0F, modelstructure->world_rotation_z});

//	 return vksurfacecapabilitieskhr.currentExtent;
// }

void vk_makeSwapchain(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_ptr[device];
	uint8_t max_graphics = m_max_graphics_ptr[device];

	//
	// SwapchainSupportDetails swapchainsupportdetails =
	// {
	//	 // .set = 0,
	//	 .format = 0,
	//	 .present_mode = 0
	// };
	m_vkswapchainkhr_format_ptr[device] = 0;
	m_vkswapchainkhr_present_mode_ptr[device] = 0;

	if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkphysicaldevice, m_vksurfacekhr, &m_vksurfacecapabilitieskhr_ptr[device]) != VK_SUCCESS)
	{
		error("vkGetPhysicalDeviceSurfaceCapabilitiesKHR")
	}

	vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, m_vksurfacekhr, &m_vkswapchainkhr_format_ptr[device], VK_NULL_HANDLE);

	if (m_vkswapchainkhr_format_ptr[device] != 0)
	{
		// swapchainsupportdetails.set |= 1;
		m_vksurfaceformatkhr_ptr[device] = malloc(m_vkswapchainkhr_format_ptr[device] * sizeof(VkSurfaceFormatKHR));
		vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, m_vksurfacekhr, &m_vkswapchainkhr_format_ptr[device], m_vksurfaceformatkhr_ptr[device]);
	}

	vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, m_vksurfacekhr, &m_vkswapchainkhr_present_mode_ptr[device], VK_NULL_HANDLE);

	if (m_vkswapchainkhr_present_mode_ptr[device] != 0)
	{
		// swapchainsupportdetails.set |= 2;
		m_vkpresentmodekhr_ptr[device] = malloc(m_vkswapchainkhr_present_mode_ptr[device] * sizeof(VkPresentModeKHR));

		vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, m_vksurfacekhr, &m_vkswapchainkhr_present_mode_ptr[device], m_vkpresentmodekhr_ptr[device]);
	}
	//

	VkSurfaceFormatKHR vksurfaceformatkhr = m_vksurfaceformatkhr_ptr[device][0];
	info("device %d", device)
	for (uint32_t i = 0; i < m_vkswapchainkhr_format_ptr[device]; ++i)
	{
		VkSurfaceFormatKHR s_vksurfaceformatkhr = m_vksurfaceformatkhr_ptr[device][i];
		info("i %d", i)
		info("format %d", s_vksurfaceformatkhr.format)
		info("colorSpace %d", s_vksurfaceformatkhr.colorSpace)
		if (s_vksurfaceformatkhr.format == VK_FORMAT_R8G8B8A8_UNORM && s_vksurfaceformatkhr.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			vksurfaceformatkhr = s_vksurfaceformatkhr;
		}
	}

	VkPresentModeKHR vkpresentmodekhr = VK_PRESENT_MODE_FIFO_KHR;//VK_PRESENT_MODE_IMMEDIATE_KHR
	for (uint32_t i = 0; i < m_vkswapchainkhr_present_mode_ptr[device]; ++i)
	{
		VkPresentModeKHR s_vkpresentmodekhr = m_vkpresentmodekhr_ptr[device][i];
		info("VkPresentModeKHR %d", s_vkpresentmodekhr)
		//VK_PRESENT_MODE_FIFO_KHR (V-Sync)
		if (s_vkpresentmodekhr == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			vkpresentmodekhr = s_vkpresentmodekhr;
		}
	}

	// VkExtent2D vkextent2d = chooseSwapExtent(vk, swapchainsupportdetails.vksurfacecapabilitieskhr);

	// uint32_t images = swapchainsupportdetails.vksurfacecapabilitieskhr.minImageCount + 1;

	// if (swapchainsupportdetails.vksurfacecapabilitieskhr.maxImageCount > 0 && images > swapchainsupportdetails.vksurfacecapabilitieskhr.maxImageCount)
	// {
	//	 images = swapchainsupportdetails.vksurfacecapabilitieskhr.maxImageCount;
	// }
	uint32_t images = 0;

	VkSwapchainCreateInfoKHR vkswapchaincreateinfokhr =
	{
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = m_vksurfacekhr,
		.minImageCount = m_vksurfacecapabilitieskhr_ptr[device].minImageCount,
		.imageFormat = vksurfaceformatkhr.format,
		.imageColorSpace = vksurfaceformatkhr.colorSpace,
		// .imageExtent = vkextent2d,
		.imageExtent =
		{
			.height = m_height,
			.width = m_width
		},
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

		.preTransform = m_vksurfacecapabilitieskhr_ptr[device].currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = vkpresentmodekhr,
		.clipped = 1,

		.queueFamilyIndexCount = max_graphics,
		.pQueueFamilyIndices = m_graphics_ptr[device]
	};

	// QueueList queuelist = vk_findQueue(vk, vkphysicaldevice);

	// uint32_t new_queuelist[2] =
	// {
	//	 queuelist.all,
	//	 queuelist.now
	// };

	if (max_graphics > 1)
	{
		vkswapchaincreateinfokhr.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
	}
	else
	{
		vkswapchaincreateinfokhr.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	if (vkCreateSwapchainKHR(m_vkdevice_ptr[device], &vkswapchaincreateinfokhr, VK_NULL_HANDLE, &m_vkswapchainkhr_ptr[device]) != VK_SUCCESS)
	{
		error("vkCreateSwapchainKHR")
	}

	vkGetSwapchainImagesKHR(m_vkdevice_ptr[device], m_vkswapchainkhr_ptr[device], &images, VK_NULL_HANDLE);

	// m_vkswapchainkhr_vkimage_ptr[] = realloc(m_vkswapchainkhr_vkimage_ptr, images * sizeof(VkImage));
	m_vkswapchainkhr_vkimage_ptr[device] = malloc(sizeof(VkImage) * images);

	vkGetSwapchainImagesKHR(m_vkdevice_ptr[device], m_vkswapchainkhr_ptr[device], &images, m_vkswapchainkhr_vkimage_ptr[device]);
	// m_vkswapchainkhr_vkformat = vksurfaceformatkhr.format;
	// m_vkswapchainkhr_vkextent2d = vkextent2d;
}

// void recreateSwapChain(vk* vk)
// {
//	 vk_createSwapchain(vk, *m_vkphysicaldevice_ptr);
//	 VulkanBuffer::createImageViews(vk);
//	 VulkanBuffer::createRenderPass(vk);
//	 VulkanPipeline::createGraphicsPipelines(vk);
//	 VulkanBuffer::createDepthResources(vk);
//	 VulkanBufferFrame::createFramebuffers(vk);
// }

// void clearSwapchain(vk* vk)
// {
//	 // for (auto vkframebufferfromvector : vulkanstructure.vulkanbufferframestructure.vkframebuffer_vector)
//	 // {
//	 //	 vkDestroyFramebuffer(vulkanstructure.vulkandevicestructure.vkdevice, vkframebufferfromvector, VK_NULL_HANDLE);
//	 // }

//	 // vkDestroyPipeline(vulkanstructure.vulkandevicestructure.vkdevice, vulkanstructure.vulkanpipelinestructure.vkpipeline, VK_NULL_HANDLE);
//	 // vkDestroyPipelineLayout(vulkanstructure.vulkandevicestructure.vkdevice, vulkanstructure.vulkanpipelinestructure.vkpipelinelayout, VK_NULL_HANDLE);
//	 // vkDestroyRenderPass(vulkanstructure.vulkandevicestructure.vkdevice, vulkanstructure.vulkanpipelinestructure.vkrenderpass, VK_NULL_HANDLE);

//	 // for (auto vkimageviewfromvector : vulkanstructure.vulkanbufferframestructure.vkimageview_vector)
//	 // {
//	 //	 vkDestroyImageView(vulkanstructure.vulkandevicestructure.vkdevice, vkimageviewfromvector, VK_NULL_HANDLE);
//	 // }

//	 vkDestroySwapchainKHR(m_vkdevice, m_vkswapchainkhr, VK_NULL_HANDLE);
// }

// void clear(vk* vk)
// {
//	 VulkanBufferFrame::clear(vulkanstructure);
//	 // VulkanBufferFrame::clearSemaphore(vulkanstructure);
//	 VulkanBuffer::clearDepthResources(vulkanstructure);//
//	 VulkanPipeline::clearGraphicsPipeline(vulkanstructure);
//	 VulkanBuffer::clearRenderPass(vulkanstructure);
//	 VulkanBuffer::clearImageViews(vulkanstructure);
//	 VulkanSwapchain::clearSwapchain(vulkanstructure);
// }
