#ifndef smpt_sf_wl_ce_H
	#define smpt_sf_wl_ce_H

	extern struct wl_display *smpt_sf_wl_ce_dp_p;
	extern struct wl_compositor *smpt_sf_wl_ce_cot_p;
	extern struct wl_surface *smpt_sf_wl_ce_sf_p;

	void smpt_sf_wl_ceMset();
	void smpt_sf_wl_ce_free();
#endif
