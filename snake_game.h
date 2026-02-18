#ifndef SNAKE_GAME_H  // 防止头文件重复包含（C++ 工程化必做）
#define SNAKE_GAME_H

#include <iostream>
#include <vector>
#include <conio.h>   // 用于检测键盘输入（_getch()函数）
#include <windows.h> // 用于控制控制台光标、延时等
#include <cstdlib>
#include <ctime>

// 定义方向枚举（限定蛇的移动方向）
enum Direction { UP, DOWN, LEFT, RIGHT };

// 定义坐标结构体（表示蛇身/食物的位置）
struct Point {
    int x;
    int y;
    Point(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}
};

// 游戏核心类（封装游戏数据和方法，面向对象思想）
class SnakeGame {
private:
    // 游戏参数
    const int WIDTH = 40;   // 游戏区域宽度
    const int HEIGHT = 20;  // 游戏区域高度
    Point food;             // 食物位置
    std::vector<Point> snake; // 蛇身（用vector存储多个坐标）
    Direction dir;          // 当前移动方向
    bool gameOver;          // 游戏是否结束
    int score;              // 得分

    // 私有方法（内部辅助函数）
    void GenerateFood();    // 随机生成食物位置
    void DrawGame();        // 绘制游戏界面
    void HandleInput();     // 处理键盘输入
    void MoveSnake();       // 移动蛇身
    void CheckCollision();  // 检测碰撞（边界/自身）

public:
    // 构造函数（初始化游戏）
    SnakeGame();
    // 启动游戏（对外暴露的核心方法）
    void StartGame();
};

#endif // SNAKE_GAME_H