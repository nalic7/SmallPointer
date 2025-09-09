const SMPTRtMB smptrPmb[SMPTReMAc + SMPTReMc] =
{
	#define X(v, n, b) b,
		SMPTRnMA
	#undef X
	#define X(v, n, b) b,
		SMPTRnM
	#undef X
};

struct SMPTRsM *smptrPm;
SMPTRtM smptrLm = 0;

struct SMPTRsCACHE *smptrPcache;

void lb_set()
{
	smptrPm = malloc(0);

	smptrPcache = malloc(sizeof(struct SMPTRsCACHE));
	smptrPcache->d_bl_p = malloc(sizeof(uint32_t) * 2);
	smptrPcache->d_bl_p[1] = 0;
	smptrPcache->d_p = f_read(NALI_F_HOME_ASSET, smptrPcache->d_bl_p);
}

#define SMPTRB_RZ NALI_M_D2R(180.0F)
void lb_u_update(float w_p[16], float ry, float q_v4_array[4], float q0_m4x4_array[16], float q1_m4x4_array[16])
{
	memcpy(w_p, smptmPm4x4, sizeof(smptmPm4x4));

	smptm_v4Mq(0, 0, SMPTRB_RZ, q_v4_array);
	smptm_v4Mq2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, w_p, sizeof(float) * 16);
	smptm_m4x4Mm(q1_m4x4_array, q0_m4x4_array, w_p);

	smptm_v4Mq(0, ry, 0, q_v4_array);
	smptm_v4Mq2m(q_v4_array, q0_m4x4_array);
	memcpy(q1_m4x4_array, w_p, sizeof(float) * 16);
	smptm_m4x4Mm(q1_m4x4_array, q0_m4x4_array, w_p);
}

void lb_free0()
{
	free(smptrPcache->d_bl_p);
	free(smptrPcache->d_p);
	free(smptrPcache);
}

void lb_free1()
{
	#if SMPT_CM_DRM || SMPT_CM_ASURFACE || SMPT_CM_WL || SMPT_CM_X11
		_sf_state |= _SF_S_EXIT;
	#endif

	#ifdef SMPT_CM_SERVER
		smptr_svMfree();
	#endif

	#ifdef SMPT_CM_CLIENT
		smptr_ceMfree(smpt_rd_vk_device);
	#endif
	free(smptrPm);

	//! switch to pipewire
	// al_clean();

	#ifdef SMPT_CM_WL
		smpt_sf_wl_ce_free();
	#endif
}
