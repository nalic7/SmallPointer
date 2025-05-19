#ifndef NALI_SURFACE_H
#define NALI_SURFACE_H

extern uint32_t s_width;
extern uint32_t s_height;
extern uint8_t s_pointer_id;

#define NALI_SURFACE_C_S_CONFIG 1
#define NALI_SURFACE_C_S_CLEAN 2
#define NALI_SURFACE_C_S_RE 4
#define NALI_SURFACE_C_S_RENDER_ABLE 8
extern uint8_t m_surface_state;

#define NALI_P_STATE_ROTATE 1
#define NALI_P_STATE_MOVE 2
#define NALI_P_STATE_ACT 4
extern uint8_t s_pointer_state;

extern float s_pointer_x, s_pointer_y;

extern float
	s_rx, s_ry, s_rz,
	s_deltra;

void s_loopPointer();

#endif