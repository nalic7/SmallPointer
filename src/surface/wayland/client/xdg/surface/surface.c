struct xdg_surface *_sf_wlc_xdg_sf_p;

static void xdg_surface_listener_configure(void *data, struct xdg_surface *_xdg_surface, uint32_t serial)
{
	xdg_surface_ack_configure(_sf_wlc_xdg_sf_p, serial);
	wl_surface_commit(_sf_wlc_sf_p);
	_sf_state |= _SF_S_SURFACE;
}

struct xdg_surface_listener _sf_wlc_xdg_sf_listener =
{
	.configure = xdg_surface_listener_configure
};

void _sf_wlc_xdg_sf_set()
{
	NALI_D_INFO("xdg_wm_base_get_xdg_surface %p", _sf_wlc_xdg_sf_p = xdg_wm_base_get_xdg_surface(_sf_wlc_xdg_wmb_p, _sf_wlc_sf_p))
	NALI_D_INFO("xdg_surface_add_listener %d", xdg_surface_add_listener(_sf_wlc_xdg_sf_p, &_sf_wlc_xdg_sf_listener, NULL))
}

void _sf_wlc_xdg_sf_free()
{
	xdg_surface_destroy(_sf_wlc_xdg_sf_p);
}
