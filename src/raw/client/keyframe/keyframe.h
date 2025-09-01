#ifndef _RC_KF_H
#define _RC_KF_H

typedef struct
{
	uint8_t
		// keyframe,//debug only
		bone_bl,
		*bone_p,

		//new
		k_min,
		k_max;
	float
		**s_p,
		**r_p,
		**t_p;
} lckf;

//select keyframe
extern lckf **lckf_p;
extern uint8_t *lckf_bl_p;

void lckf_set();

#endif
