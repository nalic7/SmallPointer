static const char *file_array[] =
{
	NALI_F_FACTORY_KEYFRAME "/SuperCutePomi0.bin"
};

static keyframe **keyframe_p;
static uint8_t *keyframe_bl_p;

void gkf_write()
{
	FILE *file = fopen(NALI_F_HOME_ASSET, "ab");
	fwrite((uint8_t[]){sizeof(file_array) / sizeof(file_array[0])}, sizeof(uint8_t), 1, file);

	keyframe_bl_p = malloc(sizeof(file_array) / sizeof(file_array[0]));
	keyframe_p = malloc(sizeof(file_array) / sizeof(file_array[0]) * sizeof(keyframe *));
	memset(keyframe_p, 0, sizeof(file_array) / sizeof(file_array[0]) * sizeof(keyframe *));

	uint32_t data_bl;
	uint8_t *data_p;
	uint32_t step;
	for (uint8_t l_0 = 0; l_0 < sizeof(file_array) / sizeof(file_array[0]); ++l_0)
	{
		data_p = f_read(file_array[l_0], &data_bl);
		step = 0;

		keyframe_bl_p[l_0] = *(uint8_t *)(data_p + step);
		fwrite(&keyframe_bl_p[l_0], sizeof(uint8_t), 1, file);
		step += sizeof(uint8_t);
		keyframe_p[l_0] = malloc(keyframe_bl_p[l_0] * sizeof(keyframe));

		for (uint32_t l_1 = 0; l_1 < keyframe_bl_p[l_0]; ++l_1)
		{
			keyframe_p[l_0][l_1].keyframe = *(uint8_t *)(data_p + step);
			fwrite(&keyframe_p[l_0][l_1].keyframe, sizeof(uint8_t), 1, file);
			step += sizeof(uint8_t);

			keyframe_p[l_0][l_1].bone_bl = *(uint8_t *)(data_p + step);
			fwrite(&keyframe_p[l_0][l_1].bone_bl, sizeof(uint8_t), 1, file);
			step += sizeof(uint8_t);

			keyframe_p[l_0][l_1].bone_p = malloc(keyframe_p[l_0][l_1].bone_bl);
			keyframe_p[l_0][l_1].animation_s_p = malloc(sizeof(float *) * keyframe_p[l_0][l_1].bone_bl);
			keyframe_p[l_0][l_1].animation_r_p = malloc(sizeof(float *) * keyframe_p[l_0][l_1].bone_bl);
			keyframe_p[l_0][l_1].animation_t_p = malloc(sizeof(float *) * keyframe_p[l_0][l_1].bone_bl);

			for (uint32_t l_2 = 0; l_2 < keyframe_p[l_0][l_1].bone_bl; ++l_2)
			{
				keyframe_p[l_0][l_1].bone_p[l_2] = *(uint8_t *)(data_p + step);
				fwrite(&keyframe_p[l_0][l_1].bone_p[l_2], sizeof(uint8_t), 1, file);
				step += sizeof(uint8_t);

				keyframe_p[l_0][l_1].animation_s_p[l_2] = malloc(sizeof(float) * 3);
				memcpy(keyframe_p[l_0][l_1].animation_s_p[l_2], data_p + step, sizeof(float) * 3);
				fwrite(keyframe_p[l_0][l_1].animation_s_p[l_2], sizeof(float), 3, file);
				step += sizeof(float) * 3;

				keyframe_p[l_0][l_1].animation_r_p[l_2] = malloc(sizeof(float) * 4);
				// memcpy(keyframe_p[l_0][l_1].animation_r_p[l_2], data + step, sizeof(float) * 4);
				keyframe_p[l_0][l_1].animation_r_p[l_2][3] = *(float *)(data_p + step);
				keyframe_p[l_0][l_1].animation_r_p[l_2][0] = *(float *)(data_p + step + sizeof(float));
				keyframe_p[l_0][l_1].animation_r_p[l_2][1] = *(float *)(data_p + step + sizeof(float) * 2);
				keyframe_p[l_0][l_1].animation_r_p[l_2][2] = *(float *)(data_p + step + sizeof(float) * 3);
				MV4_qi(keyframe_p[l_0][l_1].animation_r_p[l_2], 0)
				fwrite(keyframe_p[l_0][l_1].animation_r_p[l_2], sizeof(float), 4, file);
				step += sizeof(float) * 4;

				keyframe_p[l_0][l_1].animation_t_p[l_2]= malloc(sizeof(float) * 3);
				memcpy(keyframe_p[l_0][l_1].animation_t_p[l_2], data_p + step, sizeof(float) * 3);
				fwrite(keyframe_p[l_0][l_1].animation_t_p[l_2], sizeof(float), 3, file);
				step += sizeof(float) * 3;
			}
		}

		free(data_p);
	}

	fclose(file);
}