#ifndef SMPT_SF_WLC_H
	#define SMPT_SF_WLC_H

	extern struct wl_display *smpt_sf_wlc_dp_p;
	extern struct wl_compositor *smpt_sf_wlc_cot_p;
	extern struct wl_surface *smpt_sf_wlc_sf_p;

	void smpt_sf_wlc_set();
	void smpt_sf_wlc_free();
#endif
