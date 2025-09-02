struct zwp_pointer_constraints_v1 *smpt_sf_wlc_zwp_pc_p;

void smpt_sf_wlc_zwp_pc_set()
{
	if (smpt_sf_wlc_zwp_lp_p)
	{
		zwp_locked_pointer_v1_destroy(smpt_sf_wlc_zwp_lp_p);
		smpt_sf_wlc_zwp_lp_p = NULL;

		zwp_relative_pointer_v1_destroy(smpt_sf_wlc_zwp_rp_p);
		smpt_sf_wlc_zwp_rp_p = NULL;
	}
	else
	{
		SMPT_DB_R2L("zwp_pointer_constraints_v1_lock_pointer %p", smpt_sf_wlc_zwp_lp_p = zwp_pointer_constraints_v1_lock_pointer(smpt_sf_wlc_zwp_pc_p, smpt_sf_wlc_sf_p, smpt_sf_wlcs_pt_p, NULL, ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT))
		SMPT_DB_R2L("zwp_locked_pointer_v1_add_listener %d", zwp_locked_pointer_v1_add_listener(smpt_sf_wlc_zwp_lp_p, &smpt_sf_wlc_zwp_lp_listener, NULL))

		SMPT_DB_R2L("zwp_relative_pointer_manager_v1_get_relative_pointer %p", smpt_sf_wlc_zwp_rp_p = zwp_relative_pointer_manager_v1_get_relative_pointer(smpt_sf_wlc_zwp_rp_mng_p, smpt_sf_wlcs_pt_p))
		SMPT_DB_R2L("zwp_relative_pointer_v1_add_listener %d", zwp_relative_pointer_v1_add_listener(smpt_sf_wlc_zwp_rp_p, &smpt_sf_wlc_zwp_rp_listener, NULL))
	}
}

void smpt_sf_wlc_zwp_pc_free()
{
	zwp_pointer_constraints_v1_destroy(smpt_sf_wlc_zwp_pc_p);
}
