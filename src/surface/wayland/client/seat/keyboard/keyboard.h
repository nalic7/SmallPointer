#ifndef _SF_WLC_SEAT_KB_H
#define _SF_WLC_SEAT_KB_H
	extern struct wl_keyboard *_sf_wlc_seat_kb_p;

	extern struct wl_keyboard_listener _sf_wlc_seat_kb_listener;

	void _sf_wlc_seat_kb_free();
#endif
