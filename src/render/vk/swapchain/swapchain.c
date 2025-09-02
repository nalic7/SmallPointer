VkSwapchainKHR smpt_rd_vk_swc_khr;
VkExtent2D smpt_rd_vk_swc_et2d;
VkRenderPass smpt_rd_vk_swc_rdp;

VkImage *smpt_rd_vk_swc_im_p;
VkImageView *smpt_rd_vk_swc_imv_p;
VkFramebuffer *smpt_rd_vk_swc_fbf_p;

uint8_t smpt_rd_vk_swc_image;
uint8_t smpt_rd_vk_swc_frame = 0;
uint8_t smpt_rd_vk_swc_frame_buffer = 0;

//VkSurfaceTransformFlagBitsKHR m_vksurfacetransformflagbitskhr;

static uint32_t swapchain_image;

static VkImage vkimage_depth;
static VkImageView vkimageview_depth;
static VkDeviceMemory vkdevicememory_depth;

static VkImage vkimage_color;
static VkImageView vkimageview_color;
static VkDeviceMemory vkdevicememory_color;

void smpt_rd_vk_swc_make(VkSharingMode vksharingmode)
{
	VkPhysicalDevice vkphysicaldevice = smpt_rd_vkq_dv_pscdv_p[smpt_rd_vk_device];
	VkDevice vkdevice = smpt_rd_vkq_dv_p[smpt_rd_vk_device];

	#ifdef SMPT_RD_VK_INFO_SC
		uint32_t surface_format;
		SMPT_DB_R2L("vkGetPhysicalDeviceSurfaceFormatsKHR %d", vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, smpt_rd_vk_sf_khr, &surface_format, VK_NULL_HANDLE))
		VkSurfaceFormatKHR *vksurfaceformatkhr_p = malloc(surface_format * sizeof(VkSurfaceFormatKHR));
		SMPT_DB_R2L("vkGetPhysicalDeviceSurfaceFormatsKHR %d", vkGetPhysicalDeviceSurfaceFormatsKHR(vkphysicaldevice, smpt_rd_vk_sf_khr, &surface_format, vksurfaceformatkhr_p))
		for (uint32_t i = 0; i < surface_format; ++i)
		{
			VkSurfaceFormatKHR vksurfaceformatkhr = vksurfaceformatkhr_p[i];
			SMPT_DB_N2L("i %d", i)
			SMPT_DB_N2L("format %d", vksurfaceformatkhr.format)
			SMPT_DB_N2L("colorSpace %d", vksurfaceformatkhr.colorSpace)
		}

		free(vksurfaceformatkhr_p);

		uint32_t surface_present;
		SMPT_DB_R2L("vkGetPhysicalDeviceSurfacePresentModesKHR %d", vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, smpt_rd_vk_sf_khr, &surface_present, VK_NULL_HANDLE))
		VkPresentModeKHR *vkpresentmodekhr_p = malloc(surface_present * sizeof(VkPresentModeKHR));
		SMPT_DB_R2L("vkGetPhysicalDeviceSurfacePresentModesKHR %d", vkGetPhysicalDeviceSurfacePresentModesKHR(vkphysicaldevice, smpt_rd_vk_sf_khr, &surface_present, vkpresentmodekhr_p))
		for (uint32_t i = 0; i < surface_present; ++i)
		{
			SMPT_DB_N2L("VkPresentModeKHR %d", vkpresentmodekhr_p[i])
		}
		free(vkpresentmodekhr_p);
	#endif

	VkSurfaceCapabilitiesKHR vksurfacecapabilitieskhr;
	SMPT_DB_R2L("vkGetPhysicalDeviceSurfaceCapabilitiesKHR %d", vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkphysicaldevice, smpt_rd_vk_sf_khr, &vksurfacecapabilitieskhr))
	SMPT_DB_R2L("_vk_swc_image %d", smpt_rd_vk_swc_image = vksurfacecapabilitieskhr.minImageCount)

//	m_vksurfacetransformflagbitskhr = vksurfacecapabilitieskhr.currentTransform;
//	if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR || m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
	if (vksurfacecapabilitieskhr.currentTransform == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR || vksurfacecapabilitieskhr.currentTransform == VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR)
	{
		smpt_rd_vk_swc_et2d.width = _sf_height;
		smpt_rd_vk_swc_et2d.height = _sf_width;
//		m_width = smpt_rd_vk_swc_et2d.width;
//		m_height = smpt_rd_vk_swc_et2d.height;
	}
	else
	{
		smpt_rd_vk_swc_et2d.height = _sf_height;
		smpt_rd_vk_swc_et2d.width = _sf_width;
	}

////	if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR)
////	{
////		smpt_rd_vk_swc_et2d.height = 1;
////		smpt_rd_vk_swc_et2d.width = 1;
////		m_width = smpt_rd_vk_swc_et2d.width;
////		m_height = smpt_rd_vk_swc_et2d.height;
////	}
////	else if (m_vksurfacetransformflagbitskhr == VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR)
////	{
////		smpt_rd_vk_swc_et2d.height = 1;
////		smpt_rd_vk_swc_et2d.width = 1;
////		m_width = smpt_rd_vk_swc_et2d.width;
////		m_height = smpt_rd_vk_swc_et2d.height;
////	}
//	else
//	{
//		smpt_rd_vk_swc_et2d.height = m_height;
//		smpt_rd_vk_swc_et2d.width = m_width;
//	}

	SMPT_DB_R2L
	(
		"vkCreateSwapchainKHR %d",
		vkCreateSwapchainKHR
		(
			vkdevice,
			&(VkSwapchainCreateInfoKHR)
			{
				.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
				.surface = smpt_rd_vk_sf_khr,
				.minImageCount = vksurfacecapabilitieskhr.minImageCount,
				.imageFormat = SMPT_RD_VK_COLOR_FORMAT,
				.imageColorSpace = SMPT_RD_VK_COLOR_SPACE,
				.imageExtent = smpt_rd_vk_swc_et2d,
				.imageArrayLayers = 1,
				.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

				.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
				.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
				.presentMode = SMPT_RD_VK_PRESENT,
				.clipped = VK_TRUE,

				.queueFamilyIndexCount = smpt_rd_vkq_max_queue_surface_p[smpt_rd_vk_device],
				.pQueueFamilyIndices = smpt_rd_vkq_queue_surface_p[smpt_rd_vk_device],

				.oldSwapchain = VK_NULL_HANDLE,

				.imageSharingMode = vksharingmode,

				.flags = 0,
				.pNext = VK_NULL_HANDLE
			},
			VK_NULL_HANDLE,
			&smpt_rd_vk_swc_khr
		)
	)

	SMPT_DB_R2L("vkGetSwapchainImagesKHR %d", vkGetSwapchainImagesKHR(vkdevice, smpt_rd_vk_swc_khr, &swapchain_image, VK_NULL_HANDLE))

	#ifdef SMPT_RD_VK_INFO_SC
		SMPT_DB_N2L("vksurfaceformatkhr_image %d", swapchain_image)
	#endif

	smpt_rd_vk_swc_im_p = malloc(sizeof(VkImage) * swapchain_image);
	smpt_rd_vk_swc_imv_p = malloc(sizeof(VkImageView) * swapchain_image);
	smpt_rd_vk_swc_fbf_p = malloc(sizeof(VkFramebuffer) * swapchain_image);

	SMPT_DB_R2L("vkGetSwapchainImagesKHR %d", vkGetSwapchainImagesKHR(vkdevice, smpt_rd_vk_swc_khr, &swapchain_image, smpt_rd_vk_swc_im_p))

	SMPT_RD_VK_RDP_MAKE(smpt_rd_vk_device, &smpt_rd_vk_swc_rdp)

	SMPT_RD_VK_IM_MAKE
	(
		smpt_rd_vk_device,
		SMPT_RD_VK_DEPTH_FORMAT,
		((VkExtent3D)
		{
			.width = smpt_rd_vk_swc_et2d.width,
			.height = smpt_rd_vk_swc_et2d.height,
			.depth = 1
		}),
		1,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		SMPT_RD_VK_SAMPLE_C,
		&vkimage_depth
	)
	VkMemoryRequirements vkmemoryrequirements;
	SMPT_RD_VK_IM_GEN(smpt_rd_vk_device, vkimage_depth, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &vkdevicememory_depth, vkmemoryrequirements)
	SMPT_RD_VK_IMV_MAKE(smpt_rd_vk_device, vkimage_depth, SMPT_RD_VK_DEPTH_FORMAT, VK_IMAGE_ASPECT_DEPTH_BIT, 1, &vkimageview_depth)

	SMPT_RD_VK_IM_MAKE
	(
		smpt_rd_vk_device,
		SMPT_RD_VK_COLOR_FORMAT,
		((VkExtent3D)
		{
			.width = smpt_rd_vk_swc_et2d.width,
			.height = smpt_rd_vk_swc_et2d.height,
			.depth = 1
		}),
		1,
		VK_IMAGE_TILING_OPTIMAL,
		VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
		VK_IMAGE_LAYOUT_UNDEFINED,
		SMPT_RD_VK_SAMPLE_C,
		&vkimage_color
	)
	SMPT_RD_VK_IM_GEN(smpt_rd_vk_device, vkimage_color, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &vkdevicememory_color, vkmemoryrequirements)
	SMPT_RD_VK_IMV_MAKE(smpt_rd_vk_device, vkimage_color, SMPT_RD_VK_COLOR_FORMAT, VK_IMAGE_ASPECT_COLOR_BIT, 1, &vkimageview_color)

	for (uint32_t i = 0; i < swapchain_image; ++i)
	{
		SMPT_RD_VK_IMV_MAKE(smpt_rd_vk_device, smpt_rd_vk_swc_im_p[i], SMPT_RD_VK_COLOR_FORMAT, VK_IMAGE_ASPECT_COLOR_BIT, 1, &smpt_rd_vk_swc_imv_p[i])
		SMPT_RD_VK_FBF_MAKE
		(
			smpt_rd_vk_device,
			((VkImageView[])
			{
				vkimageview_color,
				vkimageview_depth,
				smpt_rd_vk_swc_imv_p[i]
			}),
			3,
			smpt_rd_vk_swc_rdp,
			&smpt_rd_vk_swc_fbf_p[i]
		)
	}
}

void smpt_rd_vk_swc_free()
{
//	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_p[smpt_rd_vk_device];
	VkDevice vkdevice = smpt_rd_vkq_dv_p[smpt_rd_vk_device];

	vkDestroyImageView(vkdevice, vkimageview_depth, VK_NULL_HANDLE);
	vkDestroyImage(vkdevice, vkimage_depth, VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, vkdevicememory_depth, VK_NULL_HANDLE);

	vkDestroyImageView(vkdevice, vkimageview_color, VK_NULL_HANDLE);
	vkDestroyImage(vkdevice, vkimage_color, VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, vkdevicememory_color, VK_NULL_HANDLE);

	for (uint32_t i = 0; i < swapchain_image; ++i)
	{
		vkDestroyFramebuffer(vkdevice, smpt_rd_vk_swc_fbf_p[i], VK_NULL_HANDLE);
		vkDestroyImageView(vkdevice, smpt_rd_vk_swc_imv_p[i], VK_NULL_HANDLE);
	}

	vkDestroyRenderPass(vkdevice, smpt_rd_vk_swc_rdp, VK_NULL_HANDLE);
	SMPT_DB_N2L("->vkDestroySwapchainKHR");
	vkDestroySwapchainKHR(vkdevice, smpt_rd_vk_swc_khr, VK_NULL_HANDLE);

	free(smpt_rd_vk_swc_im_p);
	free(smpt_rd_vk_swc_imv_p);
	free(smpt_rd_vk_swc_fbf_p);
}
