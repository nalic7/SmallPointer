static void wl_seat_listener_capabilities(void* data, struct wl_seat* wl_seat, uint32_t capabilities)
{
	if (capabilities & WL_SEAT_CAPABILITY_KEYBOARD)
	{
		nali_info("wl_seat_get_keyboard %p", m_wl_keyboard_p = wl_seat_get_keyboard(wl_seat))
		nali_info("wl_keyboard_add_listener %d", wl_keyboard_add_listener(m_wl_keyboard_p, &m_wl_keyboard_listener, NULL))
	}
	if (capabilities & WL_SEAT_CAPABILITY_POINTER)
	{
		nali_info("wl_seat_get_pointer %p", m_wl_pointer_p = wl_seat_get_pointer(wl_seat))
		nali_info("wl_pointer_add_listener %d", wl_pointer_add_listener(m_wl_pointer_p, &m_wl_pointer_listener, NULL))
	}
}

struct wl_seat_listener m_wl_seat_listener =
{
	.capabilities = wl_seat_listener_capabilities,
};