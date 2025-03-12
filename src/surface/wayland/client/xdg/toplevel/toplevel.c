static void xdg_toplevel_listener_configure(void* data, struct xdg_toplevel* _xdg_toplevel, int32_t width, int32_t height, struct wl_array* states)
{
	if (_xdg_toplevel == m_xdg_toplevel)
	{
		info("run_xdg_toplevel_listener_configure w%d h%d", width, height)

		if (width > 0 && height > 0)
		{
			m_width = width;
			m_height = height;
			wl_surface_commit(m_wl_surface);
			//recreate
		}

		// if (width > 0 && height > 0)
		// {
		//	 // Optionally resize your content or update layout here
		//	 // xdg_toplevel_set_min_size(xdg_toplevel, width, height);
		//	 // xdg_toplevel_set_max_size(xdg_toplevel, width, height);
		// }

	}
}

static void xdg_toplevel_listener_close(void* data, struct xdg_toplevel* xdg_toplevel)
{
	m_surface_state |= NALI_SURFACE_C_S_CLEAN;
	while (m_vkinstance != VK_NULL_HANDLE)
	{
		struct timespec ts = {1, 0};
		thrd_sleep(&ts, NULL);
	}
	wlc_clean();
	exit(EXIT_SUCCESS);
}

static void xdg_toplevel_listener_configure_bounds(void* data, struct xdg_toplevel* xdg_toplevel, int32_t width, int32_t height)
{
	// info("xdg_toplevel_listener_configure_bounds")
}

static void xdg_toplevel_listener_wm_capabilities(void* data, struct xdg_toplevel* xdg_toplevel, struct wl_array* capabilities)
{
	// info("xdg_toplevel_listener_wm_capabilities")
}

struct xdg_toplevel_listener m_xdg_toplevel_listener =
{
	.configure = xdg_toplevel_listener_configure,
	.close = xdg_toplevel_listener_close,
	.configure_bounds = xdg_toplevel_listener_configure_bounds,
	.wm_capabilities = xdg_toplevel_listener_wm_capabilities
};