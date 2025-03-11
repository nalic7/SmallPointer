VkInstance m_vkinstance;

//D
uint32_t m_max_device;

VkPhysicalDevice* m_vkphysicaldevice_ptr;
uint8_t* m_max_graphics_ptr;
uint32_t** m_graphics_ptr;
VkQueue** m_vkqueue_graphics_ptr;

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
VkImageView** m_vkswapchainkhr_vkimageview_ptr;
VkFramebuffer** m_vkswapchainkhr_vkframebuffer_ptr;

VkFence* m_vkfence_ptr;
VkSemaphore*** m_vksemaphore_ptr;

VkCommandPool** m_vkcommandpool_ptr;
//S

uint32_t m_device = 0;
uint32_t m_graphic = 0;

#ifdef NALI_VK_DEBUG
	VkDebugUtilsMessengerEXT m_vkdebugutilsmessengerext;
#endif

int vk_loop(void* arg)
{
	VkPipelineLayout vkpipelinelayout;
	VkPipeline vkpipeline;
	vk_makeGraphicsPipeline(m_device, 0, &m_vkswapchainkhr_vkrenderpass_ptr[m_device], &vkpipelinelayout, &vkpipeline);

	while (1)
	{
		struct timespec ts = {5, 0};//5sec
		thrd_sleep(&ts, NULL);
	}
	return 0;
}

void checkE(uint32_t d)
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

void vinfo(uint32_t device)
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
	);
}

void vk_init()
{
	vk_makeInstance(0);
	vk_makeSurface(0);
	#ifdef NALI_VK_DEBUG
		vk_makeDebug(0);
	#endif
	vk_makePhysicalDevice();

	m_vkdevice_ptr = malloc(sizeof(VkDevice) * m_max_device);

	m_vkswapchainkhr_ptr = malloc(sizeof(VkSwapchainKHR) * m_max_device);
	m_vkswapchainkhr_vkimage_ptr = malloc(sizeof(VkImage *) * m_max_device);

	m_vksurfacecapabilitieskhr_ptr = malloc(sizeof(VkSurfaceCapabilitiesKHR) * m_max_device);
	m_vkswapchainkhr_vkextent2d_ptr = malloc(sizeof(VkExtent2D) * m_max_device);
	m_vkswapchainkhr_vkformat_ptr = malloc(sizeof(VkFormat) * m_max_device);

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
		vinfo(d);

		m_graphics_ptr[d] = malloc(sizeof(uint32_t));

		vk_makeQueue(d);
		vk_makeDevice(d, 0, 0);
		vk_makeSwapchain(d, 0);
		vk_makeFence(d);

		uint8_t max_graphics = m_max_graphics_ptr[d];

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
	int result = thrd_create(&thread, vk_loop, NULL);
	if (result != thrd_success)
	{
		error("thrd_create")
	}
}