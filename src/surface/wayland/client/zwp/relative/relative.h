#ifndef smpt_sf_wl_ce_ZWP_R_H
	#define smpt_sf_wl_ce_ZWP_R_H

	extern struct zwp_relative_pointer_manager_v1 *smpt_sf_wl_ce_zwp_rp_mng_p;
	extern struct zwp_relative_pointer_v1 *smpt_sf_wl_ce_zwp_rp_p;

	extern struct zwp_relative_pointer_v1_listener smpt_sf_wl_ce_zwp_rp_listener;

	void smpt_sf_wl_ce_zwp_rp_free();
#endif
