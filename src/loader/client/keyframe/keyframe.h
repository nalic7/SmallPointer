#ifndef NALI_LOADER_CLIENT_KEYFRAME_H
#define NALI_LOADER_CLIENT_KEYFRAME_H

typedef struct
{
	uint8_t
		keyframe,
		bone_bl,
		*bone_p;
	float
		**animation_s_p,
		**animation_r_p,
		**animation_t_p;
} keyframe;

extern keyframe **lckf_keyframe_p;
extern uint8_t *lckf_keyframe_bl_p;

void lckf_set();

#endif