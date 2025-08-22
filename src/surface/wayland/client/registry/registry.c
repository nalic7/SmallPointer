struct wl_registry *s_wlc_r_p;

static void wl_registry_listener_global(void *data, struct wl_registry *wl_registry, uint32_t name, const char *interface, uint32_t version)
{
	NALI_D_LOG("wl_registry_listener_global_interface %s", interface)
	if (!strcmp(interface, wl_compositor_interface.name))
	{
		NALI_D_INFO("wl_registry_bind %p", s_wlcc_p = wl_registry_bind(wl_registry, name, &wl_compositor_interface, 1))
	}
	else if (!strcmp(interface, xdg_wm_base_interface.name))
	{
		NALI_D_INFO("wl_registry_bind %p", s_wlc_xdg_wm_base_p = wl_registry_bind(wl_registry, name, &xdg_wm_base_interface, 1))
		NALI_D_INFO("xdg_wm_base_add_listener %d", xdg_wm_base_add_listener(s_wlc_xdg_wm_base_p, &s_wlc_xdg_wm_base_listener, NULL))
	}
	else if (!strcmp(interface, wl_seat_interface.name))
	{
		NALI_D_INFO("wl_registry_bind %p", s_wlc_seat_p = wl_registry_bind(wl_registry, name, &wl_seat_interface, 1))
		NALI_D_INFO("wl_seat_add_listener %d", wl_seat_add_listener(s_wlc_seat_p, &s_wlc_seat_listener, NULL))
	}
	else if (!strcmp(interface, zwp_pointer_constraints_v1_interface.name))
	{
		NALI_D_INFO("wl_registry_bind %p", s_wlc_zwp_pc_p = wl_registry_bind(wl_registry, name, &zwp_pointer_constraints_v1_interface, 1))
	}
	else if (!strcmp( interface, zwp_relative_pointer_manager_v1_interface.name))
	{
		NALI_D_INFO("wl_registry_bind %p", s_wlc_zwp_rp_manager_p = wl_registry_bind(wl_registry, name, &zwp_relative_pointer_manager_v1_interface, 1))
	}
}

static void wl_registry_listener_global_remove(void *data, struct wl_registry *wl_registry, uint32_t name)
{
}

struct wl_registry_listener s_wlc_r_listener =
{
	.global = wl_registry_listener_global,
	.global_remove = wl_registry_listener_global_remove
};

void s_wlc_r_set()
{
	NALI_D_INFO("wl_display_get_registry %p", s_wlc_r_p = wl_display_get_registry(s_wlcd_p))
	NALI_D_INFO("wl_registry_add_listener %d", wl_registry_add_listener(s_wlc_r_p, &s_wlc_r_listener, NULL))
}

void s_wlc_r_free()
{
	wl_registry_destroy(s_wlc_r_p);
}
