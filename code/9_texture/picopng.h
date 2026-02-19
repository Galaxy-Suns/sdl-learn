#pragma once
#include <vector>

// args: out RGBA vector; 宽度; 高度; 指向 PNG 文件缓冲区的指针; 大小; 是否要转换为RGBA 32 true 即可
extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);