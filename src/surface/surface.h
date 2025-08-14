#ifndef NALI_SURFACE_H
#define NALI_SURFACE_H

extern uint32_t s_width;
extern uint32_t s_height;

// #define NALI_S_S_CONFIG 1
#define NALI_S_S_RENDER_ABLE 1
#define NALI_S_S_CLEAN 2
#define NALI_S_S_RE 4
#define NALI_S_S_DATA_ABLE 8
#define NALI_S_S_EXIT 16
#define NALI_S_S_EXIT_C 32
#define NALI_S_S_EXIT_S 64
extern uint8_t s_state;

#endif
