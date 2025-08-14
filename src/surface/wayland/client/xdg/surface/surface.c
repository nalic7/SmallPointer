static void xdg_surface_listener_configure(void* data, struct xdg_surface* _xdg_surface, uint32_t serial)
{
	// info("xdg_surface_listener_configure")
	xdg_surface_ack_configure(wlc_xdg_surface_p, serial);
	wl_surface_commit(wlc_wl_surface_p);
	s_state |= NALI_S_S_RENDER_ABLE;
}

struct xdg_surface_listener swlcxdg_xdg_surface_listener =
{
	.configure = xdg_surface_listener_configure
};
