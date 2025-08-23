struct zwp_pointer_constraints_v1 *_sf_wlc_zwp_pc_p;

void _sf_wlc_zwp_pc_set()
{
	if (_sf_wlc_zwp_lp_p)
	{
		zwp_locked_pointer_v1_destroy(_sf_wlc_zwp_lp_p);
		_sf_wlc_zwp_lp_p = NULL;

		zwp_relative_pointer_v1_destroy(_sf_wlc_zwp_rp_p);
		_sf_wlc_zwp_rp_p = NULL;
	}
	else
	{
		NALI_D_INFO("zwp_pointer_constraints_v1_lock_pointer %p", _sf_wlc_zwp_lp_p = zwp_pointer_constraints_v1_lock_pointer(_sf_wlc_zwp_pc_p, _sf_wlc_sf_p, _sf_wlc_seat_pt_p, NULL, ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT))
		NALI_D_INFO("zwp_locked_pointer_v1_add_listener %d", zwp_locked_pointer_v1_add_listener(_sf_wlc_zwp_lp_p, &_sf_wlc_zwp_lp_listener, NULL))

		NALI_D_INFO("zwp_relative_pointer_manager_v1_get_relative_pointer %p", _sf_wlc_zwp_rp_p = zwp_relative_pointer_manager_v1_get_relative_pointer(_sf_wlc_zwp_rp_mng_p, _sf_wlc_seat_pt_p))
		NALI_D_INFO("zwp_relative_pointer_v1_add_listener %d", zwp_relative_pointer_v1_add_listener(_sf_wlc_zwp_rp_p, &_sf_wlc_zwp_rp_listener, NULL))
	}
}

void _sf_wlc_zwp_pc_free()
{
	zwp_pointer_constraints_v1_destroy(_sf_wlc_zwp_pc_p);
}
