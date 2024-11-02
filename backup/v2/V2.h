#ifndef V2_H
#define V2_H

#pragma once

struct V2
{
	float x, y;

	static void set(std::vector<float> float_vector, std::vector<V2>& v2_vector)
	{
		for (int i = 0; i < float_vector.size(); i += 2)
		{
			V2 v2 = V2{};

			v2.x = float_vector[i];
			v2.y = float_vector[i + 1];

			v2_vector.push_back(v2);
		}
	}

	static void plus(float*& mat2, const float*& mat2_0)
	{
		mat2[0] += mat2_0[0];
		mat2[1] += mat2_0[1];
	}

	// static void normalize(float*& mat2)
	// {
	//	 float length = std::sqrt(mat2[0] * mat2[0] + mat2[1] * mat2[1]);

	//	 if (length != 0.0F)
	//	 {
	//		 float inverse_length = 1.0F / length;

	//		 mat2[0] *= inverse_length;
	//		 mat2[1] *= inverse_length;
	//	 }
	// }
};

#endif
