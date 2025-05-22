#ifndef NALI_WAYLAND_CLIENT_POINTER_H
#define NALI_WAYLAND_CLIENT_POINTER_H

extern struct wl_pointer_listener wlcsp_wl_pointer_listener;

void wlcsp_init_cursor();
void wlcsp_change_cursor();

#endif