void vk_makeSwapchain(uint32_t device, VkSwapchainCreateFlagsKHR vkswapchaincreateflagskhr)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_ptr[device];
	uint8_t max_graphics = m_max_graphics_ptr[device];

	m_vkswapchainkhr_format_ptr[device] = 0;
	m_vkswapchainkhr_present_mode_ptr[device] = 0;

	VkResult vkresult = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkphysicaldevice, m_vksurfacekhr, &m_vksurfacecapabilitieskhr_ptr[device]);
	if (vkresult != VK_SUCCESS)
	{
		error("vkGetPhysicalDeviceSurfaceCapabilitiesKHR %d", vkresult)
	}

	vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, m_vksurfacekhr, &m_vkswapchainkhr_format_ptr[device], VK_NULL_HANDLE);

	if (m_vkswapchainkhr_format_ptr[device] != 0)
	{
		m_vksurfaceformatkhr_ptr[device] = malloc(m_vkswapchainkhr_format_ptr[device] * sizeof(VkSurfaceFormatKHR));
		vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, m_vksurfacekhr, &m_vkswapchainkhr_format_ptr[device], m_vksurfaceformatkhr_ptr[device]);
	}

	vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, m_vksurfacekhr, &m_vkswapchainkhr_present_mode_ptr[device], VK_NULL_HANDLE);

	if (m_vkswapchainkhr_present_mode_ptr[device] != 0)
	{
		m_vkpresentmodekhr_ptr[device] = malloc(m_vkswapchainkhr_present_mode_ptr[device] * sizeof(VkPresentModeKHR));

		vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, m_vksurfacekhr, &m_vkswapchainkhr_present_mode_ptr[device], m_vkpresentmodekhr_ptr[device]);
	}

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

	VkPresentModeKHR vkpresentmodekhr = VK_PRESENT_MODE_FIFO_RELAXED_KHR;//VK_PRESENT_MODE_IMMEDIATE_KHR
	for (uint32_t i = 0; i < m_vkswapchainkhr_present_mode_ptr[device]; ++i)
	{
		VkPresentModeKHR s_vkpresentmodekhr = m_vkpresentmodekhr_ptr[device][i];
		info("VkPresentModeKHR %d", s_vkpresentmodekhr)
		//VK_PRESENT_MODE_FIFO_KHR (V-Sync)
		// if (s_vkpresentmodekhr == VK_PRESENT_MODE_MAILBOX_KHR)
		if (s_vkpresentmodekhr == VK_PRESENT_MODE_FIFO_KHR)
		{
			vkpresentmodekhr = s_vkpresentmodekhr;
		}
	}

	uint32_t images = 0;

	VkExtent2D vkextent2d =
	{
		.height = m_height,
		.width = m_width
	};

	m_vkswapchainkhr_vkextent2d_ptr[device] = vkextent2d;
	m_vkswapchainkhr_vkformat_ptr[device] = vksurfaceformatkhr.format;

	VkSwapchainCreateInfoKHR vkswapchaincreateinfokhr =
	{
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = m_vksurfacekhr,
		.minImageCount = m_vksurfacecapabilitieskhr_ptr[device].minImageCount,
		.imageFormat = vksurfaceformatkhr.format,
		.imageColorSpace = vksurfaceformatkhr.colorSpace,
		.imageExtent = vkextent2d,
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

		.preTransform = m_vksurfacecapabilitieskhr_ptr[device].currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = vkpresentmodekhr,
		.clipped = VK_TRUE,

		.queueFamilyIndexCount = max_graphics,
		.pQueueFamilyIndices = m_graphics_ptr[device],

		.oldSwapchain = VK_NULL_HANDLE,

		.flags = vkswapchaincreateflagskhr,
		.pNext = VK_NULL_HANDLE
	};

	if (max_graphics > 1)
	{
		vkswapchaincreateinfokhr.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
	}
	else
	{
		vkswapchaincreateinfokhr.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	vkresult = vkCreateSwapchainKHR(m_vkdevice_ptr[device], &vkswapchaincreateinfokhr, VK_NULL_HANDLE, &m_vkswapchainkhr_ptr[device]);
	if (vkresult != VK_SUCCESS)
	{
		error("vkCreateSwapchainKHR %d", vkresult)
	}

	//re
	vkGetSwapchainImagesKHR(m_vkdevice_ptr[device], m_vkswapchainkhr_ptr[device], &images, VK_NULL_HANDLE);

	info("images %d", images)

	m_vkswapchainkhr_vkimage_ptr[device] = malloc(sizeof(VkImage) * images);
	m_vkswapchainkhr_vkimageview_ptr[device] = malloc(sizeof(VkImageView) * images);
	m_vkswapchainkhr_vkframebuffer_ptr[device] = malloc(sizeof(VkFramebuffer) * images);
	// m_vkswapchainkhr_vkrenderpass_ptr[device] = malloc(sizeof(VkRenderPass) * images);

	vkGetSwapchainImagesKHR(m_vkdevice_ptr[device], m_vkswapchainkhr_ptr[device], &images, m_vkswapchainkhr_vkimage_ptr[device]);

	vk_makeRenderPass(device, 0, 0, 0, 0, &m_vkswapchainkhr_vkrenderpass_ptr[device]);

	for (uint32_t i = 0; i < images; ++i)
	{
		// vk_makeRenderPass(device, 0, 0, 0, 0, &m_vkswapchainkhr_vkrenderpass_ptr[device][i]);

		vk_makeImageView(device, &m_vkswapchainkhr_vkimage_ptr[device][i], &vksurfaceformatkhr.format, VK_IMAGE_ASPECT_COLOR_BIT, 0, &m_vkswapchainkhr_vkimageview_ptr[device][i]);
		vk_makeFrameBuffer(device, 0, &m_vkswapchainkhr_vkimageview_ptr[device][i], &m_vkswapchainkhr_vkrenderpass_ptr[device], &m_vkswapchainkhr_vkframebuffer_ptr[device][i]);
		// vk_makeFrameBuffer(device, 0, &m_vkswapchainkhr_vkimageview_ptr[device][i], &m_vkswapchainkhr_vkrenderpass_ptr[device][i], &m_vkswapchainkhr_vkframebuffer_ptr[device][i]);
	}
}