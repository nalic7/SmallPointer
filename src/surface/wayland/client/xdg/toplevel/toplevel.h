#ifndef SMPT_SF_WLC_XDG_TL_H
	#define SMPT_SF_WLC_XDG_TL_H

	extern struct xdg_toplevel *smpt_sf_wlc_xdg_tl_p;

	extern struct xdg_toplevel_listener smpt_sf_wlc_xdg_tl_listener;

	void smpt_sf_wlc_xdg_tl_set();
	void smpt_sf_wlc_xdg_tl_free();
#endif
