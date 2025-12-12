#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

extern char map[15][15]; // extern 表示变量在其他文件中定义
extern int cur;
extern int p1, p2, equal, total;
extern int movecnt;
extern char history[1000];
extern char result[100];
extern int ailevel;

// logic.c 中的函数：游戏核心规则
void startmap();//初始化棋盘 
bool checkmove(int x, int y);//检查落子是否符合标准，若符合就进行落子 
bool checkwin(int x, int y);//检查是否胜利 

// ui.c 中的函数：所有界面交互
void printmap();//打印棋盘 
void showscore();//计分板 
void pvp();//人人对战 
void pvc();//人机对战 
int setlevel();//AI难度的选择 
void ai1();//第一种难度 
void ai2();//第二种难度 
int aipos(int x, int y, char player);//第二种难度中AI的算法 

// file.c 中的函数：所有文件操作
void savefile();//保存文件 (txt)
void showresult();//读取文件并展示 
void saveCSV();
void showCSV();
void huifang();//对局回放 

// main.c 中的函数
void finish();//游戏是否结束的处理 
