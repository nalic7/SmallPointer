struct xdg_wm_base *_sf_wlc_xdg_wmb_p;

static void xdg_wm_base_handle_ping(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial)
{
	xdg_wm_base_pong(xdg_wm_base, serial);
}

struct xdg_wm_base_listener _sf_wlc_xdg_wmb_listener =
{
	.ping = xdg_wm_base_handle_ping,
};

void _sf_wlc_xdg_wmb_free()
{
	_sf_wlc_xdg_tl_free();
	_sf_wlc_xdg_sf_free();

	xdg_wm_base_destroy(_sf_wlc_xdg_wmb_p);
}
