static void wl_registry_listener_global(void* data, struct wl_registry* wl_registry, uint32_t name, const char* interface, uint32_t version)
{
	info("wl_registry_listener_global_interface %s", interface)
	if (strcmp(interface, wl_compositor_interface.name) == 0)
	{
		m_wl_compositor = wl_registry_bind(wl_registry, name, &wl_compositor_interface, 1);
	}
	else if (strcmp(interface, xdg_wm_base_interface.name) == 0)
	{
		m_xdg_wm_base = wl_registry_bind(wl_registry, name, &xdg_wm_base_interface, 1);
		xdg_wm_base_add_listener(m_xdg_wm_base, &m_xdg_wm_base_listener, NULL);
	}
	else if (strcmp(interface, wl_seat_interface.name) == 0)
	{
		m_wl_seat = wl_registry_bind(wl_registry, name, &wl_seat_interface, 1);
		wl_seat_add_listener(m_wl_seat, &m_wl_seat_listener, NULL);
	}
}

static void wl_registry_listener_global_remove(void* data, struct wl_registry* wl_registry, uint32_t name)
{
}

struct wl_registry_listener m_wl_registry_listener =
{
	.global = wl_registry_listener_global,
	.global_remove = wl_registry_listener_global_remove
};