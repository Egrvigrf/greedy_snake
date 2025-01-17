#include<bits/stdc++.h>
#include <conio.h> //不是c++标准库 isn't stl 
using namespace std;
struct link_snk {
    int x, y;
    link_snk* next = nullptr, * pre = nullptr;
};
char head_image = '@',  body_image = '*', snk_dir;
const int speed = 100, rows = 20, cols = 40;
int fruit_x, fruit_y, snk_len = 2;
bool Mp[rows + 1][cols + 1];
bool fruit_is_exist = false, alive = true;
link_snk* snk_head, * snk_tail;
map<char, char> collide = { {'a','d'},{'d','a'},{'w','s'},{'s','w'} };
void print_x_y(int y, int x, char c) { cout << "\033[" << y << ";" << x << "H" << c; } // 移动到某个位置打印字符/字符串 cursor move to (x, y) to print char or string 
void print_x_y(int y, int x, string c) { cout << "\033[" << y << ";" << x << "H" << c; }
void Snap(int t) { chrono::milliseconds pauseTime(t); this_thread::sleep_for(pauseTime); } // 作用相当于sleep, 程序暂停执行一段时间 serve as sleep(), pause the program
void fruit_generate() {
    do {
        fruit_x = rand() % (rows - 2) + 2, fruit_y = rand() % (cols - 2) + 2;
    } while (Mp[fruit_x][fruit_y]); // 如果食物的生成位置被蛇占据，重新生成食物 regenerate food if the loaction is occupied by snake
    print_x_y(fruit_x, fruit_y, '.');
    fruit_is_exist = true;
}
void move() { 
    if (kbhit()) {
        char dir = getch(); // collide用于判断按的方向键与蛇的前进方向是否相反  avoid direction collision
        if ((dir == 'w' || dir == 'a' || dir == 's' || dir == 'd') && collide[dir] == snk_dir) 
            dir = collide[dir]; 
        snk_dir = dir;
    }
    map<char, pair<int, int>> mp = { {'w',{-1,0}},{'s',{1,0}},{'a',{0,-1}},{'d',{0,1}} };
    int newhead_x = snk_head->x + mp[snk_dir].first, newhead_y = snk_head->y + mp[snk_dir].second;
    if (Mp[newhead_x][newhead_y]) {  // 撞到墙或者身体，直接return   crash itselt or a wall, return directly
        alive = false;
        return;
    }
    print_x_y(newhead_x, newhead_y, head_image);// 根据方向新增头节点 add a new node(head) according to current direction
    Mp[newhead_x][newhead_y] = 1;
    print_x_y(snk_head->x, snk_head->y, body_image);
    link_snk* p = new link_snk;
    p->x = newhead_x, p->y = newhead_y;
    p->next = snk_head, p->pre = nullptr;
    snk_head->pre = p;
    snk_head = p;
    if (fruit_x == newhead_x and fruit_y == newhead_y) { // 新的蛇头碰到食物就不删除蛇尾 if new head encounter food, not delete tail 
        fruit_is_exist = false;
        snk_len++;
    } else { // 否则删除尾巴 otherwise delete its tail 
        print_x_y(snk_tail->x, snk_tail->y, ' ');
        Mp[snk_tail->x][snk_tail->y] = 0;
        snk_tail = snk_tail->pre;
        delete snk_tail->next;      
        snk_tail->next = nullptr;
    }
}
void game_init() {
    cout << "\x1b[2J\e[?25l"; //清屏并隐藏光标的转义序列 hide cursor
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 1; i <= cols; i++) { print_x_y(1, i, '#'), print_x_y(rows, i, '#'), Mp[rows][i] = Mp[1][i] = 1; } //画周围的墙 print walls
    for (int i = 2; i <= rows-1; i++) { print_x_y(i,1,'#'), print_x_y(i,cols,'#'), Mp[i][1] = Mp[i][cols] = 1; }
    snk_head = new link_snk; //随机生成蛇头位置 generate snake head with a random loacation
    snk_head->x = rand() % (rows - 4) + 3, snk_head->y = rand() % (cols - 4) + 3;
    print_x_y(snk_head->x, snk_head->y, head_image);
    snk_tail = new link_snk;
    int i = rand() % 4; // 根据随机生成的蛇头位置四个方向随机生成蛇尾 generate tail randomly arccording to head location
    int randxy[4][2] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0} };
    snk_tail->x = snk_head->x + randxy[i][0], snk_tail->y = snk_head->y + randxy[i][1]; 
    const char matchdir[4] = { 'd', 's', 'a', 'w' };
    snk_dir = matchdir[i];
    snk_head->next = snk_tail, snk_tail->pre = snk_head;
    print_x_y(snk_tail->x, snk_tail->y, body_image);
    Mp[snk_head->x][snk_head->y] = Mp[snk_tail->x][snk_tail->y] = 1;
    string brief = "Tap 'a' or 'w' or 'd' or 's' to start";
    print_x_y(rows+1, 1, brief);
    while (true) {
        if (kbhit()) {
            char dir = getch(); // 避免按的方向键与蛇的前进方向相反产生问题 avoid direction collision 
            if ((dir == 'w' || dir == 'a' || dir == 's' || dir == 'd') && collide[dir] != snk_dir) {
                snk_dir = dir;
                break;
            }
        }
        Snap(200);
    }
    print_x_y(rows + 1, 1,string(brief.size(),' '));
}

int main() { 
    game_init();
    while (alive) {
        if (!fruit_is_exist) fruit_generate();
        move();
        Snap(speed);
    }
    print_x_y(rows + 1, 1, "Game over! \n");
    cout << "length:" << snk_len << endl;
    return 0;
}





