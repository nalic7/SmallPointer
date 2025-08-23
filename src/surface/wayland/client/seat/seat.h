#ifndef _SF_WLC_SEAT_H
#define _SF_WLC_SEAT_H
	extern struct wl_seat *_sf_wlc_seat_p;

	extern struct wl_seat_listener _sf_wlc_seat_listener;

	void _sf_wlc_seat_free();
#endif
