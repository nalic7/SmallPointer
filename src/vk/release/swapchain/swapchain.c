VkSwapchainKHR vksc_vkswapchainkhr;
VkExtent2D vksc_vkextent2d;
VkRenderPass vksc_vkrenderpass;

VkImage *vksc_vkswapchainkhr_vkimage_p;
VkImageView *vksc_vkswapchainkhr_vkimageview_p;
VkFramebuffer *vksc_vkswapchainkhr_vkframebuffer_p;

uint8_t vksc_image;

//VkSurfaceTransformFlagBitsKHR m_vksurfacetransformflagbitskhr;

static uint32_t swapchain_image;

static VkImage vkimage_depth;
static VkImageView vkimageview_depth;
static VkDeviceMemory vkdevicememory_depth;

static VkImage vkimage_color;
static VkImageView vkimageview_color;
static VkDeviceMemory vkdevicememory_color;

void vksc_make(VkSharingMode vksharingmode)
{
	VkPhysicalDevice vkphysicaldevice = vkqdpd_vkphysicaldevice_p[vk_device];
	VkDevice vkdevice = vkqd_vkdevice_p[vk_device];

	#ifdef NALI_VK_INFO_SC
		uint32_t surface_format;
		NALI_D_INFO("vkGetPhysicalDeviceSurfaceFormatsKHR %d", vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, vks_vksurfacekhr, &surface_format, VK_NULL_HANDLE))
		VkSurfaceFormatKHR *vksurfaceformatkhr_p = malloc(surface_format * sizeof(VkSurfaceFormatKHR));
		NALI_D_INFO("vkGetPhysicalDeviceSurfaceFormatsKHR %d", vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, vks_vksurfacekhr, &surface_format, vksurfaceformatkhr_p))
		for (uint32_t i = 0; i < surface_format; ++i)
		{
			VkSurfaceFormatKHR vksurfaceformatkhr = vksurfaceformatkhr_p[i];
			NALI_D_LOG("i %d", i)
			NALI_D_LOG("format %d", vksurfaceformatkhr.format)
			NALI_D_LOG("colorSpace %d", vksurfaceformatkhr.colorSpace)
		}

		free(vksurfaceformatkhr_p);

		uint32_t surface_present;
		NALI_D_INFO("vkGetPhysicalDeviceSurfacePresentModesKHR %d", vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, vks_vksurfacekhr, &surface_present, VK_NULL_HANDLE))
		VkPresentModeKHR *vkpresentmodekhr_p = malloc(surface_present * sizeof(VkPresentModeKHR));
		NALI_D_INFO("vkGetPhysicalDeviceSurfacePresentModesKHR %d", vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, vks_vksurfacekhr, &surface_present, vkpresentmodekhr_p))
		for (uint32_t i = 0; i < surface_present; ++i)
		{
			NALI_D_LOG("VkPresentModeKHR %d", vkpresentmodekhr_p[i])
		}
		free(vkpresentmodekhr_p);
	#endif

	VkSurfaceCapabilitiesKHR vksurfacecapabilitieskhr;
	NALI_D_INFO("vkGetPhysicalDeviceSurfaceCapabilitiesKHR %d", vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkphysicaldevice, vks_vksurfacekhr, &vksurfacecapabilitieskhr))
	NALI_D_INFO("vksc_image %d", vksc_image = vksurfacecapabilitieskhr.minImageCount)

//	m_vksurfacetransformflagbitskhr = vksurfacecapabilitieskhr.currentTransform;
//	if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR || m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
	if (vksurfacecapabilitieskhr.currentTransform == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR || vksurfacecapabilitieskhr.currentTransform == VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
	{
		vksc_vkextent2d.width = s_height;
		vksc_vkextent2d.height = s_width;
//		m_width = vksc_vkextent2d.width;
//		m_height = vksc_vkextent2d.height;
	}
	else
	{
		vksc_vkextent2d.height = s_height;
		vksc_vkextent2d.width = s_width;
	}

////	if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR)
////	{
////		vksc_vkextent2d.height = 1;
////		vksc_vkextent2d.width = 1;
////		m_width = vksc_vkextent2d.width;
////		m_height = vksc_vkextent2d.height;
////	}
////	else if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR)
////	{
////		vksc_vkextent2d.height = 1;
////		vksc_vkextent2d.width = 1;
////		m_width = vksc_vkextent2d.width;
////		m_height = vksc_vkextent2d.height;
////	}
//	else
//	{
//		vksc_vkextent2d.height = m_height;
//		vksc_vkextent2d.width = m_width;
//	}

	NALI_D_INFO
	(
		"vkCreateSwapchainKHR %d",
		vkCreateSwapchainKHR
		(
			vkdevice,
			&(VkSwapchainCreateInfoKHR)
			{
				.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
				.surface = vks_vksurfacekhr,
				.minImageCount = vksurfacecapabilitieskhr.minImageCount,
				.imageFormat = NALI_VK_COLOR_FORMAT,
				.imageColorSpace = NALI_VK_COLOR_SPACE,
				.imageExtent = vksc_vkextent2d,
				.imageArrayLayers = 1,
				.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

				.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
				.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
				.presentMode = NALI_VK_PRESENT,
				.clipped = VK_TRUE,

				.queueFamilyIndexCount = vkq_max_queue_surface_p[vk_device],
				.pQueueFamilyIndices = vkq_queue_surface_p[vk_device],

				.oldSwapchain = VK_NULL_HANDLE,

				.imageSharingMode = vksharingmode,

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&vksc_vkswapchainkhr
		)
	)

	NALI_D_INFO("vkGetSwapchainImagesKHR %d", vkGetSwapchainImagesKHR(vkdevice, vksc_vkswapchainkhr, &swapchain_image, VK_NULL_HANDLE))

	#ifdef NALI_VK_INFO_SC
		NALI_D_LOG("vksurfaceformatkhr_image %d", swapchain_image)
	#endif

	vksc_vkswapchainkhr_vkimage_p = malloc(sizeof(VkImage) * swapchain_image);
	vksc_vkswapchainkhr_vkimageview_p = malloc(sizeof(VkImageView) * swapchain_image);
	vksc_vkswapchainkhr_vkframebuffer_p = malloc(sizeof(VkFramebuffer) * swapchain_image);

	NALI_D_INFO("vkGetSwapchainImagesKHR %d", vkGetSwapchainImagesKHR(vkdevice, vksc_vkswapchainkhr, &swapchain_image, vksc_vkswapchainkhr_vkimage_p))

	VK_makeRenderPass(vk_device, &vksc_vkrenderpass)

	VK_makeImage
	(
		vk_device,
		NALI_VK_DEPTH_FORMAT,
		((VkExtent3D)
		{
			.width = vksc_vkextent2d.width,
			.height = vksc_vkextent2d.height,
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
	VK_genImage(vk_device, vkimage_depth, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &vkdevicememory_depth, vkmemoryrequirements)
	VK_makeImageView(vk_device, vkimage_depth, NALI_VK_DEPTH_FORMAT, VK_IMAGE_ASPECT_DEPTH_BIT, 1, &vkimageview_depth)

	VK_makeImage
	(
		vk_device,
		NALI_VK_COLOR_FORMAT,
		((VkExtent3D)
		{
			.width = vksc_vkextent2d.width,
			.height = vksc_vkextent2d.height,
			.depth = 1
		}),
		1,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		NALI_VK_SAMPLE_C,
		&vkimage_color
	)
	VK_genImage(vk_device, vkimage_color, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &vkdevicememory_color, vkmemoryrequirements)
	VK_makeImageView(vk_device, vkimage_color, NALI_VK_COLOR_FORMAT, VK_IMAGE_ASPECT_COLOR_BIT, 1, &vkimageview_color)

	for (uint32_t i = 0; i < swapchain_image; ++i)
	{
		VK_makeImageView(vk_device, vksc_vkswapchainkhr_vkimage_p[i], NALI_VK_COLOR_FORMAT, VK_IMAGE_ASPECT_COLOR_BIT, 1, &vksc_vkswapchainkhr_vkimageview_p[i])
		VK_makeFramebuffer
		(
			vk_device,
			((VkImageView[])
			{
				vkimageview_color,
				vkimageview_depth,
				vksc_vkswapchainkhr_vkimageview_p[i]
			}),
			3,
			vksc_vkrenderpass,
			&vksc_vkswapchainkhr_vkframebuffer_p[i]
		)
	}
}

void vksc_free()
{
//	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[vk_device];
	VkDevice vkdevice = vkqd_vkdevice_p[vk_device];

	vkDestroyImageView(vkdevice, vkimageview_depth, VK_NULL_HANDLE);
	vkDestroyImage(vkdevice, vkimage_depth, VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, vkdevicememory_depth, VK_NULL_HANDLE);

	vkDestroyImageView(vkdevice, vkimageview_color, VK_NULL_HANDLE);
	vkDestroyImage(vkdevice, vkimage_color, VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, vkdevicememory_color, VK_NULL_HANDLE);

	for (uint32_t i = 0; i < swapchain_image; ++i)
	{
		vkDestroyFramebuffer(vkdevice, vksc_vkswapchainkhr_vkframebuffer_p[i], VK_NULL_HANDLE);
		vkDestroyImageView(vkdevice, vksc_vkswapchainkhr_vkimageview_p[i], VK_NULL_HANDLE);
	}

	vkDestroyRenderPass(vkdevice, vksc_vkrenderpass, VK_NULL_HANDLE);
	//!this can't avoid wayland crash on startup
	#ifndef C_NALI_S_ANDROID
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	#endif
	NALI_D_LOG("->vkDestroySwapchainKHR");
	vkDestroySwapchainKHR(vkdevice, vksc_vkswapchainkhr, VK_NULL_HANDLE);

	free(vksc_vkswapchainkhr_vkimage_p);
	free(vksc_vkswapchainkhr_vkimageview_p);
	free(vksc_vkswapchainkhr_vkframebuffer_p);
}
