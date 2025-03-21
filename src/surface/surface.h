#ifndef NALI_SURFACE_H
#define NALI_SURFACE_H

extern uint32_t m_width;
extern uint32_t m_height;
extern uint8_t m_pointer_id;

// #define NALI_SURFACE_C_S_CONFIG 1
#define NALI_SURFACE_C_S_CLEAN 1
#define NALI_SURFACE_C_S_RE 2
#define NALI_SURFACE_C_S_RENDER_ABLE 4
extern unsigned char m_surface_state;

#endif
