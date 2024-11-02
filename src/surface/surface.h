#ifndef NALI_SURFACE_H
#define NALI_SURFACE_H

// // typedef struct
// // {
void surface_init();
extern struct wl_display *m_wl_display;
// extern struct wl_registry *registry;
// extern struct wl_compositor *compositor;
// // struct wl_shell *shell;
extern struct wl_surface *m_wl_surface;
// // struct wl_shell_surface *shell_surface;

// extern struct xdg_wm_base *xdg_wm_base;
// extern struct xdg_surface *xdg_surface;
// extern struct xdg_toplevel *xdg_toplevel;
// // }
// // Surface;
extern uint32_t m_width;
extern uint32_t m_height;

#endif
