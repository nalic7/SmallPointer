#ifndef _SF_WLC_XDG_TL_H
	#define _SF_WLC_XDG_TL_H

	extern struct xdg_toplevel *_sf_wlc_xdg_tl_p;

	extern struct xdg_toplevel_listener _sf_wlc_xdg_tl_listener;

	void _sf_wlc_xdg_tl_set();
	void _sf_wlc_xdg_tl_free();
#endif
