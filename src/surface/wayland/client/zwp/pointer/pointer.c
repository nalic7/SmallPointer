struct zwp_pointer_constraints_v1 *s_wlc_zwp_pc_p;

void s_wlc_zwp_set()
{
	if (s_wlc_zwp_lp_p)
	{
//		swlcsp_pointer = 0;

		zwp_locked_pointer_v1_destroy(s_wlc_zwp_lp_p);
		s_wlc_zwp_lp_p = NULL;

		zwp_relative_pointer_v1_destroy(s_wlc_zwp_rp_p);
		s_wlc_zwp_rp_p = NULL;
	}
	else
	{
//		swlcsp_pointer = 255;

		NALI_D_INFO("zwp_pointer_constraints_v1_lock_pointer %p", s_wlc_zwp_lp_p = zwp_pointer_constraints_v1_lock_pointer(s_wlc_zwp_pc_p, s_wlcs_p, s_wlc_seat_p_p, NULL, ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT))
		NALI_D_INFO("zwp_locked_pointer_v1_add_listener %d", zwp_locked_pointer_v1_add_listener(s_wlc_zwp_lp_p, &s_wlc_zwp_lp_listener, NULL))

		NALI_D_INFO("zwp_relative_pointer_manager_v1_get_relative_pointer %p", s_wlc_zwp_rp_p = zwp_relative_pointer_manager_v1_get_relative_pointer(s_wlc_zwp_rp_manager_p, s_wlc_seat_p_p))
		NALI_D_INFO("zwp_relative_pointer_v1_add_listener %d", zwp_relative_pointer_v1_add_listener(s_wlc_zwp_rp_p, &s_wlc_zwp_rp_listener, NULL))
	}
}

void s_wlc_zwp_pc_free()
{
	zwp_pointer_constraints_v1_destroy(s_wlc_zwp_pc_p);
}
