static const char *file_array[] =
{
	NALI_F_FACTORY_KEYFRAME "/SuperCutePomiWalk.bin"
};

void gkf_write()
{
	FILE *file = fopen(NALI_F_HOME_ASSET, "ab");
	fwrite((uint8_t[]){sizeof(file_array) / sizeof(file_array[0])}, sizeof(uint8_t), 1, file);

	uint32_t data_bl;
	uint8_t *data_p;
	uint32_t step;
	for (uint8_t l_0 = 0; l_0 < sizeof(file_array) / sizeof(file_array[0]); ++l_0)
	{
		data_p = f_read(file_array[l_0], &data_bl);
		step = 0;

		uint8_t keyframe_bl = *(uint8_t *)(data_p + step);
		fwrite(&keyframe_bl, sizeof(uint8_t), 1, file);
		step += sizeof(uint8_t);

		for (uint32_t l_1 = 0; l_1 < keyframe_bl; ++l_1)
		{
			uint8_t bone_bl = *(uint8_t *)(data_p + step);
			fwrite(&bone_bl, sizeof(uint8_t), 1, file);
			step += sizeof(uint8_t);

			for (uint32_t l_2 = 0; l_2 < bone_bl; ++l_2)
			{
				fwrite(data_p + step, sizeof(uint8_t), 1, file);
				step += sizeof(uint8_t);

				fwrite(data_p + step, sizeof(float), 3, file);
				step += sizeof(float) * 3;

				float r_p[4];
				r_p[3] = *(float *)(data_p + step);
				r_p[0] = *(float *)(data_p + step + sizeof(float));
				r_p[1] = *(float *)(data_p + step + sizeof(float) * 2);
				r_p[2] = *(float *)(data_p + step + sizeof(float) * 3);
				MV4_qi(r_p, 0)
				fwrite(r_p, sizeof(float), 4, file);
				step += sizeof(float) * 4;

				fwrite(data_p + step, sizeof(float), 3, file);
//				r_p[0] = *(float *)(data_p + step);
//				r_p[1] = *(float *)(data_p + step + sizeof(float));
//				r_p[2] = *(float *)(data_p + step + sizeof(float) * 2);
//				fwrite(r_p, sizeof(float), 3, file);
				step += sizeof(float) * 3;
			}
		}

		free(data_p);
	}

	fclose(file);
}
