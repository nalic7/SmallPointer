#ifndef NALI_WAYLAND_CLIENT_ZWP_RELATIVE_H
#define NALI_WAYLAND_CLIENT_ZWP_RELATIVE_H
	extern struct zwp_relative_pointer_manager_v1 *s_wlc_zwp_rp_manager_p;
	extern struct zwp_relative_pointer_v1 *s_wlc_zwp_rp_p;

	extern struct zwp_relative_pointer_v1_listener s_wlc_zwp_rp_listener;

	void s_wlc_zwp_rp_free();
#endif
