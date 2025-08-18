static void xdg_toplevel_listener_configure(void* data, struct xdg_toplevel* _xdg_toplevel, int32_t width, int32_t height, struct wl_array* states)
{
// if (_xdg_toplevel == m_xdg_toplevel)
// {
	// info("run_xdg_toplevel_listener_configure w%d h%d", width, height)

	// if (width > 0 && height > 0)
	if (s_width != width || s_height != height)
	{
		s_width = width;
		s_height = height;
		wl_surface_commit(wlc_wl_surface_p);

		if (s_state & NALI_S_S_RENDER_ABLE)
			s_state |= NALI_S_S_RE;
	}

	// if (width > 0 && height > 0)
	// {
	//	 // Optionally resize your content or update layout here
	//	 // xdg_toplevel_set_min_size(xdg_toplevel, width, height);
	//	 // xdg_toplevel_set_max_size(xdg_toplevel, width, height);
	// }

// }
}

static void xdg_toplevel_listener_close(void* data, struct xdg_toplevel* xdg_toplevel)
{
	lb_free1();
}

static void xdg_toplevel_listener_configure_bounds(void* data, struct xdg_toplevel* xdg_toplevel, int32_t width, int32_t height)
{
	// info("xdg_toplevel_listener_configure_bounds")
}

static void xdg_toplevel_listener_wm_capabilities(void* data, struct xdg_toplevel* xdg_toplevel, struct wl_array* capabilities)
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
