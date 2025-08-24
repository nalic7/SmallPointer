mtx_t *lb_mtx_t_p = &(mtx_t){};

// NALI_LB_MT lb_ms_p[NALI_LB_N_MAX] =
// {
// 	NALI_EBPOMI0_M
// };

// const uint8_t lb_ma_p[NALI_LB_MA_BL] =
// {
// 	NALI_EBPOMI0_MA,
// 	NALI_EBPOMI1_MA,
// 	NALI_EBPOMI2_MA
// };

const uint8_t *lb_map_p[NALI_LB_MA_BL] =
{
	ebpomi0_map_p,
	ebpomi1_map_p,
	ebpomi2_map_p
};

const uint8_t lb_mrb_p[NALI_LB_MA_BL] =
{
	NALI_EBPOMI0_MRB,
	NALI_EBPOMI1_MRB,
	NALI_EBPOMI2_MRB
};

const uint8_t lb_mab_p[NALI_LB_MA_BL] =
{
	NALI_EBPOMI0_MAB,
	NALI_EBPOMI1_MAB,
	NALI_EBPOMI2_MAB
};

//static depth for translucent
//follow from map ma
const float lb_mdp_p[NALI_LB_MDP_BL][3] =
{
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

//a k_s k_e
const NALI_LB_AKT lb_ak_p[NALI_LB_AK_BL][3] =
{
	{0, 3, 5},
};

// uint8_t lb_ms_abl_p[NALI_LB_N_MAX] =
// {
// 	NALI_EBPOMI0_MS_AP_BL
// };

// VkDeviceSize lb_ms_vkdevicesize_p[NALI_LB_N_MAX] =
// {
// 	NALI_EBPOMI0_MS_VKDEVICESIZE
// };

LB_C *lb_c;

void lb_set()
{
	NALI_D_INFO("mtx_init %d", mtx_init(lb_mtx_t_p, mtx_plain))

	lb_c = malloc(sizeof(LB_C));
	lb_c->d_bl_p = malloc(sizeof(uint32_t) * 2);
	lb_c->d_bl_p[1] = 0;
	lb_c->d_p = f_read(NALI_F_HOME_ASSET, lb_c->d_bl_p);
}

#define NALI_LB_RZ NALI_M_D2R(180.0F)
//t_p lt_v4_array
void lb_u_update(float w_p[16], float ry, float q_v4_array[4], float q0_m4x4_array[16], float q1_m4x4_array[16])
{
	memcpy(w_p, mm4x4_array, sizeof(mm4x4_array));

	mv4_q(0, 0, NALI_LB_RZ, q_v4_array);
	mv4_q2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, w_p, sizeof(float) * 16);
	mm4x4_m(q1_m4x4_array, q0_m4x4_array, w_p);

	mv4_q(0, ry, 0, q_v4_array);
	mv4_q2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, w_p, sizeof(float) * 16);
	mm4x4_m(q1_m4x4_array, q0_m4x4_array, w_p);
}

void lb_free0()
{
	free(lb_c->d_bl_p);
	free(lb_c->d_p);
	free(lb_c);
}

void lb_free1()
{
	#ifdef _CM_SERVER
		ls_free();
		mtx_lock(lb_mtx_t_p);
		mtx_unlock(lb_mtx_t_p);
	#endif
	#ifdef _CM_CLIENT
		lc_free();
		mtx_lock(lb_mtx_t_p);
		mtx_unlock(lb_mtx_t_p);
	#endif

	//! switch to pipewire
	// al_clean();

	#ifndef _CM_ST_ANDROID
		_sf_wlc_free();
	#endif

	mtx_destroy(lb_mtx_t_p);

	d_free();

	exit(EXIT_SUCCESS);
}
