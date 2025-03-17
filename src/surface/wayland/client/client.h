#ifndef NALI_WAYLAND_CLIENT_H
#define NALI_WAYLAND_CLIENT_H

extern struct wl_display *m_wl_display_client_p;
extern struct wl_registry *m_wl_registry_p;
extern struct wl_compositor *m_wl_compositor_p;
extern struct wl_surface *m_wl_surface_p;

extern struct xdg_wm_base *m_xdg_wm_base_p;
extern struct xdg_surface *m_xdg_surface_p;
extern struct xdg_toplevel *m_xdg_toplevel_p;

extern struct wl_seat *m_wl_seat_p;
extern struct wl_keyboard *m_wl_keyboard_p;
extern struct wl_shm *m_wl_shm_p;
extern struct wl_pointer *m_wl_pointer_p;

extern struct zwp_pointer_constraints_v1 *m_zwp_pointer_constraints_v1_p;
extern struct zwp_locked_pointer_v1 *m_zwp_locked_pointer_v1_p;

extern struct zwp_relative_pointer_manager_v1 *m_zwp_relative_pointer_manager_v1_p;
extern struct zwp_relative_pointer_v1 *m_zwp_relative_pointer_v1_p;

void wlc_init();
void wlc_clean();

#endif
