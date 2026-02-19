#version 130

in vec2 vertexPosition;
// OpenGL 会将 传入 byte 转 float
in vec4 vertexColor;

// 确保两个阶段使用相同名称 可以进行传递
out vec4 fragmentColor;
out vec2 fragmentPosition;

void main() {
    gl_Position.xy = vertexPosition;
    // 深度 
    gl_Position.z = 0.0;
    // 归一化
    gl_Position.w = 1.0;

    fragmentPosition = vertexPosition;
    fragmentColor = vertexColor;
}
