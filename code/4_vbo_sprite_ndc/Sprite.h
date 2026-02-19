
#pragma once
#include <GL/glew.h>    

    
class Sprite {
public:
    Sprite();
    ~Sprite();
    // 设置位置等
    void init(float x, float y, float width, float height);

    // 绘制精灵图
    void draw();
private:
    float _x;
    float _y;
    float _width;
    float _height;
    // 保存 顶点缓冲区对象的 id 交由 OpenGL 管理 
    GLuint _vboID; // GLuint 保证为 32 位 unsigned int
};
