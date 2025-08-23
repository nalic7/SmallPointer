#ifndef _SF_WLC_SEAT_PT_H
#define _SF_WLC_SEAT_PT_H
	extern struct wl_pointer *_sf_wlc_seat_pt_p;

	extern uint32_t _sf_wlcp_serial;

	extern struct wl_pointer_listener _sf_wlc_seat_pt_listener;

	void _sf_wlc_seat_pt_free();
#endif
