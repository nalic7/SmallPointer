struct wl_display *smpt_sf_wlc_dp_p;
struct wl_compositor *smpt_sf_wlc_cot_p;
struct wl_surface *smpt_sf_wlc_sf_p;

void smpt_sf_wlc_set()
{
	SMPT_DB_R2L("wl_display_connect %p", smpt_sf_wlc_dp_p = wl_display_connect(getenv("WAYLAND_DISPLAY")))

	smpt_sf_wlc_rgt_set();

	SMPT_DB_R2L("wl_display_roundtrip %d", wl_display_roundtrip(smpt_sf_wlc_dp_p))

	SMPT_DB_R2L("wl_compositor_create_surface %p", smpt_sf_wlc_sf_p = wl_compositor_create_surface(smpt_sf_wlc_cot_p))

	smpt_sf_wlc_xdg_sf_set();
	smpt_sf_wlc_xdg_tl_set();

	wl_surface_commit(smpt_sf_wlc_sf_p);
	SMPT_DB_R2L("wl_display_dispatch %d", wl_display_dispatch(smpt_sf_wlc_dp_p));

	//.i loop
	int r = 0;

	while (!(_sf_state & _SF_S_RENDER))
	{
		SMPT_DB_N2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
		SMPT_DB_N2L("_sf_state %d", _sf_state)
	}

	while (r != INT_MAX)
	{
		if (_sf_state & _SF_S_EXIT)
		{
			r = INT_MAX;
		}
		else
		{
			r = wl_display_dispatch(smpt_sf_wlc_dp_p);
		}
	}

	smpt_sf_wlc_free();
	SMPT_DB_N2L("r %d", r);
}

void smpt_sf_wlc_free()
{
	smpt_sf_wlcs_free();

	smpt_sf_wlc_xdg_wmb_free();

	smpt_sf_wlc_zwp_lp_free();
	smpt_sf_wlc_zwp_pc_free();

	smpt_sf_wlc_zwp_rp_free();

	wl_surface_destroy(smpt_sf_wlc_sf_p);
	wl_compositor_destroy(smpt_sf_wlc_cot_p);

	smpt_sf_wlc_rgt_free();

	wl_display_disconnect(smpt_sf_wlc_dp_p);
}
