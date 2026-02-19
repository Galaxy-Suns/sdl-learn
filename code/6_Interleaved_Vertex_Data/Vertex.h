#pragma once
#include <GL/glew.h>
#include <cstddef>

struct Vertex {
    // 保持字节数是 4 的倍数 否则进行填充对齐
    struct Position {
        float x;
        float y;
    } position;
    struct Color {
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    } color;
};