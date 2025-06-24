#ifndef NALI_MATH_M4X4_H
#define NALI_MATH_M4X4_H

extern const float mm4x4_array[16];

void mm4x4_i(float m[16]);
void mm4x4_m(const float a[16], const float b[16], float w[16]);

// float z_range = z_near - z_far;
// float tan_fov = tanf(fov);
// m4x4_p[0] = 1.0F / (tan_fov * aspect);
// m4x4_p[5] = 1.0F / tan_fov;
// m4x4_p[10] = (-z_near - z_far) / z_range;
// m4x4_p[11] = 1.0F;
// m4x4_p[14] = 2.0F * z_far * z_near / z_range;
#define MM4X4_P(fov, aspect, z_near, z_far, m4x4_p) \
	(m4x4_p)[0] = -1.0F / (fov * aspect); \
	(m4x4_p)[5] = 1.0F / fov; \
	(m4x4_p)[10] = -(z_far + z_near) / (z_far - z_near); \
	(m4x4_p)[11] = -1.0F; \
	(m4x4_p)[14] = -(2.0F * z_far * z_near) / (z_far - z_near);
// struct M4x4
// {
//	 float mat[16];
//	 // TransformComponents decompose_transform(const float* matrix)
//	 // {
//	 //	 TransformComponents components;

//	 //	 // Extract the upper 3x3 matrix
//	 //	 float upper_matrix[9];
//	 //	 for (int i = 0; i < 3; i++) {
//	 //		 for (int j = 0; j < 3; j++) {
//	 //			 upper_matrix[i * 3 + j] = matrix[i * 4 + j];
//	 //		 }
//	 //	 }

//	 //	 // Calculate the scale component
//	 //	 components.scale[0] = sqrt(upper_matrix[0] * upper_matrix[0] + upper_matrix[1] * upper_matrix[1] + upper_matrix[2] * upper_matrix[2]);
//	 //	 components.scale[1] = sqrt(upper_matrix[3] * upper_matrix[3] + upper_matrix[4] * upper_matrix[4] + upper_matrix[5] * upper_matrix[5]);
//	 //	 components.scale[2] = sqrt(upper_matrix[6] * upper_matrix[6] + upper_matrix[7] * upper_matrix[7] + upper_matrix[8] * upper_matrix[8]);

//	 //	 // Normalize the upper matrix to get the rotation component
//	 //	 float length = sqrt(upper_matrix[0] * upper_matrix[0] + upper_matrix[1] * upper_matrix[1] + upper_matrix[2] * upper_matrix[2]);
//	 //	 components.rotation[0] = std::atan2(upper_matrix[7] / length, upper_matrix[8] / length);
//	 //	 components.rotation[1] = std::atan2(-upper_matrix[6] / length, std::sqrt(upper_matrix[7] * upper_matrix[7] + upper_matrix[8] * upper_matrix[8]) / length);
//	 //	 components.rotation[2] = std::atan2(upper_matrix[3] / length, upper_matrix[0] / length);

//	 //	 // Extract the translation component
//	 //	 components.translation[0] = matrix[3];
//	 //	 components.translation[1] = matrix[7];
//	 //	 components.translation[2] = matrix[11];

//	 //	 return components;
//	 // }

//	 // static float* getIdentity()
//	 // {
//	 //	 return new float[16]
//	 //	 {
//	 //		 1.0F, 0.0F, 0.0F, 0.0F,
//	 //		 0.0F, 1.0F, 0.0F, 0.0F,
//	 //		 0.0F, 0.0F, 1.0F, 0.0F,
//	 //		 0.0F, 0.0F, 0.0F, 1.0F
//	 //	 };
//	 // }

//	 static void getEuler(float mat[], float& x, float& y, float& z)
//	 {
//		 float R[3][3];
//		 for (int i = 0; i < 3; i++)
//		 {
//			 for (int j = 0; j < 3; j++)
//			 {
//				 R[i][j] = mat[i * 4 + j];
//			 }
//		 }

//		 x = atan2f(R[2][1], R[2][2]);
//		 y = atan2f(-R[2][0], sqrtf(R[2][1]*R[2][1] + R[2][2]*R[2][2]));
//		 z = atan2f(R[1][0], R[0][0]);
//	 }

//	 // void extract_scale_from_matrix(const float* matrix, float* scale)
//	 // {
//	 //	 // Extract the upper 3x3 matrix from the 4x4 matrix
//	 //	 float upper_matrix[9];
//	 //	 for (int i = 0; i < 3; i++) {
//	 //		 for (int j = 0; j < 3; j++) {
//	 //			 upper_matrix[i * 3 + j] = matrix[i * 4 + j];
//	 //		 }
//	 //	 }

//	 //	 // Calculate the length of each row of the upper 3x3 matrix
//	 //	 float row_lengths[3];
//	 //	 for (int i = 0; i < 3; i++) {
//	 //		 row_lengths[i] = sqrt(upper_matrix[i * 3] * upper_matrix[i * 3] +
//	 //							 upper_matrix[i * 3 + 1] * upper_matrix[i * 3 + 1] +
//	 //							 upper_matrix[i * 3 + 2] * upper_matrix[i * 3 + 2]);
//	 //	 }

//	 //	 // Check if the scaling factors are uniformly scaled
//	 //	 bool is_uniform_scale = true;
//	 //	 for (int i = 0; i < 3; i++) {
//	 //		 for (int j = i + 1; j < 3; j++) {
//	 //			 if (fabs(row_lengths[i] - row_lengths[j]) > 1e-5) {
//	 //				 is_uniform_scale = false;
//	 //				 break;
//	 //			 }
//	 //		 }
//	 //	 }

//	 //	 // Calculate the scaling factors
//	 //	 if (is_uniform_scale) {
//	 //		 float avg_scale = (row_lengths[0] + row_lengths[1] + row_lengths[2]) / 3.0f;
//	 //		 scale[0] = avg_scale;
//	 //		 scale[1] = avg_scale;
//	 //		 scale[2] = avg_scale;
//	 //	 }
//	 //	 else {
//	 //		 scale[0] = row_lengths[0];
//	 //		 scale[1] = row_lengths[1];
//	 //		 scale[2] = row_lengths[2];
//	 //	 }
//	 // }

//	 // void euler_to_matrix(float alpha, float beta, float gamma, float* matrix)
//	 // {
//	 //	 float c1 = cos(alpha);
//	 //	 float s1 = sin(alpha);
//	 //	 float c2 = cos(beta);
//	 //	 float s2 = sin(beta);
//	 //	 float c3 = cos(gamma);
//	 //	 float s3 = sin(gamma);
//	 //	 matrix[0] = c2 * c3;			 // Row 1, Column 1
//	 //	 matrix[1] = -c2 * s3;			// Row 1, Column 2
//	 //	 matrix[2] = s2;				  // Row 1, Column 3
//	 //	 matrix[3] = c1 * s3 + c3 * s1 * s2; // Row 2, Column 1
//	 //	 matrix[4] = c1 * c3 - s1 * s2 * s3; // Row 2, Column 2
//	 //	 matrix[5] = -c2 * s1;			   // Row 2, Column 3
//	 //	 matrix[6] = s1 * s3 - c1 * c3 * s2; // Row 3, Column 1
//	 //	 matrix[7] = c3 * s1 + c1 * s2 * s3; // Row 3, Column 2
//	 //	 matrix[8] = c1 * c2;			   // Row 3, Column 3
//	 // }

//	 void transpose()
//	 {
//		 std::vector<float> float_vector(16);

//		 for (int i = 0; i < 4; ++i)
//		 {
//			 for (int j = 0; j < 4; ++j)
//			 {
//				 float_vector[j * 4 + i] = this->mat[i * 4 + j];
//			 }
//		 }

//		 std::copy(float_vector.begin(), float_vector.end(), this->mat);
//	 }

//	 void perspective(const float& fov, const float& aspect, const float& znear, const float& zfar)
//	 {
//		 const float zRange = znear - zfar;
//		 const float tanHalfFOV = tanf(fov);

//		 std::vector<float> float_vector
//		 {
//			 0.5F / (tanHalfFOV * aspect), 0.0F, 0.0F, 0.0F,
//			 0.0F, 0.5F / tanHalfFOV, 0.0F, 0.0F,
//			 0.0F, 0.0F, (-znear - zfar) / zRange, 1.0F,
//			 0.0F, 0.0F, 2.0F * zfar * znear / zRange, 0.0F
//		 };

//		 std::copy(float_vector.begin(), float_vector.end(), this->mat);
//	 }

//	 void translate(const float& x, const float& y, const float& z)
//	 {
//		 this->mat[12] = x;
//		 this->mat[13] = y;
//		 this->mat[14] = z;
//	 }

//	 void scale(const float& x, const float& y, const float& z)
//	 {
//		 this->mat[0] = x;
//		 this->mat[5] = y;
//		 this->mat[10] = z;
//	 }

//	 void rotateX(const float& x)
//	 {
//		 this->mat[5] = (float)cos(x);
//		 this->mat[6] = (float)sin(x);
//		 this->mat[9] = (float)-sin(x);
//		 this->mat[10] = (float)cos(x);
//	 }

//	 void rotateY(const float& y)
//	 {
//		 this->mat[0] = (float)cos(y);
//		 this->mat[2] = (float)-sin(y);
//		 this->mat[8] = (float)sin(y);
//		 this->mat[10] = (float)cos(y);
//	 }

//	 void rotateZ(const float& z)
//	 {
//		 this->mat[0] = (float)cos(z);
//		 this->mat[1] = (float)sin(z);
//		 this->mat[4] = (float)-sin(z);
//		 this->mat[5] = (float)cos(z);
//	 }

//	 void getM4x4V3(const float*& mat3_0, float*& mat3_1)
//	 {
//		 mat3_1[0] = mat3_0[0] * this->mat[0] + mat3_0[1] * this->mat[1] + mat3_0[2] * this->mat[2] + this->mat[3];
//		 mat3_1[1] = mat3_0[0] * this->mat[4] + mat3_0[1] * this->mat[5] + mat3_0[2] * this->mat[6] + this->mat[7];
//		 mat3_1[2] = mat3_0[0] * this->mat[8] + mat3_0[1] * this->mat[9] + mat3_0[2] * this->mat[10] + this->mat[11];

//		 float w = mat3_0[0] * this->mat[12] + mat3_0[1] * this->mat[13] + mat3_0[2] * this->mat[14] + this->mat[15];

//		 if (w != 1)
//		 {
//			 mat3_1[0] /= w;
//			 mat3_1[1] /= w;
//			 mat3_1[2] /= w;
//		 }
//	 }

//	 void operator *= (const M4x4& m4x4)
//	 {
//		 std::vector<float> float_vector(16);

//		 for (int i = 0; i < 4; i++)
//		 {
//			 for (int j = 0; j < 4; j++)
//			 {
//				 float_vector[i * 4 + j] = this->mat[i * 4] * m4x4.mat[j] + this->mat[i * 4 + 1] * m4x4.mat[4 + j] + this->mat[i * 4 + 2] * m4x4.mat[8 + j] + this->mat[i * 4 + 3] * m4x4.mat[12 + j];
//			 }
//		 }

//		 std::copy(float_vector.begin(), float_vector.end(), this->mat);
//	 }

//	 //void setX(V3& v3)
//	 //{
//	 //	v3.x = this->mat[0];
//	 //	v3.y = this->mat[1];
//	 //	v3.z = this->mat[2];
//	 //}
//	 //
//	 //void setZ(V3& v3)
//	 //{
//	 //	v3.x = this->mat[8];
//	 //	v3.y = this->mat[9];
//	 //	v3.z = this->mat[10];
//	 //}

//	 //void translate(const float& x, const float& y, const float& z)
//	 //{
//	 //	this->mat[12] = x;
//	 //	this->mat[13] = y;
//	 //	this->mat[14] = z;
//	 //}
//	 //
//	 //void setTranslate(float& x, float& y, float& z)
//	 //{
//	 //	x = this->mat[12];
//	 //	y = this->mat[13];
//	 //	z = this->mat[14];
//	 //}

//	 //void setTranslate(V3& v3)
//	 //{
//	 //	v3.x = this->mat[3];
//	 //	v3.y = this->mat[7];
//	 //	v3.z = this->mat[11];
//	 //}

//	 //void translateX(const float& x)
//	 //{
//	 //	this->mat[12] += x;
//	 //}
//	 //
//	 //void translateY(const float& y)
//	 //{
//	 //	this->mat[13] += y;
//	 //}
//	 //
//	 //void translateZ(const float& z)
//	 //{
//	 //	this->mat[14] += z;
//	 //}

//	 //void Tr()
//	 //{
//	 //	/*this->mat[0] = 0;
//	 //	this->mat[1] = -1;
//	 //	this->mat[3] = 1;
//	 //	this->mat[4] = 1;
//	 //	this->mat[5] = 0;*/
//	 //	this->mat[3] = this->mat[0] * this->mat[3] + this->mat[1] * this->mat[7] + this->mat[2] * this->mat[11];
//	 //	this->mat[7] = this->mat[4] * this->mat[3] + this->mat[5] * this->mat[7] + this->mat[6] * this->mat[11];
//	 //	this->mat[11] = this->mat[8] * this->mat[3] + this->mat[9] * this->mat[7] + this->mat[10] * this->mat[11];
//	 //}

//	 // void look(V3 eye, V3 target, V3 up)
//	 // {
//	 //	 V3 xv3, yv3, zv3;

//	 //	 zv3.x = eye.x - target.x;
//	 //	 zv3.y = eye.y - target.y;
//	 //	 zv3.z = eye.z - target.z;
//	 //	 zv3.normalize();

//	 //	 xv3.cross(up, zv3);
//	 //	 xv3.normalize();

//	 //	 yv3.cross(zv3, xv3);

//	 //	 mat[0] = xv3.x;
//	 //	 mat[1] = yv3.x;
//	 //	 mat[2] = zv3.x;
//	 //	 mat[4] = xv3.y;
//	 //	 mat[5] = yv3.y;
//	 //	 mat[6] = zv3.y;
//	 //	 mat[8] = xv3.z;
//	 //	 mat[9] = yv3.z;
//	 //	 mat[10] = zv3.z;
//	 //	 mat[12] = -V3::dot(xv3, eye);
//	 //	 mat[13] = -V3::dot(yv3, eye);
//	 //	 mat[14] = -V3::dot(zv3, eye);
//	 // }

//	 //void projectOrthographic(const int& cwidth, const int& cheight)
//	 //{
//	 //	//Orthographic
//	 //
//	 //		float angle = 90;
//	 //		float min = 0.1F;
//	 //		float max = 100.0F;
//	 //
//	 //		float maxx = max(fabs(-1), fabs(1));
//	 //		float maxy = max(fabs(-1), fabs(1));
//	 //		float m = max(maxx, maxy);
//	 //		float r = m * (cwidth / (float)cheight), t = m;
//	 //		float l = -r, b = -t;
//	 //
//	 //		this->mat[0] = 2 / (r - l);
//	 //		this->mat[1] = 0;
//	 //		this->mat[2] = 0;
//	 //		this->mat[3] = 0;
//	 //
//	 //		this->mat[4] = 0;
//	 //		this->mat[5] = 2 / (t - b);
//	 //		this->mat[6] = 0;
//	 //		this->mat[7] = 0;
//	 //
//	 //		this->mat[8] = 0;
//	 //		this->mat[9] = 0;
//	 //		this->mat[10] = -2 / (max - min);
//	 //		this->mat[11] = 0;
//	 //
//	 //		this->mat[12] = -(r + l) / (r - l);
//	 //		this->mat[13] = -(t + b) / (t - b);
//	 //		this->mat[14] = -(max + min) / (max - min);
//	 //		this->mat[15] = 1;
//	 //}

//	 //void multVecM4x4(Vec4& src, Vec4& dst) const
//	 //{
//	 //	dst.setX(src.getX() * this->mat[0] + src.getY() * this->mat[4] + src.getZ() * this->mat[8] + this->mat[12]);
//	 //	dst.setY(src.getX() * this->mat[1] + src.getY() * this->mat[5] + src.getZ() * this->mat[9] + this->mat[13]);
//	 //	dst.setZ(src.getX() * this->mat[2] + src.getY() * this->mat[6] + src.getZ() * this->mat[10] + this->mat[14]);
//	 //	dst.setW(src.getX() * this->mat[3] + src.getY() * this->mat[7] + src.getZ() * this->mat[11] + this->mat[15]);
//	 //}

//	 //void inverse()
//	 //{
//	 //	int a, i, j;
//	 //	M4x4 out;
//	 //	V4 v, vec[3];
//	 //	float det = 0.0f;
//	 //
//	 //	det = this->getDeterminant();
//	 //
//	 //	if (!det) return;
//	 //
//	 //	for (i = 0; i < 4; i++)
//	 //	{
//	 //		for (j = 0; j < 4; j++)
//	 //		{
//	 //			if (j != i)
//	 //			{
//	 //				a = j;
//	 //
//	 //				if (j > i) a = a - 1;
//	 //
//	 //				vec[a].setX(this->mat[j][0]);
//	 //				vec[a].setY(this->mat[j][1]);
//	 //				vec[a].setZ(this->mat[j][2]);
//	 //				vec[a].setW(this->mat[j][3]);
//	 //			}
//	 //		}
//	 //
//	 //		v.cross(vec[0], vec[1], vec[2]);
//	 //
//	 //		out.mat[0][i] = pow(-1.0f, i) * v.getX() / det;
//	 //		out.mat[1][i] = pow(-1.0f, i) * v.getY() / det;
//	 //		out.mat[2][i] = pow(-1.0f, i) * v.getZ() / det;
//	 //		out.mat[3][i] = pow(-1.0f, i) * v.getW() / det;
//	 //	}
//	 //
//	 //	this->setM4x4(out);
//	 //}

//	 //void mult(V3& source, V3& out)
//	 //{
//	 //	out.x = source.getX() * this->mat[0] + source.getY() * this->mat[4] + source.getZ() * this->mat[8] + this->mat[12];
//	 //	out.y = source.getX() * this->mat[1] + source.getY() * this->mat[5] + source.getZ() * this->mat[9] + this->mat[13];
//	 //	out.z = source.getX() * this->mat[2] + source.getY() * this->mat[6] + source.getZ() * this->mat[10] + this->mat[14];
//	 //}

//	 //void setCameraPosition(const float& x, const float& y, const float& z)
//	 //{
//	 //	this->mat[0] = x;
//	 //	this->mat[1] = y;
//	 //	this->mat[2] = z;
//	 //}

//	 //void operator*=(const Vec4& vec4)
//	 //{
//	 //	M4x4 out;
//	 //
//	 //	for (int i = 0; i < 4; i++)
//	 //	{
//	 //		for (int j = 0; j < 4; j++)
//	 //		{
//	 //			out.mat[i][j] = this->mat[i][0] * vec4.getX() + this->mat[i][1] * vec4.getY() + this->mat[i][2] * vec4.getZ() + this->mat[i][3] * vec4.getW();
//	 //		}
//	 //	}
//	 //
//	 //	this->setM4x4(out);
//	 //}

//	 //float getDeterminant()
//	 //{
//	 //	V4 minor, v1, v2, v3;
//	 //	float det;
//	 //
//	 //	v1 = V4(this->mat[0], this->mat[4], this->mat[8], this->mat[12]);
//	 //	v2 = V4(this->mat[1], this->mat[5], this->mat[9], this->mat[13]);
//	 //	v3 = V4(this->mat[2], this->mat[6], this->mat[10], this->mat[14]);
//	 //
//	 //	minor.cross(v1, v2, v3);
//	 //
//	 //	det = -(this->mat[3] * minor.getX() + this->mat[7] * minor.getY() + this->mat[11] * minor.getZ() + this->mat[15] * minor.getW());
//	 //
//	 //	return det;
//	 //}
// };

#endif
