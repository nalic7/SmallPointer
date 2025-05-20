static const char *file_array[] =
{
	NALI_FACTORY NALI_HOME_KEYFRAME "/SuperCutePomi0.bin"
};

// const uint8_t end_array[] =
// {
// 	95
// };

// typedef struct
// {
// 	uint8_t
// 		keyframe,
// 		bone_bl,
// 		*bone_p;
// 	float
// 		*animation_s_p,
// 		*animation_r_p,
// 		*animation_t_p;
// } keyframe;

keyframe **keyframe_p;
uint8_t *keyframe_bl_p;

void gkf_write()
{
	keyframe_bl_p = malloc(sizeof(file_array) / sizeof(file_array[0]));
	keyframe_p = malloc(sizeof(file_array) / sizeof(file_array[0]) * sizeof(keyframe *));
	memset(keyframe_p, 0, sizeof(file_array) / sizeof(file_array[0]) * sizeof(keyframe *));

	long file_bl;
	char *data;
	uint32_t step;
	for (uint32_t l_0 = 0; l_0 < sizeof(file_array) / sizeof(file_array[0]); ++l_0)
	{
		data = f_read(file_array[l_0], &file_bl);
		step = 0;

		// char *bone_p = malloc(0);
		// uint32_t bone_bl = 0;

		// float *f_p = malloc(0);
		// uint32_t f_bl = 0;

		// int32_t *keyframe_p = malloc(0);
		// uint32_t keyframe_bl = 0;
		// while (1)
		// {
		// 	m_str_p(&data, (const char*[]){"\""}, 1);
		// 	m_str_c2i(&data, &keyframe_p, &keyframe_bl, "\"", "\"");

		// 	uint8_t keyframe = *keyframe_p;
		// 	++keyframe_p;

		// 	m_str_c2c(&data, &bone_p, &bone_bl, "\"", "\"");

		// 	for (uint8_t l_1 = 0; l_1 < 3; ++l_1)
		// 	{
		// 		m_str_c2f(&data, &f_p, &keyframe_bl, ",", ",");
		// 	}
		// 	m_str_c2f(&data, &f_p, &keyframe_bl, " ", " ");

		// 	m_str_p(&data, (const char*[]){"["}, 1);

		// 	if (keyframe == end_array[l_0])
		// 		break;
		// }
		// free(keyframe_p);

		// free(f_p);

		// free(bone_p);
		keyframe_bl_p[l_0] = *(uint8_t *)(data + step);
		step += sizeof(uint8_t);
		keyframe_p[l_0] = malloc(keyframe_bl_p[l_0] * sizeof(keyframe));

		for (uint32_t l_1 = 0; l_1 < keyframe_bl_p[l_0]; ++l_1)
		{
			keyframe_p[l_0][l_1].keyframe = *(uint8_t *)(data + step);
			step += sizeof(uint8_t);

			keyframe_p[l_0][l_1].bone_bl = *(uint8_t *)(data + step);
			step += sizeof(uint8_t);

			keyframe_p[l_0][l_1].bone_p = malloc(keyframe_p[l_0][l_1].bone_bl);
			keyframe_p[l_0][l_1].animation_s_p = malloc(sizeof(float *) * keyframe_p[l_0][l_1].bone_bl);
			keyframe_p[l_0][l_1].animation_r_p = malloc(sizeof(float *) * keyframe_p[l_0][l_1].bone_bl);
			keyframe_p[l_0][l_1].animation_t_p = malloc(sizeof(float *) * keyframe_p[l_0][l_1].bone_bl);

			for (uint32_t l_2 = 0; l_2 < keyframe_p[l_0][l_1].bone_bl; ++l_2)
			{
				keyframe_p[l_0][l_1].bone_p[l_2] = *(uint8_t *)(data + step);
				step += sizeof(uint8_t);

				keyframe_p[l_0][l_1].animation_s_p[l_2] = malloc(sizeof(float) * 3);
				memcpy(keyframe_p[l_0][l_1].animation_s_p[l_2], data + step, sizeof(float) * 3);
				step += sizeof(float) * 3;

				keyframe_p[l_0][l_1].animation_r_p[l_2] = malloc(sizeof(float) * 4);
				// memcpy(keyframe_p[l_0][l_1].animation_r_p[l_2], data + step, sizeof(float) * 4);
				keyframe_p[l_0][l_1].animation_r_p[l_2][3] = *(float *)(data + step);
				keyframe_p[l_0][l_1].animation_r_p[l_2][0] = *(float *)(data + step + sizeof(float));
				keyframe_p[l_0][l_1].animation_r_p[l_2][1] = *(float *)(data + step + sizeof(float) * 2);
				keyframe_p[l_0][l_1].animation_r_p[l_2][2] = *(float *)(data + step + sizeof(float) * 3);
				M_V4_qi(keyframe_p[l_0][l_1].animation_r_p[l_2], 0)
				step += sizeof(float) * 4;

				keyframe_p[l_0][l_1].animation_t_p[l_2]= malloc(sizeof(float) * 3);
				memcpy(keyframe_p[l_0][l_1].animation_t_p[l_2], data + step, sizeof(float) * 3);
				step += sizeof(float) * 3;
			}
		}

		free(data);
	}
}