#ifndef _SF_WLC_XDG_SF_H
	#define _SF_WLC_XDG_SF_H

	extern struct xdg_surface *_sf_wlc_xdg_sf_p;

	extern struct xdg_surface_listener _sf_wlc_xdg_sf_listener;

	void _sf_wlc_xdg_sf_set();
	void _sf_wlc_xdg_sf_free();
#endif
