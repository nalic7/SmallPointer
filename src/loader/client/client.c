VkBuffer lc_vkbuffer;
VkDeviceMemory lc_vkdevicememory;
void *lc_vkbuffer_p;
VkDeviceSize lc_vkdevicesize;

void lc_set()
{
	lckf_set();
	lcm_set();
	s_surface_state |= NALI_SURFACE_C_S_RENDER_ABLE;
}

void lc_vk()
{
	while (!(s_surface_state & NALI_SURFACE_C_S_RENDER_ABLE))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	VkMemoryRequirements vkmemoryrequirements;
	//VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	//VK_BUFFER_USAGE_STORAGE_BUFFER_BIT
	VK_makeBuffer(vk_device, lc_vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, lc_vkbuffer, lc_vkdevicememory, vkmemoryrequirements)
	nali_info("vkMapMemory %d", vkMapMemory(vkqd_vkdevice_p[vk_device], lc_vkdevicememory, 0, lc_vkdevicesize, 0, &lc_vkbuffer_p))
	lcm_vk();

	// //update vkbuffer
	// vkFlushMappedMemoryRanges(vkqd_vkdevice_p[vk_device], 1, &(VkMappedMemoryRange)
	// {
	// 	.sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
	// 	.memory = m_vkdevicememory,
	// 	.offset = 0,
	// 	.size = step,
	// 	// .size = m_vkdevicesize
	// 	.pNext = VK_NULL_HANDLE
	// });

	lcs_vk();

	vk_cmd_draw_set();
	nali_info("thrd_create %d", thrd_create(&(thrd_t){}, vk_cmd_draw_loop, NULL))
}

void lc_freeVk(uint32_t device)
{
	lcs_freeVk(device);

	VkDevice vkdevice = vkqd_vkdevice_p[device];
	vkUnmapMemory(vkqd_vkdevice_p[device], lc_vkdevicememory);
	vkDestroyBuffer(vkdevice, lc_vkbuffer, VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, lc_vkdevicememory, VK_NULL_HANDLE);
	lc_vkbuffer_p = NULL;
}