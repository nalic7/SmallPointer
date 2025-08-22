struct wl_seat *s_wlc_seat_p;

static void wl_seat_listener_capabilities(void *data, struct wl_seat *wl_seat, uint32_t capabilities)
{
	if (capabilities & WL_SEAT_CAPABILITY_KEYBOARD)
	{
		NALI_D_INFO("wl_seat_get_keyboard %p", s_wlc_seat_kb_p = wl_seat_get_keyboard(wl_seat))
		NALI_D_INFO("wl_keyboard_add_listener %d", wl_keyboard_add_listener(s_wlc_seat_kb_p, &s_wlc_seat_kb_listener, NULL))
	}
	if (capabilities & WL_SEAT_CAPABILITY_POINTER)
	{
		NALI_D_INFO("wl_seat_get_pointer %p", s_wlc_seatp_p = wl_seat_get_pointer(wl_seat))
		NALI_D_INFO("wl_pointer_add_listener %d", wl_pointer_add_listener(s_wlc_seatp_p, &s_wlc_seat_p_listener, NULL))
	}
}

struct wl_seat_listener s_wlc_seat_listener =
{
	.capabilities = wl_seat_listener_capabilities,
};

void s_wlc_seat_free()
{
	s_wlc_seat_kb_free();
	s_wlc_seat_p_free();

	wl_seat_destroy(s_wlc_seat_p);
}
