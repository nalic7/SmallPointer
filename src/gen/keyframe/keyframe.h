#ifndef NALI_GEN_KEYFRAME_H
#define NALI_GEN_KEYFRAME_H

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

extern keyframe **keyframe_p;
extern uint8_t *keyframe_bl_p;

void gkf_write();

#endif