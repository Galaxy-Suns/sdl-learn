#include "GLSLProgram.h"
#include "Errors.h"
#include <GL/glew.h>
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : _programID(0), _vertexShaderID(0), 
                             _fragmentShaderID(0), _numAttributes(0) {
    
}

GLSLProgram::~GLSLProgram() {

}

// 编译着色器 为 OpenGL 可以使用的形式
void GLSLProgram::compileShaders(const std::string &vertexShaderFilePath, 
                                 const std::string &fragmentShaderFilePath) {
    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    _programID = glCreateProgram();
    
    // 创建顶点着色器 并分配 ID
    _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (_vertexShaderID == 0) {
        fatalError("Vertex shader failed to be created!");
    }
    // 创建 片段着色器 并分配 ID
    _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (_fragmentShaderID == 0) {
        fatalError("Fragment shader failed to be created!");
    }

    compileShader(vertexShaderFilePath, _vertexShaderID);
    compileShader(fragmentShaderFilePath, _fragmentShaderID);

   

}

// 链接着色器
void GLSLProgram::linkShaders() {
    // Attach our shaders to our program
    glAttachShader(_programID, _vertexShaderID);
    glAttachShader(_programID, _fragmentShaderID);
    
    // Link our program
    glLinkProgram(_programID);
    
    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(_programID, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
    	GLint maxLength = 0;
    	glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);
    
    	// The maxLength includes the NULL character
    	std::vector<GLchar> errorLog(maxLength);
    	glGetProgramInfoLog(_programID, maxLength, &maxLength, &errorLog[0]);
    	
    	// We don't need the program anymore.
    	glDeleteProgram(_programID);
    	// Don't leak shaders either.
    	glDeleteShader(_vertexShaderID);
    	glDeleteShader(_fragmentShaderID);
    
    	std::printf("%s\n", &(errorLog[0]));
        fatalError("Shaders failed to link!");
    }
    
    // Always detach shaders after a successful link.
    glDetachShader(_programID, _vertexShaderID);
    glDetachShader(_programID, _fragmentShaderID);
    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);
    
}

// 指定 GLSL 中 属性名称 和 索引的关系 (按照添加顺序)
// 等同于 GLSL layout(location = N) in ...
void GLSLProgram::addAttribute(const std::string &attributeName) {
    glBindAttribLocation(_programID, _numAttributes++, attributeName.c_str());
}
    
GLuint GLSLProgram::getUniformLocation(const std::string &uniformName) {
    GLuint location = glGetUniformLocation(_programID, uniformName.c_str());
    if (location == GL_INVALID_INDEX) {
        fatalError("uniform" + uniformName + "not found in shader");
    }
    return location;
}

// 编译 着色器 
void GLSLProgram::compileShader(const std::string &shaderFilePath, GLuint id) { 
    // 读取着色器源文件
    std::ifstream File(shaderFilePath);
    if (File.fail()) {
        perror(shaderFilePath.c_str());
        fatalError("Failed to open " + shaderFilePath);
    }
    std::string fileContents = "";
    std::string line;
    while (std::getline(File, line)) {
        fileContents += line + "\n";
    }
    File.close();
    // 传入着色器的代码
    // args: 分配的着色器id; 字符串数量; 指向C字符串的指针其地址; 一个指针
    const char *contentsPtr = fileContents.c_str();
    glShaderSource(id, 1, &contentsPtr, nullptr);
    // 编译顶点着色器
    glCompileShader(id);
    // 对源代码错误检查
    GLint isCompiled = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
    	GLint maxLength = 0;
    	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
    
    	// The maxLength includes the NULL character
    	std::vector<GLchar> errorLog(maxLength);
    	glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
    
    	// Provide the infolog in whatever manor you deem best.
    	// Exit with failure.
    	glDeleteShader(id); // Don't leak the shader.

        std::printf("%s\n", &(errorLog[0]));
        fatalError("Shader" + shaderFilePath + " failed to compile!");
    } 
}

void GLSLProgram::use() {
    glUseProgram(_programID);
    for (int i = 0; i < _numAttributes; i++) {
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::unuse() {
    glUseProgram(0);
    for (int i = 0; i < _numAttributes; i++) {
        glDisableVertexAttribArray(i);
    }
}
