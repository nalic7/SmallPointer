static void xdg_wm_base_handle_ping(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial)
{
	xdg_wm_base_pong(xdg_wm_base, serial);
}

struct xdg_wm_base_listener swlcxdg_xdg_wm_base_listener =
{
	.ping = xdg_wm_base_handle_ping,
};