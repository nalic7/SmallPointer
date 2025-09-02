#ifndef SMPT_SF_WLC_ZWP_L_H
	#define SMPT_SF_WLC_ZWP_L_H

	extern struct zwp_locked_pointer_v1 *smpt_sf_wlc_zwp_lp_p;

	extern struct zwp_locked_pointer_v1_listener smpt_sf_wlc_zwp_lp_listener;

	void smpt_sf_wlc_zwp_lp_free();
#endif
