const float smptmPm4x4[] =
{
	1.0F, 0.0F, 0.0F, 0.0F,
	0.0F, 1.0F, 0.0F, 0.0F,
	0.0F, 0.0F, 1.0F, 0.0F,
	0.0F, 0.0F, 0.0F, 1.0F
};

void smptm_m4x4Mi(float m[16])
{
	float identity[] =
	{
		1.0F, 0.0F, 0.0F, 0.0F,
		0.0F, 1.0F, 0.0F, 0.0F,
		0.0F, 0.0F, 1.0F, 0.0F,
		0.0F, 0.0F, 0.0F, 1.0F
	};

	int32_t l_0, l_1, l_2;
	float s[16];
	float t[16];
	memcpy(s, smptmPm4x4, sizeof(smptmPm4x4));
	memcpy(t, m, sizeof(float) * 16);

	for (l_0 = 0; l_0 < 3; l_0++)
	{
		int32_t pivot = l_0;

		float pivotsize = t[l_0 * 4 + l_0];

		if (pivotsize < 0)
		{
			pivotsize = -pivotsize;
		}

		for (l_1 = l_0 + 1; l_1 < 4; l_1++)
		{
			float l_f = t[l_1 * 4 + l_0];

			if (l_f < 0)
				l_f = -l_f;

			if (l_f > pivotsize)
			{
				pivot = l_1;
				pivotsize = l_f;
			}
		}

		if (pivotsize == 0)
		{
			memcpy(m, identity, sizeof(float) * 16);
			return;
		}

		if (pivot != l_0)
		{
			for (l_1 = 0; l_1 < 4; l_1++)
			{
				int32_t i4j = l_0 * 4 + l_1;
				int32_t p4j = pivot * 4 + l_1;
				float tmp;

				tmp = t[i4j];
				t[i4j] = t[p4j];
				t[p4j] = tmp;

				tmp = s[i4j];
				s[i4j] = s[p4j];
				s[p4j] = tmp;
			}
		}

		for (l_1 = l_0 + 1; l_1 < 4; l_1++)
		{
			float l_f = t[l_1 * 4 + l_0] / t[l_0 * 4 + l_0];

			for (l_2 = 0; l_2 < 4; l_2++)
			{
				int32_t j4k = l_1 * 4 + l_2;
				int32_t i4k = l_0 * 4 + l_2;
				t[j4k] -= l_f * t[i4k];
				s[j4k] -= l_f * s[i4k];
			}
		}
	}

	for (l_0 = 3; l_0 >= 0; --l_0)
	{
		float l_f;

		if (!(l_f = t[l_0 * 4 + l_0]))
		{
			memcpy(m, identity, sizeof(float) * 16);
			return;
		}

		for (l_1 = 0; l_1 < 4; l_1++)
		{
			int32_t i4j = l_0 * 4 + l_1;

			t[i4j] /= l_f;
			s[i4j] /= l_f;
		}

		for (l_1 = 0; l_1 < l_0; l_1++)
		{
			l_f = t[l_1 * 4 + l_0];

			for (l_2 = 0; l_2 < 4; l_2++)
			{
				int32_t j4k = l_1 * 4 + l_2;
				int32_t i4k = l_0 * 4 + l_2;
				t[j4k] -= l_f * t[i4k];
				s[j4k] -= l_f * s[i4k];
			}
		}
	}

	memcpy(m, s, sizeof(float) * 16);
}

void smptm_m4x4Mm(const float a[16], const float b[16], float w[16])
{
	for (uint8_t l_0 = 0; l_0 < 4; l_0++)
	{
		for (uint8_t l_1 = 0; l_1 < 4; l_1++)
		{
			w[l_0 * 4 + l_1] = a[l_0 * 4] * b[l_1] + a[l_0 * 4 + 1] * b[4 + l_1] + a[l_0 * 4 + 2] * b[8 + l_1] + a[l_0 * 4 + 3] * b[12 + l_1];
		}
	}
}
