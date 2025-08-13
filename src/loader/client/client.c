NALI_LCS_DSIT *lc_dsi_p;
uint8_t *lc_a_p;

//to bypass oit / sort for translucent
//x1 switch color attribute
//2 no translucent now
//3 in shader get current pixel on screen then switch color <- need to check every pixel
//->sort is easy

//should save gpu memory and less update
//if Frame-in-Flight
//more memory need
//set on lc_vkdevicesize
//++ only
//255%N == N-1
//-> to copy buffer to next frame
//need to keep update state to next frame
//still need to flush all?
//#define NALI_LC_FRAME 4
//uint8_t frame;
VkBuffer lc_vkbuffer;
VkDeviceMemory lc_vkdevicememory;
void *lc_vkbuffer_p;
VkDeviceSize lc_vkdevicesize;

NALI_LB_PT lc_net_bl = 0;
uint8_t lc_net_p[NALI_LB_NET_BL];

// float lc_delta = 0;

void lc_set()
{
	lcs_set();
	lckf_set();
	lcp_set();
	s_state |= NALI_S_S_DATA_ABLE;

	lc_dsi_p = malloc(0);
	lc_a_p = malloc(0);

	lcm_set();

	nc_set();
}

void lc_vk()
{
	while (!(s_state & NALI_S_S_DATA_ABLE))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	VkMemoryRequirements vkmemoryrequirements;
	//VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	//VK_BUFFER_USAGE_STORAGE_BUFFER_BIT
	lc_vkdevicesize = (NALI_LC_P_BL + (vk_non_coherent_atom_size - 1)) & ~(vk_non_coherent_atom_size - 1);
	VK_makeBuffer(vk_device, lc_vkdevicesize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, lc_vkbuffer, lc_vkdevicememory, vkmemoryrequirements)
	NALI_D_INFO("vkMapMemory %d", vkMapMemory(vkqd_vkdevice_p[vk_device], lc_vkdevicememory, 0, lc_vkdevicesize, 0, &lc_vkbuffer_p))
	lcp_vk();

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
	#ifdef C_NALI_S_ANDROID
		NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, vk_cmd_draw_loop, NULL))
	#else
		vk_cmd_draw_loop();
	#endif
}

static void lc_send()
{
	clock_gettime(CLOCK_MONOTONIC, (struct timespec *)lc_net_p);
	lc_net_bl = sizeof(struct timespec);

	lcu_send();

	nc_send();
}

static struct timespec lc_time = {0};
static struct timespec l_time;
void lc_read()
{
	l_time = *(struct timespec *)lc_net_p;

	if ((l_time.tv_sec > lc_time.tv_sec) || (l_time.tv_sec == lc_time.tv_sec && l_time.tv_nsec > lc_time.tv_nsec))
	{
		lc_net_bl = sizeof(struct timespec);

		lcm_re();

		lcu_read();
		lcm_read();

		lc_time = l_time;
	}
}

void lc_freeloop()
{
	nc_free();

	lcm_free();

	lcp_free();
	lcs_free();

	free(lc_dsi_p);
	free(lc_a_p);

	mtx_unlock(lb_mtx_t_p);
}

void lc_freeVk(uint32_t device)
{
	lcs_freeVk(device);

	VkDevice vkdevice = vkqd_vkdevice_p[device];
	vkUnmapMemory(vkqd_vkdevice_p[device], lc_vkdevicememory);
	vkDestroyBuffer(vkdevice, lc_vkbuffer, VK_NULL_HANDLE);
	vkFreeMemory(vkdevice, lc_vkdevicememory, VK_NULL_HANDLE);
	// lc_vkbuffer_p = NULL;
}

void lc_free()
{
	if (s_state & NALI_S_S_EXIT_C)
	{
		return;
	}
	s_state |= NALI_S_S_EXIT_C;

	mtx_lock(lb_mtx_t_p);

	s_state |= NALI_S_S_CLEAN;
}
