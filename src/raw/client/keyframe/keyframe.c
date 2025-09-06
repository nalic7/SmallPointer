struct lckf **lckf_p;
uint8_t *lckf_bl_p;
// static uint8_t lckf_keyframe_bl;

void lckf_set()
{
	uint8_t l_keyframe_bl = *(uint8_t *)lb_c->d_p;
	lb_c->d_bl_p[1] += sizeof(uint8_t);
	lckf_bl_p = malloc(l_keyframe_bl);
	lckf_p = malloc(l_keyframe_bl * sizeof(struct lckf *));
	memset(lckf_p, 0, l_keyframe_bl * sizeof(struct lckf *));

	for (uint8_t l_0 = 0; l_0 < l_keyframe_bl; ++l_0)
	{
		lckf_bl_p[l_0] = *(uint8_t *)(lb_c->d_p + lb_c->d_bl_p[1]);
		lb_c->d_bl_p[1] += sizeof(uint8_t);
		lckf_p[l_0] = malloc(lckf_bl_p[l_0] * sizeof(struct lckf));

		for (uint32_t l_1 = 0; l_1 < lckf_bl_p[l_0]; ++l_1)
		{
			// lckf_p[l_0][l_1].keyframe = *(uint8_t *)(lb_c->d_p + lb_c->d_bl_p[1]);
			// lb_c->d_bl_p[1] += sizeof(uint8_t);

			lckf_p[l_0][l_1].bone_bl = *(uint8_t *)(lb_c->d_p + lb_c->d_bl_p[1]);
			lb_c->d_bl_p[1] += sizeof(uint8_t);

			lckf_p[l_0][l_1].bone_p = malloc(lckf_p[l_0][l_1].bone_bl);
			lckf_p[l_0][l_1].s_p = malloc(sizeof(float *) * lckf_p[l_0][l_1].bone_bl);
			lckf_p[l_0][l_1].r_p = malloc(sizeof(float *) * lckf_p[l_0][l_1].bone_bl);
			lckf_p[l_0][l_1].t_p = malloc(sizeof(float *) * lckf_p[l_0][l_1].bone_bl);

			for (uint32_t l_2 = 0; l_2 < lckf_p[l_0][l_1].bone_bl; ++l_2)
			{
				lckf_p[l_0][l_1].bone_p[l_2] = *(uint8_t *)(lb_c->d_p + lb_c->d_bl_p[1]);
				lb_c->d_bl_p[1] += sizeof(uint8_t);

				lckf_p[l_0][l_1].s_p[l_2] = malloc(sizeof(float) * 3);
				memcpy(lckf_p[l_0][l_1].s_p[l_2], lb_c->d_p + lb_c->d_bl_p[1], sizeof(float) * 3);
				lb_c->d_bl_p[1] += sizeof(float) * 3;

				lckf_p[l_0][l_1].r_p[l_2] = malloc(sizeof(float) * 4);
				memcpy(lckf_p[l_0][l_1].r_p[l_2], lb_c->d_p + lb_c->d_bl_p[1], sizeof(float) * 4);
				lb_c->d_bl_p[1] += sizeof(float) * 4;

				lckf_p[l_0][l_1].t_p[l_2] = malloc(sizeof(float) * 3);
				memcpy(lckf_p[l_0][l_1].t_p[l_2], lb_c->d_p + lb_c->d_bl_p[1], sizeof(float) * 3);
				lb_c->d_bl_p[1] += sizeof(float) * 3;
			}

			lckf_p[l_0][l_1].k_min = lckf_p[l_0][l_1].bone_p[0];
			lckf_p[l_0][l_1].k_max = lckf_p[l_0][l_1].bone_p[lckf_p[l_0][l_1].bone_bl - 1];
			if (l_1 > 0)
			{
				if (lckf_p[l_0][l_1 - 1].k_min > lckf_p[l_0][l_1].bone_p[0])
				{
					lckf_p[l_0][l_1 - 1].k_min = lckf_p[l_0][l_1].bone_p[0];
				}
				if (lckf_p[l_0][l_1 - 1].k_max < lckf_p[l_0][l_1].bone_p[lckf_p[l_0][l_1].bone_bl - 1])
				{
					lckf_p[l_0][l_1 - 1].k_max = lckf_p[l_0][l_1].bone_p[lckf_p[l_0][l_1].bone_bl - 1];
				}
			}
		}

		if (lckf_p[l_0][lckf_bl_p[l_0] - 1].k_min > lckf_p[l_0][0].bone_p[0])
		{
			lckf_p[l_0][lckf_bl_p[l_0] - 1].k_min = lckf_p[l_0][0].bone_p[0];
		}
		if (lckf_p[l_0][lckf_bl_p[l_0] - 1].k_max < lckf_p[l_0][0].bone_p[lckf_p[l_0][0].bone_bl - 1])
		{
			lckf_p[l_0][lckf_bl_p[l_0] - 1].k_max = lckf_p[l_0][0].bone_p[lckf_p[l_0][0].bone_bl - 1];
		}
	}
}
