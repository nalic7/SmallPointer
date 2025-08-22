#ifndef NALI_WAYLAND_CLIENT_WM_BASE_H
#define NALI_WAYLAND_CLIENT_WM_BASE_H
	extern struct xdg_wm_base *s_wlc_xdg_wm_base_p;

	extern struct xdg_wm_base_listener s_wlc_xdg_wm_base_listener;

	void s_wlc_xdg_wm_base_free();
#endif
