#ifndef NALI_WAYLAND_CLIENT_TOPLEVEL_H
#define NALI_WAYLAND_CLIENT_TOPLEVEL_H
	extern struct xdg_toplevel *s_wlc_xdg_tl_p;

	extern struct xdg_toplevel_listener swlcxdg_xdg_toplevel_listener;

	void s_wlc_xdg_tl_set();
	void s_wlc_xdg_tl_free();
#endif
