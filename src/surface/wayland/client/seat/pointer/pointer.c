struct wl_pointer *s_wlc_seatp_p;

uint32_t s_wlcp_serial = 0xFFFFFFFFu;

static uint8_t pointer = 0;
#define NALI_SWLCP_P_ROTATE 1
#define NALI_SWLCP_P_MOVE 2
#define NALI_SWLCP_P_ACT 4

static void wl_pointer_listener_enter(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
	s_wlcp_serial = serial;
}

static void wl_pointer_listener_leave(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface)
{
	s_wlcp_serial = 0xFFFFFFFFu;
}

static float x = 0, y = 0;
static void wl_pointer_listener_motion(void *data, struct wl_pointer *wl_pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
	float
		l_x = wl_fixed_to_double(surface_x),
		l_y = wl_fixed_to_double(surface_y);
	mtx_lock(lb_mtx_t_p);
	if (pointer & NALI_SWLCP_P_ROTATE)
	{
		lcu_xy_p[0] = l_x - x;
		lcu_xy_p[1] = l_y - y;
	}
	else
	{
		lcu_xy_p[0] = 0;
		lcu_xy_p[1] = 0;
	}
	mtx_unlock(lb_mtx_t_p);
	x = l_x;
	y = l_y;
}

static void wl_pointer_listener_button(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state)
{
	switch (button)
	{
		case BTN_LEFT:
			if (state == WL_POINTER_BUTTON_STATE_PRESSED)
				pointer |= NALI_SWLCP_P_ACT;
			else
				pointer &= 0xFFu - NALI_SWLCP_P_ACT;
			break;
		case BTN_RIGHT:
			if (state == WL_POINTER_BUTTON_STATE_PRESSED)
				pointer |= NALI_SWLCP_P_ROTATE;
			else
				pointer &= 0xFFu - NALI_SWLCP_P_ROTATE;
			break;
		case BTN_MIDDLE:
			mtx_lock(lb_mtx_t_p);
			if (state == WL_POINTER_BUTTON_STATE_PRESSED)
				lcu_k |= NALI_LB_K_REROTATE;
			else
				lcu_k &= 0xFFu - NALI_SWLCP_P_ROTATE;
			mtx_unlock(lb_mtx_t_p);
	}
}

static void wl_pointer_listener_axis(void *data, struct wl_pointer *wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value)
{
	float scroll = wl_fixed_to_double(value);
	mtx_lock(lb_mtx_t_p);
	lcu_xy_p[0] = axis == WL_POINTER_AXIS_VERTICAL_SCROLL ? scroll : 0;
	lcu_xy_p[1] = axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL ? scroll : 0;
	mtx_unlock(lb_mtx_t_p);
}

struct wl_pointer_listener s_wlc_seat_p_listener =
{
	.enter = wl_pointer_listener_enter,
	.leave = wl_pointer_listener_leave,
	.motion = wl_pointer_listener_motion,
	.button = wl_pointer_listener_button,
	.axis = wl_pointer_listener_axis,
};

void s_wlc_seat_p_free()
{
	wl_pointer_destroy(s_wlc_seatp_p);
}
