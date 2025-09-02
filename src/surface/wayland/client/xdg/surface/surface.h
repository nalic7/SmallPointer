#ifndef SMPT_SF_WLC_XDG_SF_H
	#define SMPT_SF_WLC_XDG_SF_H

	extern struct xdg_surface *smpt_sf_wlc_xdg_sf_p;

	extern struct xdg_surface_listener smpt_sf_wlc_xdg_sf_listener;

	void smpt_sf_wlc_xdg_sf_set();
	void smpt_sf_wlc_xdg_sf_free();
#endif
