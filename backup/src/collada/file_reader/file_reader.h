#ifndef NALI_FILEREADER_H
#define NALI_FILEREADER_H

char file_reader_match(FILE *file_p, const char *mchar_p[], const uint32_t size);
char **file_reader_char_p(FILE *file_p, const char *f_char_p, const char *e_char_p, char **char_p, uint32_t *size);
float *file_reader_float(FILE *file_p, const char *e_char_p, float *float_p, uint32_t *size);
int32_t *file_reader_int(FILE *file_p, const char *e_char_p, int32_t *int_p, uint32_t *size);
collada_Bone *file_reader_node(FILE *file_p, collada_Bone *collada_bone_p, uint32_t *size);

#endif
