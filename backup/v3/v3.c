// void vec_add_v3(vec *vec, v3 value)
// {
//	 vec->data = realloc(vec->data, (vec->size + 1) * sizeof(v3));
//	 v3 *data = (v3 *)vec->data;
//	 data[vec->size++] = value;
// }

// void v3_set(vec *vec_f, vec *vec_v3)
// {
//	 for (int i = 0; i < vec_f->size; i += 3)
//	 {
//		 float *data = vec_f->data;
//		 v3 v3 =
//		 {
//			 .x = data[i],
//			 .y = data[i + 1],
//			 .z = data[i + 2]
//		 };

//		 vec_add_v3(vec_v3, v3);
//	 }
// }

// void v3_plus(vec *vec_m3_d, vec *vec_m3_s)
// {
//	 M3 *m3 = vec_m3_d->data;
//	 vec_m3_d[0] += vec_m3_s[0];
//	 vec_m3_d[1] += vec_m3_s[1];
//	 vec_m3_d[2] += vec_m3_s[2];
// }
