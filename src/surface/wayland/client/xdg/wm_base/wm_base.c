struct xdg_wm_base *s_wlc_xdg_wm_base_p;

static void xdg_wm_base_handle_ping(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial)
{
	xdg_wm_base_pong(xdg_wm_base, serial);
}

struct xdg_wm_base_listener s_wlc_xdg_wm_base_listener =
{
	.ping = xdg_wm_base_handle_ping,
};

void s_wlc_xdg_wm_base_free()
{
	s_wlc_xdg_tl_free();
	s_wlc_xdgs_free();

	xdg_wm_base_destroy(s_wlc_xdg_wm_base_p);
}
