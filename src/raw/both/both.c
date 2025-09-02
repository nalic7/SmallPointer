#if SMPT_CM_CLIENT && SMPT_CM_SERVER
	mtx_t *lb_mtx_t_p = &(mtx_t){};
#endif

const uint8_t *lb_map_p[SMPTRB_MA_BL] =
{
	ebpomi0_map_p,
	ebpomi1_map_p,
	ebpomi2_map_p
};

const uint8_t lb_mrb_p[SMPTRB_MA_BL] =
{
	NALI_EBPOMI0_MRB,
	NALI_EBPOMI1_MRB,
	NALI_EBPOMI2_MRB
};

const uint8_t lb_mab_p[SMPTRB_MA_BL] =
{
	NALI_EBPOMI0_MAB,
	NALI_EBPOMI1_MAB,
	NALI_EBPOMI2_MAB
};

//static depth for translucent
//follow from map ma
const float lb_mdp_p[SMPTRB_MDP_BL][3] =
{
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

//a k_s k_e
const SMPTRB_AKT lb_ak_p[SMPTRB_AK_BL][3] =
{
	{0, 3, 5},
};

LB_C *lb_c;

void lb_set()
{
	#if SMPT_CM_CLIENT && SMPT_CM_SERVER
		SMPT_DB_R2L("mtx_init %d", mtx_init(lb_mtx_t_p, mtx_plain))
	#endif

	lb_c = malloc(sizeof(LB_C));
	lb_c->d_bl_p = malloc(sizeof(uint32_t) * 2);
	lb_c->d_bl_p[1] = 0;
	lb_c->d_p = f_read(NALI_F_HOME_ASSET, lb_c->d_bl_p);
}

#define SMPTRB_RZ NALI_M_D2R(180.0F)
void lb_u_update(float w_p[16], float ry, float q_v4_array[4], float q0_m4x4_array[16], float q1_m4x4_array[16])
{
	memcpy(w_p, mm4x4_array, sizeof(mm4x4_array));

	mv4_q(0, 0, SMPTRB_RZ, q_v4_array);
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
	#if SMPT_CM_DRM || SMPT_CM_ASURFACE || SMPT_CM_WL || SMPT_CM_X11
		_sf_state |= _SF_S_EXIT;
	#endif

	#ifdef SMPT_CM_SERVER
		ls_free();
	#endif

	#ifdef SMPT_CM_CLIENT
		lc_free(smpt_rd_vk_device);
	#endif

	//! switch to pipewire
	// al_clean();

	#ifdef SMPT_CM_WL
		smpt_sf_wlc_free();
	#endif

	#if SMPT_CM_CLIENT && SMPT_CM_SERVER
		mtx_destroy(lb_mtx_t_p);
	#endif
}
