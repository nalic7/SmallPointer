static void xdg_surface_listener_configure(void* data, struct xdg_surface* _xdg_surface, uint32_t serial)
{
	xdg_surface_ack_configure(m_xdg_surface, serial);
	// if ((state & NALI_SURFACE_C_S_CONFIG) == 0)
	// {
	// 	state |= NALI_SURFACE_C_S_CONFIG;
	// }
	// else
	// {
	wl_surface_commit(m_wl_surface);
	// }
}

struct xdg_surface_listener m_xdg_surface_listener =
{
	.configure = xdg_surface_listener_configure
};
