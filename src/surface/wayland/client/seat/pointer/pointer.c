static struct wl_cursor_theme *wl_cursor_theme;
static struct wl_cursor **wl_cursor_p;
static struct wl_surface *wl_surface_cursor;
static struct wl_buffer *wl_buffer_cursor;
static uint32_t pointer_serial = -1;
static uint32_t cursor_i = 0;
static clock_t cursor_start = 0;

void wlcp_init_cursor()
{
	wl_cursor_theme = wl_cursor_theme_load(getenv("XCURSOR_THEME"), atoi(getenv("XCURSOR_SIZE")), m_wl_shm_p);

	if (!wl_cursor_theme)
	{
		error("wl_cursor_theme");
	}

	wl_cursor_p = malloc(sizeof(struct wl_cursor) * 2);
	wl_cursor_p[0] = wl_cursor_theme_get_cursor(wl_cursor_theme, "left_ptr");//wait watch
	wl_cursor_p[1] = wl_cursor_theme_get_cursor(wl_cursor_theme, "progress");

	wl_surface_cursor = wl_compositor_create_surface(m_wl_compositor_p);
}

void wlcp_change_cursor()
{
	if (pointer_serial != -1)
	{
		if (m_pointer_id == 255)
		{
			wl_pointer_set_cursor(m_wl_pointer_p, pointer_serial, NULL, 0, 0);
		}
		else
		{
			struct wl_cursor *wl_cursor = wl_cursor_p[m_pointer_id];

			if (wl_cursor && wl_cursor->image_count > 0)
			{
				if (cursor_i == wl_cursor->image_count)
				{
					cursor_i = 0;
				}
				wl_buffer_cursor = wl_cursor_image_get_buffer(wl_cursor->images[cursor_i]);
				wl_pointer_set_cursor(m_wl_pointer_p, pointer_serial, wl_surface_cursor, 0, 0);
				wl_surface_attach(wl_surface_cursor, wl_buffer_cursor, 0, 0);
				wl_surface_commit(wl_surface_cursor);

				clock_t cursor_end = clock();
				if (cursor_end - cursor_start > 200000)
				{
					cursor_start = cursor_end;
					++cursor_i;
				}
			}
		}
	}
}

static void wl_pointer_listener_enter(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
	pointer_serial = serial;
}

static void wl_pointer_listener_leave(void *data, struct wl_pointer *wl_pointer, uint32_t serial, struct wl_surface *surface)
{
	pointer_serial = -1;
}

static void wl_pointer_listener_motion(void *data, struct wl_pointer *wl_pointer, uint32_t time, wl_fixed_t surface_x, wl_fixed_t surface_y)
{
	info("surface_x %f", wl_fixed_to_double(surface_x))
	info("surface_y %f", wl_fixed_to_double(surface_y))
}

static void wl_pointer_listener_button(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button, uint32_t state)
{
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