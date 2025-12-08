#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 1. 声明全局变量（具体定义在 main.c 中）
extern char map[15][15]; // extern 表示变量在其他文件中定义
extern int cur;
extern int p1, p2, equal, total;
extern int movecnt;
extern char history[1000];
extern char result[100];
extern int ailevel;

// 2. 声明所有函数原型（按模块分组）

// logic.c 中的函数：游戏核心规则
void startmap();
bool checkmove(int x, int y);
bool checkwin(int x, int y);

// ui.c 中的函数：所有界面交互
void printmap();
void showscore();
void pvp();
void pvc();
int setlevel();
void ai1();
void ai2();
int aipos(int x, int y, char player);

// file.c 中的函数：所有文件操作
void savefile();
void showresult();
void saveCSV();
void showCSV();
void huifang();

// main.c 中的函数：程序流程控制
void finish();
