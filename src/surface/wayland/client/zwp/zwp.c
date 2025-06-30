void swlczwp_setPointer()
{
	if (wlc_zwp_locked_pointer_v1_p)
	{
		swlcsp_pointer = 0;

		zwp_locked_pointer_v1_destroy(wlc_zwp_locked_pointer_v1_p);
		wlc_zwp_locked_pointer_v1_p = NULL;

		zwp_relative_pointer_v1_destroy(wlc_zwp_relative_pointer_v1_p);
		wlc_zwp_relative_pointer_v1_p = NULL;
	}
	else
	{
		swlcsp_pointer = 255;

		NALI_D_INFO("zwp_pointer_constraints_v1_lock_pointer %p", wlc_zwp_locked_pointer_v1_p = zwp_pointer_constraints_v1_lock_pointer(wlc_zwp_pointer_constraints_v1_p, wlc_wl_surface_p, wlc_wl_pointer_p, NULL, ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT))
		NALI_D_INFO("zwp_locked_pointer_v1_add_listener %d", zwp_locked_pointer_v1_add_listener(wlc_zwp_locked_pointer_v1_p, &swlczwp_zwp_locked_pointer_v1_listener, NULL))

		NALI_D_INFO("zwp_relative_pointer_manager_v1_get_relative_pointer %p", wlc_zwp_relative_pointer_v1_p = zwp_relative_pointer_manager_v1_get_relative_pointer(wlc_zwp_relative_pointer_manager_v1_p, wlc_wl_pointer_p))
		NALI_D_INFO("zwp_relative_pointer_v1_add_listener %d", zwp_relative_pointer_v1_add_listener(wlc_zwp_relative_pointer_v1_p, &swlczwp_zwp_relative_pointer_v1_listener, NULL))
	}
}