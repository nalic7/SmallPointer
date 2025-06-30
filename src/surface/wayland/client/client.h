#ifndef NALI_WAYLAND_CLIENT_H
#define NALI_WAYLAND_CLIENT_H

extern struct wl_display *wlc_wl_display_client_p;
extern struct wl_registry *wlc_wl_registry_p;
extern struct wl_compositor *wlc_wl_compositor_p;
extern struct wl_surface *wlc_wl_surface_p;

extern struct xdg_wm_base *wlc_xdg_wm_base_p;
extern struct xdg_surface *wlc_xdg_surface_p;
extern struct xdg_toplevel *wlc_xdg_toplevel_p;

extern struct wl_seat *wlc_wl_seat_p;
extern struct wl_keyboard *wlc_wl_keyboard_p;
extern struct wl_shm *wlc_wl_shm_p;
extern struct wl_pointer *wlc_wl_pointer_p;

extern struct zwp_pointer_constraints_v1 *wlc_zwp_pointer_constraints_v1_p;
extern struct zwp_locked_pointer_v1 *wlc_zwp_locked_pointer_v1_p;

extern struct zwp_relative_pointer_manager_v1 *wlc_zwp_relative_pointer_manager_v1_p;
extern struct zwp_relative_pointer_v1 *wlc_zwp_relative_pointer_v1_p;

void swlc_clean();
void swlc_set();

#endif