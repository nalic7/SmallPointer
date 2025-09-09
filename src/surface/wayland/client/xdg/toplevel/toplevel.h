#ifndef smpt_sf_wl_ce_XDG_TL_H
	#define smpt_sf_wl_ce_XDG_TL_H

	extern struct xdg_toplevel *smpt_sf_wl_ce_xdg_tl_p;

	extern struct xdg_toplevel_listener smpt_sf_wl_ce_xdg_tl_listener;

	void smpt_sf_wl_ce_xdg_tl_set();
	void smpt_sf_wl_ce_xdg_tl_free();
#endif
