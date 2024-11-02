VkInstance m_vkinstance;

//D
uint32_t m_max_device;

VkPhysicalDevice *m_vkphysicaldevice_ptr;
unsigned char *m_max_graphics_ptr;
uint32_t **m_graphics_ptr;
VkQueue **m_vkqueue_graphics_ptr;

VkDevice *m_vkdevice_ptr;
//D

//S
VkSurfaceKHR m_vksurfacekhr;

VkSwapchainKHR *m_vkswapchainkhr_ptr;

VkSurfaceCapabilitiesKHR *m_vksurfacecapabilitieskhr_ptr;

VkSurfaceFormatKHR **m_vksurfaceformatkhr_ptr;
uint32_t *m_vkswapchainkhr_format_ptr;

VkPresentModeKHR **m_vkpresentmodekhr_ptr;
uint32_t *m_vkswapchainkhr_present_mode_ptr;

VkImage **m_vkswapchainkhr_vkimage_ptr;

VkFence *m_vkfence_ptr;
VkSemaphore ***m_vksemaphore_ptr;

VkCommandPool **m_vkcommandpool_ptr;
//S

uint32_t m_device = 0;
uint32_t m_graphic = 0;

VkDebugUtilsMessengerEXT m_vkdebugutilsmessengerext;
// // vk m_vk;

// // typedef struct
// // {
// //	 uint32_t queueFamilyIndex;
// //	 uint32_t presentFamily;
// //	 uint32_t computeFamily;
// //	 VkBool32 foundGraphics;
// //	 VkBool32 foundPresent;
// //	 VkBool32 foundCompute;
// // } QueueFamilyIndices;

// // QueueFamilyIndices find_queue_families(VkPhysicalDevice device, VkSurfaceKHR surface)
// // {
// //	 QueueFamilyIndices indices =
// //	 {
// //		 .queueFamilyIndex = -1,
// //		 .presentFamily = -1,
// //		 .computeFamily = -1,
// //		 .foundGraphics = VK_FALSE,
// //		 .foundPresent = VK_FALSE,
// //		 .foundCompute = VK_FALSE
// //	 };

// //	 uint32_t queueFamilyCount = 0;
// //	 vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, NULL);

// //	 VkQueueFamilyProperties *queueFamilies = malloc(sizeof(VkQueueFamilyProperties) * queueFamilyCount);
// //	 vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies);

// //	 for (uint32_t i = 0; i < queueFamilyCount; i++) {
// //		 if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
// //			 indices.queueFamilyIndex = i;
// //			 indices.foundGraphics = VK_TRUE;
// //		 }

// //		 VkBool32 presentSupport = VK_FALSE;
// //		 vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
// //		 if (presentSupport) {
// //			 indices.presentFamily = i;
// //			 indices.foundPresent = VK_TRUE;
// //		 }

// //		 if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
// //			 indices.computeFamily = i;
// //			 indices.foundCompute = VK_TRUE;
// //		 }

// //		 if (indices.foundGraphics && indices.foundPresent && indices.foundCompute) {
// //			 break;
// //		 }
// //	 }

// //	 free(queueFamilies);
// //	 return indices;
// // }

// VkCommandPool vkcommandpool;
// VkCommandBuffer *vkcommandbuffer_ptr;

// VkRenderPass vkrenderpass;
// VkFramebuffer vkframebuffer;

// // VkImageView color_vkimageview;
// // VkImageView depth_vkimageview;
// // VkImage color_vkimage;
// // VkImage depth_vkimage;
// // VkDeviceMemory color_vkdevicememory;
// // VkDeviceMemory depth_vkdevicememory;

// uint32_t imageIndex = 0;
// VkSemaphore imageAvailableSemaphore;
// VkSemaphore renderingCompleteSemaphore;

// uint32_t findMemoryType(vk *vk, uint32_t device, uint32_t typefilter, VkMemoryPropertyFlags vkmemorypropertyflags)
// {
//	 VkPhysicalDevice vkphysicaldevice = vk->vkphysicaldevice_ptr[device];
//	 VkPhysicalDeviceMemoryProperties vkphysicaldevicememoryproperties;
//	 vkGetPhysicalDeviceMemoryProperties(vkphysicaldevice, &vkphysicaldevicememoryproperties);

//	 for (uint32_t t = 0; t < vkphysicaldevicememoryproperties.memoryTypeCount; ++t)
//	 {
//		 if ((typefilter & (1 << t)) && (vkphysicaldevicememoryproperties.memoryTypes[t].propertyFlags & vkmemorypropertyflags) == vkmemorypropertyflags)
//		 {
//			 return t;
//		 }
//	 }

//	 error("No MemoryType!")

//	 return 0;
// }

// void createImage(vk *vk, uint32_t device, uint32_t width, uint32_t height, VkFormat vkformat, VkImageTiling vkimagetiling, VkImageUsageFlags vkimageusageflags, VkMemoryPropertyFlags vkmemorypropertyflags, VkImage *vkimage, VkDeviceMemory *vkdevicememory)
// {
//	 VkImageCreateInfo vkimagecreateinfo;
//	 vkimagecreateinfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
//	 vkimagecreateinfo.imageType = VK_IMAGE_TYPE_2D;
//	 vkimagecreateinfo.extent.width = width;
//	 vkimagecreateinfo.extent.height = height;
//	 vkimagecreateinfo.extent.depth = 1;
//	 vkimagecreateinfo.mipLevels = 1;
//	 vkimagecreateinfo.arrayLayers = 1;
//	 vkimagecreateinfo.format = vkformat;
//	 vkimagecreateinfo.tiling = vkimagetiling;
//	 vkimagecreateinfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//	 vkimagecreateinfo.usage = vkimageusageflags;
//	 vkimagecreateinfo.samples = VK_SAMPLE_COUNT_1_BIT;
//	 vkimagecreateinfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
//	 vkimagecreateinfo.flags = 0;
//	 vkimagecreateinfo.pNext = NULL;

//	 if (vkCreateImage(vk->vkdevice, &vkimagecreateinfo, NULL, vkimage) != VK_SUCCESS)
//	 {
//		 error("vkCreateImage")
//	 }

//	 VkMemoryRequirements vkmemoryrequirements;
//	 vkGetImageMemoryRequirements(vk->vkdevice, *vkimage, &vkmemoryrequirements);

//	 VkMemoryAllocateInfo vkmemoryallocateinfo;
//	 vkmemoryallocateinfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
//	 vkmemoryallocateinfo.allocationSize = vkmemoryrequirements.size;
//	 vkmemoryallocateinfo.memoryTypeIndex = findMemoryType(vk, device, vkmemoryrequirements.memoryTypeBits, vkmemorypropertyflags);
//	 vkmemoryallocateinfo.pNext = NULL;

//	 if (vkAllocateMemory(vk->vkdevice, &vkmemoryallocateinfo, NULL, vkdevicememory) != VK_SUCCESS)
//	 {
//		 error("vkAllocateMemory")
//	 }

//	 vkBindImageMemory(vk->vkdevice, *vkimage, *vkdevicememory, 0);
// }

// // VkImageView createImageViews(vk *vk, VkImage vkimage, VkFormat vkformat, VkImageAspectFlags vkimageaspectflags/* , VkComponentMapping vkcomponentmapping */)
// // {
// //	 VkImageView vkimageview;

// //	 VkImageViewCreateInfo vkimageviewcreateinfo;
// //	 vkimageviewcreateinfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
// //	 vkimageviewcreateinfo.image = vkimage;
// //	 vkimageviewcreateinfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
// //	 vkimageviewcreateinfo.format = vkformat;
// //	 vkimageviewcreateinfo.subresourceRange.aspectMask = vkimageaspectflags;
// //	 vkimageviewcreateinfo.subresourceRange.baseMipLevel = 0;
// //	 vkimageviewcreateinfo.subresourceRange.levelCount = 1;
// //	 vkimageviewcreateinfo.subresourceRange.baseArrayLayer = 0;
// //	 vkimageviewcreateinfo.subresourceRange.layerCount = 1;
// //	 vkimageviewcreateinfo.pNext = NULL;
// //	 vkimageviewcreateinfo.flags = 0;
// //	 // vkimageviewcreateinfo.components = vkcomponentmapping;
// //	 vkimageviewcreateinfo.components.r = VK_COMPONENT_SWIZZLE_R;
// //	 vkimageviewcreateinfo.components.g = VK_COMPONENT_SWIZZLE_G;
// //	 vkimageviewcreateinfo.components.b = VK_COMPONENT_SWIZZLE_B;
// //	 vkimageviewcreateinfo.components.a = VK_COMPONENT_SWIZZLE_A;

// //	 if (vkCreateImageView(vk->vkdevice, &vkimageviewcreateinfo, NULL, &vkimageview) != VK_SUCCESS)
// //	 {
// //		 error("vkCreateImageView")
// //	 }

// //	 return vkimageview;
// // }

// VkFormat findSupportedFormat(vk *vk, uint32_t device, VkFormat vkformatvector[], uint32_t vkformatvector_size, VkImageTiling vkimagetiling, VkFormatFeatureFlags vkformatfeatureflags)
// {
//	 VkFormat vkformatfromvector;
//	 for (uint32_t i = 0; i < vkformatvector_size; ++i)
//	 {
//		 vkformatfromvector = vkformatvector[i];
//		 VkFormatProperties vkformatproperties;

//		 vkGetPhysicalDeviceFormatProperties(vk->vkphysicaldevice_ptr[device], vkformatfromvector, &vkformatproperties);

//		 if (vkimagetiling == VK_IMAGE_TILING_LINEAR && (vkformatproperties.linearTilingFeatures & vkformatfeatureflags) == vkformatfeatureflags)
//		 {
//			 return vkformatfromvector;
//		 }
//		 else if (vkimagetiling == VK_IMAGE_TILING_OPTIMAL && (vkformatproperties.optimalTilingFeatures & vkformatfeatureflags) == vkformatfeatureflags)
//		 {
//			 return vkformatfromvector;
//		 }
//	 }

//	 error("No SupportedFormat!")

//	 return vkformatfromvector;
// }

// VkFormat findDepthFormat(vk *vk, uint32_t device)
// {
//	 VkFormat vkformat[] = { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT };
//	 return findSupportedFormat(vk, device, vkformat, 3, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
// }

// void createFramebuffers(vk *vk, uint32_t device)
// {
//	 info("run_createFramebuffers")
//	 VkFormat depth_vkformat = findDepthFormat(vk, device);
//	 // info("run_createImage")
//	 // createImage(vk, 0, m_width, m_height, depth_vkformat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &depth_vkimage, &depth_vkdevicememory);
//	 info("run_createImageViews")
//	 // VkComponentMapping color_vkcomponentmapping =
//	 // {
//	 //	 VK_COMPONENT_SWIZZLE_R,
//	 //	 VK_COMPONENT_SWIZZLE_G,
//	 //	 VK_COMPONENT_SWIZZLE_B,
//	 //	 VK_COMPONENT_SWIZZLE_A
//	 // };
//	 // VkComponentMapping depth_vkcomponentmapping =
//	 // {
//	 //	 VK_COMPONENT_SWIZZLE_ONE,
//	 //	 VK_COMPONENT_SWIZZLE_ONE,
//	 //	 VK_COMPONENT_SWIZZLE_ONE,
//	 //	 VK_COMPONENT_SWIZZLE_ONE
//	 // };
//	 color_vkimageview = createImageViews(vk, vk->vkswapchainkhr_vkimage_ptr[0], vk->vkswapchainkhr_vkformat, VK_IMAGE_ASPECT_COLOR_BIT/* , color_vkcomponentmapping */);
//	 depth_vkimageview = createImageViews(vk, depth_vkimage, depth_vkformat, VK_IMAGE_ASPECT_DEPTH_BIT/* , depth_vkcomponentmapping */);
//	 // vulkanstructure.vulkanbufferframestructure.vkframebuffer_vector.resize(vulkanstructure.vulkanbufferframestructure.vkimageview_vector.size());

//	 // for (size_t t = 0; t < vulkanstructure.vulkanbufferframestructure.vkimageview_vector.size(); ++t)
//	 // {
//	 VkImageView vkimageview[] =
//	 {
//		 color_vkimageview,
//		 depth_vkimageview
//	 };
//	 VkFramebufferCreateInfo vkframebuffercreateinfo;
//	 vkframebuffercreateinfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
//	 vkframebuffercreateinfo.renderPass = vkrenderpass;
//	 vkframebuffercreateinfo.attachmentCount = 2;
//	 vkframebuffercreateinfo.pAttachments = vkimageview;
//	 vkframebuffercreateinfo.width = m_width;
//	 vkframebuffercreateinfo.height = m_height;
//	 vkframebuffercreateinfo.layers = 1;
//	 vkframebuffercreateinfo.pNext = NULL;
//	 vkframebuffercreateinfo.flags = 0;

//	 info("run_vkCreateFramebuffer")
//	 if (vkCreateFramebuffer(vk->vkdevice, &vkframebuffercreateinfo, 0, &vkframebuffer) != VK_SUCCESS)
//	 {
//		 error("vkCreateFramebuffer")
//	 }
//	 // }
// }

// void createRenderPass(vk *vk, uint32_t device)
// {
//	 info("run_createRenderPass")
//	 VkAttachmentDescription color_vkattachmentdescription;
//	 color_vkattachmentdescription.format = vk->vkswapchainkhr_vkformat;
//	 color_vkattachmentdescription.samples = VK_SAMPLE_COUNT_1_BIT;
//	 color_vkattachmentdescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//	 color_vkattachmentdescription.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
//	 color_vkattachmentdescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//	 color_vkattachmentdescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//	 color_vkattachmentdescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//	 color_vkattachmentdescription.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
//	 color_vkattachmentdescription.flags = 0;

//	 VkAttachmentDescription depthvkattachmentdescription;
//	 depthvkattachmentdescription.format = findDepthFormat(vk, device);
//	 depthvkattachmentdescription.samples = VK_SAMPLE_COUNT_1_BIT;
//	 depthvkattachmentdescription.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//	 depthvkattachmentdescription.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//	 depthvkattachmentdescription.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//	 depthvkattachmentdescription.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//	 depthvkattachmentdescription.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//	 depthvkattachmentdescription.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
//	 depthvkattachmentdescription.flags = 0;

//	 VkAttachmentReference vkattachmentreference;
//	 vkattachmentreference.attachment = 0;
//	 vkattachmentreference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

//	 VkAttachmentReference depthvkattachmentreference;
//	 depthvkattachmentreference.attachment = 1;
//	 depthvkattachmentreference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
//	 // depthvkattachmentreference.layout = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;

//	 VkSubpassDescription vksubpassdescription;
//	 vksubpassdescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
//	 vksubpassdescription.inputAttachmentCount = 0;
//	 vksubpassdescription.preserveAttachmentCount = 0;
//	 vksubpassdescription.pResolveAttachments = NULL;
//	 vksubpassdescription.colorAttachmentCount = 1;
//	 vksubpassdescription.pColorAttachments = &vkattachmentreference;
//	 vksubpassdescription.pDepthStencilAttachment = &depthvkattachmentreference;
//	 vksubpassdescription.flags = 0;

//	 VkSubpassDependency vksubpassdependency;
//	 vksubpassdependency.srcSubpass = VK_SUBPASS_EXTERNAL;
//	 vksubpassdependency.dstSubpass = 0;
//	 vksubpassdependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
//	 vksubpassdependency.srcAccessMask = 0;
//	 vksubpassdependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
//	 vksubpassdependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
//	 vksubpassdependency.dependencyFlags = 0;

//	 VkAttachmentDescription vkattachmentdescription[] =
//	 {
//		 color_vkattachmentdescription,
//		 depthvkattachmentdescription
//	 };
//	 // VkAttachmentDescription *vkattachmentdescription_ptr = malloc(2 * sizeof(VkAttachmentDescription));
//	 // vkattachmentdescription_ptr[0] = color_vkattachmentdescription;
//	 // vkattachmentdescription_ptr[1] = depthvkattachmentdescription;

//	 VkRenderPassCreateInfo vkrenderpasscreateinfo;
//	 vkrenderpasscreateinfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
//	 vkrenderpasscreateinfo.attachmentCount = 2;
//	 vkrenderpasscreateinfo.pAttachments = vkattachmentdescription;
//	 vkrenderpasscreateinfo.subpassCount = 1;
//	 vkrenderpasscreateinfo.pSubpasses = &vksubpassdescription;
//	 vkrenderpasscreateinfo.dependencyCount = 1;
//	 vkrenderpasscreateinfo.pDependencies = &vksubpassdependency;
//	 // vkrenderpasscreateinfo.flags = VK_RENDER_PASS_CREATE_TRANSFORM_BIT_QCOM;
//	 vkrenderpasscreateinfo.flags = 0;
//	 vkrenderpasscreateinfo.pNext = NULL;

//	 if (vkCreateRenderPass(vk->vkdevice, &vkrenderpasscreateinfo, NULL, &vkrenderpass) != VK_SUCCESS)
//	 {
//		 error("vkCreateRenderPass")
//	 }
// }

int vk_loop(void *arg)
{
	// uint32_t d = 0;

	// VkDevice device = m_vk.vkdevice;
	// VkQueue queue = m_vk.vkqueue_graphics_ptr[d][0];
	// VkSwapchainKHR swapchain = m_vk.vkswapchainkhr;

	// vkcommandbuffer_ptr = malloc(sizeof(VkCommandBuffer));

	// // uint32_t device = 0;
	// VkCommandPoolCreateInfo vkcommandpoolcreateinfo;
	// vkcommandpoolcreateinfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	// vkcommandpoolcreateinfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	// vkcommandpoolcreateinfo.queueFamilyIndex = m_vk.graphics_ptr[d][0];
	// vkcommandpoolcreateinfo.pNext = NULL;

	// if (vkCreateCommandPool(m_vk.vkdevice, &vkcommandpoolcreateinfo, NULL, &vkcommandpool) != VK_SUCCESS)
	// {
	//	 error("vkCreateCommandPool")
	// }

	// VkCommandBufferAllocateInfo vkcommandbufferallocateinfo;
	// vkcommandbufferallocateinfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	// vkcommandbufferallocateinfo.commandPool = vkcommandpool;
	// vkcommandbufferallocateinfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	// vkcommandbufferallocateinfo.commandBufferCount = 1;
	// vkcommandbufferallocateinfo.pNext = NULL;

	// if (vkAllocateCommandBuffers(m_vk.vkdevice, &vkcommandbufferallocateinfo, vkcommandbuffer_ptr) != VK_SUCCESS)
	// {
	//	 error("vkAllocateCommandBuffers")
	// }

	// // VkCommandBufferBeginInfo vkcommandbufferbegininfo;
	// // vkcommandbufferbegininfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	// // //vkcommandbufferbegininfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

	// // if (vkBeginCommandBuffer(vkcommandbuffer_ptr[0], &vkcommandbufferbegininfo) != VK_SUCCESS)
	// // {
	// //	 error("vkBeginCommandBuffer");
	// // }

	// info("run_VkSemaphoreCreateInfo")
	// createRenderPass(&m_vk, d);
	// createFramebuffers(&m_vk, d);

	// // Define the semaphore creation information
	// VkSemaphoreCreateInfo semaphoreCreateInfo;
	// semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	// semaphoreCreateInfo.pNext = NULL; // Optional, should be NULL if no extensions are used
	// semaphoreCreateInfo.flags = 0; // Reserved for future use, must be 0

	// // Create the semaphore
	// VkResult result = vkCreateSemaphore(m_vk.vkdevice, &semaphoreCreateInfo, NULL, &imageAvailableSemaphore);
	// if (result != VK_SUCCESS)
	// {
	//	 error("Failed to create semaphore!")
	// }

	// result = vkCreateSemaphore(m_vk.vkdevice, &semaphoreCreateInfo, NULL, &renderingCompleteSemaphore);
	// if (result != VK_SUCCESS)
	// {
	//	 error("Failed to create semaphore!")
	// }

	// // uint32_t pImageIndices = 0;
	// // result = vkAcquireNextImageKHR(m_vk.vkdevice, m_vk.vkswapchainkhr, UINT64_MAX, vksemaphore, VK_NULL_HANDLE, &imageIndex);
	// // info("run_VkPresentInfoKHR")
	// // // Fill in the VkPresentInfoKHR structure
	// // VkPresentInfoKHR presentInfo;
	// // presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	// // presentInfo.pNext = NULL; // No extensions
	// // presentInfo.waitSemaphoreCount = 1; // Number of semaphores to wait for
	// // presentInfo.pWaitSemaphores = &vksemaphore; // Semaphore to wait for before presenting
	// // presentInfo.swapchainCount = 1; // Number of swapchains to present to
	// // presentInfo.pSwapchains = &m_vk.vkswapchainkhr; // The swapchain to present to
	// // presentInfo.pImageIndices = &imageIndex; // The index of the swapchain image to present
	// // // presentInfo.pImageIndices = &pImageIndices;
	// // presentInfo.pResults = NULL; // Optional, can be used to get results for each swapchain

	// // // Call vkQueuePresentKHR with a valid pPresentInfo pointer
	// // result = vkQueuePresentKHR(*m_vk.vkqueue_graphics_ptr[0], &presentInfo);
	// // if (result != VK_SUCCESS)
	// // {
	// //	 // Handle the error appropriately
	// //	 error("Failed to present swapchain image!")
	// // }

	// // Command buffer and rendering setup should be done here.
	// // Example code for simplicity, assumes valid command buffer setup.

	// // Start recording commands
	// VkCommandBuffer commandBuffer = vkcommandbuffer_ptr[0]; // Initialize commandBuffer

	// VkClearValue clearValue[] =
	// {
	//	 {
	//		 .color =
	//		 {
	//			 1.0F, 0.0F, 0.0F, 1.0F
	//		 }
	//	 },
	//	 {
	//		 .depthStencil =
	//		 {
	//			 .depth = 1.0F,
	//			 .stencil = 0
	//		 },
	//	 }
	// };

	// VkCommandBufferBeginInfo vkcommandbufferbegininfo;
	// vkcommandbufferbegininfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	// // vkcommandbufferbegininfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	// vkcommandbufferbegininfo.flags = 0;
	// vkcommandbufferbegininfo.pNext = NULL;

	// VkRenderPassBeginInfo renderPassInfo =
	// {
	//	 .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
	//	 .renderArea.extent.width = m_width,
	//	 .renderArea.extent.height = m_height,
	//	 .renderArea.offset = {0, 0},
	//	 .pClearValues = clearValue,
	//	 .clearValueCount = 2,
	//	 .renderPass = vkrenderpass,
	//	 .framebuffer = vkframebuffer,
	//	 .pNext = NULL
	// };

	// info("run_VkFenceCreateInfo")
	// VkFenceCreateInfo fenceInfo;
	// fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	// fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	// fenceInfo.pNext = NULL;

	// // VkFenceCreateInfo fenceInfo2;
	// // fenceInfo2.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	// // fenceInfo2.flags = VK_FENCE_CREATE_SIGNALED_BIT;
	// // fenceInfo2.pNext = NULL;

	// VkFence renderFence;
	// // VkFence imageFence;
	// vkCreateFence(device, &fenceInfo, NULL, &renderFence);
	// // vkCreateFence(device, &fenceInfo2, NULL, &imageFence);

	// VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };

	// // int ttt = 2;
	// // while (ttt--)
	while (1)
	{
		// // info("run_vk_loop")
		// // int aresult = wl_display_dispatch(m_wl_display);
		// // if (aresult < 0)
		// // {
		// //	 error("wl_display_dispatch")
		// // }
		// result = vkWaitForFences(device, 1, &renderFence, VK_TRUE, UINT64_MAX);
		// result = vkResetFences(device, 1, &renderFence);
		// // result = vkResetFences(device, 1, &imageFence);

		// // result = vkAcquireNextImageKHR(m_vk.vkdevice, swapchain, UINT64_MAX, imageAvailableSemaphore, imageFence, &imageIndex);
		// // result = vkWaitForFences(device, 1, &imageFence, VK_TRUE, UINT64_MAX);
		// result = vkAcquireNextImageKHR(m_vk.vkdevice, swapchain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
		// if (result != VK_SUCCESS)
		// {
		//	 error("vkAcquireNextImageKHR")
		// }

		// // if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
		// // {

		// // }

		// // info("run_command")
		// // vkResetCommandBuffer(commandBuffer, 0);
		// vkBeginCommandBuffer(commandBuffer, &vkcommandbufferbegininfo);

		// VkImageMemoryBarrier barrier;
		// barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		// barrier.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;//VK_ACCESS_TRANSFER_WRITE_BIT
		// barrier.dstAccessMask = VK_ACCESS_MEMORY_WRITE_BIT;//VK_ACCESS_SHADER_READ_BIT
		// barrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;//VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL
		// barrier.newLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;//VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL
		// barrier.image = m_vk.vkswapchainkhr_vkimage_ptr[imageIndex];
		// barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		// barrier.subresourceRange.baseMipLevel = 0;
		// barrier.subresourceRange.levelCount = 1;
		// barrier.subresourceRange.baseArrayLayer = 0;
		// barrier.subresourceRange.layerCount = 1;

		// // barrier.oldLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL; // or whatever layout you used for rendering
		// barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		// barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

		// vkCmdPipelineBarrier
		// (
		//	 commandBuffer,
		//	 VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,//VK_PIPELINE_STAGE_TRANSFER_BIT
		//	 VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,//VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
		//	 0,
		//	 0, NULL,
		//	 0, NULL,
		//	 1, &barrier
		// );

		// vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		// // vkCmdClearColorImage(commandBuffer, colorImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clearColor, 1, &colorAttachmentRange);
		// // vkCmdClearAttachments(commandBuffer, 2, clearValue, 1, &rect);
		// vkCmdEndRenderPass(commandBuffer);
		// vkEndCommandBuffer(commandBuffer);

		// // info("run_draw")
		// // info("run_VkSubmitInfo")
		// VkSubmitInfo submitInfo;
		// submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		// submitInfo.commandBufferCount = 1;
		// submitInfo.pCommandBuffers = &commandBuffer;
		// submitInfo.pNext = NULL;
		// // submitInfo.waitSemaphoreCount = 0;
		// // submitInfo.signalSemaphoreCount = 0;
		// submitInfo.pWaitDstStageMask = waitStages;
		// submitInfo.signalSemaphoreCount = 1;
		// submitInfo.pSignalSemaphores = &renderingCompleteSemaphore;
		// submitInfo.waitSemaphoreCount = 1;
		// submitInfo.pWaitSemaphores = &imageAvailableSemaphore;

		// // if (!queue)
		// // {
		// //	 error("queue")
		// // }

		// // info("run_submit")
		// result = vkQueueSubmit(queue, 1, &submitInfo, renderFence);
		// // result = vkQueueSubmit(queue, 1, &submitInfo, NULL);
		// if (result != VK_SUCCESS)
		// {
		//	 // Handle the error appropriately
		//	 error("vkQueueSubmit")
		// }

		// // info("run_VkPresentInfoKHR")
		// // Fill in the VkPresentInfoKHR structure
		// VkPresentInfoKHR presentInfo;
		// presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		// presentInfo.pNext = NULL; // No extensions
		// presentInfo.waitSemaphoreCount = 1; // Number of semaphores to wait for
		// presentInfo.pWaitSemaphores = &renderingCompleteSemaphore; // Semaphore to wait for before presenting
		// presentInfo.swapchainCount = 1; // Number of swapchains to present to
		// presentInfo.pSwapchains = &swapchain; // The swapchain to present to
		// presentInfo.pImageIndices = &imageIndex; // The index of the swapchain image to present
		// // presentInfo.pImageIndices = &pImageIndices;
		// presentInfo.pResults = NULL; // Optional, can be used to get results for each swapchain

		// result = vkQueueWaitIdle(queue);
		// if (result != VK_SUCCESS)
		// {
		//	 error("vkQueueWaitIdle")
		// }

		// // // info("wait_fences")
		// // result = vkWaitForFences(device, 1, &renderFence, VK_TRUE, UINT64_MAX);
		// // if (result != VK_SUCCESS)
		// // {
		// //	 // Handle the error appropriately
		// //	 error("vkWaitForFences")
		// // }
		// // // Reset the fence if you plan to reuse it
		// // result = vkResetFences(device, 1, &renderFence);
		// // if (result != VK_SUCCESS)
		// // {
		// //	 // Handle the error appropriately
		// //	 error("vkResetFences")
		// // }

		// // vkWaitForFences(device, 1, &imageFence, VK_TRUE, UINT64_MAX);
		// // vkResetFences(device, 1, &imageFence);

		// // Call vkQueuePresentKHR with a valid pPresentInfo pointer
		// result = vkQueuePresentKHR(queue, &presentInfo);
		// if (result != VK_SUCCESS)
		// {
		//	 // Handle the error appropriately
		//	 error("Failed to present swapchain image!")
		// }

		// // if (wl_display_flush(m_wl_display) < 0)
		// // {
		// //	 error("wl_display_flush");
		// // }

		// // int event = wl_display_read_events(m_wl_display);
		struct timespec ts = {5, 0}; // 5 second
		thrd_sleep(&ts, NULL);
	}

	// while (1)
	// {
	//	 VkSubmitInfo submitInfo;
	//	 submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	//	 submitInfo.commandBufferCount = 1;
	//	 submitInfo.pCommandBuffers = &commandBuffer;
	//	 submitInfo.pNext = NULL;
	//	 submitInfo.pWaitDstStageMask = waitStages;
	//	 submitInfo.signalSemaphoreCount = 1;
	//	 submitInfo.pSignalSemaphores = &renderingCompleteSemaphore;
	//	 submitInfo.waitSemaphoreCount = 1;
	//	 submitInfo.pWaitSemaphores = &imageAvailableSemaphore;

	//	 result = vkQueueSubmit(queue, 1, &submitInfo, NULL);
	//	 if (result != VK_SUCCESS)
	//	 {
	//		 error("vkQueueSubmit")
	//	 }

	//	 VkPresentInfoKHR presentInfo;
	//	 presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	//	 presentInfo.pNext = NULL; // No extensions
	//	 presentInfo.waitSemaphoreCount = 1; // Number of semaphores to wait for
	//	 presentInfo.pWaitSemaphores = &renderingCompleteSemaphore; // Semaphore to wait for before presenting
	//	 presentInfo.swapchainCount = 1; // Number of swapchains to present to
	//	 presentInfo.pSwapchains = &swapchain; // The swapchain to present to
	//	 presentInfo.pImageIndices = &imageIndex; // The index of the swapchain image to present
	//	 presentInfo.pResults = NULL; // Optional, can be used to get results for each swapchain

	//	 result = vkQueuePresentKHR(queue, &presentInfo);
	//	 if (result != VK_SUCCESS)
	//	 {
	//		 error("Failed to present swapchain image!")
	//	 }

	//	 vkQueueWaitIdle(queue);
	// }

	return 0;
}

void checkE(uint32_t d)
{
	VkPhysicalDevice vkphysicaldevice = m_vkphysicaldevice_ptr[d];

	uint32_t extensions = 0;
	vkEnumerateDeviceExtensionProperties(vkphysicaldevice, VK_NULL_HANDLE, &extensions, VK_NULL_HANDLE);

	VkExtensionProperties *vkextensionproperties_ptr = malloc(extensions * sizeof(VkExtensionProperties));
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

void vk_init()
{
	vk_makeInstance();
	vk_makeSurface();
	vk_makeDebug();
	vk_makePhysicalDevice();

	m_vkdevice_ptr = malloc(sizeof(VkDevice) * m_max_device);

	m_vkswapchainkhr_ptr = malloc(sizeof(VkSwapchainKHR) * m_max_device);
	m_vkswapchainkhr_vkimage_ptr = malloc(sizeof(VkImage *) * m_max_device);
	m_vksurfacecapabilitieskhr_ptr = malloc(sizeof(VkSurfaceCapabilitiesKHR) * m_max_device);
	m_vkswapchainkhr_format_ptr = malloc(sizeof(uint32_t) * m_max_device);
	m_vkswapchainkhr_present_mode_ptr = malloc(sizeof(uint32_t) * m_max_device);
	m_vksurfaceformatkhr_ptr = malloc(sizeof(VkSurfaceFormatKHR *) * m_max_device);
	m_vkpresentmodekhr_ptr = malloc(sizeof(VkPresentModeKHR *) * m_max_device);

	m_vkfence_ptr = malloc(sizeof(VkFence) * m_max_device);
	m_vksemaphore_ptr = malloc(sizeof(VkSemaphore *) * m_max_device);

	m_vkcommandpool_ptr = malloc(sizeof(VkCommandPool *) * m_max_device);

	for (uint32_t d = 0; d < m_max_device; ++d)
	{
		info("device %d", d)
		checkE(d);

		m_graphics_ptr[d] = malloc(sizeof(uint32_t));

		vk_makeQueue(d);
		vk_makeDevice(d);
		vk_makeSwapchain(d);
		vk_makeFence(d);

		unsigned char max_graphics = m_max_graphics_ptr[d];

		m_vksemaphore_ptr[d] = malloc(sizeof(VkSemaphore **) * max_graphics);

		m_vkcommandpool_ptr[d] = malloc(sizeof(VkCommandPool) * max_graphics);

		for (unsigned char g = 0; g < max_graphics; ++g)
		{
			m_vksemaphore_ptr[d][g] = malloc(sizeof(VkSemaphore) * 2);

			vk_makeSemaphore(d, g);
			vk_makeCommandPool(d, g);
		}
	}

	thrd_t thread;
	int result = thrd_create(&thread, vk_loop, NULL);
	if (result != thrd_success)
	{
		error("thrd_create")
	}

	// uint32_t device = 0;
	// //count device
	// uint32_t device_count = 0;
	// result = vkEnumeratePhysicalDevices(vk->vkinstance, &device_count, NULL);
	// if (result != VK_SUCCESS || device_count == 0)
	// {
	//	 error("vkEnumeratePhysicalDevices0")
	// }

	// VkPhysicalDevice *all_vkphysicaldevice = malloc(sizeof(VkPhysicalDevice) * device_count);
	// result = vkEnumeratePhysicalDevices(vk->vkinstance, &device_count, all_vkphysicaldevice);
	// if (result != VK_SUCCESS)
	// {
	//	 error("vkEnumeratePhysicalDevices1")
	// }
	// //count device.

	// //select device
	// VkPhysicalDevice chosen_vkphysicaldevice = VK_NULL_HANDLE;

	// for (uint32_t i = 0; i < device_count; ++i)
	// {
	//	 VkPhysicalDeviceProperties vkphysicaldeviceproperties;
	//	 vkGetPhysicalDeviceProperties(all_vkphysicaldevice[i], &vkphysicaldeviceproperties);

	//	 VkPhysicalDeviceFeatures vkphysicaldevicefeatures;
	//	 vkGetPhysicalDeviceFeatures(all_vkphysicaldevice[i], &vkphysicaldevicefeatures);

	//	 // Check if device supports required extensions and features
	//	 // Example check for Vulkan Wayland extension
	//	 uint32_t extension_count = 0;
	//	 vkEnumerateDeviceExtensionProperties(all_vkphysicaldevice[i], NULL, &extension_count, NULL);

	//	 VkExtensionProperties *vkextensionproperties = malloc(extension_count * sizeof(VkExtensionProperties));
	//	 vkEnumerateDeviceExtensionProperties(all_vkphysicaldevice[i], NULL, &extension_count, vkextensionproperties);

	//	 char supports_wayland = 0;
	//	 for (uint32_t j = 0; j < extension_count; ++j)
	//	 {
	//		 if (strcmp(vkextensionproperties[j].extensionName, VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME) == 0)
	//		 {
	//			 supports_wayland = 1;
	//			 break;
	//		 }
	//	 }

	//	 free(vkextensionproperties);

	//	 if (supports_wayland)
	//	 {
	//		 chosen_vkphysicaldevice = all_vkphysicaldevice[i];
	//		 break;
	//	 }
	// }

	// if (chosen_vkphysicaldevice == VK_NULL_HANDLE)
	// {
	//	 error("VKPHYSICALDEVICE_NULL")

	//	 info("VKPHYSICALDEVICE_1")
	//	 chosen_vkphysicaldevice = all_vkphysicaldevice[1];
	// }
	// //select device.

	// free(all_vkphysicaldevice);

	// QueueFamilyIndices queuefamilyindices = find_queue_families(chosen_vkphysicaldevice, vk->vksurfacekhr);

	// //create device
	// float queue_priority = 1.0f;
	// VkDeviceQueueCreateInfo vkdevicequeuecreateinfo =
	// {
	//	 .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
	//	 .queueFamilyIndex = queuefamilyindices.queueFamilyIndex,
	//	 .queueCount = 1,
	//	 .pQueuePriorities = &queue_priority
	// };

	// VkPhysicalDeviceFeatures vkphysicaldevicefeatures = {};
	// VkDeviceCreateInfo vkdevicecreateinfo =
	// {
	//	 .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
	//	 .queueCreateInfoCount = 1,
	//	 .pQueueCreateInfos = &vkdevicequeuecreateinfo,
	//	 .pEnabledFeatures = &vkphysicaldevicefeatures,
	//	 .enabledExtensionCount = sizeof(ppEnabledExtensionNames) / sizeof(ppEnabledExtensionNames[0]),
	//	 .ppEnabledExtensionNames = ppEnabledExtensionNames
	// };

	// result = vkCreateDevice(chosen_vkphysicaldevice, &vkdevicecreateinfo, NULL, &vk->vkdevice);
	// if (result != VK_SUCCESS)
	// {
	//	 error("vkCreateDevice")
	// }
	// //create device.

	// VkSwapchainCreateInfoKHR vkswapchaincreateinfokhr =
	// {
	//	 .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
	//	 .surface = vk->vksurfacekhr,
	//	 .minImageCount = 2,
	//	 .imageFormat = VK_FORMAT_B8G8R8A8_SRGB,
	//	 .imageExtent.width = 1920,
	//	 .imageExtent.height = 1080,
	//	 .imageArrayLayers = 1,
	//	 .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
	//	 .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
	//	 .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
	//	 .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
	//	 .clipped = VK_TRUE,
	//	 .presentMode = VK_PRESENT_MODE_FIFO_KHR
	// };

	// result = vkCreateSwapchainKHR(vk->vkdevice, &vkswapchaincreateinfokhr, NULL, &vk->vkswapchainkhr);
	// if (result != VK_SUCCESS)
	// {
	//	 error("vkCreateSwapchainKHR")
	// }
}

// // Function to cleanup Vulkan resources
// void cleanup(VkDevice device, VkSwapchainKHR swapchain) {
//	 vkDestroySwapchainKHR(device, swapchain, NULL);
//	 vkDestroyDevice(device, NULL);
// }

// // Function to setup Vulkan with a new GPU
// VkDevice create_device(VkPhysicalDevice physical_device, QueueFamilyIndices queue_family_indices) {
//	 VkDeviceCreateInfo device_create_info = {};
//	 device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

//	 VkDeviceQueueCreateInfo queue_create_info = {};
//	 queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//	 queue_create_info.queueFamilyIndex = queue_family_indices.queueFamilyIndex;
//	 queue_create_info.queueCount = 1;
//	 float queue_priority = 1.0f;
//	 queue_create_info.pQueuePriorities = &queue_priority;

//	 device_create_info.queueCreateInfoCount = 1;
//	 device_create_info.pQueueCreateInfos = &queue_create_info;

//	 VkPhysicalDeviceFeatures device_features = {};
//	 device_create_info.pEnabledFeatures = &device_features;

//	 VkDevice device;
//	 vkCreateDevice(physical_device, &device_create_info, NULL, &device);
//	 return device;
// }

// // Example of switching GPUs
// void switch_gpu(VkPhysicalDevice new_physical_device) {
//	 // Cleanup resources from the old GPU
//	 cleanup(current_device, current_swapchain);

//	 // Create new device with the new GPU
//	 QueueFamilyIndices queue_family_indices = find_queue_families(new_physical_device);

//	 if (queue_family_indices.foundGraphics) {
//		 info("Graphics queue family index: %d", queue_family_indices.graphicsFamily)
//	 }
//	 if (queue_family_indices.foundPresent) {
//		 info("Presentation queue family index: %d", queue_family_indices.presentFamily)
//	 }
//	 if (queue_family_indices.foundCompute) {
//		 info("Compute queue family index: %d", queue_family_indices.computeFamily)
//	 }

//	 current_device = create_device(new_physical_device, queue_family_indices);

//	 // Recreate resources (e.g., swapchain)
//	 // current_swapchain = create_swapchain(current_device, ...);
// }

// JNIEXPORT void JNICALL Java_com_nali_summer_Summer_run(JNIEnv *env, jobject obj, jintArray array)
// {
//	 // Get the array elements
//	 jint *elements = (*env)->GetIntArrayElements(env, array, NULL);
//	 // if (elements == NULL) {
//	 //	 return; // Out of memory error handled by JNI
//	 // }

//	 // Get the array length
//	 jsize length = (*env)->GetArrayLength(env, array);

//	 // Modify the array elements (example: set all elements to 10)
//	 // for (jsize i = 0; i < length; i++) {
//	 //	 elements[i] = 10;
//	 // }
//	 memset(elements, 10, length);

//	 // Release the array elements
//	 (*env)->ReleaseIntArrayElements(env, array, elements, 0);
// }

// static uint32_t* read_shader_file(const char* filename, size_t* out_size) {
//	 FILE* file = fopen(filename, "rb");
//	 if (!file) {
//		 error("Failed to open file")
//		 return NULL;
//	 }
	
//	 fseek(file, 0, SEEK_END);
//	 long size = ftell(file);
//	 fseek(file, 0, SEEK_SET);

//	 uint32_t* buffer = malloc(size);
//	 if (fread(buffer, 1, size, file) != size) {
//		 error("Failed to read file")
//		 free(buffer);
//		 fclose(file);
//		 return NULL;
//	 }

//	 fclose(file);
//	 *out_size = size;
//	 return buffer;
// }

// // Function to create a Vulkan shader module
// VkShaderModule create_shader_module(VkDevice device, const char* filename) {
//	 size_t code_size;
//	 uint32_t* code = read_shader_file(filename, &code_size);
//	 if (!code) {
//		 return VK_NULL_HANDLE;
//	 }

//	 VkShaderModuleCreateInfo create_info = {};
//	 create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
//	 create_info.codeSize = code_size;
//	 create_info.pCode = code;

//	 VkShaderModule shader_module;
//	 if (vkCreateShaderModule(device, &create_info, NULL, &shader_module) != VK_SUCCESS) {
//		 info("Failed to create shader module")
//		 free(code);
//		 return VK_NULL_HANDLE;
//	 }

//	 free(code);
//	 return shader_module;
// }

// void draw()
// {
//	 // VkResult result;

//	 // // Step 1: Acquire an Image from the Swapchain
//	 // uint32_t imageIndex;
//	 // result = vkAcquireNextImageKHR(device, swapchain, UINT64_MAX, imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
//	 // if (result != VK_SUCCESS)
//	 // {
//	 //	 // Handle error
//	 // }

//	 // // Step 2: Begin a Render Pass

//	 // VkClearValue clearColor = {{{0.0f, 0.5f, 0.5f, 1.0f}}};  // Example clear color (RGBA)

//	 // VkRenderPassBeginInfo renderPassInfo = {};
//	 // renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
//	 // renderPassInfo.renderPass = renderPass; // Assume this is already created
//	 // renderPassInfo.framebuffer = framebuffers[imageIndex]; // Use the framebuffer corresponding to the image
//	 // renderPassInfo.renderArea.offset = (VkOffset2D){0, 0};
//	 // renderPassInfo.renderArea.extent = swapchainExtent;
//	 // renderPassInfo.clearValueCount = 1;
//	 // renderPassInfo.pClearValues = &clearColor;

//	 // vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

//	 // // Additional drawing commands would go here, but for clearing the color, this is enough

//	 // vkCmdEndRenderPass(commandBuffer);

//	 // // Step 3: End Command Buffer

//	 // result = vkEndCommandBuffer(commandBuffer);
//	 // if (result != VK_SUCCESS) {
//	 //	 // Handle error
//	 // }

//	 // // Step 4: Submit the Command Buffer to the Graphics Queue

//	 // VkSubmitInfo submitInfo = {};
//	 // submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
//	 // VkSemaphore waitSemaphores[] = {imageAvailableSemaphore};
//	 // VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
//	 // submitInfo.waitSemaphoreCount = 1;
//	 // submitInfo.pWaitSemaphores = waitSemaphores;
//	 // submitInfo.pWaitDstStageMask = waitStages;
//	 // submitInfo.commandBufferCount = 1;
//	 // submitInfo.pCommandBuffers = &commandBuffer;
//	 // VkSemaphore signalSemaphores[] = {renderFinishedSemaphore};
//	 // submitInfo.signalSemaphoreCount = 1;
//	 // submitInfo.pSignalSemaphores = signalSemaphores;

//	 // result = vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
//	 // if (result != VK_SUCCESS) {
//	 //	 // Handle error
//	 // }

//	 // // Step 5: Present the Image

//	 // VkPresentInfoKHR presentInfo = {};
//	 // presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
//	 // presentInfo.waitSemaphoreCount = 1;
//	 // presentInfo.pWaitSemaphores = signalSemaphores;
//	 // VkSwapchainKHR swapchains[] = {swapchain};
//	 // presentInfo.swapchainCount = 1;
//	 // presentInfo.pSwapchains = swapchains;
//	 // presentInfo.pImageIndices = &imageIndex;
//	 // presentInfo.pResults = NULL; // Optional

//	 // result = vkQueuePresentKHR(presentQueue, &presentInfo);
//	 // if (result != VK_SUCCESS) {
//	 //	 // Handle error
//	 // }
// }
