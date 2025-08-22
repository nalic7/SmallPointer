#ifndef NALI_WAYLAND_CLIENT_H
#define NALI_WAYLAND_CLIENT_H
	extern struct wl_display *s_wlcd_p;
	extern struct wl_compositor *s_wlcc_p;
	extern struct wl_surface *s_wlcs_p;

	void s_wlc_set();
	void s_wlc_free();
#endif
