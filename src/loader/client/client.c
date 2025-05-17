VkBuffer m_vkbuffer;
VkDeviceMemory m_vkdevicememory;
void *m_vkbuffer_p;
VkDeviceSize m_vkdevicesize;

void lc_init()
{
	lcm_init();
	m_surface_state |= NALI_SURFACE_C_S_RENDER_ABLE;
}

void lc_vk()
{
	while (!(m_surface_state & NALI_SURFACE_C_S_RENDER_ABLE))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	VkMemoryRequirements vkmemoryrequirements;
	//VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	//VK_BUFFER_USAGE_STORAGE_BUFFER_BIT
	VK_makeBuffer(m_device, m_vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, m_vkbuffer, m_vkdevicememory, vkmemoryrequirements)
	nali_info("vkMapMemory %d", vkMapMemory(m_vkdevice_p[m_device], m_vkdevicememory, 0, m_vkdevicesize, 0, &m_vkbuffer_p))
	lcm_vk();

	// //update vkbuffer
	// vkFlushMappedMemoryRanges(m_vkdevice_p[m_device], 1, &(VkMappedMemoryRange)
	// {
	// 	.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
	// 	.memory = m_vkdevicememory,
	// 	.offset = 0,
	// 	.size = step,
	// 	// .size = m_vkdevicesize
	// 	.pNext = VK_NULL_HANDLE
	// });

	lcs_vk();

	vk_initCmdDraw();
	nali_info("thrd_create %d", thrd_create(&(thrd_t){}, vk_cmdDraw, NULL))
}

void lc_freeVk(uint32_t device)
{
	lcs_freeVk(device);

	VkDevice vkdevice = m_vkdevice_p[device];
	vkUnmapMemory(m_vkdevice_p[device], m_vkdevicememory);
	vkDestroyBuffer(vkdevice, m_vkbuffer, VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, m_vkdevicememory, VK_NULL_HANDLE);
	m_vkbuffer_p = NULL;
}