static void wl_keyboard_listener_keymap(void* data, struct wl_keyboard* wl_keyboard, uint32_t format, int32_t fd, uint32_t size)
{
	// nali_log("wl_keyboard_listener_keymap fd %d", fd)
}

static void wl_keyboard_listener_key(void* data, struct wl_keyboard* wl_keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state)
{
	// nali_log("wl_keyboard_listener_key key %d", key)
	if (state == WL_KEYBOARD_KEY_STATE_PRESSED)
	{
		if (key == KEY_TAB)
			wlczwp_setPointer();

		if (key == KEY_W)
			s_key |= NALI_KEY_W;
		if (key == KEY_S)
			s_key |= NALI_KEY_S;
		if (key == KEY_A)
			s_key |= NALI_KEY_A;
		if (key == KEY_D)
			s_key |= NALI_KEY_D;
	}
	else
	{
		if (key == KEY_W)
			s_key &= 0xFFu - NALI_KEY_W;
		if (key == KEY_S)
			s_key &= 0xFFu - NALI_KEY_S;
		if (key == KEY_A)
			s_key &= 0xFFu - NALI_KEY_A;
		if (key == KEY_D)
			s_key &= 0xFFu - NALI_KEY_D;
	}
}

static void wl_keyboard_listener_enter(void* data, struct wl_keyboard* wl_keyboard, uint32_t serial, struct wl_surface* surface, struct wl_array* keys)
{
	// nali_log("wl_keyboard_listener_enter")
}

static void wl_keyboard_listener_leave(void* data, struct wl_keyboard* wl_keyboard, uint32_t serial, struct wl_surface* surface)
{
	// nali_log("wl_keyboard_listener_leave")
}

static void wl_keyboard_listener_modifiers(void* data, struct wl_keyboard* wl_keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group)
{
	// nali_log("wl_keyboard_listener_modifiers group %d", group)
}

static void wl_keyboard_listener_repeat_info(void* data, struct wl_keyboard* wl_keyboard, int32_t rate, int32_t delay)
{
	// nali_log("wl_keyboard_listener_repeat_info")
}

struct wl_keyboard_listener m_wl_keyboard_listener =
{
	.keymap = wl_keyboard_listener_keymap,
	.enter = wl_keyboard_listener_enter,
	.leave = wl_keyboard_listener_leave,
	.key = wl_keyboard_listener_key,
	.modifiers = wl_keyboard_listener_modifiers,
	.repeat_info = wl_keyboard_listener_repeat_info
};