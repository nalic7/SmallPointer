struct xdg_toplevel *s_wlc_xdg_tl_p;

static void xdg_toplevel_listener_configure(void *data, struct xdg_toplevel *_xdg_toplevel, int32_t width, int32_t height, struct wl_array *states)
{
	if (s_state & NALI_S_S_RENDER_ABLE)
	{
		if (s_width != width || s_height != height)
		{
			s_width = width;
			s_height = height;
			wl_surface_commit(s_wlcs_p);

			s_state |= NALI_S_S_RE;
		}
	}
}

static void xdg_toplevel_listener_close(void *data, struct xdg_toplevel *xdg_toplevel)
{
	lb_free1();
}

static void xdg_toplevel_listener_configure_bounds(void *data, struct xdg_toplevel *xdg_toplevel, int32_t width, int32_t height)
{
	// info("xdg_toplevel_listener_configure_bounds")
}

static void xdg_toplevel_listener_wm_capabilities(void *data, struct xdg_toplevel *xdg_toplevel, struct wl_array *capabilities)
{
	// info("xdg_toplevel_listener_wm_capabilities")
}

struct xdg_toplevel_listener swlcxdg_xdg_toplevel_listener =
{
	.configure = xdg_toplevel_listener_configure,
	.close = xdg_toplevel_listener_close,
	.configure_bounds = xdg_toplevel_listener_configure_bounds,
	.wm_capabilities = xdg_toplevel_listener_wm_capabilities
};

void s_wlc_xdg_tl_set()
{
	NALI_D_INFO("xdg_surface_get_toplevel %p", s_wlc_xdg_tl_p = xdg_surface_get_toplevel(s_wlc_xdgs_p))
	NALI_D_INFO("xdg_toplevel_add_listener %d", xdg_toplevel_add_listener(s_wlc_xdg_tl_p, &swlcxdg_xdg_toplevel_listener, NULL))
}

void s_wlc_xdg_tl_free()
{
	xdg_toplevel_destroy(s_wlc_xdg_tl_p);
}
