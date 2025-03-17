struct wl_display *m_wl_display_client_p;
struct wl_registry *m_wl_registry_p;
struct wl_compositor *m_wl_compositor_p;
struct wl_surface *m_wl_surface_p;

struct xdg_wm_base *m_xdg_wm_base_p;
struct xdg_surface *m_xdg_surface_p;
struct xdg_toplevel *m_xdg_toplevel_p;

struct wl_seat *m_wl_seat_p;
struct wl_keyboard *m_wl_keyboard_p;
struct wl_shm *m_wl_shm_p;
struct wl_pointer *m_wl_pointer_p;

struct zwp_pointer_constraints_v1 *m_zwp_pointer_constraints_v1_p;
struct zwp_locked_pointer_v1 *m_zwp_locked_pointer_v1_p;

struct zwp_relative_pointer_manager_v1 *m_zwp_relative_pointer_manager_v1_p;
struct zwp_relative_pointer_v1 *m_zwp_relative_pointer_v1_p;

static int loop(void* arg)
{
	int result;
	while ((m_surface_state & NALI_SURFACE_C_S_CLEAN) == 0)
	{
		result = wl_display_dispatch(m_wl_display_client_p);
		if (result < 0)
		{
			error("wl_display_dispatch")
		}
		wlcp_change_cursor(1);
	}

	error("wl_display_dispatch %d", result);
	//recreate?
	return 0;
}
void wlc_init()
{
	m_wl_display_client_p = wl_display_connect(getenv("WAYLAND_DISPLAY"));
	if (!m_wl_display_client_p)
	{
		error("wl_display_connect")
	}
	// info("wl_display_get_fd %d", wl_display_get_fd(m_wl_display_client))

	m_wl_registry_p = wl_display_get_registry(m_wl_display_client_p);
	if (!m_wl_registry_p)
	{
		error("wl_display_get_registry")
	}

	wl_registry_add_listener(m_wl_registry_p, &m_wl_registry_listener, NULL);
	int roundtrip = wl_display_roundtrip(m_wl_display_client_p);
	info("wl_display_roundtrip %d", roundtrip)
	wlcp_init_cursor();

	// if (!m_wl_compositor)
	// {
	// 	error("m_wl_compositor")
	// }

	m_wl_surface_p = wl_compositor_create_surface(m_wl_compositor_p);
	if (!m_wl_surface_p)
	{
		error("wl_compositor_create_surface")
	}

	m_xdg_surface_p = xdg_wm_base_get_xdg_surface(m_xdg_wm_base_p, m_wl_surface_p);
	m_xdg_toplevel_p = xdg_surface_get_toplevel(m_xdg_surface_p);

	xdg_surface_add_listener(m_xdg_surface_p, &m_xdg_surface_listener, NULL);
	xdg_toplevel_add_listener(m_xdg_toplevel_p, &m_xdg_toplevel_listener, NULL);

	wl_surface_commit(m_wl_surface_p);

	// int i;
	// do
	// {
	// 	i = wl_display_dispatch(m_wl_display_client);
	// 	info("wl_display_dispatch %d", i)
	// }
	// while (i != -1 && (m_surface_state & NALI_SURFACE_C_S_CONFIG) == 0);
	// wl_surface_commit(m_wl_surface);

	int i;
	while ((i = wl_display_dispatch(m_wl_display_client_p)) != 1)
	{
		info("wl_display_dispatch %d", i)
	}

	thrd_t thrd_t;
	if (thrd_create(&thrd_t, loop, NULL) != thrd_success)
	{
		error("thrd_create")
	}
}

void wlc_clean()
{
	if (m_wl_seat_p)
	{
		wl_seat_destroy(m_wl_seat_p);
	}
	if (m_wl_keyboard_p)
	{
		wl_keyboard_destroy(m_wl_keyboard_p);
	}
	if (m_wl_pointer_p)
	{
		wl_pointer_destroy(m_wl_pointer_p);
	}

	if (m_xdg_toplevel_p)
	{
		xdg_toplevel_destroy(m_xdg_toplevel_p);
	}
	if (m_xdg_surface_p)
	{
		xdg_surface_destroy(m_xdg_surface_p);
	}
	if (m_xdg_wm_base_p)
	{
		xdg_wm_base_destroy(m_xdg_wm_base_p);
	}

	if (m_zwp_locked_pointer_v1_p)
	{
		zwp_locked_pointer_v1_destroy(m_zwp_locked_pointer_v1_p);
	}
	if (m_zwp_pointer_constraints_v1_p)
	{
		zwp_pointer_constraints_v1_destroy(m_zwp_pointer_constraints_v1_p);
	}

	if (m_zwp_relative_pointer_v1_p)
	{
		zwp_relative_pointer_v1_destroy(m_zwp_relative_pointer_v1_p);
	}
	if (m_zwp_relative_pointer_manager_v1_p)
	{
		zwp_relative_pointer_manager_v1_destroy(m_zwp_relative_pointer_manager_v1_p);
	}

	if (m_wl_surface_p)
	{
		wl_surface_destroy(m_wl_surface_p);
	}
	if (m_wl_compositor_p)
	{
		wl_compositor_destroy(m_wl_compositor_p);
	}
	if (m_wl_shm_p)
	{
		wl_shm_destroy(m_wl_shm_p);
	}

	if (m_wl_registry_p)
	{
		wl_registry_destroy(m_wl_registry_p);
	}
	if (m_wl_display_client_p)
	{
		wl_display_disconnect(m_wl_display_client_p);
	}
}