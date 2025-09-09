struct wl_display *smpt_sf_wl_ce_dp_p;
struct wl_compositor *smpt_sf_wl_ce_cot_p;
struct wl_surface *smpt_sf_wl_ce_sf_p;

void smpt_sf_wl_ceMset()
{
	SMPT_DBmR2L("wl_display_connect %p", smpt_sf_wl_ce_dp_p = wl_display_connect(getenv("WAYLAND_DISPLAY")))

	smpt_sf_wl_ce_rgt_set();

	SMPT_DBmR2L("wl_display_roundtrip %d", wl_display_roundtrip(smpt_sf_wl_ce_dp_p))

	SMPT_DBmR2L("wl_compositor_create_surface %p", smpt_sf_wl_ce_sf_p = wl_compositor_create_surface(smpt_sf_wl_ce_cot_p))

	smpt_sf_wl_ce_xdg_sf_set();
	smpt_sf_wl_ce_xdg_tl_set();

	wl_surface_commit(smpt_sf_wl_ce_sf_p);
	SMPT_DBmR2L("wl_display_dispatch %d", wl_display_dispatch(smpt_sf_wl_ce_dp_p));

	//.i loop
	int r = 0;

	while (!(_sf_state & _SF_S_RENDER))
	{
		SMPT_DBmN2L("thrd_sleep %d", thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL))
		SMPT_DBmN2L("_sf_state %d", _sf_state)
	}

	while (r != INT_MAX)
	{
		if (_sf_state & _SF_S_EXIT)
		{
			r = INT_MAX;
		}
		else
		{
			r = wl_display_dispatch(smpt_sf_wl_ce_dp_p);
		}
	}

	smpt_sf_wl_ce_free();
	SMPT_DBmN2L("r %d", r);
}

void smpt_sf_wl_ce_free()
{
	smpt_sf_wl_ces_free();

	smpt_sf_wl_ce_xdg_wmb_free();

	smpt_sf_wl_ce_zwp_lp_free();
	smpt_sf_wl_ce_zwp_pc_free();

	smpt_sf_wl_ce_zwp_rp_free();

	wl_surface_destroy(smpt_sf_wl_ce_sf_p);
	wl_compositor_destroy(smpt_sf_wl_ce_cot_p);

	smpt_sf_wl_ce_rgt_free();

	wl_display_disconnect(smpt_sf_wl_ce_dp_p);
}
