struct wl_display* m_wl_display_client;
struct wl_registry* m_wl_registry;
struct wl_compositor* m_wl_compositor;
struct wl_surface* m_wl_surface;

struct xdg_wm_base* m_xdg_wm_base;
struct xdg_surface* m_xdg_surface;
struct xdg_toplevel* m_xdg_toplevel;

struct wl_seat* m_wl_seat;
struct wl_keyboard* m_wl_keyboard;
struct wl_pointer* m_wl_pointer;

static int loop(void* arg)
{
	int result;
	while ((m_surface_state & NALI_SURFACE_C_S_CLEAN) == 0)
	{
		result = wl_display_dispatch(m_wl_display_client);
		if (result < 0)
		{
			error("wl_display_dispatch")
		}
	}

	error("wl_display_dispatch %d", result);
	//recreate?
	return 0;
}
void wlc_init()
{
	m_wl_display_client = wl_display_connect(NULL);
	if (!m_wl_display_client)
	{
		error("wl_display_connect")
	}
	// info("wl_display_get_fd %d", wl_display_get_fd(m_wl_display_client))

	m_wl_registry = wl_display_get_registry(m_wl_display_client);
	if (!m_wl_registry)
	{
		error("wl_display_get_registry")
	}

	wl_registry_add_listener(m_wl_registry, &m_wl_registry_listener, NULL);
	int roundtrip = wl_display_roundtrip(m_wl_display_client);
	info("wl_display_roundtrip %d", roundtrip)

	// if (!m_wl_compositor)
	// {
	// 	error("m_wl_compositor")
	// }

	m_wl_surface = wl_compositor_create_surface(m_wl_compositor);
	if (!m_wl_surface)
	{
		error("wl_compositor_create_surface")
	}

	m_width = 1;
	m_height = 1;

	m_xdg_surface = xdg_wm_base_get_xdg_surface(m_xdg_wm_base, m_wl_surface);
	m_xdg_toplevel = xdg_surface_get_toplevel(m_xdg_surface);

	xdg_surface_add_listener(m_xdg_surface, &m_xdg_surface_listener, NULL);
	xdg_toplevel_add_listener(m_xdg_toplevel, &m_xdg_toplevel_listener, NULL);

	wl_surface_commit(m_wl_surface);

	// int i;
	// do
	// {
	// 	i = wl_display_dispatch(m_wl_display_client);
	// 	info("wl_display_dispatch %d", i)
	// }
	// while (i != -1 && (m_surface_state & NALI_SURFACE_C_S_CONFIG) == 0);
	// wl_surface_commit(m_wl_surface);

	// int i;
	// while ((i = wl_display_dispatch(m_wl_display_client)) != 1)
	// {
	// 	info("wl_display_dispatch %d", i)
	// }

	thrd_t thread;
	if (thrd_create(&thread, loop, NULL) != thrd_success)
	{
		error("thrd_create")
	}
}

void wlc_clean()
{
	if (m_wl_seat)
	{
		wl_seat_destroy(m_wl_seat);
	}
	if (m_wl_keyboard)
	{
		wl_keyboard_destroy(m_wl_keyboard);
	}
	if (m_wl_pointer)
	{
		wl_pointer_destroy(m_wl_pointer);
	}

	if (m_xdg_toplevel)
	{
		xdg_toplevel_destroy(m_xdg_toplevel);
	}
	if (m_xdg_surface)
	{
		xdg_surface_destroy(m_xdg_surface);
	}
	if (m_xdg_wm_base)
	{
		xdg_wm_base_destroy(m_xdg_wm_base);
	}

	if (m_wl_surface)
	{
		wl_surface_destroy(m_wl_surface);
	}
	if (m_wl_compositor)
	{
		wl_compositor_destroy(m_wl_compositor);
	}
	// if (wl_registry)
	// {
	// 	wl_registry_destroy(wl_registry);
	// }
	if (m_wl_display_client)
	{
		wl_display_disconnect(m_wl_display_client);
	}
}