#ifndef NALI_WAYLAND_CLIENT_POINTER_H
#define NALI_WAYLAND_CLIENT_POINTER_H
	extern struct wl_pointer *s_wlc_seat_p_p;

	extern struct wl_pointer_listener s_wlc_seat_p_listener;

	void s_wlc_seat_p_free();
#endif
