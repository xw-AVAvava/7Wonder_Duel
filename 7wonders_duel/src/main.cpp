#include "../include/game/Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    // 初始化随机数种子
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    try {
        Game game;
        game.startGame();
    } catch (const std::exception& e) {
        std::cerr << "游戏发生错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
