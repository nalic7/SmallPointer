keyframe **lckf_keyframe_p;
uint8_t *lckf_keyframe_bl_p;
// static uint8_t lckf_keyframe_bl;

void lckf_set()
{
	uint8_t l_keyframe_bl = *(uint8_t *)NALI_CACHE_P_D_P;
	NALI_CACHE_P_D_BL_P[1] += sizeof(uint8_t);
	lckf_keyframe_bl_p = malloc(l_keyframe_bl);
	lckf_keyframe_p = malloc(l_keyframe_bl * sizeof(keyframe *));
	memset(lckf_keyframe_p, 0, l_keyframe_bl * sizeof(keyframe *));

	for (uint8_t l_0 = 0; l_0 < l_keyframe_bl; ++l_0)
	{
		lckf_keyframe_bl_p[l_0] = *(uint8_t *)(NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1]);
		NALI_CACHE_P_D_BL_P[1] += sizeof(uint8_t);
		lckf_keyframe_p[l_0] = malloc(lckf_keyframe_bl_p[l_0] * sizeof(keyframe));

		for (uint32_t l_1 = 0; l_1 < lckf_keyframe_bl_p[l_0]; ++l_1)
		{
			lckf_keyframe_p[l_0][l_1].keyframe = *(uint8_t *)(NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1]);
			NALI_CACHE_P_D_BL_P[1] += sizeof(uint8_t);

			lckf_keyframe_p[l_0][l_1].bone_bl = *(uint8_t *)(NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1]);
			NALI_CACHE_P_D_BL_P[1] += sizeof(uint8_t);

			lckf_keyframe_p[l_0][l_1].bone_p = malloc(lckf_keyframe_p[l_0][l_1].bone_bl);
			lckf_keyframe_p[l_0][l_1].animation_s_p = malloc(sizeof(float *) * lckf_keyframe_p[l_0][l_1].bone_bl);
			lckf_keyframe_p[l_0][l_1].animation_r_p = malloc(sizeof(float *) * lckf_keyframe_p[l_0][l_1].bone_bl);
			lckf_keyframe_p[l_0][l_1].animation_t_p = malloc(sizeof(float *) * lckf_keyframe_p[l_0][l_1].bone_bl);

			for (uint32_t l_2 = 0; l_2 < lckf_keyframe_p[l_0][l_1].bone_bl; ++l_2)
			{
				lckf_keyframe_p[l_0][l_1].bone_p[l_2] = *(uint8_t *)(NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1]);
				NALI_CACHE_P_D_BL_P[1] += sizeof(uint8_t);

				lckf_keyframe_p[l_0][l_1].animation_s_p[l_2] = malloc(sizeof(float) * 3);
				memcpy(lckf_keyframe_p[l_0][l_1].animation_s_p[l_2], NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1], sizeof(float) * 3);
				NALI_CACHE_P_D_BL_P[1] += sizeof(float) * 3;

				lckf_keyframe_p[l_0][l_1].animation_r_p[l_2] = malloc(sizeof(float) * 4);
				memcpy(lckf_keyframe_p[l_0][l_1].animation_r_p[l_2], NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1], sizeof(float) * 4);
				NALI_CACHE_P_D_BL_P[1] += sizeof(float) * 4;

				lckf_keyframe_p[l_0][l_1].animation_t_p[l_2]= malloc(sizeof(float) * 3);
				memcpy(lckf_keyframe_p[l_0][l_1].animation_t_p[l_2], NALI_CACHE_P_D_P + NALI_CACHE_P_D_BL_P[1], sizeof(float) * 3);
				NALI_CACHE_P_D_BL_P[1] += sizeof(float) * 3;
			}
		}
	}
}