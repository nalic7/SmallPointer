struct zwp_relative_pointer_manager_v1 *s_wlc_zwp_rp_manager_p;
struct zwp_relative_pointer_v1 *s_wlc_zwp_rp_p = NULL;

static void zwp_relative_pointer_v1_listener_relative_motion(void *data, struct zwp_relative_pointer_v1 *zwp_relative_pointer_v1, uint32_t utime_hi, uint32_t utime_lo, wl_fixed_t dx, wl_fixed_t dy, wl_fixed_t dx_unaccel, wl_fixed_t dy_unaccel)
{
	NALI_D_LOG("x %f", wl_fixed_to_double(dx))
	NALI_D_LOG("y %f", wl_fixed_to_double(dy))
}

struct zwp_relative_pointer_v1_listener s_wlc_zwp_rp_listener =
{
	.relative_motion = zwp_relative_pointer_v1_listener_relative_motion
};

void s_wlc_zwp_rp_free()
{
	if (s_wlc_zwp_rp_p)
	{
		zwp_relative_pointer_v1_destroy(s_wlc_zwp_rp_p);
		s_wlc_zwp_rp_p = NULL;
	}

	zwp_relative_pointer_manager_v1_destroy(s_wlc_zwp_rp_manager_p);
}
