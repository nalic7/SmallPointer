#ifndef NALI_WAYLAND_CLIENT_KEYBOARD_H
#define NALI_WAYLAND_CLIENT_KEYBOARD_H
	extern struct wl_keyboard *s_wlc_seat_kb_p;

	extern struct wl_keyboard_listener s_wlc_seat_kb_listener;

	void s_wlc_seat_kb_free();
#endif
