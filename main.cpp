#include "snake_game.h"

int main() {
    // 强制控制台编码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // 创建游戏对象并启动游戏
    SnakeGame game;
    std::cout << "=======================" << std::endl;
    std::cout << "    Snake Game Start!    " << std::endl;
    std::cout << "Press any key to start..." << std::endl;
    std::cout << "=======================" << std::endl;
    _getch(); // 等待用户按任意键开始
    game.StartGame(); // 启动游戏主循环

    system("pause");
    return 0;
}