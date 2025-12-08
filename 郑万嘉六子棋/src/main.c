#include "head.h" 
char map[15][15];
int cur = 1;
int p1 = 0, p2 = 0, equal = 0, total = 0;
int movecnt = 0;
char history[1000] = "";
char result[100] = "";
int ailevel = 1;
bool flag = 1; 

int main() {
    srand(time(NULL));
    int choice;
    startmap(); 
    while (flag) {
        printf("----------------欢迎使用六子棋------------------------\n");
        printf("-                 请选择模式                         -\n");
        printf("-                    1.人-人对战游戏                 -\n");
        printf("-                    2.人-机对战游戏                 -\n");
        printf("-                    3.查看历史记录                  -\n");
        printf("-                    4.查看CSV格式记录               -\n");
        printf("-                    5.对局回放                      -\n");
        printf("-                    0.退出游戏                      -\n");
        printf("------------------------------------------------------\n");
        printf("请输入：");
        scanf("%d", &choice);
        getchar(); // 吸收回车

       
        if (choice == 1) {
            pvp();
            finish();
        } else if (choice == 2) {
            ailevel = setlevel();
            pvc();
            finish();
        } else if (choice == 3) {
            showresult();
            finish();
        } else if (choice == 4) {
            showCSV();
            finish();
        } else if (choice == 5) {
            huifang();
            finish();
        } else if (choice == 0) {
            printf("感谢使用六子棋游戏，再见！\n");
            flag = 0;
        } else {
            printf("无效的输入，请重新输入\n");
        }
    }
    return 0;
}
void finish() {
    int f;
    printf("是否重新开始游戏：任意键（开始游戏）/0（退出游戏）：");
    scanf("%d", &f);
    if (f == 0)
        flag = 0;
    getchar(); // 吸收回车
}
