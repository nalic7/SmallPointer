#ifndef NALI_SURFACE_H
#define NALI_SURFACE_H

extern uint32_t s_width;
extern uint32_t s_height;
extern uint8_t s_pointer_id;

#define NALI_SURFACE_C_S_CONFIG 1
#define NALI_SURFACE_C_S_CLEAN 2
#define NALI_SURFACE_C_S_RE 4
#define NALI_SURFACE_C_S_RENDER_ABLE 8
#define NALI_SURFACE_C_S_EXIT 16
extern uint8_t s_surface_state;

#define NALI_P_STATE_ROTATE 1
#define NALI_P_STATE_MOVE 2
#define NALI_P_STATE_ACT 4
#define NALI_P_STATE_REROTATE 8
extern uint8_t s_pointer_state;

#define NALI_KEY_W 1
#define NALI_KEY_S 2
#define NALI_KEY_A 4
#define NALI_KEY_D 8
#define NALI_KEY_SPACE 16
#define NALI_KEY_LEFTCTRL 32
extern uint8_t s_key;

extern float
	s_pointer_x, s_pointer_y,
	s_rx, s_ry, s_rz,
	s_tx, s_ty, s_tz,
	s_deltra;

void s_set();
void s_loop();

#endif