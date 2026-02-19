#pragma once
#include <SDL.h>
#include <GL/glew.h>
#include "Sprite.h"

enum class GameState {PLAY, EXIT};

class MainGame {
public:
    MainGame();
    ~MainGame();
    // 运行游戏 
    void run();
private:
    void initSystems();  // -- update    
    // 处理输入 
    void processInput();    
    // 主游戏循环 
    void gameLoop();        
    // 绘制
    void drawGame();    // -- new

    SDL_Window *_window;
    int _screenWidth; 
    int _screenHeight;
    // 指示游戏状态 
    GameState _gameState;  
    // test
    Sprite _sprite;
};  
