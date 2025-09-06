#ifndef _RC_KF_H
#define _RC_KF_H

struct lckf
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
};

//select keyframe
extern struct lckf **lckf_p;
extern uint8_t *lckf_bl_p;

void lckf_set();

#endif
