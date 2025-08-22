struct wl_display *s_wlcd_p;
struct wl_compositor *s_wlcc_p;
struct wl_surface *s_wlcs_p;

static int loop(void *p)
{
	int r = 0;

	while (!(s_state & NALI_S_S_VK))
	{
		NALI_D_LOG("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
		NALI_D_LOG("s_state %d", s_state)
	}

	while (r != INT_MAX)
	{
		if (s_state & NALI_S_S_CLEAN)
		{
			r = INT_MAX;
		}
		else
		{
			//swlcsp_change_cursor(1);
			r = wl_display_dispatch(s_wlcd_p);
		}
	}

	if (r == INT_MAX)
	{
		s_wlc_free();
	}
	else
	{
		//! re-create wl if crash before vk_sc
		NALI_D_LOG("wl_display_dispatch %d", r);
	}

	return 0;
}

void s_wlc_set()
{
	NALI_D_INFO("wl_display_connect %p", s_wlcd_p = wl_display_connect(getenv("WAYLAND_DISPLAY")))

	s_wlc_r_set();

	NALI_D_INFO("wl_display_roundtrip %d", wl_display_roundtrip(s_wlcd_p))

	NALI_D_INFO("wl_compositor_create_surface %p", s_wlcs_p = wl_compositor_create_surface(s_wlcc_p))

	s_wlc_xdgs_set();
	s_wlc_xdg_tl_set();

	//! need more test
	wl_surface_commit(s_wlcs_p);
	NALI_D_INFO("wl_display_dispatch %d", wl_display_dispatch(s_wlcd_p));

	NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, loop, NULL))
}

void s_wlc_free()
{
	s_wlc_seat_free();

	s_wlc_xdg_wm_base_free();

	s_wlc_zwp_lp_free();
	s_wlc_zwp_pc_free();

	s_wlc_zwp_rp_free();

	wl_surface_destroy(s_wlcs_p);
	wl_compositor_destroy(s_wlcc_p);

	s_wlc_r_free();

	wl_display_disconnect(s_wlcd_p);
}
