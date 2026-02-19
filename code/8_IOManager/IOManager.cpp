#include "IOManager.h"
#include <fstream>

// 读取文件到字符串buffer 并自动适应文件大小
bool IOManager::readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer) {
    std::ifstream file(filePath, std::ios::binary);
    if (file.fail()) {
        perror(filePath.c_str());
        return false;
    }
    
    // seek to the end
    file.seekg(0, std::ios::end);
    // get the file size (byte)
    int fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    fileSize -= file.tellg(); // 不考虑元信息大小

    buffer.resize(fileSize);
    file.read((char *)&(buffer[0]), fileSize);
    file.close();
    
    return true;
}