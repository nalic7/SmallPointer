struct wl_display *m_wl_display_client_p = NULL;
struct wl_registry *m_wl_registry_p = NULL;
struct wl_compositor *m_wl_compositor_p = NULL;
struct wl_surface *m_wl_surface_p = NULL;

struct xdg_wm_base *m_xdg_wm_base_p = NULL;
struct xdg_surface *m_xdg_surface_p = NULL;
struct xdg_toplevel *m_xdg_toplevel_p = NULL;

struct wl_seat *m_wl_seat_p = NULL;
struct wl_keyboard *m_wl_keyboard_p = NULL;
struct wl_shm *m_wl_shm_p = NULL;
struct wl_pointer *m_wl_pointer_p = NULL;
// struct wl_touch *m_wl_touch_p = NULL;

struct zwp_pointer_constraints_v1 *m_zwp_pointer_constraints_v1_p = NULL;
struct zwp_locked_pointer_v1 *m_zwp_locked_pointer_v1_p = NULL;

struct zwp_relative_pointer_manager_v1 *m_zwp_relative_pointer_manager_v1_p = NULL;
struct zwp_relative_pointer_v1 *m_zwp_relative_pointer_v1_p = NULL;

void wlc_clean()
{
	if (m_wl_seat_p)
	{
		wl_seat_destroy(m_wl_seat_p);
		m_wl_seat_p = NULL;
	}
	if (m_wl_keyboard_p)
	{
		wl_keyboard_destroy(m_wl_keyboard_p);
		m_wl_keyboard_p = NULL;
	}
	if (m_wl_pointer_p)
	{
		wl_pointer_destroy(m_wl_pointer_p);
		m_wl_pointer_p = NULL;
	}

	if (m_xdg_toplevel_p)
	{
		xdg_toplevel_destroy(m_xdg_toplevel_p);
		m_xdg_toplevel_p = NULL;
	}
	if (m_xdg_surface_p)
	{
		xdg_surface_destroy(m_xdg_surface_p);
		m_xdg_surface_p = NULL;
	}
	if (m_xdg_wm_base_p)
	{
		xdg_wm_base_destroy(m_xdg_wm_base_p);
		m_xdg_wm_base_p = NULL;
	}

	if (m_zwp_locked_pointer_v1_p)
	{
		zwp_locked_pointer_v1_destroy(m_zwp_locked_pointer_v1_p);
		m_zwp_locked_pointer_v1_p = NULL;
	}
	if (m_zwp_pointer_constraints_v1_p)
	{
		zwp_pointer_constraints_v1_destroy(m_zwp_pointer_constraints_v1_p);
		m_zwp_pointer_constraints_v1_p = NULL;
	}

	if (m_zwp_relative_pointer_v1_p)
	{
		zwp_relative_pointer_v1_destroy(m_zwp_relative_pointer_v1_p);
		m_zwp_relative_pointer_v1_p = NULL;
	}
	if (m_zwp_relative_pointer_manager_v1_p)
	{
		zwp_relative_pointer_manager_v1_destroy(m_zwp_relative_pointer_manager_v1_p);
		m_zwp_relative_pointer_manager_v1_p = NULL;
	}

	if (m_wl_surface_p)
	{
		wl_surface_destroy(m_wl_surface_p);
		m_wl_surface_p = NULL;
	}
	if (m_wl_compositor_p)
	{
		wl_compositor_destroy(m_wl_compositor_p);
		m_wl_compositor_p = NULL;
	}
	if (m_wl_shm_p)
	{
		wl_shm_destroy(m_wl_shm_p);
		m_wl_shm_p = NULL;
	}

	if (m_wl_registry_p)
	{
		wl_registry_destroy(m_wl_registry_p);
		m_wl_registry_p = NULL;
	}
	if (m_wl_display_client_p)
	{
		wl_display_disconnect(m_wl_display_client_p);
		m_wl_display_client_p = NULL;
	}
}

static int loop(void* arg)
{
	while (!(m_surface_state & NALI_SURFACE_C_S_CONFIG))
	{
		thrd_sleep(&(struct timespec){.tv_sec = 1, .tv_nsec = 0}, NULL);
	}

	int r = wl_display_dispatch(m_wl_display_client_p);
	while (r > -1 && r != INT_MAX)
	{
		if (m_surface_state & NALI_SURFACE_C_S_CLEAN)
		{
			r = INT_MAX;
		}
		else
		{
			wlcp_change_cursor(1);
			r = wl_display_dispatch(m_wl_display_client_p);
		}
	}

	if (r < 0)
	{
		nali_log("wl_display_dispatch %d", r);
		wlc_clean();
		wlc_init();
		//if surface fail on vk need re vksurface
	}
	return 0;
}
void wlc_init()
{
	nali_info("wl_display_connect %p", m_wl_display_client_p = wl_display_connect(getenv("WAYLAND_DISPLAY")))
	// info("wl_display_get_fd %d", wl_display_get_fd(m_wl_display_client))

	nali_info("wl_display_get_registry %p", m_wl_registry_p = wl_display_get_registry(m_wl_display_client_p))

	nali_info("wl_registry_add_listener %d", wl_registry_add_listener(m_wl_registry_p, &m_wl_registry_listener, NULL))
	nali_info("wl_display_roundtrip %d", wl_display_roundtrip(m_wl_display_client_p))
	wlcp_init_cursor();

	// if (!m_wl_compositor)
	// {
	// 	error("m_wl_compositor")
	// }

	nali_info("wl_compositor_create_surface %p", m_wl_surface_p = wl_compositor_create_surface(m_wl_compositor_p))

	nali_info("xdg_wm_base_get_xdg_surface %p", m_xdg_surface_p = xdg_wm_base_get_xdg_surface(m_xdg_wm_base_p, m_wl_surface_p))
	nali_info("xdg_surface_get_toplevel %p", m_xdg_toplevel_p = xdg_surface_get_toplevel(m_xdg_surface_p))

	nali_info("xdg_surface_add_listener %d", xdg_surface_add_listener(m_xdg_surface_p, &m_xdg_surface_listener, NULL))
	nali_info("xdg_toplevel_add_listener %d", xdg_toplevel_add_listener(m_xdg_toplevel_p, &m_xdg_toplevel_listener, NULL))

	wl_surface_commit(m_wl_surface_p);

	nali_info("thrd_create %d", thrd_create(&(thrd_t){}, loop, NULL))
}