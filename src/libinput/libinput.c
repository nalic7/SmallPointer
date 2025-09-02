static int open_restricted(const char *path, int flags, void *user_data)
{
	int fd = open(path, flags);
	SMPT_DB_N2L("open %d", fd)
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
static struct udev *_lip_udev_p;

static void _lip_free()
{
	SMPT_DB_R2L("libinput_unref %p", libinput_unref(_lip_p))
	SMPT_DB_R2L("udev_unref %p", udev_unref(_lip_udev_p))
}

void _lip_set()
{
	SMPT_DB_R2L("udev_new %p", _lip_udev_p = udev_new())

	SMPT_DB_R2L("libinput_udev_create_context %p", _lip_p = libinput_udev_create_context(&_lip_interface, NULL, _lip_udev_p))

	SMPT_DB_R2L("libinput_udev_assign_seat %p", libinput_udev_assign_seat(_lip_p, "seat0"))
}

void _lip_loop()
{
	struct libinput_event *_lip_ev_p;
	//! set state
	while (!(_sf_state & _SF_S_EXIT))
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
					SMPT_DB_N2L("libinput_event_keyboard_get_key %d", key)
					if (key == KEY_ESC)
						lb_free1();
					break;

				case LIBINPUT_EVENT_POINTER_MOTION:
					_lip_evpt_p = libinput_event_get_pointer_event(_lip_ev_p);
					double dx = libinput_event_pointer_get_dx(_lip_evpt_p);
					double dy = libinput_event_pointer_get_dx(_lip_evpt_p);
					SMPT_DB_N2L("libinput_event_pointer_get_dx %f", dx)
					SMPT_DB_N2L("libinput_event_pointer_get_dy %f", dy)
					break;
				case LIBINPUT_EVENT_POINTER_BUTTON:
					_lip_evpt_p = libinput_event_get_pointer_event(_lip_ev_p);
					uint32_t button = libinput_event_pointer_get_button(_lip_evpt_p);
					SMPT_DB_N2L("libinput_event_pointer_get_button %d", button)
//					if (button == BTN_RIGHT)
//						lb_free1();
					break;

				case LIBINPUT_EVENT_TOUCH_UP:
					_lip_evt_p = libinput_event_get_touch_event(_lip_ev_p);
					slot = libinput_event_touch_get_slot(_lip_evt_p);
					SMPT_DB_N2L("libinput_event_touch_get_slot %d", slot)
					break;
				case LIBINPUT_EVENT_TOUCH_DOWN:
					_lip_evt_p = libinput_event_get_touch_event(_lip_ev_p);
					slot = libinput_event_touch_get_slot(_lip_evt_p);
					SMPT_DB_N2L("libinput_event_touch_get_slot %d", slot)
					break;
				case LIBINPUT_EVENT_TOUCH_MOTION:
					_lip_evt_p = libinput_event_get_touch_event(_lip_ev_p);
					slot = libinput_event_touch_get_slot(_lip_evt_p);
					SMPT_DB_N2L("libinput_event_touch_get_slot %d", slot)
					break;
				case LIBINPUT_EVENT_TOUCH_CANCEL:
					_lip_evt_p = libinput_event_get_touch_event(_lip_ev_p);
					slot = libinput_event_touch_get_slot(_lip_evt_p);
					SMPT_DB_N2L("libinput_event_touch_get_slot %d", slot)
			}
			libinput_event_destroy(_lip_ev_p);
		}
	}
	_lip_free();
}
