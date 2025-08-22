#ifndef NALI_WAYLAND_CLIENT_SURFACE_H
#define NALI_WAYLAND_CLIENT_SURFACE_H
	extern struct xdg_surface *s_wlc_xdgs_p;

	extern struct xdg_surface_listener s_wlc_xdgs_listener;

	void s_wlc_xdgs_set();
	void s_wlc_xdgs_free();
#endif
