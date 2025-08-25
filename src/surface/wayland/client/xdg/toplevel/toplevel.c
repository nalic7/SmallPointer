struct xdg_toplevel *_sf_wlc_xdg_tl_p;

static void xdg_toplevel_listener_configure(void *data, struct xdg_toplevel *_xdg_toplevel, int32_t width, int32_t height, struct wl_array *states)
{
	if (_sf_state & _SF_S_SURFACE)
	{
		if (_sf_width != width || _sf_height != height)
		{
			_sf_width = width;
			_sf_height = height;
			wl_surface_commit(_sf_wlc_sf_p);

			_sf_state |= _SF_S_RE;
		}
	}
}

static void xdg_toplevel_listener_close(void *data, struct xdg_toplevel *xdg_toplevel)
{
	lb_free1();
}

static void xdg_toplevel_listener_configure_bounds(void *data, struct xdg_toplevel *xdg_toplevel, int32_t width, int32_t height)
{
	// info("xdg_toplevel_listener_configure_bounds")
}

static void xdg_toplevel_listener_wm_capabilities(void *data, struct xdg_toplevel *xdg_toplevel, struct wl_array *capabilities)
{
	// info("xdg_toplevel_listener_wm_capabilities")
}

struct xdg_toplevel_listener _sf_wlc_xdg_tl_listener =
{
	.configure = xdg_toplevel_listener_configure,
	.close = xdg_toplevel_listener_close,
	.configure_bounds = xdg_toplevel_listener_configure_bounds,
	.wm_capabilities = xdg_toplevel_listener_wm_capabilities
};

void _sf_wlc_xdg_tl_set()
{
	_DB_R2L("xdg_surface_get_toplevel %p", _sf_wlc_xdg_tl_p = xdg_surface_get_toplevel(_sf_wlc_xdg_sf_p))
	_DB_R2L("xdg_toplevel_add_listener %d", xdg_toplevel_add_listener(_sf_wlc_xdg_tl_p, &_sf_wlc_xdg_tl_listener, NULL))
}

void _sf_wlc_xdg_tl_free()
{
	xdg_toplevel_destroy(_sf_wlc_xdg_tl_p);
}
