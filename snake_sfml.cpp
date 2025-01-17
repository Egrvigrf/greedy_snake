#include<bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
struct link_snk {
    int x, y;
    link_snk* next = nullptr, * pre = nullptr;
};
char snk_dir;
const int speed = 150, rows = 20, cols = 20;
int fruit_x, fruit_y, snk_len = 2;
bool Mp[rows + 1][cols + 1];
bool fruit_is_exist = false, alive = true;
link_snk* snk_head, * snk_tail;
map<char, char> collide = { {'a','d'},{'d','a'},{'w','s'},{'s','w'} };
const int gridSize = 40; // 单位方格大小
const int windowWidth = (cols+2)*gridSize;
const int windowHeight = (rows+2)*gridSize;
    // 使用 sf::Vector2u 创建 VideoMode
sf::RenderWindow window(sf::VideoMode(sf::Vector2u(windowWidth, windowHeight)), "greedysnake");
void print_x_y(int x, int y, char c) {
    sf::RectangleShape block(sf::Vector2f(gridSize, gridSize));
    if (x == fruit_x && y == fruit_y) {
        block.setFillColor(sf::Color::Blue); // 食物蓝色
    }
    else if ( x == 1 || y == 1 || y == cols || x == rows ) {
        block.setFillColor(sf::Color::White); // 墙壁白色
    }
    else if (x == snk_head->x && y == snk_head->y){
        block.setFillColor(sf::Color::Cyan); // 蛇头青色
    } else {
        block.setFillColor(sf::Color::Green); // 蛇身绿色
    }
    block.setPosition(sf::Vector2f((float)x*gridSize, (float)y*gridSize));
    window.draw(block);
}
void print() {
    window.clear();  // 清空当前帧的窗口内容
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            if (Mp[i][j]) {
                print_x_y(i, j, 'c');
            }
        }
    }
    window.display();
}
void Snap(int t) { chrono::milliseconds pauseTime(t); this_thread::sleep_for(pauseTime); } // 作用相当于sleep, 程序暂停执行一段时间 serve as sleep(), pause the program
void fruit_generate() {
    do {
        fruit_x = rand() % (rows - 2) + 2, fruit_y = rand() % (cols - 2) + 2;
    } while (Mp[fruit_x][fruit_y]); // 如果食物的生成位置被蛇占据，重新生成食物 regenerate food if the loaction is occupied by snake
    Mp[fruit_x][fruit_y] = 1;
    fruit_is_exist = true;
}
void move() {
    sf::Clock clock;  // 创建一个时钟对象
    // sf::Event event;
    char dir = snk_dir;
    std::optional<sf::Event> event; 
    // event = window.pollEvent();  // 获取事件
        while (clock.getElapsedTime().asSeconds() < speed / 1000.0) {
            const std::optional<sf::Event> event = window.pollEvent();
            // 检查是否关闭窗口
            // 处理键盘按下事件
            if (event->is<sf::Event::KeyPressed>()) {
                const auto& keyEvent = event->getIf<sf::Event::KeyPressed>();
                if (keyEvent) {
                    if (keyEvent->code == sf::Keyboard::Key::W) {
                        dir = 'w';  // 向上
                    } else if (keyEvent->code == sf::Keyboard::Key::A) {
                        dir = 'a';  // 向左
                    } else if (keyEvent->code == sf::Keyboard::Key::S) {
                        dir = 's';  // 向下
                    } else if (keyEvent->code == sf::Keyboard::Key::D) {
                        dir = 'd';  // 向右
                    }
                }
            }
        }

    if (!(collide[dir] == snk_dir)) {
        snk_dir = dir;
    }
    map<char, pair<int, int>> mp = { {'w',{0,-1}},{'s',{0,1}},{'a',{-1,0}},{'d',{1,0}} };
    int newhead_x = snk_head->x + mp[snk_dir].first, newhead_y = snk_head->y + mp[snk_dir].second;
    link_snk* p = new link_snk;
    p->x = newhead_x, p->y = newhead_y;
    p->next = snk_head, p->pre = nullptr;
    snk_head->pre = p;
    snk_head = p;
    if (fruit_x == newhead_x and fruit_y == newhead_y) { // 新的蛇头碰到食物就不删除蛇尾 if new head encounter food, not delete tail 
        fruit_is_exist = false;
        snk_len++;
    } else if (Mp[newhead_x][newhead_y]) {
        alive = false;
    }
    else {
        Mp[snk_tail->x][snk_tail->y] = 0;
        snk_tail = snk_tail->pre;
        delete snk_tail->next;
        snk_tail->next = nullptr;
    }
    Mp[newhead_x][newhead_y] = 1;
}
void game_init() {
    cout << "\x1b[2J\e[?25l"; //清屏并隐藏光标的转义序列 hide cursor
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 1; i <= rows; i++) {
        Mp[i][1] = Mp[i][cols] = 1;
    }
    for (int i = 2; i <= cols - 1; i++) {
        Mp[1][i] = Mp[rows][i] = 1;
    }
    snk_head = new link_snk; //随机生成蛇头位置 generate snake head with a random loacation
    snk_head->x = rand() % (rows - 4) + 5, snk_head->y = rand() % (cols - 4) + 5;
    snk_tail = new link_snk;
    int i = rand() % 4; // 根据随机生成的蛇头位置四个方向随机生成蛇尾 generate tail randomly arccording to head location
    int randxy[4][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };
    snk_tail->x = snk_head->x + randxy[i][0], snk_tail->y = snk_head->y + randxy[i][1];
    const char matchdir[4] = { 'd', 's', 'a', 'w' };
    snk_dir = matchdir[i];
    snk_head->next = snk_tail, snk_tail->pre = snk_head;
    Mp[snk_head->x][snk_head->y] = Mp[snk_tail->x][snk_tail->y] = 1;
    fruit_generate();
    print();
    Snap(1000);
}
int main() {
    game_init();

    while (alive) {
        if (!fruit_is_exist) fruit_generate();
        move();
        print();
    }
    cout << "Game over!\n length: " <<snk_len << endl;
    Snap(1000);
    window.close();
    return 0;
}





