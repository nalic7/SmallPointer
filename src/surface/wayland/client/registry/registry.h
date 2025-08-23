#ifndef _SF_WLC_RTR_H
#define _SF_WLC_RTR_H
	extern struct wl_registry *_sf_wlc_rtr_p;

	extern struct wl_registry_listener _sf_wlc_rtr_listener;

	void _sf_wlc_rtr_set();
	void _sf_wlc_rtr_free();
#endif
