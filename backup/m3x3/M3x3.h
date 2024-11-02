#ifndef M3X3_H
#define M3X3_H

#pragma once

struct M3x3
{
	float mat[9] =
	{
		1.0F, 0.0F, 0.0F,
		0.0F, 1.0F, 0.0F,
		0.0F, 0.0F, 1.0F
	};

//	static void rotateX(float*& mat9, const float& x)
//	{
//		mat9[4] = (float)cos(x);
//		mat9[5] = (float)sin(x);
//		mat9[7] = (float)-sin(x);
//		mat9[8] = (float)cos(x);
//	}
//
//	static void rotateY(float*& mat9, const float& y)
//	{
//		mat9[0] = (float)cos(y);
//		mat9[2] = (float)-sin(y);
//		mat9[6] = (float)sin(y);
//		mat9[8] = (float)cos(y);
//	}
//
//	static void rotateZ(float*& mat9, const float& z)
//	{
//		mat9[0] = (float)cos(z);
//		mat9[1] = (float)sin(z);
//		mat9[3] = (float)-sin(z);
//		mat9[4] = (float)cos(z);
//	}

//	static void getM3x3V3(const float*& mat9, const float*& mat3_0, float*& mat3_1)
//	{
//		mat3_1[0] = mat3_0[0] * mat9[0] + mat3_0[1] * mat9[1] + mat3_0[2] * mat9[2];
//		mat3_1[1] = mat3_0[0] * mat9[3] + mat3_0[1] * mat9[4] + mat3_0[2] * mat9[5];
//		mat3_1[2] = mat3_0[0] * mat9[6] + mat3_0[1] * mat9[7] + mat3_0[2] * mat9[8];
//	}

//	static void multiply(float*& mat9, const float*& mat9_0)
//	{
//		float* float_array = new float[9];
//
//		for (int i = 0; i < 3; i++)
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				float_array[i * 3 + j] = mat9[i * 3] * mat9_0[j] + mat9[i * 3 + 1] * mat9_0[3 + j] + mat9[i * 3 + 2] * mat9_0[6 + j];
//			}
//		}
//
//		delete[] mat9;
//
//		mat9 = float_array;
//	}

	void getM3x3V3(const V3& v30, V3& v31)
	{
		v31.x = v30.x * this->mat[0] + v30.y * this->mat[1] + v30.z * this->mat[2];
		v31.y = v30.x * this->mat[3] + v30.y * this->mat[4] + v30.z * this->mat[5];
		v31.z = v30.x * this->mat[6] + v30.y * this->mat[7] + v30.z * this->mat[8];
	}

	void multiply(const M3x3& m3x3)
	{
		std::vector<float> float_vector(16);

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				float_vector[i * 3 + j] = this->mat[i * 3] * m3x3.mat[j] + this->mat[i * 3 + 1] * m3x3.mat[3 + j] + this->mat[i * 3 + 2] * m3x3.mat[6 + j];
			}
		}

		std::copy(float_vector.begin(), float_vector.end(), this->mat);
	}
};

#endif
