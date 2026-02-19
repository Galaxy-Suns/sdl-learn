#pragma once
#include <vector>
#include <string>
    
class IOManager
{
public:
    // 读取文件到字符串buffer 并自动适应文件大小
    static bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);
};