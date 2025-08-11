static uint8_t swlcp_pointer = 0;
#define NALI_SWLCP_P_ROTATE 1
#define NALI_SWLCP_P_MOVE 2
#define NALI_SWLCP_P_ACT 4

//uint8_t swlcsp_pointer = 1;
//static struct wl_cursor_theme *wl_cursor_theme;
//static struct wl_cursor **wl_cursor_p;
//static struct wl_surface *wl_surface_cursor;
//static struct wl_buffer *wl_buffer_cursor;
//
//void swlcsp_init_cursor()
//{
//	NALI_D_INFO("wl_cursor_theme_load %p", wl_cursor_theme = wl_cursor_theme_load(getenv("XCURSOR_THEME"), atoi(getenv("XCURSOR_SIZE")), wlc_wl_shm_p))
//
//	wl_cursor_p = malloc(sizeof(struct wl_cursor) * 2);
//	NALI_D_INFO("wl_cursor_theme_get_cursor %p", wl_cursor_p[0] = wl_cursor_theme_get_cursor(wl_cursor_theme, "left_ptr"))//wait watch
//	NALI_D_INFO("wl_cursor_theme_get_cursor %p", wl_cursor_p[1] = wl_cursor_theme_get_cursor(wl_cursor_theme, "progress"))
//
//	NALI_D_INFO("wl_compositor_create_surface %p", wl_surface_cursor = wl_compositor_create_surface(wlc_wl_compositor_p))
//}
//
//static uint32_t
//	pointer_serial = -1,
//	cursor_i = 0;
//static struct wl_cursor *wl_cursor;
//static struct timespec cursor_start = {0}, cursor_end;
//// static clock_t
//// 	cursor_start = 0,
//// 	cursor_end;
//void swlcsp_change_cursor()
//{
//	if (pointer_serial != -1)
//	{
//		if (swlcsp_pointer == 255)
//		{
//			wl_pointer_set_cursor(wlc_wl_pointer_p, pointer_serial, NULL, 0, 0);
//		}
//		else
//		{
//			wl_cursor = wl_cursor_p[swlcsp_pointer];
//
//			if (wl_cursor && wl_cursor->image_count > 0)
//			{
//				if (cursor_i == wl_cursor->image_count)
//				{
//					cursor_i = 0;
//				}
//				wl_buffer_cursor = wl_cursor_image_get_buffer(wl_cursor->images[cursor_i]);
//				wl_pointer_set_cursor(wlc_wl_pointer_p, pointer_serial, wl_surface_cursor, 0, 0);
//				wl_surface_attach(wl_surface_cursor, wl_buffer_cursor, 0, 0);
//				wl_surface_commit(wl_surface_cursor);
//
//				// cursor_end = clock();
//				clock_gettime(CLOCK_MONOTONIC, &cursor_end);
//				if (cursor_end.tv_sec + (double)cursor_end.tv_nsec / 1e9 - cursor_start.tv_sec - (double)cursor_start.tv_nsec / 1e9 >= 0.125)
//				{
//					cursor_start = cursor_end;
//					++cursor_i;
//				}
//			}
//		}
//	}
//}

static void wl_pointer_listener_enter(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
//	pointer_serial = serial;
}

static void wl_pointer_listener_leave(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface)
{
//	pointer_serial = -1;
}

static float x = 0, y = 0;
static void wl_pointer_listener_motion(void *data, struct wl_pointer *wl_pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
	float
		l_x = wl_fixed_to_double(surface_x),
		l_y = wl_fixed_to_double(surface_y);
	mtx_lock(lb_mtx_t_p);
	if (swlcp_pointer & NALI_SWLCP_P_ROTATE)
	{
		lcu_xy_p[0] = l_x - x;
		lcu_xy_p[1] = l_y - y;
		// NALI_D_LOG("x %f", s_pointer_x)
		// NALI_D_LOG("y %f", s_pointer_y)
	}
	else
	{
		lcu_xy_p[0] = 0;
		lcu_xy_p[1] = 0;
	}
	mtx_unlock(lb_mtx_t_p);
	x = l_x;
	y = l_y;
	// NALI_D_LOG("surface_x %f", wl_fixed_to_double(surface_x))
	// NALI_D_LOG("surface_y %f", wl_fixed_to_double(surface_y))
}

static void wl_pointer_listener_button(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state)
{
	switch (button)
	{
		case BTN_LEFT:
			if (state == WL_POINTER_BUTTON_STATE_PRESSED)
				swlcp_pointer |= NALI_SWLCP_P_ACT;
			else
				swlcp_pointer &= 0xFFu - NALI_SWLCP_P_ACT;
			break;
		case BTN_RIGHT:
			if (state == WL_POINTER_BUTTON_STATE_PRESSED)
				swlcp_pointer |= NALI_SWLCP_P_ROTATE;
			else
				swlcp_pointer &= 0xFFu - NALI_SWLCP_P_ROTATE;
			break;
		case BTN_MIDDLE:
			mtx_lock(lb_mtx_t_p);
			if (state == WL_POINTER_BUTTON_STATE_PRESSED)
				lcu_k |= NALI_LB_K_REROTATE;
			else
				lcu_k &= 0xFFu - NALI_SWLCP_P_ROTATE;
			mtx_unlock(lb_mtx_t_p);
	}
	// NALI_D_LOG("surface_button %d", button)
}

static void wl_pointer_listener_axis(void *data, struct wl_pointer *wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value)
{
	float scroll = wl_fixed_to_double(value);
	mtx_lock(lb_mtx_t_p);
	lcu_xy_p[0] = axis == WL_POINTER_AXIS_VERTICAL_SCROLL ? scroll : 0;
	lcu_xy_p[1] = axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL ? scroll : 0;
	mtx_unlock(lb_mtx_t_p);
}

struct wl_pointer_listener swlcsp_wl_pointer_listener =
{
	.enter = wl_pointer_listener_enter,
	.leave = wl_pointer_listener_leave,
	.motion = wl_pointer_listener_motion,
	.button = wl_pointer_listener_button,
	.axis = wl_pointer_listener_axis,
};
