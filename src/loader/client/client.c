float lc_rt_array[NALI_LB_MAX_CLIENT][3+3] = {0};

uint8_t lc_m_bl_array[NALI_VD_M_MAX] = {0};
uint8_t *lc_m_p_array[NALI_VD_M_MAX];
float *lc_m_rt_p_array[NALI_VD_M_MAX];

VkBuffer lc_vkbuffer;
VkDeviceMemory lc_vkdevicememory;
void *lc_vkbuffer_p;
VkDeviceSize lc_vkdevicesize;

void lc_set()
{
	vd_set();
	lcs_set();
	v_set();
	s_set();
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
	NALI_D_INFO("vkMapMemory %d", vkMapMemory(vkqd_vkdevice_p[vk_device], lc_vkdevicememory, 0, lc_vkdevicesize, 0, &lc_vkbuffer_p))
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
	NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, vk_cmd_draw_loop, NULL))
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


mtx_t *vd_mtx_t_p = &(mtx_t){};

void vd_set()
{
	NALI_D_INFO("mtx_init %d", mtx_init(vd_mtx_t_p, mtx_plain))
	NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, lc_loop, NULL))
}

void vd_free()
{
	mtx_destroy(vd_mtx_t_p);
}

static void add(uint8_t a, uint8_t j, uint16_t *s_index_p, void (*fp)(uint8_t, uint16_t))
{
	// NALI_VD_M_POMI0;
	lcs_add_ds_p_array[a] = realloc(lcs_add_ds_p_array[a], lcs_add_i_bl_array[a] + 1);
	lcs_add_j_p_array[a] = realloc(lcs_add_j_p_array[a], lcs_add_i_bl_array[a] + 1);
	lcs_add_a_p_array[a] = realloc(lcs_add_a_p_array[a], lcs_add_i_bl_array[a] + 1);
	lcs_add_a_bl_p_array[a] = realloc(lcs_add_a_bl_p_array[a], lcs_add_i_bl_array[a] + 1);
	lcs_add_vkdevicesize_p[a] = realloc(lcs_add_vkdevicesize_p[a], sizeof(VkDeviceSize) * NALI_LCS_D_SIZE * (lcs_add_i_bl_array[a] + 1));

	lcs_add_ds_p_array[a][lcs_add_i_bl_array[a]] = v_a_bl0_array[a];
	lcs_add_j_p_array[a][lcs_add_i_bl_array[a]] = j;

	lcs_add_a_p_array[a][lcs_add_i_bl_array[a]] = malloc(4);
	lcs_add_a_p_array[a][lcs_add_i_bl_array[a]][0] = 9;
	lcs_add_a_p_array[a][lcs_add_i_bl_array[a]][1] = 4;
	lcs_add_a_p_array[a][lcs_add_i_bl_array[a]][2] = 6;
	lcs_add_a_p_array[a][lcs_add_i_bl_array[a]][3] = 8;

	lcs_add_a_bl_p_array[a][lcs_add_i_bl_array[a]] = 4;

	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_array[a] * NALI_LCS_D_SIZE] = sizeof(float) * 16 * 2;//world
	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_array[a] * NALI_LCS_D_SIZE + 1] = lcm_vkdevicesize_p[j];//b
	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_array[a] * NALI_LCS_D_SIZE + 2] = lcm_vkdevicesize_p[lcm_joint_count_bl + 1] + NALI_LCM_BONE_BL * sizeof(float) * 4 * 4 * v_a_bl0_array[a] + sizeof(float) * 4;//a
	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_array[a] * NALI_LCS_D_SIZE + 3] = NALI_LCM_VP_BL + lcm_rgba_bl;//rgba a
	lcs_add_vkdevicesize_p[a][lcs_add_i_bl_array[a] * NALI_LCS_D_SIZE + 4] = lcm_vkdevicesize_p[lcm_joint_count_bl + 1] + NALI_LCM_BONE_BL * sizeof(float) * 4 * 4 * v_a_bl0_array[a];//rgba b
	
	?vd_m_bl_array
	?vd_m_p_array
	?vd_m_rt_p_array
	?vd_m_animate_p_array
	?vd_m_keyframe_p_array

	lcs_write_fp = realloc(lcs_write_fp, sizeof(void (*)()) * (lcs_write_fp_bl + 1));
	lcs_write_fp[lcs_write_fp_bl] = fp;//pre_update
	++lcs_write_fp_bl;

	*s_index_p = v_a_bl0_array[a];

	++v_a_bl0_array[a];
	++lcs_add_i_bl_array[a];
}

int lc_loop(void *p)
{
	while (1)
	{
		uint8_t *data_p = get_data();
		if (data_p)
		{
			read_data(data_p);
			free(data_p);
		}

		if (add_pomi)
		{
			mtx_lock(vd_mtx_t_p);
			vk_cmd_d_fp = realloc(vk_cmd_d_fp, sizeof(void (*)()) * (vk_cmd_d_fp_bl + 1));
			vk_cmd_d_fp[vk_cmd_d_fp_bl] = e_pomi0_add;
			++vk_cmd_d_fp_bl;
			mtx_unlock(vd_mtx_t_p);
		}
		//read
		//draw
	}

	return 0;
}