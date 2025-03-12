static void wl_pointer_listener_enter(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
}

static void wl_pointer_listener_leave(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface)
{
}

static void wl_pointer_listener_motion(void *data, struct wl_pointer *wl_pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
}

static void wl_pointer_listener_button(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state)
{
	// info("wl_pointer_listener_button button %d", button);//linux/input-event-codes.h
	// info("wl_pointer_listener_button state %d", state);//wayland-client-protocol.h
}

static void wl_pointer_listener_axis(void *data, struct wl_pointer *wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value)
{
}

struct wl_pointer_listener m_wl_pointer_listener =
{
	.enter = wl_pointer_listener_enter,
	.leave = wl_pointer_listener_leave,
	.motion = wl_pointer_listener_motion,
	.button = wl_pointer_listener_button,
	.axis = wl_pointer_listener_axis,
};