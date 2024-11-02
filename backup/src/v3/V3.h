#ifndef V3_H
#define V3_H

struct V3
{
	float x, y, z;

	void set(std::vector<float> float_vector, std::vector<V3>& v3_vector)
	{
		for (int i = 0; i < float_vector.size(); i += 3)
		{
			V3 v3 = V3{};

			v3.x = float_vector[i];
			v3.y = float_vector[i + 1];
			v3.z = float_vector[i + 2];

			v3_vector.push_back(v3);
		}
	}

	void plus(float*& mat3, const float*& mat3_0)
	{
		mat3[0] += mat3_0[0];
		mat3[1] += mat3_0[1];
		mat3[2] += mat3_0[2];
	}

	void normalize(float*& mat3)
	{
		float w = std::sqrt(mat3[0] * mat3[0] + mat3[1] * mat3[1] + mat3[2] * mat3[2]);

		mat3[0] /= w;
		mat3[1] /= w;
		mat3[2] /= w;
	}

	void cross(float*& mat3, const float*& mat3_0, const float*& mat3_1)
	{
		mat3[0] = mat3_0[1] * mat3_1[2] - mat3_0[2] * mat3_1[1];
		mat3[1] = mat3_0[2] * mat3_1[0] - mat3_0[0] * mat3_1[2];
		mat3[2] = mat3_0[0] * mat3_1[1] - mat3_0[1] * mat3_1[0];
	}

	float getDot(const float*& mat3_0, const float*& mat3_1)
	{
		return mat3_0[0] * mat3_1[0] + mat3_0[1] * mat3_1[1] + mat3_0[2] * mat3_1[2];
	}
};

#endif
