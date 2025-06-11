#ifndef NALI_SURFACE_H
#define NALI_SURFACE_H

extern uint32_t s_width;
extern uint32_t s_height;
extern uint8_t s_pointer_id;

// #define NALI_S_S_CONFIG 1
#define NALI_S_S_CLEAN 2
#define NALI_S_S_RE 4
#define NALI_S_S_DATA_ABLE 8
#define NALI_S_S_EXIT 16
#define NALI_S_S_EXIT_C 32
#define NALI_S_S_EXIT_S 64
#define NALI_S_S_RENDER_ABLE 1
extern uint8_t s_surface_state;

#define NALI_S_PS_ROTATE 1
#define NALI_S_PS_MOVE 2
#define NALI_S_PS_ACT 4
#define NALI_S_PS_REROTATE 8
extern uint8_t s_pointer_state;

#define NALI_S_KEY_W 1
#define NALI_S_KEY_S 2
#define NALI_S_KEY_A 4
#define NALI_S_KEY_D 8
#define NALI_S_KEY_SPACE 16
#define NALI_S_KEY_LEFTCTRL 32
extern uint8_t s_key;

extern float
	s_pointer_x, s_pointer_y,
	s_rx, s_ry, s_rz,
	s_tx, s_ty, s_tz,
	s_deltra;

void s_set();
void s_loop();

#endif