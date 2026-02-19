#pragma once
#include "GLTexture.h"
#include <string>

class ImageLoader {
public:
    // 从指定目录加载 png 到 GLTexture
    static GLTexture loadPNG(std::string filePath);   
};