void smptm_v3Mq2m(const float q[3], float w[16])
{
	float xy = q[0] * q[1];
	float xz = q[0] * q[2];
	float x = q[0];
	float yz = q[1] * q[2];
	float y = q[1];
	float z = q[2];
	float x_squared = q[0] * q[0];
	float y_squared = q[1] * q[1];
	float z_squared = q[2] * q[2];

	w[0] = 1 - 2 * (y_squared + z_squared);
	w[1] = 2 * (xy - z);
	w[2] = 2 * (xz + y);
	w[4] = 2 * (xy + z);
	w[5] = 1 - 2 * (x_squared + z_squared);
	w[6] = 2 * (yz - x);
	w[8] = 2 * (xz - y);
	w[9] = 2 * (yz + x);
	w[10] = 1 - 2 * (x_squared + y_squared);
}
