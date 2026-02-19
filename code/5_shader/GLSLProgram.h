#pragma once
#include <string>
#include <GL/glew.h>
    
class GLSLProgram {
public:
    GLSLProgram();
    ~GLSLProgram();

    // 编译着色器 为 OpenGL 可以使用的形式
    void compileShaders(const std::string &vertexShaderFilePath, 
                        const std::string &fragmentShaderFilePath);
    void addAttribute(const std::string &attributeName);
    // 链接着色器
    void linkShaders();
    GLuint getUniformLocation(const std::string &uniformName);
    void use();
    void unuse();
private:
    void compileShader(const std::string &fileFilePath, GLuint id);

    GLuint _programID;
    GLuint _vertexShaderID;
    GLuint _fragmentShaderID;
    // 当前要绑定的属性索引
    int _numAttributes;
};
