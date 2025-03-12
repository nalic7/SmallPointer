#ifndef NALI_WAYLAND_CLIENT_H
#define NALI_WAYLAND_CLIENT_H

extern struct wl_display* m_wl_display_client;
extern struct wl_registry* m_wl_registry;
extern struct wl_compositor* m_wl_compositor;
extern struct wl_surface* m_wl_surface;

extern struct xdg_wm_base* m_xdg_wm_base;
extern struct xdg_surface* m_xdg_surface;
extern struct xdg_toplevel* m_xdg_toplevel;

extern struct wl_seat* m_wl_seat;
extern struct wl_keyboard* m_wl_keyboard;
extern struct wl_pointer* m_wl_pointer;

void wlc_init();
void wlc_clean();

#endif
