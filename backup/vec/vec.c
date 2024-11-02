// // typedef struct
// // {
// //	 int *data;
// //	 size_t size;
// //	 size_t capacity;
// // } vector;

// // void vector_init(vector *vec, size_t initialCapacity)
// // {
// //	 vec->data = malloc(initialCapacity * sizeof(int));
// //	 vec->size = 0;
// //	 vec->capacity = initialCapacity;
// // }

// void vec_add_i(vec *vec, int value)
// {
//	 // if (vec->size == vec->capacity)
//	 // {
//	 //	 vec->capacity *= 2;
//	 //	 vec->data = realloc(vec->data, vec->capacity * sizeof(int));
//	 // }
//	 vec->data = realloc(vec->data, (vec->size + 1) * sizeof(int));
//	 int *data = (int *)vec->data;
//	 data[vec->size++] = value;
// }

// void vec_add_f(vec *vec, float value)
// {
//	 vec->data = realloc(vec->data, (vec->size + 1) * sizeof(float));
//	 float *data = (float *)vec->data;
//	 data[vec->size++] = value;
// }

// // int vector_get(vec *vec, size_t index)
// // {
// //	 // if (index < vec->size)
// //	 // {
// //	 int *data = (int *)vec->data;
// //	 return data[index];
// //	 // }
// //	 // return -1;
// // }

// // void vector_freeVector(vector *vec)
// // {
// //	 free(vec->data);
// //	 // vec->data = NULL;
// //	 // vec->size = 0;
// //	 // vec->capacity = 0;
// // }

// // int main()
// // {
// //	 vec vec =
// //	 {
// //		 .size = 0
// //	 };
// //	 vector_addF(&vec, 5.1f);
// //	 printf("size %zu\n", vec.size);
// //	 // int *data = (int *)vec.data;
// //	 float *data = (float *)vec.data;
// //	 printf("0 %f\n", data[0]);
// // }
