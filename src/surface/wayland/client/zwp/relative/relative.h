#ifndef _SF_WLC_ZWP_R_H
	#define _SF_WLC_ZWP_R_H

	extern struct zwp_relative_pointer_manager_v1 *_sf_wlc_zwp_rp_mng_p;
	extern struct zwp_relative_pointer_v1 *_sf_wlc_zwp_rp_p;

	extern struct zwp_relative_pointer_v1_listener _sf_wlc_zwp_rp_listener;

	void _sf_wlc_zwp_rp_free();
#endif
