struct wl_seat *smpt_sf_wl_ces_p;

static void wl_seat_listener_capabilities(void *data, struct wl_seat *wl_seat, uint32_t capabilities)
{
	if (capabilities & WL_SEAT_CAPABILITY_KEYBOARD)
	{
		SMPT_DBmR2L("wl_seat_get_keyboard %p", smpt_sf_wl_ces_kb_p = wl_seat_get_keyboard(wl_seat))
		SMPT_DBmR2L("wl_keyboard_add_listener %d", wl_keyboard_add_listener(smpt_sf_wl_ces_kb_p, &smpt_sf_wl_ces_kb_listener, NULL))
	}
	if (capabilities & WL_SEAT_CAPABILITY_POINTER)
	{
		SMPT_DBmR2L("wl_seat_get_pointer %p", smpt_sf_wl_ces_pt_p = wl_seat_get_pointer(wl_seat))
		SMPT_DBmR2L("wl_pointer_add_listener %d", wl_pointer_add_listener(smpt_sf_wl_ces_pt_p, &smpt_sf_wl_ces_pt_listener, NULL))
	}
}

struct wl_seat_listener smpt_sf_wl_ces_listener =
{
	.capabilities = wl_seat_listener_capabilities,
};

void smpt_sf_wl_ces_free()
{
	smpt_sf_wl_ces_kb_free();
	smpt_sf_wl_ces_pt_free();

	wl_seat_destroy(smpt_sf_wl_ces_p);
}
