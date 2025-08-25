#ifndef _SF_WLC_H
	#define _SF_WLC_H

	extern struct wl_display *_sf_wlc_dp_p;
	extern struct wl_compositor *_sf_wlc_cot_p;
	extern struct wl_surface *_sf_wlc_sf_p;

	void _sf_wlc_set();
	void _sf_wlc_free();
#endif
