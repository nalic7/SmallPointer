struct wl_registry *_sf_wlc_rgt_p;

static void wl_registry_listener_global(void *data, struct wl_registry *wl_registry, uint32_t name, const char *interface, uint32_t version)
{
	_DB_N2L("wl_registry_listener_global_interface %s", interface)
	if (!strcmp(interface, wl_compositor_interface.name))
	{
		_DB_R2L("wl_registry_bind %p", _sf_wlc_cot_p = wl_registry_bind(wl_registry, name, &wl_compositor_interface, 1))
	}
	else if (!strcmp(interface, xdg_wm_base_interface.name))
	{
		_DB_R2L("wl_registry_bind %p", _sf_wlc_xdg_wmb_p = wl_registry_bind(wl_registry, name, &xdg_wm_base_interface, 1))
		_DB_R2L("xdg_wm_base_add_listener %d", xdg_wm_base_add_listener(_sf_wlc_xdg_wmb_p, &_sf_wlc_xdg_wmb_listener, NULL))
	}
	else if (!strcmp(interface, wl_seat_interface.name))
	{
		_DB_R2L("wl_registry_bind %p", _sf_wlcs_p = wl_registry_bind(wl_registry, name, &wl_seat_interface, 1))
		_DB_R2L("wl_seat_add_listener %d", wl_seat_add_listener(_sf_wlcs_p, &_sf_wlcs_listener, NULL))
	}
	else if (!strcmp(interface, zwp_pointer_constraints_v1_interface.name))
	{
		_DB_R2L("wl_registry_bind %p", _sf_wlc_zwp_pc_p = wl_registry_bind(wl_registry, name, &zwp_pointer_constraints_v1_interface, 1))
	}
	else if (!strcmp( interface, zwp_relative_pointer_manager_v1_interface.name))
	{
		_DB_R2L("wl_registry_bind %p", _sf_wlc_zwp_rp_mng_p = wl_registry_bind(wl_registry, name, &zwp_relative_pointer_manager_v1_interface, 1))
	}
}

static void wl_registry_listener_global_remove(void *data, struct wl_registry *wl_registry, uint32_t name)
{
}

struct wl_registry_listener _sf_wlc_rgt_listener =
{
	.global = wl_registry_listener_global,
	.global_remove = wl_registry_listener_global_remove
};

void _sf_wlc_rgt_set()
{
	_DB_R2L("wl_display_get_registry %p", _sf_wlc_rgt_p = wl_display_get_registry(_sf_wlc_dp_p))
	_DB_R2L("wl_registry_add_listener %d", wl_registry_add_listener(_sf_wlc_rgt_p, &_sf_wlc_rgt_listener, NULL))
}

void _sf_wlc_rgt_free()
{
	wl_registry_destroy(_sf_wlc_rgt_p);
}
