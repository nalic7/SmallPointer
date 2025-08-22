struct xdg_surface *s_wlc_xdgs_p;

static void xdg_surface_listener_configure(void *data, struct xdg_surface *_xdg_surface, uint32_t serial)
{
	xdg_surface_ack_configure(s_wlc_xdgs_p, serial);
	wl_surface_commit(s_wlcs_p);
	s_state |= NALI_S_S_RENDER_ABLE;
}

struct xdg_surface_listener s_wlc_xdgs_listener =
{
	.configure = xdg_surface_listener_configure
};

void s_wlc_xdgs_set()
{
	NALI_D_INFO("xdg_wm_base_get_xdg_surface %p", s_wlc_xdgs_p = xdg_wm_base_get_xdg_surface(s_wlc_xdg_wm_base_p, s_wlcs_p))
	NALI_D_INFO("xdg_surface_add_listener %d", xdg_surface_add_listener(s_wlc_xdgs_p, &s_wlc_xdgs_listener, NULL))
}

void s_wlc_xdgs_free()
{
	xdg_surface_destroy(s_wlc_xdgs_p);
}
