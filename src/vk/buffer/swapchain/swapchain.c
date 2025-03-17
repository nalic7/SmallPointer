void vk_reSwapchain(uint32_t device, VkSwapchainCreateFlagsKHR vkswapchaincreateflagskhr, VkSurfaceFormatKHR* vksurfaceformatkhr_p, VkPresentModeKHR* vkpresentmodekhr_p, uint8_t max_graphics)
{
	VkExtent2D vkextent2d =
	{
		.height = m_height,
		.width = m_width
	};

	m_vkswapchainkhr_vkextent2d_p[device] = vkextent2d;
	m_vkswapchainkhr_vkformat_p[device] = vksurfaceformatkhr_p->format;

	VkSwapchainCreateInfoKHR vkswapchaincreateinfokhr =
	{
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = m_vksurfacekhr,
		.minImageCount = m_vksurfacecapabilitieskhr_p[device].minImageCount,
		.imageFormat = vksurfaceformatkhr_p->format,
		.imageColorSpace = vksurfaceformatkhr_p->colorSpace,
		.imageExtent = vkextent2d,
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

		.preTransform = m_vksurfacecapabilitieskhr_p[device].currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = *vkpresentmodekhr_p,
		.clipped = VK_TRUE,

		.queueFamilyIndexCount = max_graphics,
		.pQueueFamilyIndices = m_graphic_p[device],

		.oldSwapchain = VK_NULL_HANDLE,

		.imageSharingMode = max_graphics > 1 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE,

		.flags = vkswapchaincreateflagskhr,
		.pNext = VK_NULL_HANDLE
	};

	VkResult vkresult = vkCreateSwapchainKHR(m_vkdevice_p[device], &vkswapchaincreateinfokhr, VK_NULL_HANDLE, &m_vkswapchainkhr_p[device]);
	if (vkresult != VK_SUCCESS)
	{
		error("vkCreateSwapchainKHR %d", vkresult)
	}

	vkGetSwapchainImagesKHR(m_vkdevice_p[device], m_vkswapchainkhr_p[device], &m_vksurfaceformatkhr_image_p[device], VK_NULL_HANDLE);

	uint32_t vksurfaceformatkhr_image = m_vksurfaceformatkhr_image_p[device];
	#ifdef NALI_VK_INFO_SC
		info("vksurfaceformatkhr_image %d", vksurfaceformatkhr_image)
	#endif

	m_vkswapchainkhr_vkimage_p[device] = malloc(sizeof(VkImage) * vksurfaceformatkhr_image);
	m_vkswapchainkhr_vkimageview_p[device] = malloc(sizeof(VkImageView) * vksurfaceformatkhr_image);
	m_vkswapchainkhr_vkframebuffer_p[device] = malloc(sizeof(VkFramebuffer) * vksurfaceformatkhr_image);
	// m_vkswapchainkhr_vkrenderpass_p[device] = malloc(sizeof(VkRenderPass) * images);

	vkGetSwapchainImagesKHR(m_vkdevice_p[device], m_vkswapchainkhr_p[device], &vksurfaceformatkhr_image, m_vkswapchainkhr_vkimage_p[device]);

	vk_makeRenderPass(device, 0, 0, 0, 0, &m_vkswapchainkhr_vkrenderpass_p[device]);

	for (uint32_t i = 0; i < vksurfaceformatkhr_image; ++i)
	{
		// vk_makeRenderPass(device, 0, 0, 0, 0, &m_vkswapchainkhr_vkrenderpass_p[device][i]);

		vk_makeImageView(device, &m_vkswapchainkhr_vkimage_p[device][i], &vksurfaceformatkhr_p->format, VK_IMAGE_ASPECT_COLOR_BIT, 0, &m_vkswapchainkhr_vkimageview_p[device][i]);
		vk_makeFrameBuffer(device, 0, &m_vkswapchainkhr_vkimageview_p[device][i], &m_vkswapchainkhr_vkrenderpass_p[device], &m_vkswapchainkhr_vkframebuffer_p[device][i]);
		// vk_makeFrameBuffer(device, 0, &m_vkswapchainkhr_vkimageview_p[device][i], &m_vkswapchainkhr_vkrenderpass_p[device][i], &m_vkswapchainkhr_vkframebuffer_p[device][i]);
	}
}

void vk_makeSwapchain(uint32_t device, VkSwapchainCreateFlagsKHR vkswapchaincreateflagskhr)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[device];
	uint8_t max_graphics = m_max_graphic_p[device];

	m_vkswapchainkhr_format_p[device] = 0;
	m_vkswapchainkhr_present_mode_p[device] = 0;

	VkResult vkresult = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkphysicaldevice, m_vksurfacekhr, &m_vksurfacecapabilitieskhr_p[device]);
	if (vkresult != VK_SUCCESS)
	{
		error("vkGetPhysicalDeviceSurfaceCapabilitiesKHR %d", vkresult)
	}

	vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, m_vksurfacekhr, &m_vkswapchainkhr_format_p[device], VK_NULL_HANDLE);

	if (m_vkswapchainkhr_format_p[device] != 0)
	{
		m_vksurfaceformatkhr_p[device] = malloc(m_vkswapchainkhr_format_p[device] * sizeof(VkSurfaceFormatKHR));
		vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, m_vksurfacekhr, &m_vkswapchainkhr_format_p[device], m_vksurfaceformatkhr_p[device]);
	}

	vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, m_vksurfacekhr, &m_vkswapchainkhr_present_mode_p[device], VK_NULL_HANDLE);

	if (m_vkswapchainkhr_present_mode_p[device] != 0)
	{
		m_vkpresentmodekhr_p[device] = malloc(m_vkswapchainkhr_present_mode_p[device] * sizeof(VkPresentModeKHR));

		vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, m_vksurfacekhr, &m_vkswapchainkhr_present_mode_p[device], m_vkpresentmodekhr_p[device]);
	}

	VkSurfaceFormatKHR vksurfaceformatkhr = m_vksurfaceformatkhr_p[device][0];
	#ifdef NALI_VK_INFO_SC
		info("device %d", device)
	#endif
	for (uint32_t i = 0; i < m_vkswapchainkhr_format_p[device]; ++i)
	{
		VkSurfaceFormatKHR s_vksurfaceformatkhr = m_vksurfaceformatkhr_p[device][i];
		#ifdef NALI_VK_INFO_SC
			info("i %d", i)
			info("format %d", s_vksurfaceformatkhr.format)
			info("colorSpace %d", s_vksurfaceformatkhr.colorSpace)
		#endif
		if (s_vksurfaceformatkhr.format == VK_FORMAT_R8G8B8A8_UNORM && s_vksurfaceformatkhr.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			vksurfaceformatkhr = s_vksurfaceformatkhr;
		}
	}

	VkPresentModeKHR vkpresentmodekhr = VK_PRESENT_MODE_IMMEDIATE_KHR;
	for (uint32_t i = 0; i < m_vkswapchainkhr_present_mode_p[device]; ++i)
	{
		VkPresentModeKHR s_vkpresentmodekhr = m_vkpresentmodekhr_p[device][i];
		#ifdef NALI_VK_INFO_SC
			info("VkPresentModeKHR %d", s_vkpresentmodekhr)
		#endif
		if (s_vkpresentmodekhr == VK_PRESENT_MODE_FIFO_KHR)
		{
			vkpresentmodekhr = s_vkpresentmodekhr;
		}
	}

	// uint32_t images = 0;

	vk_reSwapchain(device, vkswapchaincreateflagskhr, &vksurfaceformatkhr, &vkpresentmodekhr, max_graphics);
}

void vk_cleanSwapchain(uint32_t device)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[device];
	uint8_t max_graphics = m_max_graphic_p[device];
	VkDevice vkdevice = m_vkdevice_p[device];

	VkFramebuffer* vkframebuffer_p = m_vkswapchainkhr_vkframebuffer_p[device];
	VkImageView* vkimageview_p = m_vkswapchainkhr_vkimageview_p[device];
	for (uint32_t i = 0; i < m_vksurfaceformatkhr_image_p[device]; ++i)
	{
		vkDestroyFramebuffer(vkdevice, vkframebuffer_p[i], VK_NULL_HANDLE);
		vkDestroyImageView(vkdevice, vkimageview_p[i], VK_NULL_HANDLE);
	}

	vkDestroyRenderPass(vkdevice, m_vkswapchainkhr_vkrenderpass_p[device], VK_NULL_HANDLE);
	vkDestroySwapchainKHR(vkdevice, m_vkswapchainkhr_p[device], VK_NULL_HANDLE);

	free(m_vkswapchainkhr_vkimage_p[device]);
	free(m_vkswapchainkhr_vkimageview_p[device]);
	free(m_vkswapchainkhr_vkframebuffer_p[device]);

	free(m_vksurfaceformatkhr_p[device]);
	free(m_vkpresentmodekhr_p[device]);
}