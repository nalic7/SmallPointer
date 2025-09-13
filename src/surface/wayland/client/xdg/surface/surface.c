struct xdg_surface *smpt_sf_wl_ce_xdg_sf_p;

static void xdg_surface_listener_configure(void *data, struct xdg_surface *_xdg_surface, uint32_t serial)
{
	xdg_surface_ack_configure(smpt_sf_wl_ce_xdg_sf_p, serial);
	wl_surface_commit(smpt_sf_wl_ce_sf_p);
	#ifdef SMPT_CM_VK
		smpt_rd_vkMset();
	#endif
}

struct xdg_surface_listener smpt_sf_wl_ce_xdg_sf_listener =
{
	.configure = xdg_surface_listener_configure
};

void smpt_sf_wl_ce_xdg_sf_set()
{
	SMPT_DBmR2L("xdg_wm_base_get_xdg_surface %p", smpt_sf_wl_ce_xdg_sf_p = xdg_wm_base_get_xdg_surface(smpt_sf_wl_ce_xdg_wmb_p, smpt_sf_wl_ce_sf_p))
	SMPT_DBmR2L("xdg_surface_add_listener %d", xdg_surface_add_listener(smpt_sf_wl_ce_xdg_sf_p, &smpt_sf_wl_ce_xdg_sf_listener, NULL))
}

void smpt_sf_wl_ce_xdg_sf_free()
{
	xdg_surface_destroy(smpt_sf_wl_ce_xdg_sf_p);
}
