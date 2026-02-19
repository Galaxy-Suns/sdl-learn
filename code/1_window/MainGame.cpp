
#include "MainGame.h"
#include "Sprite.h"    
#include <iostream>
#include <string>

// 显示 errorString 并退出程序 
void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Enter any key to quit...";
    std::cin.get();
    SDL_Quit();
}

MainGame::MainGame() { 
    _window = nullptr;
    _screenWidth = 1024;
    _screenHeight = 768;
    _gameState = GameState::PLAY;
}

MainGame::~MainGame() {
}

void MainGame::run() {
    initSystems();

    // 从左下到中间的正方形 
    _sprite.init(-1.0f, -1.0f, 1.0f, 1.0f);
    
    gameLoop();
}

// 初始化各种系统
void MainGame::initSystems() {
    // 初始化SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    // 创建窗口
    _window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight,
                                SDL_WINDOW_OPENGL);
    if (_window == nullptr) {
        fatalError("SDL Window could not be created!");
    }
    // 初始化 GL 上下文
    SDL_GLContext glContex = SDL_GL_CreateContext(_window);
    if (glContex == nullptr) {
        fatalError("SDL_GL context could not be created!");
    }
    // 初始化 glew
    GLenum error = glewInit();
    if (error != GLEW_OK) {
        fatalError("Could not initalize glew!");
    }
    // 启用双缓冲区
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // 设置背景
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

// 处理输入
void MainGame::processInput() {
    SDL_Event evnt;
    while(SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                // std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
                break;
        }
    }
}
    
void MainGame::gameLoop() {
    while (_gameState != GameState::EXIT) {
        processInput();
        drawGame();
    }
}

// 绘制游戏画面
void MainGame::drawGame() {
    glClearDepth(1.0); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    

    _sprite.draw();

    SDL_GL_SwapWindow(_window);
}
