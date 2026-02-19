#include "Errors.h"
#include <SDL.h>
#include <iostream>
#include <cstdlib>
    
// 显示 errorString 并退出程序 
void fatalError(std::string errorString) {
    std::cout << errorString << std::endl;
    std::cout << "Enter any key to quit...";
    std::cin.get();
    SDL_Quit();
    exit(69);
}