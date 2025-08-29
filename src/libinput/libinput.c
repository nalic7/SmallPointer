static int open_restricted(const char *path, int flags, void *user_data)
{
	int fd = open(path, flags);
	_DB_N2L("open %d", fd)
	return fd;
}

static void close_restricted(int fd, void *user_data)
{
	close(fd);
}

static struct libinput_interface _lip_interface =
{
	.open_restricted = open_restricted,
	.close_restricted = close_restricted
};

static struct libinput *_lip_p;

static int loop(void *p)
{
	struct libinput_event *_lip_ev_p;
	//! set state
	while (1)
	{
		libinput_dispatch(_lip_p);

		struct libinput_event_pointer *_lip_evpt_p;

		struct libinput_event_touch *_lip_evt_p;
		uint32_t slot;
		while ((_lip_ev_p = libinput_get_event(_lip_p)))
		{
			switch (libinput_event_get_type(_lip_ev_p))
			{
				case LIBINPUT_EVENT_KEYBOARD_KEY:
					struct libinput_event_keyboard *_lip_evkb_p = libinput_event_get_keyboard_event(_lip_ev_p);
					uint32_t key = libinput_event_keyboard_get_key(_lip_evkb_p);
					_DB_N2L("libinput_event_keyboard_get_key %d", key)
					if (key == KEY_ESC)
						lb_free1();
					break;

				case LIBINPUT_EVENT_POINTER_MOTION:
					_lip_evpt_p = libinput_event_get_pointer_event(_lip_ev_p);
					double dx = libinput_event_pointer_get_dx(_lip_evpt_p);
					double dy = libinput_event_pointer_get_dx(_lip_evpt_p);
					_DB_N2L("libinput_event_pointer_get_dx %f", dx)
					_DB_N2L("libinput_event_pointer_get_dy %f", dy)
					break;
				case LIBINPUT_EVENT_POINTER_BUTTON:
					_lip_evpt_p = libinput_event_get_pointer_event(_lip_ev_p);
					uint32_t button = libinput_event_pointer_get_button(_lip_evpt_p);
					_DB_N2L("libinput_event_pointer_get_button %d", button)
//					if (button == BTN_RIGHT)
//						lb_free1();
					break;

				case LIBINPUT_EVENT_TOUCH_UP:
					_lip_evt_p = libinput_event_get_touch_event(_lip_ev_p);
					slot = libinput_event_touch_get_slot(_lip_evt_p);
					_DB_N2L("libinput_event_touch_get_slot %d", slot)
					break;
				case LIBINPUT_EVENT_TOUCH_DOWN:
					_lip_evt_p = libinput_event_get_touch_event(_lip_ev_p);
					slot = libinput_event_touch_get_slot(_lip_evt_p);
					_DB_N2L("libinput_event_touch_get_slot %d", slot)
					break;
				case LIBINPUT_EVENT_TOUCH_MOTION:
					_lip_evt_p = libinput_event_get_touch_event(_lip_ev_p);
					slot = libinput_event_touch_get_slot(_lip_evt_p);
					_DB_N2L("libinput_event_touch_get_slot %d", slot)
					break;
				case LIBINPUT_EVENT_TOUCH_CANCEL:
					_lip_evt_p = libinput_event_get_touch_event(_lip_ev_p);
					slot = libinput_event_touch_get_slot(_lip_evt_p);
					_DB_N2L("libinput_event_touch_get_slot %d", slot)
			}
		}
	}
	return 0;
}

void _lip_set()
{
	struct udev *udev = udev_new();
	_DB_N2L("udev_new %d", udev_new)

	_lip_p = libinput_udev_create_context(&_lip_interface, NULL, udev);
	_DB_N2L("libinput_udev_create_context %p", _lip_p)

	_DB_R2L("libinput_udev_assign_seat %d", libinput_udev_assign_seat(_lip_p, "seat0"))

	_DB_R2L("thrd_create %d", thrd_create(&(thrd_t){}, loop, NULL))
}

void _lip_free()
{
	//! free
}
