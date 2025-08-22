#ifndef NALI_WAYLAND_CLIENT_REGISTER_H
#define NALI_WAYLAND_CLIENT_REGISTER_H
	extern struct wl_registry *s_wlc_r_p;

	extern struct wl_registry_listener s_wlc_r_listener;

	void s_wlc_r_set();
	void s_wlc_r_free();
#endif
