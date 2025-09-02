#ifndef SMPT_SF_WLC_RGT_H
	#define SMPT_SF_WLC_RGT_H

	extern struct wl_registry *smpt_sf_wlc_rgt_p;

	extern struct wl_registry_listener smpt_sf_wlc_rgt_listener;

	void smpt_sf_wlc_rgt_set();
	void smpt_sf_wlc_rgt_free();
#endif
