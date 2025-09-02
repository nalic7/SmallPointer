#ifndef SMPT_SF_WLCS_H
	#define SMPT_SF_WLCS_H

	extern struct wl_seat *smpt_sf_wlcs_p;

	extern struct wl_seat_listener smpt_sf_wlcs_listener;

	void smpt_sf_wlcs_free();
#endif
