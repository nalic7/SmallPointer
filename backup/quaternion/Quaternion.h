#ifndef QUATERNION_H
#define QUATERNION_H

#pragma once

struct Quaternion
{
	float x, y, z, w;

	Quaternion(float x, float y, float z)
	{
		// float c1 = cosf(x / 2);
		// float s1 = sinf(x / 2);
		// float c2 = cosf(y / 2);
		// float s2 = sinf(y / 2);
		// float c3 = cosf(z / 2);
		// float s3 = sinf(z / 2);
		// this->x = c1 * c2 * c3 + s1 * s2 * s3; // Scalar part
		// this->y = s1 * c2 * c3 - c1 * s2 * s3; // X-component of vector part
		// this->z = c1 * s2 * c3 + s1 * c2 * s3; // Y-component of vector part
		// this->w = c1 * c2 * s3 - s1 * s2 * c3; // Z-component of vector part

		float c1 = std::cos(x / 2);
		float s1 = std::sin(x / 2);
		float c2 = std::cos(y / 2);
		float s2 = std::sin(y / 2);
		float c3 = std::cos(z / 2);
		float s3 = std::sin(z / 2);

		this->w = c1 * c2 * c3 - s1 * s2 * s3; // Scalar part
		this->x = s1 * c2 * c3 + c1 * s2 * s3; // X-component of vector part
		this->y = c1 * s2 * c3 - s1 * c2 * s3; // Y-component of vector part
		this->z = c1 * c2 * s3 + s1 * s2 * c3; // Z-component of vector part
	}

	static void getEuler(Quaternion quaternion, float& x, float& y, float& z)
	{
		x = atan2f(2 * (quaternion.x * quaternion.y + quaternion.z * quaternion.w), 1 - 2 * (quaternion.y * quaternion.y + quaternion.z * quaternion.z));
		y = asinf(2 * (quaternion.x * quaternion.z - quaternion.w * quaternion.y));
		z = atan2f(2 * (quaternion.x * quaternion.w + quaternion.y * quaternion.z), 1 - 2 * (quaternion.z * quaternion.z + quaternion.w * quaternion.w));
	}

	M4x4 getM4x4()
	{
		float xy = this->x * this->y;
		float xz = this->x * this->z;
		float xw = this->x * this->w;
		float yz = this->y * this->z;
		float yw = this->y * this->w;
		float zw = this->z * this->w;
		float x_squared = this->x * this->x;
		float y_squared = this->y * this->y;
		float z_squared = this->z * this->z;

		M4x4 m4x4{};
		m4x4.mat[0] = 1 - 2 * (y_squared + z_squared);
		m4x4.mat[1] = 2 * (xy - zw);
		m4x4.mat[2] = 2 * (xz + yw);
		//m4x4.mat[3] = 0;
		m4x4.mat[4] = 2 * (xy + zw);
		m4x4.mat[5] = 1 - 2 * (x_squared + z_squared);
		m4x4.mat[6] = 2 * (yz - xw);
		//m4x4.mat[7] = 0;
		m4x4.mat[8] = 2 * (xz - yw);
		m4x4.mat[9] = 2 * (yz + xw);
		m4x4.mat[10] = 1 - 2 * (x_squared + y_squared);
		//m4x4.mat[11] = 0;
		//m4x4.mat[12] = 0;
		//m4x4.mat[13] = 0;
		//m4x4.mat[14] = 0;
		//m4x4.mat[15] = 1;

		return m4x4;
	}

	M3x3 getM3x3()
	{
		float xy = this->x * this->y;
		float xz = this->x * this->z;
		float xw = this->x * this->w;
		float yz = this->y * this->z;
		float yw = this->y * this->w;
		float zw = this->z * this->w;
		float x_squared = this->x * this->x;
		float y_squared = this->y * this->y;
		float z_squared = this->z * this->z;

		M3x3 m3x3{};
		m3x3.mat[0] = 1 - 2 * (y_squared + z_squared);
		m3x3.mat[1] = 2 * (xy - zw);
		m3x3.mat[2] = 2 * (xz + yw);
		m3x3.mat[3] = 2 * (xy + zw);
		m3x3.mat[4] = 1 - 2 * (x_squared + z_squared);
		m3x3.mat[5] = 2 * (yz - xw);
		m3x3.mat[6] = 2 * (xz - yw);
		m3x3.mat[7] = 2 * (yz + xw);
		m3x3.mat[8] = 1 - 2 * (x_squared + y_squared);

		return m3x3;
	}

	void multiply(const Quaternion& quaternion)
	{
		float x = this->w * quaternion.x + this->x * quaternion.w + this->y * quaternion.z - this->z * quaternion.y;
		float y = this->w * quaternion.y - this->x * quaternion.z + this->y * quaternion.w + this->z * quaternion.x;
		float z = this->w * quaternion.z + this->x * quaternion.y - this->y * quaternion.x + this->z * quaternion.w;
		float w = this->w * quaternion.w - this->x * quaternion.x - this->y * quaternion.y - this->z * quaternion.z;

		this->w = w;
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

#endif
