#ifndef V4_H
#define V4_H

#pragma once

template <typename T>
struct V4
{
	T x, y, z, w;

	static void set(std::vector<T> float_vector, std::vector<V4>& v4_vector)
	{
		for (int i = 0; i < float_vector.size(); i += 4)
		{
			V4 v4 = V4{};

			v4.x = float_vector[i];
			v4.y = float_vector[i + 1];
			v4.z = float_vector[i + 2];
			v4.w = float_vector[i + 3];

			v4_vector.push_back(v4);
		}
	}

	static void cross(T*& mat4, const T*& mat4_0, const T*& mat4_1, const T*& mat4_2)
	{
		mat4[0] = mat4_0[1] * (mat4_1[2] * mat4_2[3] - mat4_2[2] * mat4_1[3]) - mat4_0[2] * (mat4_1[1] * mat4_2[3] - mat4_2[1] * mat4_1[3]) + mat4_0[3] * (mat4_1[1] * mat4_2[2] - mat4_1[2] * mat4_2[1]);
		mat4[1] = -(mat4_0[0] * (mat4_1[2] * mat4_2[3] - mat4_2[2] * mat4_1[3]) - mat4_0[2] * (mat4_1[0] * mat4_2[3] - mat4_2[0] * mat4_1[3]) + mat4_0[3] * (mat4_1[0] * mat4_2[2] - mat4_2[0] * mat4_1[2]));
		mat4[2] = mat4_0[0] * (mat4_1[1] * mat4_2[3] - mat4_2[1] * mat4_1[3]) - mat4_0[1] * (mat4_1[0] * mat4_2[3] - mat4_2[0] * mat4_1[3]) + mat4_0[3] * (mat4_1[0] * mat4_2[1] - mat4_2[0] * mat4_1[1]);
		mat4[3] = -(mat4_0[0] * (mat4_1[1] * mat4_2[2] - mat4_2[1] * mat4_1[2]) - mat4_0[1] * (mat4_1[0] * mat4_2[2] - mat4_2[0] * mat4_1[2]) + mat4_0[2] * (mat4_1[0] * mat4_2[1] - mat4_2[0] * mat4_1[1]));
	}
};

#endif
