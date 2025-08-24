#ifndef _SF_WLC_RGT_H
#define _SF_WLC_RGT_H
	extern struct wl_registry *_sf_wlc_rgt_p;

	extern struct wl_registry_listener _sf_wlc_rgt_listener;

	void _sf_wlc_rgt_set();
	void _sf_wlc_rgt_free();
#endif
