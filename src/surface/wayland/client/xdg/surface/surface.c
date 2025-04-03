static void xdg_surface_listener_configure(void* data, struct xdg_surface* _xdg_surface, uint32_t serial)
{
	// info("xdg_surface_listener_configure")
	xdg_surface_ack_configure(m_xdg_surface_p, serial);
	wl_surface_commit(m_wl_surface_p);
}

struct xdg_surface_listener m_xdg_surface_listener =
{
	.configure = xdg_surface_listener_configure
};
