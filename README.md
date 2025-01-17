# greedy_snake
Implement a console-based Snake game in C++ with 170 lines of code, single-file, fully commented（also in English）, and featuring a custom doubly linked list,click in to see a gif display. 用170行代码实现控制台版贪吃蛇（C++）,单文件带详细注释，手写双向链表，点进来有演示动图。

![Display GIF](display.gif)  

# 介绍
用链表实现贪吃蛇，移动时新增一个头节点，同时删除一个尾节点；吃到食物时只在食物位置更新头节点。  

使用的一些技巧      
`kbhit()`：非stl，读取键盘输入,依赖头文件`#include <conio.h>`  

使用转义序列控制屏幕：    
在某处打印字符：`cout << "\033[" << y << ";" << x << "H" << c;`  
清屏：`cout << "\x1b[2J";`   
隐藏控制台光标：`cout << "\e[?25l";`  

# 历史
version1.0 :     
用类实现功能，单向链表    
--20231225     
version2.0 :   
不使用类，使用双向链表，删除了冗余功能和代码，把移动和判断的时间复杂度从O(n)优化到O(1)   
--20240706    

# Introduction
Implement the Snake game using a linked list. When the snake moves, a new head node is added while a tail node is deleted. When the snake eats food, only the head node is updated at the food position.

Some techniques used:
kbhit(): A non-STL function to read keyboard input, relying on the header file #include <conio.h>.

Control the screen using escape sequences:
Print a character at a specific position:
cout << "\033[" << y << ";" << x << "H" << c;
Clear screen:
cout << "\x1b[2J";
Hide the console cursor:
cout << "\e[?25l";

# History
version 1.0:
Implemented using classes and a singly linked list.
--20231225
version 2.0:
Replaced the class with a doubly linked list, removed redundant features and code, optimized the time complexity of movement and judgment from O(n) to O(1).
--20240706

