#include "Sprite.h"
    
Sprite::Sprite() {
    _vboID = 0;
}

Sprite::~Sprite() {
    // 删除缓冲区
    if (_vboID != 0) {
        // args: buffer数量; id的指针 
        glDeleteBuffers(1, &_vboID);
    }
}

void Sprite::init(float x, float y, float width, float height) {
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    // 没有创建缓冲区 则创建
    if (_vboID == 0) {
        // args: 创建 buffer 数; 保存 id 的 指针; 
        glGenBuffers(1, &_vboID);
    }

    // 保存 6 个顶点 精灵是 正方形 由两个三角形组成
    float vertexData[12];
    // 坐标系 设 左下为原点
    // 三角形1
    // 右上
    vertexData[0] = x + width;
    vertexData[1] = y + height;
    // 左上
    vertexData[2] = x;
    vertexData[3] = y + height;
    // 左下
    vertexData[4] = x;
    vertexData[5] = y;
    // 三角形2
    // 右下
    vertexData[6] = x + width;
    vertexData[7] = y;
    // 右上
    vertexData[8] = x + width;
    vertexData[9] = y + height;
    // 左下
    vertexData[10] = x;
    vertexData[11] = y;

    // 告知 GL 哪个 buffer 激活
    // args: buffer的类型; ID
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    // 向缓冲区发送数据
    // args: buffer的类型; 字节数; buffer 开头的指针; 用法(指示绘制一次还是多次)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    // 解绑缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    // 属性数组中 只有 位置信息 0 代表索引 第一个 
    // 表示启用 属性索引0
    glEnableVertexAttribArray(0);

    // 告诉 OpenGL 从缓冲区的哪个位置绘制 
    // args: 使用的 属性索引 ; 每个顶点的元素数量; 数组类型; 规范化; 步幅; 有关交错顶点的指针
    // 这里的2 后续可以 通过 in vec2 读取到 
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    // 绘制 
    // args: 绘制的类型; 开始索引; 顶点个数
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
