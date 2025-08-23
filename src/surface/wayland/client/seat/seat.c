struct wl_seat *_sf_wlc_seat_p;

static void wl_seat_listener_capabilities(void *data, struct wl_seat *wl_seat, uint32_t capabilities)
{
	if (capabilities & WL_SEAT_CAPABILITY_KEYBOARD)
	{
		NALI_D_INFO("wl_seat_get_keyboard %p", _sf_wlc_seat_kb_p = wl_seat_get_keyboard(wl_seat))
		NALI_D_INFO("wl_keyboard_add_listener %d", wl_keyboard_add_listener(_sf_wlc_seat_kb_p, &_sf_wlc_seat_kb_listener, NULL))
	}
	if (capabilities & WL_SEAT_CAPABILITY_POINTER)
	{
		NALI_D_INFO("wl_seat_get_pointer %p", _sf_wlc_seat_pt_p = wl_seat_get_pointer(wl_seat))
		NALI_D_INFO("wl_pointer_add_listener %d", wl_pointer_add_listener(_sf_wlc_seat_pt_p, &_sf_wlc_seat_pt_listener, NULL))
	}
}

struct wl_seat_listener _sf_wlc_seat_listener =
{
	.capabilities = wl_seat_listener_capabilities,
};

void _sf_wlc_seat_free()
{
	_sf_wlc_seat_kb_free();
	_sf_wlc_seat_pt_free();

	wl_seat_destroy(_sf_wlc_seat_p);
}
