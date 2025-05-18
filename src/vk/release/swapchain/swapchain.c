VkSwapchainKHR m_vkswapchainkhr;
VkExtent2D m_vkextent2d;
VkRenderPass m_vkrenderpass;

VkImage *m_vkswapchainkhr_vkimage_p;
VkImageView *m_vkswapchainkhr_vkimageview_p;
VkFramebuffer *m_vkswapchainkhr_vkframebuffer_p = NULL;

//VkSurfaceTransformFlagBitsKHR m_vksurfacetransformflagbitskhr;

static uint32_t swapchain_image;

static VkImage vkimage_depth;
static VkImageView vkimageview_depth;
static VkDeviceMemory vkdevicememory_depth;

static VkImage vkimage_color;
static VkImageView vkimageview_color;
static VkDeviceMemory vkdevicememory_color;

void vk_makeSwapchain(VkSharingMode vksharingmode)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[m_device];
	VkDevice vkdevice = m_vkdevice_p[m_device];

	#ifdef NALI_VK_INFO_SC
		uint32_t surface_format;
		nali_info("vkGetPhysicalDeviceSurfaceFormatsKHR %d", vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, m_vksurfacekhr, &surface_format, VK_NULL_HANDLE))
		VkSurfaceFormatKHR *vksurfaceformatkhr_p = malloc(surface_format * sizeof(VkSurfaceFormatKHR));
		nali_info("vkGetPhysicalDeviceSurfaceFormatsKHR %d", vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, m_vksurfacekhr, &surface_format, vksurfaceformatkhr_p))
		for (uint32_t i = 0; i < surface_format; ++i)
		{
			VkSurfaceFormatKHR vksurfaceformatkhr = vksurfaceformatkhr_p[i];
			nali_log("i %d", i)
			nali_log("format %d", vksurfaceformatkhr.format)
			nali_log("colorSpace %d", vksurfaceformatkhr.colorSpace)
		}

		free(vksurfaceformatkhr_p);

		uint32_t surface_present;
		nali_info("vkGetPhysicalDeviceSurfacePresentModesKHR %d", vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, m_vksurfacekhr, &surface_present, VK_NULL_HANDLE))
		VkPresentModeKHR *vkpresentmodekhr_p = malloc(surface_present * sizeof(VkPresentModeKHR));
		nali_info("vkGetPhysicalDeviceSurfacePresentModesKHR %d", vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, m_vksurfacekhr, &surface_present, vkpresentmodekhr_p))
		for (uint32_t i = 0; i < surface_present; ++i)
		{
			nali_log("VkPresentModeKHR %d", vkpresentmodekhr_p[i])
		}
		free(vkpresentmodekhr_p);
	#endif

	VkSurfaceCapabilitiesKHR vksurfacecapabilitieskhr;
	nali_info("vkGetPhysicalDeviceSurfaceCapabilitiesKHR %d", vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkphysicaldevice, m_vksurfacekhr, &vksurfacecapabilitieskhr))

//	m_vksurfacetransformflagbitskhr = vksurfacecapabilitieskhr.currentTransform;
//	if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR || m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
	if (vksurfacecapabilitieskhr.currentTransform == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR || vksurfacecapabilitieskhr.currentTransform == VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
	{
		m_vkextent2d.width = s_height;
		m_vkextent2d.height = s_width;
//		m_width = m_vkextent2d.width;
//		m_height = m_vkextent2d.height;
	}
	else
	{
		m_vkextent2d.height = s_height;
		m_vkextent2d.width = s_width;
	}

////	if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR)
////	{
////		m_vkextent2d.height = 1;
////		m_vkextent2d.width = 1;
////		m_width = m_vkextent2d.width;
////		m_height = m_vkextent2d.height;
////	}
////	else if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR)
////	{
////		m_vkextent2d.height = 1;
////		m_vkextent2d.width = 1;
////		m_width = m_vkextent2d.width;
////		m_height = m_vkextent2d.height;
////	}
//	else
//	{
//		m_vkextent2d.height = m_height;
//		m_vkextent2d.width = m_width;
//	}

	nali_info
	(
		"vkCreateSwapchainKHR %d",
		vkCreateSwapchainKHR
		(
			vkdevice,
			&(VkSwapchainCreateInfoKHR)
			{
				.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
				.surface = m_vksurfacekhr,
				.minImageCount = vksurfacecapabilitieskhr.minImageCount,
				.imageFormat = NALI_VK_COLOR_FORMAT,
				.imageColorSpace = NALI_VK_COLOR_SPACE,
				.imageExtent = m_vkextent2d,
				.imageArrayLayers = 1,
				.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

				.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
				.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
				.presentMode = NALI_VK_PRESENT,
				.clipped = VK_TRUE,

				.queueFamilyIndexCount = m_max_queue_surface_p[m_device],
				.pQueueFamilyIndices = m_queue_surface_p[m_device],

				.oldSwapchain = VK_NULL_HANDLE,

				.imageSharingMode = vksharingmode,

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&m_vkswapchainkhr
		)
	)

	nali_info("vkGetSwapchainImagesKHR %d", vkGetSwapchainImagesKHR(vkdevice, m_vkswapchainkhr, &swapchain_image, VK_NULL_HANDLE))

	#ifdef NALI_VK_INFO_SC
		nali_log("vksurfaceformatkhr_image %d", swapchain_image)
	#endif

	m_vkswapchainkhr_vkimage_p = malloc(sizeof(VkImage) * swapchain_image);
	m_vkswapchainkhr_vkimageview_p = malloc(sizeof(VkImageView) * swapchain_image);
	m_vkswapchainkhr_vkframebuffer_p = malloc(sizeof(VkFramebuffer) * swapchain_image);

	nali_info("vkGetSwapchainImagesKHR %d", vkGetSwapchainImagesKHR(vkdevice, m_vkswapchainkhr, &swapchain_image, m_vkswapchainkhr_vkimage_p))

	VK_makeRenderPass(m_device, &m_vkrenderpass)

	VK_makeImage
	(
		m_device,
		NALI_VK_DEPTH_FORMAT,
		((VkExtent3D)
		{
			.width = m_vkextent2d.width,
			.height = m_vkextent2d.height,
			.depth = 1
		}),
		1,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		NALI_VK_SAMPLE_C,
		&vkimage_depth
	)
	VkMemoryRequirements vkmemoryrequirements;
	VK_genImage(m_device, vkimage_depth, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &vkdevicememory_depth, vkmemoryrequirements)
	VK_makeImageView(m_device, vkimage_depth, NALI_VK_DEPTH_FORMAT, VK_IMAGE_ASPECT_DEPTH_BIT, 1, &vkimageview_depth)

	VK_makeImage
	(
		m_device,
		NALI_VK_COLOR_FORMAT,
		((VkExtent3D)
		{
			.width = m_vkextent2d.width,
			.height = m_vkextent2d.height,
			.depth = 1
		}),
		1,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		NALI_VK_SAMPLE_C,
		&vkimage_color
	)
	VK_genImage(m_device, vkimage_color, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &vkdevicememory_color, vkmemoryrequirements)
	VK_makeImageView(m_device, vkimage_color, NALI_VK_COLOR_FORMAT, VK_IMAGE_ASPECT_COLOR_BIT, 1, &vkimageview_color)

	for (uint32_t i = 0; i < swapchain_image; ++i)
	{
		VK_makeImageView(m_device, m_vkswapchainkhr_vkimage_p[i], NALI_VK_COLOR_FORMAT, VK_IMAGE_ASPECT_COLOR_BIT, 1, &m_vkswapchainkhr_vkimageview_p[i])
		VK_makeFramebuffer
		(
			m_device,
			((VkImageView[])
			{
				vkimageview_color,
				vkimageview_depth,
				m_vkswapchainkhr_vkimageview_p[i]
			}),
			3,
			m_vkrenderpass,
			&m_vkswapchainkhr_vkframebuffer_p[i]
		)
	}
}

void vk_freeSwapchain()
{
	if (m_vkswapchainkhr_vkframebuffer_p == NULL)
	{
		return;
	}
//	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[m_device];
	VkDevice vkdevice = m_vkdevice_p[m_device];

	vkDestroyImageView(vkdevice, vkimageview_depth, VK_NULL_HANDLE);
	vkDestroyImage(vkdevice, vkimage_depth, VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, vkdevicememory_depth, VK_NULL_HANDLE);

	vkDestroyImageView(vkdevice, vkimageview_color, VK_NULL_HANDLE);
	vkDestroyImage(vkdevice, vkimage_color, VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, vkdevicememory_color, VK_NULL_HANDLE);

	for (uint32_t i = 0; i < swapchain_image; ++i)
	{
		vkDestroyFramebuffer(vkdevice, m_vkswapchainkhr_vkframebuffer_p[i], VK_NULL_HANDLE);
		vkDestroyImageView(vkdevice, m_vkswapchainkhr_vkimageview_p[i], VK_NULL_HANDLE);
	}

	vkDestroyRenderPass(vkdevice, m_vkrenderpass, VK_NULL_HANDLE);
	vkDestroySwapchainKHR(vkdevice, m_vkswapchainkhr, VK_NULL_HANDLE);

	free(m_vkswapchainkhr_vkimage_p);
	free(m_vkswapchainkhr_vkimageview_p);
	free(m_vkswapchainkhr_vkframebuffer_p);
	m_vkswapchainkhr_vkframebuffer_p = NULL;
}