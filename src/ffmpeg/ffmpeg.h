#ifndef NALI_FFMPEG_H
#define NALI_FFMPEG_H

void ffmpeg_read(const char *filename);
uint8_t* ffmpeg_png(uint32_t* width_ptr, uint32_t* height_ptr);
void ffmpeg_clean();

#endif