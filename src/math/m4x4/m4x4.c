float m_m4x4_mat[] =
{
	1.0F, 0.0F, 0.0F, 0.0F,
	0.0F, 1.0F, 0.0F, 0.0F,
	0.0F, 0.0F, 1.0F, 0.0F,
	0.0F, 0.0F, 0.0F, 1.0F
};

void m4x4_inverse(float* m4x4_p)
{
	float identity[] =
	{
		1.0F, 0.0F, 0.0F, 0.0F,
		0.0F, 1.0F, 0.0F, 0.0F,
		0.0F, 0.0F, 1.0F, 0.0F,
		0.0F, 0.0F, 0.0F, 1.0F
	};

	int32_t i, j, k;
	float s[16];
	float t[16];
	memcpy(s, m_m4x4_mat, sizeof(float) * 16);
	memcpy(t, m4x4_p, sizeof(float) * 16);

	for (i = 0; i < 3; i++)
	{
		int32_t pivot = i;

		float pivotsize = t[i * 4 + i];

		if (pivotsize < 0)
		{
			pivotsize = -pivotsize;
		}

		for (j = i + 1; j < 4; j++)
		{
			float tmp = t[j * 4 + i];

			if (tmp < 0)
				tmp = -tmp;

			if (tmp > pivotsize)
			{
				pivot = j;
				pivotsize = tmp;
			}
		}

		if (pivotsize == 0)
		{
			memcpy(m4x4_p, identity, sizeof(float) * 16);
			return;
		}

		if (pivot != i)
		{
			for (j = 0; j < 4; j++)
			{
				int32_t i4j = i * 4 + j;
				int32_t p4j = pivot * 4 + j;
				float tmp;

				tmp = t[i4j];
				t[i4j] = t[p4j];
				t[p4j] = tmp;

				tmp = s[i4j];
				s[i4j] = s[p4j];
				s[p4j] = tmp;
			}
		}

		for (j = i + 1; j < 4; j++)
		{
			float f = t[j * 4 + i] / t[i * 4 + i];

			for (k = 0; k < 4; k++)
			{
				int32_t j4k = j * 4 + k;
				int32_t i4k = i * 4 + k;
				t[j4k] -= f * t[i4k];
				s[j4k] -= f * s[i4k];
			}
		}
	}

	for (i = 3; i >= 0; --i)
	{
		float f;

		if ((f = t[i * 4 + i]) == 0)
		{
			memcpy(m4x4_p, identity, sizeof(float) * 16);
			return;
		}

		for (j = 0; j < 4; j++)
		{
			int32_t i4j = i * 4 + j;

			t[i4j] /= f;
			s[i4j] /= f;
		}

		for (j = 0; j < i; j++)
		{
			f = t[j * 4 + i];

			for (k = 0; k < 4; k++)
			{
				int32_t j4k = j * 4 + k;
				int32_t i4k = i * 4 + k;
				t[j4k] -= f * t[i4k];
				s[j4k] -= f * s[i4k];
			}
		}
	}

	memcpy(m4x4_p, s, sizeof(float) * 16);
}

void m4x4_p(float fov, float aspect, float z_near, float z_far, float* m4x4_p)
{
	// float z_range = z_near - z_far;
	// float tan_fov = tanf(fov);

	// m4x4_p[0] = 1.0F / (tan_fov * aspect);
	// m4x4_p[5] = 1.0F / tan_fov;
	// m4x4_p[10] = (-z_near - z_far) / z_range;
	// m4x4_p[11] = 1.0F;
	// m4x4_p[14] = 2.0F * z_far * z_near / z_range;

	fov *= (M_PI / 180.0F);
	float z_range = z_far - z_near;
	float tan_half_fov = tanf(fov / 2.0F);

	m4x4_p[0] = 1.0F / (tan_half_fov * aspect);
	m4x4_p[5] = 1.0F / tan_half_fov;
	m4x4_p[10] = -(z_far + z_near) / z_range;
	m4x4_p[11] = -1.0F;
	m4x4_p[14] = -(2.0F * z_far * z_near) / z_range;
}