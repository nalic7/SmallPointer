static void xdg_toplevel_listener_configure(void* data, struct xdg_toplevel* _xdg_toplevel, int32_t width, int32_t height, struct wl_array* states)
{
// if (_xdg_toplevel == m_xdg_toplevel)
// {
	// info("run_xdg_toplevel_listener_configure w%d h%d", width, height)

	// if (width > 0 && height > 0)
	if (m_width != width || m_height != height)
	{
		m_width = width;
		m_height = height;
		wl_surface_commit(m_wl_surface_p);
		m_surface_state |= NALI_SURFACE_C_S_RE;
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
	info("xdg_toplevel_listener_close 0")
	m_surface_state |= NALI_SURFACE_C_S_CLEAN;
	al_clean();
	// while (m_vkinstance != VK_NULL_HANDLE || m_client_socket != -1)
	while (m_vkinstance != VK_NULL_HANDLE)
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}
	wlc_clean();
	info("xdg_toplevel_listener_close 1")
	#ifdef NALI_DEBUG
		debug_free();
	#endif
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