VkSwapchainKHR _rd_vk_swc_khr;
VkExtent2D _rd_vk_swc_et2d;
VkRenderPass _rd_vk_swc_rdp;

VkImage *_rd_vk_swc_im_p;
VkImageView *_rd_vk_swc_imv_p;
VkFramebuffer *_rd_vk_swc_fbf_p;

uint8_t _rd_vk_swc_image;
uint8_t _rd_vk_swc_frame = 0;
uint8_t _rd_vk_swc_frame_buffer = 0;

//VkSurfaceTransformFlagBitsKHR m_vksurfacetransformflagbitskhr;

static uint32_t swapchain_image;

static VkImage vkimage_depth;
static VkImageView vkimageview_depth;
static VkDeviceMemory vkdevicememory_depth;

static VkImage vkimage_color;
static VkImageView vkimageview_color;
static VkDeviceMemory vkdevicememory_color;

void _rd_vk_swc_make(VkSharingMode vksharingmode)
{
	VkPhysicalDevice vkphysicaldevice = _rd_vkq_dv_pscdv_p[_rd_vk_device];
	VkDevice vkdevice = _rd_vkq_dv_p[_rd_vk_device];

	#ifdef _RD_VK_INFO_SC
		uint32_t surface_format;
		_DB_R2L("vkGetPhysicalDeviceSurfaceFormatsKHR %d", vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, _rd_vk_sf_khr, &surface_format, VK_NULL_HANDLE))
		VkSurfaceFormatKHR *vksurfaceformatkhr_p = malloc(surface_format * sizeof(VkSurfaceFormatKHR));
		_DB_R2L("vkGetPhysicalDeviceSurfaceFormatsKHR %d", vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, _rd_vk_sf_khr, &surface_format, vksurfaceformatkhr_p))
		for (uint32_t i = 0; i < surface_format; ++i)
		{
			VkSurfaceFormatKHR vksurfaceformatkhr = vksurfaceformatkhr_p[i];
			_DB_N2L("i %d", i)
			_DB_N2L("format %d", vksurfaceformatkhr.format)
			_DB_N2L("colorSpace %d", vksurfaceformatkhr.colorSpace)
		}

		free(vksurfaceformatkhr_p);

		uint32_t surface_present;
		_DB_R2L("vkGetPhysicalDeviceSurfacePresentModesKHR %d", vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, _rd_vk_sf_khr, &surface_present, VK_NULL_HANDLE))
		VkPresentModeKHR *vkpresentmodekhr_p = malloc(surface_present * sizeof(VkPresentModeKHR));
		_DB_R2L("vkGetPhysicalDeviceSurfacePresentModesKHR %d", vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, _rd_vk_sf_khr, &surface_present, vkpresentmodekhr_p))
		for (uint32_t i = 0; i < surface_present; ++i)
		{
			_DB_N2L("VkPresentModeKHR %d", vkpresentmodekhr_p[i])
		}
		free(vkpresentmodekhr_p);
	#endif

	VkSurfaceCapabilitiesKHR vksurfacecapabilitieskhr;
	_DB_R2L("vkGetPhysicalDeviceSurfaceCapabilitiesKHR %d", vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkphysicaldevice, _rd_vk_sf_khr, &vksurfacecapabilitieskhr))
	_DB_R2L("_vk_swc_image %d", _rd_vk_swc_image = vksurfacecapabilitieskhr.minImageCount)

//	m_vksurfacetransformflagbitskhr = vksurfacecapabilitieskhr.currentTransform;
//	if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR || m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
	if (vksurfacecapabilitieskhr.currentTransform == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR || vksurfacecapabilitieskhr.currentTransform == VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
	{
		_rd_vk_swc_et2d.width = _sf_height;
		_rd_vk_swc_et2d.height = _sf_width;
//		m_width = _rd_vk_swc_et2d.width;
//		m_height = _rd_vk_swc_et2d.height;
	}
	else
	{
		_rd_vk_swc_et2d.height = _sf_height;
		_rd_vk_swc_et2d.width = _sf_width;
	}

////	if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR)
////	{
////		_rd_vk_swc_et2d.height = 1;
////		_rd_vk_swc_et2d.width = 1;
////		m_width = _rd_vk_swc_et2d.width;
////		m_height = _rd_vk_swc_et2d.height;
////	}
////	else if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR)
////	{
////		_rd_vk_swc_et2d.height = 1;
////		_rd_vk_swc_et2d.width = 1;
////		m_width = _rd_vk_swc_et2d.width;
////		m_height = _rd_vk_swc_et2d.height;
////	}
//	else
//	{
//		_rd_vk_swc_et2d.height = m_height;
//		_rd_vk_swc_et2d.width = m_width;
//	}

	_DB_R2L
	(
		"vkCreateSwapchainKHR %d",
		vkCreateSwapchainKHR
		(
			vkdevice,
			&(VkSwapchainCreateInfoKHR)
			{
				.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
				.surface = _rd_vk_sf_khr,
				.minImageCount = vksurfacecapabilitieskhr.minImageCount,
				.imageFormat = _RD_VK_COLOR_FORMAT,
				.imageColorSpace = _RD_VK_COLOR_SPACE,
				.imageExtent = _rd_vk_swc_et2d,
				.imageArrayLayers = 1,
				.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

				.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
				.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
				.presentMode = _RD_VK_PRESENT,
				.clipped = VK_TRUE,

				.queueFamilyIndexCount = _rd_vkq_max_queue_surface_p[_rd_vk_device],
				.pQueueFamilyIndices = _rd_vkq_queue_surface_p[_rd_vk_device],

				.oldSwapchain = VK_NULL_HANDLE,

				.imageSharingMode = vksharingmode,

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&_rd_vk_swc_khr
		)
	)

	_DB_R2L("vkGetSwapchainImagesKHR %d", vkGetSwapchainImagesKHR(vkdevice, _rd_vk_swc_khr, &swapchain_image, VK_NULL_HANDLE))

	#ifdef _RD_VK_INFO_SC
		_DB_N2L("vksurfaceformatkhr_image %d", swapchain_image)
	#endif

	_rd_vk_swc_im_p = malloc(sizeof(VkImage) * swapchain_image);
	_rd_vk_swc_imv_p = malloc(sizeof(VkImageView) * swapchain_image);
	_rd_vk_swc_fbf_p = malloc(sizeof(VkFramebuffer) * swapchain_image);

	_DB_R2L("vkGetSwapchainImagesKHR %d", vkGetSwapchainImagesKHR(vkdevice, _rd_vk_swc_khr, &swapchain_image, _rd_vk_swc_im_p))

	_RD_VK_RDP_MAKE(_rd_vk_device, &_rd_vk_swc_rdp)

	_RD_VK_IM_MAKE
	(
		_rd_vk_device,
		_RD_VK_DEPTH_FORMAT,
		((VkExtent3D)
		{
			.width = _rd_vk_swc_et2d.width,
			.height = _rd_vk_swc_et2d.height,
			.depth = 1
		}),
		1,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		_RD_VK_SAMPLE_C,
		&vkimage_depth
	)
	VkMemoryRequirements vkmemoryrequirements;
	_RD_VK_IM_GEN(_rd_vk_device, vkimage_depth, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &vkdevicememory_depth, vkmemoryrequirements)
	_RD_VK_IMV_MAKE(_rd_vk_device, vkimage_depth, _RD_VK_DEPTH_FORMAT, VK_IMAGE_ASPECT_DEPTH_BIT, 1, &vkimageview_depth)

	_RD_VK_IM_MAKE
	(
		_rd_vk_device,
		_RD_VK_COLOR_FORMAT,
		((VkExtent3D)
		{
			.width = _rd_vk_swc_et2d.width,
			.height = _rd_vk_swc_et2d.height,
			.depth = 1
		}),
		1,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		_RD_VK_SAMPLE_C,
		&vkimage_color
	)
	_RD_VK_IM_GEN(_rd_vk_device, vkimage_color, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &vkdevicememory_color, vkmemoryrequirements)
	_RD_VK_IMV_MAKE(_rd_vk_device, vkimage_color, _RD_VK_COLOR_FORMAT, VK_IMAGE_ASPECT_COLOR_BIT, 1, &vkimageview_color)

	for (uint32_t i = 0; i < swapchain_image; ++i)
	{
		_RD_VK_IMV_MAKE(_rd_vk_device, _rd_vk_swc_im_p[i], _RD_VK_COLOR_FORMAT, VK_IMAGE_ASPECT_COLOR_BIT, 1, &_rd_vk_swc_imv_p[i])
		_RD_VK_FBF_MAKE
		(
			_rd_vk_device,
			((VkImageView[])
			{
				vkimageview_color,
				vkimageview_depth,
				_rd_vk_swc_imv_p[i]
			}),
			3,
			_rd_vk_swc_rdp,
			&_rd_vk_swc_fbf_p[i]
		)
	}
}

void _rd_vk_swc_free()
{
//	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[_rd_vk_device];
	VkDevice vkdevice = _rd_vkq_dv_p[_rd_vk_device];

	vkDestroyImageView(vkdevice, vkimageview_depth, VK_NULL_HANDLE);
	vkDestroyImage(vkdevice, vkimage_depth, VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, vkdevicememory_depth, VK_NULL_HANDLE);

	vkDestroyImageView(vkdevice, vkimageview_color, VK_NULL_HANDLE);
	vkDestroyImage(vkdevice, vkimage_color, VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, vkdevicememory_color, VK_NULL_HANDLE);

	for (uint32_t i = 0; i < swapchain_image; ++i)
	{
		vkDestroyFramebuffer(vkdevice, _rd_vk_swc_fbf_p[i], VK_NULL_HANDLE);
		vkDestroyImageView(vkdevice, _rd_vk_swc_imv_p[i], VK_NULL_HANDLE);
	}

	vkDestroyRenderPass(vkdevice, _rd_vk_swc_rdp, VK_NULL_HANDLE);
	_DB_N2L("->vkDestroySwapchainKHR");
	vkDestroySwapchainKHR(vkdevice, _rd_vk_swc_khr, VK_NULL_HANDLE);

	free(_rd_vk_swc_im_p);
	free(_rd_vk_swc_imv_p);
	free(_rd_vk_swc_fbf_p);
}
