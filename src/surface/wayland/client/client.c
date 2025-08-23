struct wl_display *_sf_wlc_dp_p;
struct wl_compositor *_sf_wlc_cot_p;
struct wl_surface *_sf_wlc_sf_p;

static int loop(void *p)
{
	int r = 0;

	while (!(_sf_state & _SF_S_RENDER))
	{
		NALI_D_LOG("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
		NALI_D_LOG("_sf_state %d", _sf_state)
	}

	while (r != INT_MAX)
	{
		if (_sf_state & _SF_S_EXIT)
		{
			r = INT_MAX;
		}
		else
		{
			//swlcsp_change_cursor(1);
			r = wl_display_dispatch(_sf_wlc_dp_p);
		}
	}

	if (r == INT_MAX)
	{
		_sf_wlc_free();
	}
	else
	{
		//! re-create wl if crash before vk_sc
		NALI_D_LOG("wl_display_dispatch %d", r);
	}

	return 0;
}

void _sf_wlc_set()
{
	NALI_D_INFO("wl_display_connect %p", _sf_wlc_dp_p = wl_display_connect(getenv("WAYLAND_DISPLAY")))

	_sf_wlc_rtr_set();

	NALI_D_INFO("wl_display_roundtrip %d", wl_display_roundtrip(_sf_wlc_dp_p))

	NALI_D_INFO("wl_compositor_create_surface %p", _sf_wlc_sf_p = wl_compositor_create_surface(_sf_wlc_cot_p))

	_sf_wlc_xdg_sf_set();
	_sf_wlc_xdg_tl_set();

	//! need more test
	wl_surface_commit(_sf_wlc_sf_p);
	NALI_D_INFO("wl_display_dispatch %d", wl_display_dispatch(_sf_wlc_dp_p));

	NALI_D_INFO("thrd_create %d", thrd_create(&(thrd_t){}, loop, NULL))
}

void _sf_wlc_free()
{
	_sf_wlc_seat_free();

	_sf_wlc_xdg_wmb_free();

	_sf_wlc_zwp_lp_free();
	_sf_wlc_zwp_pc_free();

	_sf_wlc_zwp_rp_free();

	wl_surface_destroy(_sf_wlc_sf_p);
	wl_compositor_destroy(_sf_wlc_cot_p);

	_sf_wlc_rtr_free();

	wl_display_disconnect(_sf_wlc_dp_p);
}
