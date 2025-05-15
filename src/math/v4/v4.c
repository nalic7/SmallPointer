void v4_q(float x, float y, float z, float *w_qv4_float_p)
{
	float c1 = cosf(x / 2);
	float s1 = sinf(x / 2);
	float c2 = cosf(y / 2);
	float s2 = sinf(y / 2);
	float c3 = cosf(z / 2);
	float s3 = sinf(z / 2);

	w_qv4_float_p[0] = s1 * c2 * c3 + c1 * s2 * s3;
	w_qv4_float_p[1] = c1 * s2 * c3 - s1 * c2 * s3;
	w_qv4_float_p[2] = c1 * c2 * s3 + s1 * s2 * c3;
	w_qv4_float_p[3] = c1 * c2 * c3 - s1 * s2 * s3;
}

void v4_qm(float *r_qv4_float_p, float *w_m4x4_float_p)
{
	float xy = r_qv4_float_p[0] * r_qv4_float_p[1];
	float xz = r_qv4_float_p[0] * r_qv4_float_p[2];
	float xw = r_qv4_float_p[0] * r_qv4_float_p[3];
	float yz = r_qv4_float_p[1] * r_qv4_float_p[2];
	float yw = r_qv4_float_p[1] * r_qv4_float_p[3];
	float zw = r_qv4_float_p[2] * r_qv4_float_p[3];
	float x_squared = r_qv4_float_p[0] * r_qv4_float_p[0];
	float y_squared = r_qv4_float_p[1] * r_qv4_float_p[1];
	float z_squared = r_qv4_float_p[2] * r_qv4_float_p[2];

	w_m4x4_float_p[0] = 1 - 2 * (y_squared + z_squared);
	w_m4x4_float_p[1] = 2 * (xy - zw);
	w_m4x4_float_p[2] = 2 * (xz + yw);
	w_m4x4_float_p[4] = 2 * (xy + zw);
	w_m4x4_float_p[5] = 1 - 2 * (x_squared + z_squared);
	w_m4x4_float_p[6] = 2 * (yz - xw);
	w_m4x4_float_p[8] = 2 * (xz - yw);
	w_m4x4_float_p[9] = 2 * (yz + xw);
	w_m4x4_float_p[10] = 1 - 2 * (x_squared + y_squared);
}

void v4_m(float *a, float *b, float *w)
{
	w[0] = a[3]*b[0] + a[0]*b[3] + a[1]*b[2] - a[2]*b[1];
	w[1] = a[3]*b[1] - a[0]*b[2] + a[1]*b[3] + a[2]*b[0];
	w[2] = a[3]*b[2] + a[0]*b[1] - a[1]*b[0] + a[2]*b[3];
	w[3] = a[3]*b[3] - a[0]*b[0] - a[1]*b[1] - a[2]*b[2];
}