#include "ImageLoader.h"
#include <vector>
#include "picopng.h"
#include "IOManager.h"
#include "Errors.h"

// 从指定目录加载 png 到 GLTexture
GLTexture ImageLoader::loadPNG(std::string filePath) {
    GLTexture texture{};

    std::vector<unsigned char> in;
    std::vector<unsigned char> out;
    unsigned long width, height;

    if (IOManager::readFileToBuffer(filePath, in) == false) {
        fatalError("Failed to load PNG file to buffer!");
        
    }
    
    int errorCode = decodePNG(out, width, height, &in[0], in.size());

    if (errorCode != 0) {
        fatalError("decodePNG failed with error" + std::to_string(errorCode));
    }

    // 分配一个 id
    glGenTextures(1, &(texture.id));

    // 使用这个 texture
    glBindTexture(GL_TEXTURE_2D, texture.id);

    // 实际加载 纹理
    // args: texture 类型; 地图级别; 内部格式; 宽; 高; 是否要边框围绕纹理; 
    //       读取像素数据的格式; 数组类型; 指向数组的指针
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 
                 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

    // 设置纹理参数 
    // args: texture 类型; 参数名称; 参数值 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    texture.width = width;
    texture.height = height;
    
    return texture;
}