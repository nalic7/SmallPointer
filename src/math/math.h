#ifndef NALI_MATH_H
#define NALI_MATH_H

#pragma once

float math_radian(float degree);
float math_degree(float radian);
char* math_combine(const char* str1, const char* str2);
uint32_t math_n_c_size(int number);

// template<class T>
// static void getXX2DVector(std::vector<T> t_vector, std::vector<std::vector<T>>& t_2d_vector, const int& size)
// {
//	 for (int i = 0; i < t_vector.size(); i += size)
//	 {
//		 std::vector<T> temp_t_vector;

//		 for (int l = 0; l < size; ++l)
//		 {
//			 temp_t_vector.push_back(t_vector[i + l]);
//		 }

//		 t_2d_vector.push_back(temp_t_vector);
//	 }
// }

#endif
