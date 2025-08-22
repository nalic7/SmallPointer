#ifndef NALI_WAYLAND_CLIENT_ZWP_LOCKED_H
#define NALI_WAYLAND_CLIENT_ZWP_LOCKED_H
	extern struct zwp_locked_pointer_v1 *s_wlc_zwp_lp_p;

	extern struct zwp_locked_pointer_v1_listener s_wlc_zwp_lp_listener;

	void s_wlc_zwp_lp_free();
#endif
