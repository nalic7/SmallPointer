#ifndef NALI_WAYLAND_CLIENT_POINTER_H
#define NALI_WAYLAND_CLIENT_POINTER_H

extern struct wl_pointer_listener m_wl_pointer_listener;

void wlcp_init_cursor();
void wlcp_change_cursor();

#endif