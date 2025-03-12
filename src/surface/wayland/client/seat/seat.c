static void wl_seat_listener_capabilities(void* data, struct wl_seat* wl_seat, uint32_t capabilities)
{
	if (capabilities & WL_SEAT_CAPABILITY_KEYBOARD)
	{
		m_wl_keyboard = wl_seat_get_keyboard(wl_seat);
		wl_keyboard_add_listener(m_wl_keyboard, &m_wl_keyboard_listener, NULL);
	}
	if (capabilities & WL_SEAT_CAPABILITY_POINTER)
	{
		m_wl_pointer = wl_seat_get_pointer(wl_seat);
		wl_pointer_add_listener(m_wl_pointer, &m_wl_pointer_listener, NULL);
	}
}

struct wl_seat_listener m_wl_seat_listener =
{
	.capabilities = wl_seat_listener_capabilities,
};