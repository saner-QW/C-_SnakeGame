#include "snake_game.h"  // 包含自定义头文件

// 构造函数：初始化游戏状态
SnakeGame::SnakeGame() {
    // 初始化随机数种子
    srand((unsigned int)time(NULL));
    // 初始化蛇身（初始3节，居中）
    snake.push_back(Point(WIDTH/2, HEIGHT/2));
    snake.push_back(Point(WIDTH/2 - 1, HEIGHT/2));
    snake.push_back(Point(WIDTH/2 - 2, HEIGHT/2));
    // 初始方向向右
    dir = RIGHT;
    gameOver = false;
    score = 0;
    // 生成第一个食物
    GenerateFood();

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

// 随机生成食物（避免生成在蛇身上）
void SnakeGame::GenerateFood() {
    while (true) {
        // 随机生成食物坐标（避开边界）
        food.x = rand() % (WIDTH - 2) + 1;
        food.y = rand() % (HEIGHT - 2) + 1;
        // 检查是否和蛇身重叠
        bool overlap = false;
        for (const auto& p : snake) {
            if (p.x == food.x && p.y == food.y) {
                overlap = true;
                break;
            }
        }
        if (!overlap) break; // 不重叠则退出循环
    }
}

// 绘制游戏界面
void SnakeGame::DrawGame() {
    // 清屏（Windows控制台）
    system("cls");

    // 绘制上边界
    for (int i = 0; i < WIDTH; i++) std::cout << "#";
    std::cout << std::endl;

    // 绘制游戏区域
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // 绘制左边界
            if (x == 0) std::cout << "#";
            
            // 绘制蛇头
            if (x == snake[0].x && y == snake[0].y) std::cout << "O";
            // 绘制蛇身
            else {
                bool isBody = false;
                for (size_t i = 1; i < snake.size(); i++) {
                    if (x == snake[i].x && y == snake[i].y) {
                        std::cout << "o";
                        isBody = true;
                        break;
                    }
                }
                // 绘制食物
                if (!isBody && x == food.x && y == food.y) std::cout << "*";
                // 空白区域
                else if (!isBody && x != WIDTH - 1) std::cout << " ";
            }

            // 绘制右边界
            if (x == WIDTH - 1) std::cout << "#";
        }
        std::cout << std::endl;
    }

    // 绘制下边界
    for (int i = 0; i < WIDTH; i++) std::cout << "#";
    std::cout << std::endl;

    // 显示得分和提示
    std::cout << "得分: " << score << std::endl;
    std::cout << "按 WASD 控制方向，按 X 退出游戏" << std::endl;
}

// 处理键盘输入（非阻塞，实时响应）
void SnakeGame::HandleInput() {
    if (_kbhit()) { // 检测是否有按键按下
        switch (_getch()) { // 获取按键（无需回车）
            case 'w': case 'W':
                if (dir != DOWN) dir = UP; // 防止反向移动
                break;
            case 's': case 'S':
                if (dir != UP) dir = DOWN;
                break;
            case 'a': case 'A':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd': case 'D':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'x': case 'X':
                gameOver = true; // 按X结束游戏
                break;
        }
    }
}

// 移动蛇身
void SnakeGame::MoveSnake() {
    // 1. 新增蛇头（根据方向）
    Point newHead = snake[0];
    switch (dir) {
        case UP: newHead.y--; break;
        case DOWN: newHead.y++; break;
        case LEFT: newHead.x--; break;
        case RIGHT: newHead.x++; break;
    }
    snake.insert(snake.begin(), newHead); // 插入到蛇身最前面

    // 2. 判断是否吃到食物
    if (newHead.x == food.x && newHead.y == food.y) {
        score += 10; // 得分+10
        GenerateFood(); // 重新生成食物（蛇身不缩短）
    } else {
        snake.pop_back(); // 没吃到食物，缩短蛇尾（模拟移动）
    }
}

// 检测碰撞（边界/自身）
void SnakeGame::CheckCollision() {
    // 1. 边界碰撞
    if (snake[0].x <= 0 || snake[0].x >= WIDTH - 1 ||
        snake[0].y <= 0 || snake[0].y >= HEIGHT - 1) {
        gameOver = true;
    }

    // 2. 自身碰撞
    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            gameOver = true;
            break;
        }
    }
}

// 启动游戏（主循环）
void SnakeGame::StartGame() {
    while (!gameOver) {
        DrawGame();    // 绘制界面
        HandleInput(); // 处理输入
        MoveSnake();   // 移动蛇身
        CheckCollision(); // 检测碰撞
        Sleep(200);    // 延时200ms（控制游戏速度）
    }

    // 游戏结束提示
    system("cls");
    std::cout << "=======================" << std::endl;
    std::cout << "      game over！       " << std::endl;
    std::cout << "      total scores: " << score << "      " << std::endl;
    std::cout << "=======================" << std::endl;
    system("pause");
}