#ifndef NALI_GRAPHICREADER_H
#define NALI_GRAPHICREADER_H

// void graphic_reader_repaste(char *char_ptr, char c_char, char r_char);
uint32_t graphic_reader_count(char *char_ptr, char c_char);
void graphic_reader_sanitize(char *char_ptr);
// void graphic_reader_switchBones(SourceDataType *sourcedatatype_ptr);
// void graphic_reader_switchAnimationBones(SourceDataType *sourcedatatype_ptr);
void graphic_reader_makeBones(SourceDataType *sourcedatatype_ptr);
void graphic_reader_compressVertex(SourceDataType *sourcedatatype_ptr);
// bool canPackNew(SourceDataType& sourcedatatype, int& x, int& y);
// bool canPack(SourceDataType& sourcedatatype, int& x, int& y, int& z);
void graphic_reader_fixAnimation(SourceDataType *sourcedatatype_ptr);
// void unPackIndex(SourceDataType& sourcedatatype);
// void unPackVisualBones(SourceDataType& sourcedatatype);
// void updateBones(SourceDataType& sourcedatatype);

#endif
