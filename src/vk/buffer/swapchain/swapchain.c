// #define NALI_INFO_SC

void vk_reSwapchain(uint32_t device, VkSwapchainCreateFlagsKHR vkswapchaincreateflagskhr, VkSurfaceFormatKHR* vksurfaceformatkhr_ptr, VkPresentModeKHR* vkpresentmodekhr_ptr, uint8_t max_graphics)
{
	VkExtent2D vkextent2d =
	{
		.height = m_height,
		.width = m_width
	};

	m_vkswapchainkhr_vkextent2d_ptr[device] = vkextent2d;
	m_vkswapchainkhr_vkformat_ptr[device] = vksurfaceformatkhr_ptr->format;

	VkSwapchainCreateInfoKHR vkswapchaincreateinfokhr =
	{
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = m_vksurfacekhr,
		.minImageCount = m_vksurfacecapabilitieskhr_ptr[device].minImageCount,
		.imageFormat = vksurfaceformatkhr_ptr->format,
		.imageColorSpace = vksurfaceformatkhr_ptr->colorSpace,
		.imageExtent = vkextent2d,
		.imageArrayLayers = 1,
		.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

		.preTransform = m_vksurfacecapabilitieskhr_ptr[device].currentTransform,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = *vkpresentmodekhr_ptr,
		.clipped = VK_TRUE,

		.queueFamilyIndexCount = max_graphics,
		.pQueueFamilyIndices = m_graphic_ptr[device],

		.oldSwapchain = VK_NULL_HANDLE,

		.imageSharingMode = max_graphics > 1 ? VK_SHARING_MODE_CONCURRENT : VK_SHARING_MODE_EXCLUSIVE,

		.flags = vkswapchaincreateflagskhr,
		.pNext = VK_NULL_HANDLE
	};

	VkResult vkresult = vkCreateSwapchainKHR(m_vkdevice_ptr[device], &vkswapchaincreateinfokhr, VK_NULL_HANDLE, &m_vkswapchainkhr_ptr[device]);
	if (vkresult != VK_SUCCESS)
	{
		error("vkCreateSwapchainKHR %d", vkresult)
	}

	vkGetSwapchainImagesKHR(m_vkdevice_ptr[device], m_vkswapchainkhr_ptr[device], &m_vksurfaceformatkhr_image_ptr[device], VK_NULL_HANDLE);

	uint32_t vksurfaceformatkhr_image = m_vksurfaceformatkhr_image_ptr[device];
	#ifdef NALI_INFO_SC
		info("vksurfaceformatkhr_image %d", vksurfaceformatkhr_image)
	#endif

	m_vkswapchainkhr_vkimage_ptr[device] = malloc(sizeof(VkImage) * vksurfaceformatkhr_image);
	m_vkswapchainkhr_vkimageview_ptr[device] = malloc(sizeof(VkImageView) * vksurfaceformatkhr_image);
	m_vkswapchainkhr_vkframebuffer_ptr[device] = malloc(sizeof(VkFramebuffer) * vksurfaceformatkhr_image);
	// m_vkswapchainkhr_vkrenderpass_ptr[device] = malloc(sizeof(VkRenderPass) * images);

	vkGetSwapchainImagesKHR(m_vkdevice_ptr[device], m_vkswapchainkhr_ptr[device], &vksurfaceformatkhr_image, m_vkswapchainkhr_vkimage_ptr[device]);

	vk_makeRenderPass(device, 0, 0, 0, 0, &m_vkswapchainkhr_vkrenderpass_ptr[device]);

	for (uint32_t i = 0; i < vksurfaceformatkhr_image; ++i)
	{
		// vk_makeRenderPass(device, 0, 0, 0, 0, &m_vkswapchainkhr_vkrenderpass_ptr[device][i]);

		vk_makeImageView(device, &m_vkswapchainkhr_vkimage_ptr[device][i], &vksurfaceformatkhr_ptr->format, VK_IMAGE_ASPECT_COLOR_BIT, 0, &m_vkswapchainkhr_vkimageview_ptr[device][i]);
		vk_makeFrameBuffer(device, 0, &m_vkswapchainkhr_vkimageview_ptr[device][i], &m_vkswapchainkhr_vkrenderpass_ptr[device], &m_vkswapchainkhr_vkframebuffer_ptr[device][i]);
		// vk_makeFrameBuffer(device, 0, &m_vkswapchainkhr_vkimageview_ptr[device][i], &m_vkswapchainkhr_vkrenderpass_ptr[device][i], &m_vkswapchainkhr_vkframebuffer_ptr[device][i]);
	}
}

void vk_makeSwapchain(uint32_t device, VkSwapchainCreateFlagsKHR vkswapchaincreateflagskhr)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_ptr[device];
	uint8_t max_graphics = m_max_graphic_ptr[device];

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
	#ifdef NALI_INFO_SC
		info("device %d", device)
	#endif
	for (uint32_t i = 0; i < m_vkswapchainkhr_format_ptr[device]; ++i)
	{
		VkSurfaceFormatKHR s_vksurfaceformatkhr = m_vksurfaceformatkhr_ptr[device][i];
		#ifdef NALI_INFO_SC
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
	for (uint32_t i = 0; i < m_vkswapchainkhr_present_mode_ptr[device]; ++i)
	{
		VkPresentModeKHR s_vkpresentmodekhr = m_vkpresentmodekhr_ptr[device][i];
		#ifdef NALI_INFO_SC
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
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_ptr[device];
	uint8_t max_graphics = m_max_graphic_ptr[device];
	VkDevice vkdevice = m_vkdevice_ptr[device];

	VkFramebuffer* vkframebuffer_ptr = m_vkswapchainkhr_vkframebuffer_ptr[device];
	VkImageView* vkimageview_ptr = m_vkswapchainkhr_vkimageview_ptr[device];
	for (uint32_t i = 0; i < m_vksurfaceformatkhr_image_ptr[device]; ++i)
	{
		vkDestroyFramebuffer(vkdevice, vkframebuffer_ptr[i], VK_NULL_HANDLE);
		vkDestroyImageView(vkdevice, vkimageview_ptr[i], VK_NULL_HANDLE);
	}

	vkDestroyRenderPass(vkdevice, m_vkswapchainkhr_vkrenderpass_ptr[device], VK_NULL_HANDLE);
	vkDestroySwapchainKHR(vkdevice, m_vkswapchainkhr_ptr[device], VK_NULL_HANDLE);

	free(m_vkswapchainkhr_vkimage_ptr[device]);
	free(m_vkswapchainkhr_vkimageview_ptr[device]);
	free(m_vkswapchainkhr_vkframebuffer_ptr[device]);

	free(m_vksurfaceformatkhr_ptr[device]);
	free(m_vkpresentmodekhr_ptr[device]);
}