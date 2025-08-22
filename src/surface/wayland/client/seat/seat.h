#ifndef NALI_WAYLAND_CLIENT_SEAT_H
#define NALI_WAYLAND_CLIENT_SEAT_H
	extern struct wl_seat *s_wlc_seat_p;

	extern struct wl_seat_listener s_wlc_seat_listener;

	void s_wlc_seat_free();
#endif
