// JNIEXPORT void JNICALL Java_com_nali_summer_SmallRender_init(JNIEnv* env, jobject obj)
// {
//	 struct wl_display* display = wl_display_connect(NULL);
//	 if (!display)
//	 {
//		 info(stderr, "Failed to connect to Wayland display.")
//	 }

//	 info(stderr, "Connection established!")

//	 wl_display_disconnect(display);
// }

// Global variables
struct wl_display* m_wl_display;
struct wl_registry* wl_registry;
struct wl_compositor* wl_compositor;
struct wl_surface* m_wl_surface;
struct xdg_wm_base* xdg_wm_base;
struct xdg_surface* xdg_surface;
struct xdg_toplevel* xdg_toplevel;

struct wl_seat* wl_seat;
struct wl_keyboard* wl_keyboard;

uint32_t m_width;
uint32_t m_height;

// void cleanup()
// {
//	 // info("run_clean")

//	 if (xdg_toplevel)
//	 {
//		 xdg_toplevel_destroy(xdg_toplevel);
//	 }
//	 if (xdg_surface)
//	 {
//		 xdg_surface_destroy(xdg_surface);
//	 }
//	 if (m_wl_surface)
//	 {
//		 wl_surface_destroy(m_wl_surface);
//	 }
//	 if (xdg_wm_base)
//	 {
//		 xdg_wm_base_destroy(xdg_wm_base);
//	 }
//	 if (wl_compositor)
//	 {
//		 wl_compositor_destroy(wl_compositor);
//	 }
//	 if (m_wl_display)
//	 {
//		 wl_display_disconnect(m_wl_display);
//	 }
//	 if (wl_seat)
//	 {
//		 wl_seat_destroy(wl_seat);
//	 }
// }

void wl_keyboard_listener_keymap(void* data, struct wl_keyboard* wl_keyboard, uint32_t format, int32_t fd, uint32_t size)
{
	info("wl_keyboard_listener_keymap_fd %d", fd)
}

void wl_keyboard_listener_key(void* data, struct wl_keyboard* wl_keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state)
{
	info("wl_keyboard_listener_key_key %d", key)
}

void wl_keyboard_listener_enter(void* data, struct wl_keyboard* wl_keyboard, uint32_t serial, struct wl_surface* surface, struct wl_array* keys)
{

}

void wl_keyboard_listener_leave(void* data, struct wl_keyboard* wl_keyboard, uint32_t serial, struct wl_surface* surface)
{

}

void wl_keyboard_listener_modifiers(void* data, struct wl_keyboard* wl_keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group)
{
	info("wl_keyboard_listener_modifiers_group %d", group)
}

void wl_keyboard_listener_repeat_info(void* data, struct wl_keyboard* wl_keyboard, int32_t rate, int32_t delay)
{

}

struct wl_keyboard_listener wl_keyboard_listener =
{
	.keymap = wl_keyboard_listener_keymap,
	.enter = wl_keyboard_listener_enter,
	.leave = wl_keyboard_listener_leave,
	.key = wl_keyboard_listener_key,
	.modifiers = wl_keyboard_listener_modifiers,
	.repeat_info = wl_keyboard_listener_repeat_info
};

void wl_seat_listener_capabilities(void* data, struct wl_seat* wl_seat, uint32_t capabilities)
{
	if (capabilities & WL_SEAT_CAPABILITY_KEYBOARD)
	{
		wl_keyboard = wl_seat_get_keyboard(wl_seat);
		wl_keyboard_add_listener(wl_keyboard, &wl_keyboard_listener, NULL);
	}
}

struct wl_seat_listener wl_seat_listener =
{
	.capabilities = wl_seat_listener_capabilities,
};

void wl_registry_listener_global(void* data, struct wl_registry* wl_registry, uint32_t name, const char* interface, uint32_t version)
{
	info("wl_registry_listener_global_interface %s", interface)
	if (strcmp(interface, wl_compositor_interface.name) == 0)
	{
		// info("run_compositor")
		wl_compositor = wl_registry_bind(wl_registry, name, &wl_compositor_interface, 1);
	}
	// else if (strcmp(interface, wl_shell_interface.name) == 0)
	// {
	//	 shell = wl_registry_bind(wl_registry, name, &wl_shell_interface, 1);
	//	 info("wl_shell")
	// }
	else if (strcmp(interface, xdg_wm_base_interface.name) == 0)
	{
		// info("run_xdg_wm_base")
		xdg_wm_base = wl_registry_bind(wl_registry, name, &xdg_wm_base_interface, 1);
	}
	else if (strcmp(interface, "wl_seat") == 0)
	{
		wl_seat = wl_registry_bind(wl_registry, name, &wl_seat_interface, 1);
		wl_seat_add_listener(wl_seat, &wl_seat_listener, NULL);
	}
	// else
	// {
	//	 info("Failed to get compositor or shell")
	// }
}

void wl_registry_listener_remove(void* data, struct wl_registry* registry, uint32_t id)
{
	// info("run_wl_registry_listener_remove")
}

struct wl_registry_listener registry_listener =
{
	.global = wl_registry_listener_global,
	.global_remove = wl_registry_listener_remove
};

void xdg_surface_listener_configure(void* data, struct xdg_surface* _xdg_surface, uint32_t serial)
{
	// info("run_xdg_surface_listener_configure")
	// if (_xdg_surface == xdg_surface)
	// {
	//	 xdg_surface_ack_configure(xdg_surface, serial);

	//	 wl_surface_commit(m_wl_surface);
	// }
}

struct xdg_surface_listener xdg_surface_listener =
{
	.configure = xdg_surface_listener_configure
};

void xdg_toplevel_listener_configure(void* data, struct xdg_toplevel* _xdg_toplevel, int32_t width, int32_t height, struct wl_array* states)
{
	if (_xdg_toplevel == xdg_toplevel)
	{
		// info("run_xdg_toplevel_listener_configure w%d h%d", width, height)

		if (width > 0 && height > 0)
		{
			m_width = width;
			m_height = height;
		}

		// // If the width or height is zero, it might indicate an issue with the initial size.
		// if (width > 0 && height > 0)
		// {
		//	 // Optionally resize your content or update layout here
		//	 // xdg_toplevel_set_min_size(xdg_toplevel, width, height);
		//	 // xdg_toplevel_set_max_size(xdg_toplevel, width, height);
		// }

		// Respond to the configuration
		// wl_surface_commit(m_wl_surface);
	}
}

void xdg_toplevel_listener_close(void* data, struct xdg_toplevel* xdg_toplevel)
{
	// info("run_xdg_toplevel_listener_close")
	// cleanup();
	exit(EXIT_SUCCESS);
}

void xdg_toplevel_listener_configure_bounds(void* data, struct xdg_toplevel* xdg_toplevel, int32_t width, int32_t height)
{
	// info("run_xdg_toplevel_listener_configure_bounds")
}

void xdg_toplevel_listener_wm_capabilities(void* data, struct xdg_toplevel* xdg_toplevel, struct wl_array* capabilities)
{
	// info("run_xdg_toplevel_listener_wm_capabilities")
}

struct xdg_toplevel_listener xdg_toplevel_listener =
{
	.configure = xdg_toplevel_listener_configure,
	.close = xdg_toplevel_listener_close,
	.configure_bounds = xdg_toplevel_listener_configure_bounds,
	.wm_capabilities = xdg_toplevel_listener_wm_capabilities
};

// Event loop
int surface_loop(void* arg)
{
	// info("run_surface_loop")

	// struct wl_event_queue* queue = wl_display_create_queue(m_wl_display);
	// if (!queue)
	// {
	//	 error("wl_event_queue")
	// }

	int result;
	while (1)
	{
		// info("start!")

		// info("dispatch_pending!")
		// wl_display_dispatch_pending(m_wl_display);

		// info("prepare_event!")
		// wl_display_prepare_read(m_wl_display);
		// info("event!")
		// int event = wl_display_read_events(m_wl_display);
		// // wl_display_cancel_read(m_wl_display);
		// info("dispatch!")
		result = wl_display_dispatch(m_wl_display);
		if (result < 0)
		{
			error("wl_display_dispatch")
		}
		// wl_display_dispatch_pending(m_wl_display);
		// wl_display_flush(m_wl_display);

		// info("flush!")
		// int flush = wl_display_flush(m_wl_display);
		// if (wl_display_flush(m_wl_display) < 0)
		// {
		//	 error("wl_display_flush")
		// }

		// Request a sync event and wait for it
		// struct wl_event_queue* queue = wl_display_create_queue(m_wl_display);
		// if (!queue)
		// {
		//	 error("wl_event_queue")
		// }

		// if (wl_display_prepare_read_queue(m_wl_display, queue) < 0)
		// {
		//	 error("wl_display_dispatch")
		// }
		// if (wl_display_sync(m_wl_display) < 0)
		// {
		//	 error("wl_display_sync")
		// }

		// result = wl_display_dispatch_queue(m_wl_display, queue);
		// if (result < 0)
		// {
		//	 error("wl_display_dispatch_queue: %d\n", result)
		// }

		// wl_event_queue_destroy(queue);
		// info("end!")

		// // else
		// // {
		// //	 // vkQueuePresentKHR(queue, &present_info);
		// //	 // vkQueueSubmit(queue, 1, &submit_info, VK_NULL_HANDLE);
		// //	 info("run_ready")
		// // }
	}

	// // Clean up
	// wl_shell_surface_destroy(shell_surface);

	// wl_surface_destroy(surface);
	// wl_compositor_destroy(compositor);

	// wl_registry_destroy(registry);
	// wl_display_disconnect(display);
	// cleanup();
	error("wl_display_dispatch %d", result);
	return 0;
}

// JNIEXPORT void JNICALL Java_com_nali_summer_SmallRender_init(JNIEnv* env, jobject obj)
void surface_init()
{
	// info("run_surface.c")

	// Connect to the Wayland display server
	m_wl_display = wl_display_connect(NULL);
	if (!m_wl_display)
	{
		error("wl_display_connect")
	}

	// Get the Wayland registry
	wl_registry = wl_display_get_registry(m_wl_display);
	if (!wl_registry)
	{
		error("wl_display_get_registry")
	}

	wl_registry_add_listener(wl_registry, &registry_listener, NULL);
	// wl_display_dispatch(m_wl_display);
	wl_display_roundtrip(m_wl_display);

	if (!wl_compositor)
	{
		error("COMPOSITOR_NULL")
	}

	if (!xdg_wm_base)
	{
		error("XDG_WM_BASE_NULL")
	}

	// if (!shell)
	// {
	//	 info(stderr, "Failed to get shell")
	// }

	// Create a surface
	// info("run_create_surface")

	m_wl_surface = wl_compositor_create_surface(wl_compositor);
	if (!m_wl_surface)
	{
		error("wl_compositor_create_surface")
	}

	// info("run_create_shell")

	// // Create a shell surface
	// shell_surface = wl_shell_get_shell_surface(shell, surface);
	// if (!shell_surface)
	// {
	//	 info("Failed to create Wayland shell surface")
	// }
	// // Set shell surface properties
	// wl_shell_surface_set_title(shell_surface, "Wayland Window");
	// wl_shell_surface_set_toplevel(shell_surface);

	// Create an XDG surface
	xdg_surface = xdg_wm_base_get_xdg_surface(xdg_wm_base, m_wl_surface);
	if (!xdg_surface)
	{
		error("xdg_wm_base_get_xdg_surface")
	}

	xdg_surface_add_listener(xdg_surface, &xdg_surface_listener, NULL);

	// Create an XDG toplevel
	xdg_toplevel = xdg_surface_get_toplevel(xdg_surface);
	if (!xdg_toplevel)
	{
		error("xdg_surface_get_toplevel")
	}

	xdg_toplevel_add_listener(xdg_toplevel, &xdg_toplevel_listener, NULL);
	// Set title
	// xdg_toplevel_set_title(xdg_toplevel, "Wayland-XDG");
	// xdg_toplevel_set_app_id(xdg_toplevel, "Wayland-XDG");

	m_width = 800;
	m_height = 600;
	// xdg_surface_set_window_geometry(xdg_surface, 0, 0, 1, 1);
	// xdg_toplevel_set_min_size(xdg_toplevel, 1, 1);
	// xdg_toplevel_set_max_size(xdg_toplevel, 800, 600);

	// //
	// wl_display_roundtrip(m_wl_display);
	// wl_surface_attach(m_wl_surface, buffer, 0, 0);

	// Commit changes
	// wl_surface_commit(m_wl_surface);

	// info("run_create_thread")
	// // Run the event loop
	// event_loop();
	thrd_t thread;
	int result = thrd_create(&thread, surface_loop, NULL);
	if (result != thrd_success)
	{
		error("thrd_create")
	}
}
